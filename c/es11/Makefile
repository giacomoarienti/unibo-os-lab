CFLAGS=-ansi -Wall -Wpedantic -Werror

all: dammi_il_precedente.exe

dammi_il_precedente.exe: dammi_il_precedente.o
	gcc ${CFLAGS} -o dammi_il_prececedente.exe dammi_il_precdente.o

dammi_il_precedente.o: dammi_il_precedente.c
	gcc -c ${CFLAGS} -o dammi_il_precdente.o dammi_il_precedente.c

.PHONY: clean

clean: 
	-rm -f *.o *.exe
