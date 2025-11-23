#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status {ACESO, QUEIMADO, APAGADO};
enum opcao {NAO, SIM};

struct no {
    int numero;
    struct no * proximo;
};

struct grafo {
    struct no ** lista_adj;
    enum status * status; //o indice n representa o status do elemento n
};

struct fila {
    struct no * fila;
    struct no * fim_fila;  //ponteiro para o fim da fila
};

struct grafo * cria_grafo (int numero_lampadas);

//lê a entrada e preenche o grafo com base nelas
void preenche_grafo (struct grafo * grafo, int numero_conexoes);

//libera uma lista ligada qualquer
void libera_lista(struct no * lista);

//libera todas as estruturas associadas ao grafo
void libera_grafo (struct grafo * grafo, int numero_lampadas);

struct fila criar_fila (int numero_lampadas);

//coloca um elemento na fila, inserindo-o no final
void enfileirar (struct fila * fila, int vertice);

//remove o primeiro elemento da fila
int desenfileirar (struct fila * fila);

//libera todos os elementos relacionados a fila
void libera_fila (struct fila * fila);

//calcula a distância de uma lâmpada até a origem do sistema
int calcula_distancia (int * pais, int vertice, int origem);

//muda os status das lâmpadas que estão em um ciclo para "QUEIMADO"
void queima_lampada (struct grafo * grafo, int vertice1, int vertice2, int * pais, int origem);

/*realiza uma busca em largura por meio de uma fila, produzindo o vetor de pais de cada vértice, identificando ciclos e chamando a função 
queima lampada, e mudando o status para lampadas que estão após uma lâmpada queimada para "APAGADO"*/
int * busca_em_largura(struct grafo * grafo, int origem, int numero_lampadas);

/*cria um vetor de listas ligadas, onde a posicão i deste vetor contém todos os vértices (de forma ordenada)
que se situam a distância i da origem*/
struct no ** organiza_distancias (int * pais, int numero_conexoes, int numero_lampadas, int origem);

//libera todas as estruturas relacionadas ao vetor de listas ligadas
void libera_distancias (struct no ** distancias, int numero_conexoes);

//realiza a saída como a organizada no enunciado
void saida (struct no ** distancias, struct grafo * grafo, int numero_conexoes);