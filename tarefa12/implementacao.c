#include "grafo.h"
#include "fila_prioridade.h"
#include "implementacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int * dijkstra (struct grafo * grafo, int origem) {
    int * distancias = malloc(grafo->numero_cidades * sizeof(int));

    struct heap * heap = cria_heap(grafo->numero_cidades, distancias);

    distancias[origem] = 0;
    diminui_prioridade(heap, 0, origem);

    while(heap->ponta != 0) {

        struct item pai = tira_minimo(heap);
        if (pai.prioridade != infinita) {

            for (struct no_grafo * filho = grafo->lista_adj[pai.id]; filho != NULL; filho = filho->proximo) {

                if (pai.prioridade + filho->peso < heap(heap->posicoes[filho->id]).prioridade) {

                    diminui_prioridade(heap, pai.prioridade + filho->peso, filho->id);
                    distancias[filho->id] = heap(heap->posicoes[filho->id]).prioridade;
                }
            }
        }

    }
    free(heap->fila);
    free(heap->posicoes);
    free(heap);
    return distancias;
}

int maior_menor_distancia(struct grafo * grafo, int centro1, int centro2) {
    int maior_menor_distancia = 0;

    int * distancias1 = dijkstra(grafo, centro1);
    int * distancias2 = dijkstra(grafo, centro2);

    for (int i = 0; i < grafo->numero_cidades; i++) { //procura a menor distancia entre ambos os centros e a cidade de id i
        int menor_distancia = distancias1[i];

        if (distancias1[i] > distancias2[i])  menor_distancia = distancias2[i];
        if (menor_distancia > maior_menor_distancia) maior_menor_distancia = menor_distancia; //atualiza a maior distância geral
    }

    free(distancias1);
    free(distancias2);
    return maior_menor_distancia;
}

void melhor_cenario (struct grafo * grafo) {
    int menor_distancia = infinita;
    int id1, id2;
    int soma_habitantes;

    int distancia;
    for (int i = 0; i <= grafo->numero_cidades; i++) { //testa todas as combinações possíveis de cidade
        for (int j = i + 1; j < grafo->numero_cidades; j++) {
            distancia = maior_menor_distancia(grafo, i, j);

            if (distancia < menor_distancia)  {
                menor_distancia = distancia;
                soma_habitantes = grafo->id_cidades[i].numero_habitantes + grafo->id_cidades[j].numero_habitantes;
                
                if (i < j) { //garantindo ordem alfabetica
                    id1 = i;
                    id2 = j;
                } else {
                    id1 = j;
                    id2 = i;
                }

            } else if (distancia == menor_distancia) { //criterio de desempate
                if (grafo->id_cidades[i].numero_habitantes + grafo->id_cidades[j].numero_habitantes > soma_habitantes) {
                    soma_habitantes = grafo->id_cidades[i].numero_habitantes + grafo->id_cidades[j].numero_habitantes;

                    if (i < j) {
                        id1 = i;
                        id2 = j;

                    } else {
                        id1 = j;
                        id2 = i;
                    }
                }
            }

        }
    }
    //impressão da resposta
    printf("Centros de distribuicao: %s e %s\n", grafo->id_cidades[id1].nome, grafo->id_cidades[id2].nome);
    printf("Distancia de atendimento: %d\n", menor_distancia);
}