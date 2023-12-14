CFLAGS=-ansi -Wpedantic -Wall

all: main.exe

main.exe: main.o quadrato.o dimezza.o
	gcc ${CLFAGS} -o main.exe main.o quadrato.o dimezza.o -lm

main.o: main.c quadrato.h dimezza.h
	gcc -c ${CFLAGS} -o main.o main.c

quadrato.o: quadrato.c quadrato.h
	gcc -c ${CFLAGS} -o quadrato.o quadrato.c

dimezza.o: dimezza.c dimezza.h
	gcc -c ${CFLAGS} -o dimezza.o dimezza.c

.PHONY: clean

clean:
	-rm -f *.exe *.o


