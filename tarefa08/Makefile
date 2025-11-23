CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm -g

.PHONY: all clean

all: cidades

cidades: cliente.o arvores_quartenarias.o
	gcc cliente.o arvores_quartenarias.o  $(LDFLAGS) -o cidades

cliente.o: cliente.c arvores_quartenarias.h
	gcc $(CFLAGS) -c cliente.c 

arvores_quartenarias.o: arvores_quartenarias.c arvores_quartenarias.h
	gcc $(CFLAGS) -c arvores_quartenarias.c

clean:
	rm -f cidades
