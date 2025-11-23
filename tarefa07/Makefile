CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: otimizar

otimizar: cliente.o arvore.o
	gcc cliente.o arvore.o -g -lm -o otimizar

cliente.o: cliente.c arvore.h
	gcc $(CFLAGS) -c cliente.c

arvore.o: arvore.c arvore.h
	gcc $(CFLAGS) -c arvore.c

clean:
	rm -f otimizar
