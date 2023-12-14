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

#define THREADS 5
#define MAX_CONIGLI_TANA 2

/* dati da proteggere */
int conigliNellaTana=0; 
int tanaLibera=1;

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;
pthread_cond_t   condTana;
pthread_cond_t   condPartner;

void *Coniglio (void *arg);

void crea_coniglio(intptr_t i) {
	pthread_t th;
	int rc = pthread_create(&th,NULL,Coniglio,(void*)i); 
	if(rc) PrintERROR_andExit(rc,"pthread_create failed");
}

void *Coniglio (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;
	intptr_t indiceFiglio;

	indice=(intptr_t)arg;
	indiceFiglio = (intptr_t)( (int)indice + 1 );
	sprintf(Plabel,"Coniglio%" PRIiPTR "",indice);

	DBGpthread_mutex_lock(&mutex,Plabel);

	while(!tanaLibera) {
		DBGpthread_cond_wait(&condTana, &mutex, Plabel);
	}

	/* entra nella tana */
	conigliNellaTana++;

	printf("%s entra nella tana\n", Plabel);
	fflush(stdout);

	/* verifico se c'è un'altro coniglio nella tana */
	if(conigliNellaTana < MAX_CONIGLI_TANA) {
		/* sveglio un'altro coniglio in attesa fuori dalla tana*/
		DBGpthread_cond_signal(&condTana, Plabel);
		/* aspetto che il coniglio svegliato entri */
		DBGpthread_cond_wait(&condPartner, &mutex, Plabel);
	} else {
		/* sveglio il coniglio in attesa dentro la tana */
		DBGpthread_cond_broadcast(&condPartner, Plabel);
		tanaLibera = 0;
	}
	DBGpthread_mutex_unlock(&mutex,Plabel);

	/* si riproduce */
	printf("%s si riproduce\n", Plabel);
	fflush(stdout);
	sleep(2);

	/* esce dalla tana */
	DBGpthread_mutex_lock(&mutex, Plabel);
	conigliNellaTana--;
	/* tana libera */
	if(conigliNellaTana == 0) {
		tanaLibera=1;
	}
	DBGpthread_cond_signal(&condTana, Plabel);
	DBGpthread_mutex_unlock(&mutex, Plabel);

	printf("%s esce dalla tana\n", Plabel);
	fflush(stdout);
	
	crea_coniglio(indiceFiglio);

	pthread_exit(NULL); 
}

int main ( int argc, char* argv[] ) 
{ 
	int  rc;
	uintptr_t i=0;

	rc = pthread_mutex_init(&mutex, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	rc = pthread_cond_init(&condTana, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	
	rc = pthread_cond_init(&condPartner, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	/* INIZIALIZZATE VOSTRE VARIABILI CONDIVISE e tutto quel che serve - fate voi */
	conigliNellaTana=0;

	/* CREAZIONE PTHREAD dei tiratori */
	for(i=0;i<THREADS;i++) {
		crea_coniglio(i);
	}

	pthread_exit(NULL);
	return(0); 
} 
  
