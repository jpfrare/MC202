CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm -g

.PHONY: all clean

all: cache

cache: cliente.o fila_prioridade.o
	gcc cliente.o fila_prioridade.o  $(LDFLAGS) -o cache

cliente.o: cliente.c fila_prioridade.h
	gcc $(CFLAGS) -c cliente.c 

fila_prioridade.o: fila_prioridade.c fila_prioridade.h
	gcc $(CFLAGS) -c fila_prioridade.c

clean:
	rm -f cache
