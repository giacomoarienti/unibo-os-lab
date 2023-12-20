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

#define ALIENI 5
#define MAXALIENI 2

/* dati da proteggere */
int alieniInCasa;
int alieniFuoriCasa;

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;
pthread_cond_t   condEntra;
pthread_cond_t	 condEsci;

void *Alieno(void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;
	pthread_t th; 
	int  rc;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Alieno%" PRIiPTR "",indice);

	/* alieno attende fuori casa */
	DBGpthread_mutex_lock(&mutex, Plabel);
	alieniFuoriCasa++;

	/* se ci sono due alieni in casa aspetto fuori */
	while(alieniInCasa >= MAXALIENI) {
		DBGpthread_cond_wait(&condEntra, &mutex, Plabel);
	}

	/* entro in casa */
	alieniFuoriCasa--;
	alieniInCasa++;
	printf("%s entra in casa\n", Plabel);
	fflush(stdout);

	/* se sono l'unico alieno in casa */
	if(alieniInCasa == 1) {
		/* fa entrare un alieno */
		DBGpthread_cond_signal(&condEntra, Plabel);
	} else {
		/* sveglio l'alieno che può uscire*/
		DBGpthread_cond_signal(&condEsci, Plabel);
	}
	/* aspetto di poter uscire */
	DBGpthread_cond_wait(&condEsci, &mutex, Plabel);

	/* esco dalla casa */
	printf("%s esce di casa\n", Plabel);
	fflush(stdout);
	alieniInCasa--;

	/* faccio entrare un'altro alieno */
	DBGpthread_cond_signal(&condEntra, Plabel);
	DBGpthread_mutex_unlock(&mutex, Plabel);

	/* se numero di alieni furoi casa < 3 crea alieni */
	if(alieniFuoriCasa < 3) {
		rc=pthread_create(&th,NULL,Alieno,(void*)indice); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
		rc=pthread_create(&th,NULL,Alieno,(void*)indice); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* muore */
	pthread_exit(NULL); 
}

int main ( int argc, char* argv[] ) 
{ 
	pthread_t th; 
	int  rc;
	uintptr_t i=0;

	rc = pthread_mutex_init(&mutex, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	rc = pthread_cond_init(&condEntra, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	rc = pthread_cond_init(&condEsci, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	/* inizializzazione variabili globali */
	alieniInCasa=0;
	alieniFuoriCasa=0;

	/* creazione PTHREAD degli Alieni */
	for(i=0;i<ALIENI;i++) {
		rc=pthread_create(&th,NULL,Alieno,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}
	
	pthread_exit(NULL);
	return(0); 
} 
  
