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

#define MAXAUTO 5
#define MACCHINE 50

/* dati da proteggere */
int turnoCorsia; /* 1 o 2 */
int macchineSulPonte;
int macchineUscite;

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex;
pthread_cond_t   condSvegliaCorsia1;
pthread_cond_t	 condSvegliaCorsia2;


void *Macchina1(void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;
	int i = 0;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Macchina1(%" PRIiPTR ")",indice);

	DBGpthread_mutex_lock(&mutex,Plabel);
	/* se non e' il turno 1 o ci sono più di 5 macchine aspetto*/
	while(turnoCorsia != 1 || macchineSulPonte >= MAXAUTO) {
		DBGpthread_cond_wait(&condSvegliaCorsia1, &mutex, Plabel);
	}

	/* entra sul ponte */
	printf("%s entra sul ponte\n", Plabel);
	fflush(stdout);
	macchineSulPonte++;
	DBGpthread_mutex_unlock(&mutex, Plabel);
	
	/* percorre il ponte */
	sleep(1);

	/* esce dal ponte */
	printf("%s esce dal ponte\n", Plabel);
	fflush(stdout);

	DBGpthread_mutex_lock(&mutex,Plabel);
	macchineUscite++;
	/* se tutte le macchine sono uscite */
	if(macchineUscite == MAXAUTO) {
		macchineSulPonte = 0;
		macchineUscite = 0;
		/* sveglio altra corsia*/
		turnoCorsia = 2;
		for(i=0; i<MAXAUTO; i++) {
			DBGpthread_cond_signal(&condSvegliaCorsia2, Plabel);
		}
	}
	
	DBGpthread_mutex_unlock(&mutex, Plabel);

	pthread_exit(NULL); 
}

void *Macchina2(void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;
	int i = 0;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Macchina2(%" PRIiPTR ")",indice);

	DBGpthread_mutex_lock(&mutex,Plabel);
	/* se non e' il turno 2 o ci sono più di 5 macchine aspetto*/
	while(turnoCorsia != 2 || macchineSulPonte >= MAXAUTO) {
		DBGpthread_cond_wait(&condSvegliaCorsia2, &mutex, Plabel);
	}

	/* entra sul ponte */
	printf("%s entra sul ponte\n", Plabel);
	fflush(stdout);

	macchineSulPonte++;
	DBGpthread_mutex_unlock(&mutex, Plabel);
	
	/* percorre il ponte */
	sleep(1);

	/* esce dal ponte */
	printf("%s esce dal ponte\n", Plabel);
	fflush(stdout);

	DBGpthread_mutex_lock(&mutex,Plabel);
	macchineUscite++;
	/* se tutte le macchine sono uscite */
	if(macchineUscite == MAXAUTO) {
		macchineSulPonte = 0;
		macchineUscite = 0;
		/* sveglio altra corsia*/
		turnoCorsia = 1;
		for(i=0; i<MAXAUTO; i++) {
			DBGpthread_cond_signal(&condSvegliaCorsia1, Plabel);
		}
	}
	
	DBGpthread_mutex_unlock(&mutex, Plabel);

	pthread_exit(NULL); 
}

int main ( int argc, char* argv[] ) 
{ 
	pthread_t th; 
	int  rc;
	uintptr_t i=0;

	rc = pthread_mutex_init(&mutex, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	rc = pthread_cond_init(&condSvegliaCorsia1, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	rc = pthread_cond_init(&condSvegliaCorsia2, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	/* inizializzazione variabili globali */
	turnoCorsia=1;
	macchineSulPonte=0;
	macchineUscite=0;

	/* creazione PTHREAD delle Macchine1 */
	for(i=0;i<MACCHINE;i++) {
		rc=pthread_create(&th,NULL,Macchina1,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* creazione PTHREAD delle Macchine2 */
	for(i=0;i<MACCHINE;i++) {
		rc=pthread_create(&th,NULL,Macchina2,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}
	
	pthread_exit(NULL);
	return(0); 
} 
  
