#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H 


#define pai(i) ((i - 1)/2)
#define f_esq(i) (2*i + 1)
#define f_dir(i) (2*i + 2)
#define heap(i) heap->fila[i]
#define infinita 100000

struct item {
    int id;
    int prioridade;
};

struct heap { //neste caso, se trata de um heap de mínimo
    struct item * fila;
    int * posicoes;
    int ponta;
    int tamanho;
};

//troca os conteúdos de v[i] e v[j]
void troca (struct item * item1, struct item * item2);

//sobe um item no heap, baseado em sua prioridade
void sobe_no_heap (struct heap * heap, int posicao_no_heap);

//desce um item no heap, baseado em sua prioridade
void desce_no_heap (struct heap * heap, int posicao_no_heap);

//retorna o item que contém a menor prioridade do heap
struct item tira_minimo (struct heap * heap);

//diminui a prioridade de um item e depois chama a função sobe_no_heap
void diminui_prioridade (struct heap * heap, int nova_prioridade, int id);

//insere um item no heap
void insere_no_heap (struct heap * heap, struct item item);

//cria o heap do programa
struct heap * cria_heap (int numero_cidades, int * distancias);

#endif //FILA_PRIORIDADE_H