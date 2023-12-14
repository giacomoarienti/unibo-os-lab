CFLAGS=-ansi -Wall -Wpedantic

all: main.exe

main.exe: main.o
	gcc ${CFLAGS} -o main.exe main.o

main.o: main.c macro.h
	gcc -c ${CFLAGS} -o main.o main.c

.PHONY: clean

clean:
	-rm -f *.o *.exe


