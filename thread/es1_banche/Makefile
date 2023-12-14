CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread
DBGPTHREADFUNCTION_SOURCE_DIR=./

all: 	 es1_banche.exe

es1_banche.exe:  es1_banche.o 
	gcc -o es1_banche.exe es1_banche.o ${LIBRARIES}

es1_banche.o: es1_banche.c ${DBGPTHREADFUNCTION_SOURCE_DIR}printerror.h
	gcc -c ${CFLAGS} -I${DBGPTHREADFUNCTION_SOURCE_DIR} es1_banche.c


.PHONY:	clean

clean:
	-rm -f es1_banche.o  es1_banche.exe