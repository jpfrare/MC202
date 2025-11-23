CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm -g

.PHONY: all clean

all: centros

centros: cliente.o implementacao.o grafo.o fila_prioridade.o
	gcc cliente.o implementacao.o grafo.o fila_prioridade.o $(LDFLAGS) -o centros

cliente.o: cliente.c
	gcc $(CFLAGS) -c cliente.c 
	
implementacao.o: implementacao.c
	gcc $(CFLAGS) -c implementacao.c

grafo.o: grafo.c
	gcc $(CFLAGS) -c grafo.c

fila_prioridade.o: fila_prioridade.c
	gcc $(CFLAGS) -c fila_prioridade.c
	
clean:
	rm -f centros
