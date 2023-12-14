CFLAGS=-ansi -Wall -Wpedantic -Werror

all: casuale.exe

casuale.exe: casuale.o
	gcc ${CFLAGS} -o casuale.exe casuale.o

casuale.o: casuale.c 
	gcc -c ${CFLAGS} -o casuale.o casuale.c

.PHONY: clean

clean:
	-rm -f *.o *.exe

