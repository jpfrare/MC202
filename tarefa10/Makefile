CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm -g

.PHONY: all clean

all: corretor

corretor: cliente.o tabela_hash.o
	gcc cliente.o tabela_hash.o  $(LDFLAGS) -o corretor

cliente.o: cliente.c tabela_hash.h
	gcc $(CFLAGS) -c cliente.c 
	
tabela_hash.o: tabela_hash.c tabela_hash.h
	gcc $(CFLAGS) -c tabela_hash.c

clean:
	rm -f corretor
