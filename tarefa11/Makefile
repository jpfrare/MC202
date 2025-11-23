CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm -g

.PHONY: all clean

all: piscapisca

piscapisca: cliente.o grafo.o
	gcc cliente.o grafo.o  $(LDFLAGS) -o piscapisca

cliente.o: cliente.c grafo.h
	gcc $(CFLAGS) -c cliente.c 
	
grafo.o: grafo.c grafo.h
	gcc $(CFLAGS) -c grafo.c

clean:
	rm -f piscapisca
