#ifndef GRAFO_H 
#define GRAFO_H

#define max_len 25

struct no_grafo {
    int peso;
    int id;
    struct no_grafo * proximo;
};

struct cidade {
    char nome[max_len];
    int numero_habitantes;
};

struct grafo {
    int numero_cidades;
    struct no_grafo ** lista_adj;
    struct cidade * id_cidades; //acessa o nome e numero de habitantes da cidade de id i
};

//lê o nome de duas cidades e associa-as aos respectivos ids
void busca_id (struct grafo * grafo, int * id1, int * id2);

//cria um nó da lista de adjacencias do grafo
void cria_no_grafo (struct grafo * grafo, int id_ligacao, int peso, int id_cidade);

//lê as entradas do programa e preenche o grafo, associando cada cidade a um id definido por ordem de inserção
struct grafo * cria_e_preenche_grafo();

//libera a memória uma lista ligada
void libera_fila (struct no_grafo * fila);

//libera a memória de um grafo
void libera_grafo (struct grafo * grafo);

#endif // GRAFO_H