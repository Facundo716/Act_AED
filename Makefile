CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

simulador: main.o artemis.o validaciones.o
	$(CC) $(CFLAGS) -o simulador main.o artemis.o validaciones.o $(LDFLAGS)

main.o: main.c artemis.h validaciones.h
	$(CC) $(CFLAGS) -c main.c

artemis.o: artemis.c artemis.h
	$(CC) $(CFLAGS) -c artemis.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

clean:
	rm -f *.o simulador simulador.exe
