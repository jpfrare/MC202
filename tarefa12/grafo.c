#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cria_no_grafo (struct grafo * grafo, int id_ligacao, int peso, int id_cidade) {
    struct no_grafo * ligacao = malloc(sizeof(struct no_grafo));

    ligacao->id = id_ligacao;
    ligacao->peso = peso;
    ligacao->proximo = grafo->lista_adj[id_cidade];
    grafo->lista_adj[id_cidade] = ligacao;
}

void busca_id (struct grafo * grafo, int * id1, int * id2) {
    char cidade1[max_len];
    char cidade2[max_len];

    scanf("%s %s", cidade1, cidade2);

    for (int j = 0; *id1 == -1 || *id2 == -1; j++) { 

        if (strcmp(grafo->id_cidades[j].nome, cidade1) == 0) {
            *id1 = j;

        } else if (strcmp(grafo->id_cidades[j].nome, cidade2) == 0) {
            *id2 = j;
        }
    }
}

struct grafo * cria_e_preenche_grafo() {
    struct grafo * grafo = malloc(sizeof(struct grafo));

    scanf("%d", &grafo->numero_cidades);
    grafo->id_cidades = malloc(grafo->numero_cidades * sizeof(struct cidade));
    grafo->lista_adj = calloc(grafo->numero_cidades, sizeof(struct no_grafo *));

    for (int i = 0; i < grafo->numero_cidades; i++) { //fazendo cada cidade receber um id, por ordem de inserção
        struct cidade cidade;
        scanf("%s %d", cidade.nome, &cidade.numero_habitantes);
        
        grafo->id_cidades[i] = cidade;
    }

    int numero_conexoes;
    scanf("%d", &numero_conexoes);

    for (int i = 0; i < numero_conexoes; i++) {
        int id1 = -1, id2 = -1;
        int peso;

        //procurando os ids das respectivas cidades
        busca_id(grafo, &id1, &id2);

        scanf(" %d", &peso);

        //coloca as ligaçoes no grafo
        cria_no_grafo(grafo, id2, peso, id1);

        cria_no_grafo(grafo, id1, peso, id2);
    }

    return grafo;
}

void libera_fila (struct no_grafo * fila) {
    if (fila != NULL) {
        libera_fila(fila->proximo);
        free(fila);
    }
}

void libera_grafo (struct grafo * grafo) {
    free(grafo->id_cidades);

    for (int i = 0; i < grafo->numero_cidades; i++) {
        libera_fila(grafo->lista_adj[i]);
    }

    free(grafo->lista_adj);
    free(grafo);
}
