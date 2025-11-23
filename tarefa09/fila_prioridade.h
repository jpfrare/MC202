#include <stdio.h>
#include <stdlib.h>
#define heap(i) cache->heap[i] //simplicidade de notação
#define pai(i) ((i - 1)/2)
#define f_esq(i) (2*i + 1)
#define f_dir(i) (2*i + 2)

struct no {
    int dado;
    struct no * proximo;
};

struct objeto {
    int id; //tipo de objeto
    int chave; //é a posição de próximo acesso do objeto, é a prioridade
    struct no * lista_chaves; //lista ligada que contém todas as futuras chaves do objeto
    struct no * ultima_chave; //aponta para o final da lista ligada, não é usado na main, porém é importante na construção do vetor de objetos 
};

struct heap {
    struct objeto * heap; //estrutura princpal, é um vetor de objetos que será tratado como heap max
    int * pos_no_heap; //pos_heap[i] é a posição do objeto de id i no heap
    int ponta_heap; //indice da próxima inserção do heap
    int tamanho_heap; //tamanho total do heap
};

struct vetor_acessos {
    int * v; //vetor que guarda as entradas
    int tamanho;
};

//troca o conteudo dos ponteiros entre dois objetos
void troca (struct objeto * objeto_1, struct objeto * objeto_2);

//sobe um objeto no heap caso sua prioridade seja maior que a de seu pai
void sobe_no_heap(struct heap * cache, int posicao);

//desce no heap, caso sua prioridade seja menor que a de seus filhos
void desce_no_heap (struct heap * cache, int posicao_no_heap);

//tira o objeto com a maior chave do heap (indice 0)
void tira_maximo (struct heap * cache);

//faz a inserção de um novo elemento no heap, utilizando as funções anteriores
void insere_no_heap (struct heap * cache, struct objeto objeto, int * n_insercoes);

//cria o cache com base nas condições do problema
struct heap * cria_cache(int c, int n);

//cria o vetor que contém os objetos
struct objeto * cria_objetos (int n);

//cria o vetor de acessos no cache, ao mesmo tmepo que lê as entradas e completa o vetor de objetos
struct vetor_acessos * cria_e_preenche_vetores (int m, int n, struct objeto * objetos);

//avalia os acessos ao cache e, a partir disso, decide como proceder
void processa_acessos (struct heap * cache, struct vetor_acessos * acessos, struct objeto * objetos, int * n_insercoes);

//libera todas a memórias alocadas
void fim_programa(struct heap * cache, struct vetor_acessos * acessos, struct objeto * objetos, int n);