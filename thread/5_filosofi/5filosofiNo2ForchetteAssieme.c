/* file:  5filosofiNo2ForchetteAssieme.c  */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* uint64_t */
#include <sys/time.h>	/* gettimeofday()    struct timeval */
#include <pthread.h> 
#include "printerror.h"
#include "DBGpthread.h"

#define NUMFILOSOFI 5

/* variabili da proteggere */
/* la forchetta a sinistra di un filosofo
   ha lo stesso indice del filosofo.
	 */
/* int forchettaoccupata[NUMFILOSOFI]; */

/* variabili per la sincronizzazione */
pthread_mutex_t	 mutexForchetta[NUMFILOSOFI]; 

/* gli indici  dei filosofi crescono in senso orario, da 0 a NUMFILOSOFI-1 
*/

int indiceasinistra ( int indice) {
	return indice;
}

int indiceadestra ( int indice) {
	return (indice+1)%NUMFILOSOFI;
}

void *filosofo (void *arg) 
{ 
	char Flabel[128];
	int indice;

	indice=*((int*)arg);
	free(arg);
	sprintf(Flabel,"F%d",indice);

	
	while(1) {
		int indiceforchetta1;
		int indiceforchetta2;
		printf("filosofo %s sta pensando \n", Flabel ); 
		fflush(stdout);
		/* il filosofo pensa per 1/2 di sec piu o meno */
		DBGnanosleep( 500000000+indice*1000000, Flabel );

		/* il filosofo prende le due forchette NON IN MANIERA ATOMICA */
		/* AGGIUNGERE CODICE */
		/* il primo filosofo prende per prima la forchetta di destra */
		if(indice == 0) {
			indiceforchetta1=indiceadestra(indice);
			indiceforchetta2=indiceasinistra(indice);
		} else {
			/* gli altri quelli di sinistra */
			indiceforchetta1=indiceasinistra(indice);
			indiceforchetta2=indiceadestra(indice);
		}
		DBGpthread_mutex_lock(&mutexForchetta[indiceforchetta1], Flabel);
		DBGpthread_mutex_lock(&mutexForchetta[indiceforchetta2], Flabel);


		/* FINE AGGIUNTA CODICE */

		/*  FILOSOFO MANGIA */
		printf("filosofo %s MANGIA \n", Flabel ); 
		fflush(stdout);
		/* il filosofo mangia per circa 11 sec */
		DBGnanosleep( 11000000000+indice*1000000, Flabel );
		printf("filosofo %s FINISCE DI MANGIARE \n", Flabel ); 
		fflush(stdout);

		/* il filosofo rilascia le forchette */
		/* AGGIUNGERE CODICE */
		DBGpthread_mutex_unlock(&mutexForchetta[indiceforchetta1], Flabel);
		DBGpthread_mutex_unlock(&mutexForchetta[indiceforchetta2], Flabel);


		/* FINE AGGIUNTA CODICE */

	}
	pthread_exit(NULL); 
} 

int main (int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc, i, *intptr;

	for(i=0;i<NUMFILOSOFI;i++) {
		rc = pthread_mutex_init( &mutexForchetta[i], NULL); 
		if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");
	}

	for(i=0;i<NUMFILOSOFI;i++) {
		intptr=malloc(sizeof(int));
		if( !intptr ) { printf("malloc failed\n");exit(1); }
		*intptr=i;
		rc=pthread_create( &th,NULL,filosofo,(void*)intptr); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 

	return(0); 
} 
  
  
  
