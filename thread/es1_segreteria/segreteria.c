/* file:  piattello.c */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

/* la   #define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE     /* per random e srandom */
#endif


/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>     /* random  srandom */
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>     /* uint64_t intptr_t */
#include <inttypes.h>   /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define STUDENTI 50
#define MODULI 5

/* dati da proteggere */
int moduliDisponibili;

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;
pthread_cond_t   condSvegliaSegretaria;
pthread_cond_t	 condSvegliaStudenti;


void *Studente (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Studente%" PRIiPTR "",indice);

	DBGpthread_mutex_lock(&mutex,Plabel);
	/* se non ci sono moduli aspetto la segretaria*/
	while(moduliDisponibili <= 0) {
		printf("%s aspetta segretaria\n", Plabel);
		fflush(stdout);
		DBGpthread_cond_wait(&condSvegliaStudenti, &mutex, Plabel);
	}

	/* prende modulo ed esce */
	printf("%s prende modulo\n", Plabel);
	fflush(stdout);
	moduliDisponibili--;

	/* se i moduli sono finiti sveglio la segretaria*/
	if(moduliDisponibili <= 0) {
		printf("%s sveglia segretaria\n", Plabel);
		fflush(stdout);
		DBGpthread_cond_signal(&condSvegliaSegretaria, Plabel);
	}
	
	DBGpthread_mutex_unlock(&mutex, Plabel);

	pthread_exit(NULL); 
}


void *Segretaria (void *arg) 
{ 
	char Plabel[] = "Segretaria";
	int i = 0;

	DBGpthread_mutex_lock(&mutex,Plabel);

	while(1) {
		/* la segretaria attende di essere svegliata dagli studenti */
		while(moduliDisponibili > 0) {
			printf("%s aspetta studenti\n", Plabel);
			fflush(stdout);
			DBGpthread_cond_wait(&condSvegliaSegretaria, &mutex, Plabel);
		}

		/* produce moduli */
		printf("%s produce moduli\n", Plabel);
		fflush(stdout);
		sleep(5);
		moduliDisponibili = MODULI;

		/* sveglia studenti */
		printf("%s sveglia studenti\n", Plabel);
		fflush(stdout);
		for(i = 0; i < MODULI; i++) {
			DBGpthread_cond_signal(&condSvegliaStudenti, Plabel);
		}
	}

	pthread_exit(NULL); 
}


int main ( int argc, char* argv[] ) 
{ 
	pthread_t th; 
	int  rc;
	uintptr_t i=0;

	rc = pthread_mutex_init(&mutex, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	rc = pthread_cond_init(&condSvegliaSegretaria, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	rc = pthread_cond_init(&condSvegliaStudenti, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	/* inizializzazione variabili globali */
	moduliDisponibili=MODULI;

	/* creazione PTHREAD degli Studenti */
	for(i=0;i<STUDENTI;i++) {
		rc=pthread_create(&th,NULL,Studente,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* creazione PTHREAD della Segretaria */
	rc=pthread_create(&th,NULL,Segretaria, NULL);
	if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	
	pthread_exit(NULL);
	return(0); 
} 
  
