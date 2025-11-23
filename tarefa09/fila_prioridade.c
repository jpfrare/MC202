#include "fila_prioridade.h"

void troca (struct objeto * objeto_1, struct objeto * objeto_2) {
    struct objeto temporario = (*objeto_1);
    
    (*objeto_1) = (*objeto_2);
    (*objeto_2) = temporario;
}

void sobe_no_heap (struct heap * cache, int posicao_no_heap) {
    if (posicao_no_heap > 0 && heap(posicao_no_heap).chave > heap(pai(posicao_no_heap)).chave) {

       cache->pos_no_heap[heap(posicao_no_heap).id] = pai(posicao_no_heap);
       cache->pos_no_heap[heap(pai(posicao_no_heap)).id] = posicao_no_heap;

       troca(&heap(posicao_no_heap), &heap(pai(posicao_no_heap))); 
       sobe_no_heap(cache, pai(posicao_no_heap));
    }
}

void desce_no_heap (struct heap * cache, int posicao_no_heap) {
    int pos_maior_filho;

    if (f_esq(posicao_no_heap) < cache->ponta_heap) {
        pos_maior_filho = f_esq(posicao_no_heap);

        if (f_dir(posicao_no_heap) < cache->ponta_heap && heap(f_esq(posicao_no_heap)).chave < heap(f_dir(posicao_no_heap)).chave) {
            pos_maior_filho = f_dir(posicao_no_heap);
        }

        if(heap(pos_maior_filho).chave > heap(posicao_no_heap).chave) {
            cache->pos_no_heap[heap(pos_maior_filho).id] = posicao_no_heap;
            cache->pos_no_heap[heap(posicao_no_heap).id] = pos_maior_filho;

            troca(&heap(posicao_no_heap), &heap(pos_maior_filho));
            desce_no_heap(cache, pos_maior_filho);
        }
    }
}

void tira_maximo (struct heap * cache) {
    cache->pos_no_heap[heap(0).id] = cache->tamanho_heap; //é uma identificação de que o elemento de id x não está no cache

    if (cache->tamanho_heap == 1) {
        cache->ponta_heap--;
        return;
    }
    
    cache->ponta_heap--;
    troca(&heap(0), &heap(cache->ponta_heap));

    cache->pos_no_heap[heap(0).id] = 0;
    desce_no_heap(cache, 0);
}

void insere_no_heap (struct heap * cache, struct objeto objeto, int * n_insercoes) {

    if (cache->ponta_heap < cache->tamanho_heap) {
        heap(cache->ponta_heap) =  objeto;
        cache->pos_no_heap[objeto.id] = cache->ponta_heap;
        
        sobe_no_heap(cache, cache->ponta_heap);

        cache->ponta_heap++;

        (*n_insercoes)++;
    
    } else {
        tira_maximo(cache);
        insere_no_heap(cache, objeto, n_insercoes);
    }
}

struct heap * cria_cache (int c, int n) {
    struct heap * cache = malloc(sizeof(struct heap));
    cache->heap = malloc(c * sizeof(struct objeto));
    cache->tamanho_heap = c;
    cache->ponta_heap = 0;

    cache->pos_no_heap = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        cache->pos_no_heap[i] = cache->tamanho_heap;
    }

    return cache;
}

struct objeto * cria_objetos (int n) {
    struct objeto * objetos = malloc(n * sizeof(struct objeto));

    for (int i = 0; i < n; i++) {
        struct objeto objeto;
        objeto.id = i;
        objeto.lista_chaves = NULL;
        objeto.ultima_chave = NULL;
        objetos[i] = objeto;
    }

    return objetos;
}

struct vetor_acessos * cria_e_preenche_vetores (int m, int n, struct objeto * objetos) {
    struct vetor_acessos * acessos = malloc(sizeof(struct vetor_acessos));

    acessos->tamanho = m;
    acessos->v = malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        int id;
        scanf ("%d", &id);
        acessos->v[i] = id;

        //preenchendo o vetor de objetos
        if (objetos[id].ultima_chave == NULL) { //primeiro acesso
            struct no * no = malloc(sizeof(struct no));
            no->dado = i;
            no->proximo = NULL;
            objetos[id].lista_chaves = no;
            objetos[id].ultima_chave = no;

        } else { //acessos posteriores
            struct no * no = malloc(sizeof(struct no));
            no->dado = i;
            no->proximo = NULL;
            objetos[id].ultima_chave->proximo = no;
            objetos[id].ultima_chave = objetos[id].ultima_chave->proximo;
        }
    }

    return acessos;
}

void processa_acessos (struct heap * cache, struct vetor_acessos * acessos, struct objeto * objetos, int * n_insercoes) {
    for (int i = 0; i < acessos->tamanho; i++) {
        int id = acessos->v[i];

        if (cache->pos_no_heap[id] == cache->tamanho_heap) { //não está no heap
            //definindo a chave
            if (objetos[id].lista_chaves->proximo == NULL)  { //já não possui acessos futuros
                free(objetos[id].lista_chaves);
                objetos[id].lista_chaves = NULL;
                objetos[id].ultima_chave = NULL;
                objetos[id].chave = acessos->tamanho; //chave "infinita"

            } else { //possui acessos futuros, mudança de chave antes de inserir no heap
                objetos[id].chave = objetos[id].lista_chaves->proximo->dado;
                struct no * temporario = objetos[id].lista_chaves;
                objetos[id].lista_chaves = objetos[id].lista_chaves->proximo;
                free(temporario);
            }

            insere_no_heap(cache, objetos[id], n_insercoes);

        } else { //está no heap, mas temos que alterar a prioridade
            int posicao_no_heap = cache->pos_no_heap[id];

            if (objetos[id].lista_chaves->proximo == NULL) { //se não há mais acessos
                free(objetos[id].lista_chaves);
                objetos[id].lista_chaves = NULL;
                objetos[id].ultima_chave = NULL;
                objetos[id].chave = acessos->tamanho; //chave "infinita"
                heap(posicao_no_heap).chave = acessos->tamanho;

            } else { //mudando as prioridades tanto no heap como na lista
                heap(posicao_no_heap).chave = objetos[id].lista_chaves->proximo->dado;

                objetos[id].chave = objetos[id].lista_chaves->proximo->dado;
                struct no * temporario = objetos[id].lista_chaves;
                objetos[id].lista_chaves = objetos[id].lista_chaves->proximo;
                free(temporario);

            }

            sobe_no_heap(cache, posicao_no_heap); //como a prioridade aumentou, sobe no heap
        }
    }
}

void fim_programa (struct heap * cache, struct vetor_acessos * acessos, struct objeto * objetos, int n) {
    free(cache->pos_no_heap);
    free(cache->heap);
    free(cache);
    free(objetos);
    free(acessos->v);
    free(acessos);
}
