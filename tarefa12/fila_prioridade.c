#include "fila_prioridade.h"
#include <stdlib.h>

void troca (struct item * item1, struct item * item2) {
    struct item temporario = (*item1);
    
    (*item1) = (*item2);
    (*item2) = temporario;
}

void sobe_no_heap (struct heap * heap, int posicao_no_heap) {
    if (posicao_no_heap > 0 && heap(posicao_no_heap).prioridade < heap(pai(posicao_no_heap)).prioridade) {

       heap->posicoes[heap(posicao_no_heap).id] = pai(posicao_no_heap);
       heap->posicoes[heap(pai(posicao_no_heap)).id] = posicao_no_heap;

       troca(&heap(posicao_no_heap), &heap(pai(posicao_no_heap))); 
       sobe_no_heap(heap, pai(posicao_no_heap));
    }
}

void desce_no_heap (struct heap * heap, int posicao_no_heap) {
    int pos_menor_filho;

    if (f_esq(posicao_no_heap) < heap->ponta) {
        pos_menor_filho = f_esq(posicao_no_heap);

        if (f_dir(posicao_no_heap) < heap->ponta && heap(f_esq(posicao_no_heap)).prioridade > heap(f_dir(posicao_no_heap)).prioridade) {
            pos_menor_filho = f_dir(posicao_no_heap);
        }

        if(heap(pos_menor_filho).prioridade < heap(posicao_no_heap).prioridade) {
            heap->posicoes[heap(pos_menor_filho).id] = posicao_no_heap;
            heap->posicoes[heap(posicao_no_heap).id] = pos_menor_filho;

            troca(&heap(posicao_no_heap), &heap(pos_menor_filho));
            desce_no_heap(heap, pos_menor_filho);
        }
    }
}

struct item tira_minimo (struct heap * heap) {
    struct item retorno = heap(0);
    heap->ponta--;

    heap->posicoes[heap(0).id] = heap->ponta;
    troca(&heap(0), &heap(heap->ponta));
    heap->posicoes[heap(0).id] = 0;
    desce_no_heap(heap, 0);

    return retorno;
}

void diminui_prioridade (struct heap * heap, int nova_prioridade, int id) {
    heap(heap->posicoes[id]).prioridade = nova_prioridade;
    sobe_no_heap(heap, heap->posicoes[id]);
}

void insere_no_heap (struct heap * heap, struct item item) {
    if (heap->ponta < heap->tamanho) {
        heap(heap->ponta) =  item;
        heap->posicoes[item.id] = heap->ponta;
        
        sobe_no_heap(heap, heap->ponta);

        heap->ponta++;
    
    } else {
        tira_minimo(heap);
        insere_no_heap(heap, item);
    }
}

struct heap * cria_heap (int numero_cidades, int * distancias) {
    struct heap * heap = malloc(sizeof (struct heap));
    heap->fila = malloc(numero_cidades * sizeof(struct item));
    heap->posicoes = malloc(numero_cidades * sizeof(int));
    heap->tamanho = numero_cidades;
    heap->ponta = 0;
    
    for (int i = 0; i < numero_cidades; i++) {
        struct item vertice;
        vertice.id = i;
        vertice.prioridade = infinita;
        insere_no_heap(heap, vertice);
        distancias[i] = infinita;
    }

    return heap;
}
