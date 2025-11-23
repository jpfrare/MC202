#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_len 26
#define tam_hash 103

enum cor {VERMELHO, VERDE, AMARELO};

//lista ligada que compõe a tabela hash
struct no{
    char palavra[max_len];
    struct no * proximo;
};

struct tabela_hash {
    struct no * vetor[tam_hash];
};

//função que determina o índice da string no hash
int funcao_hash (char palavra[]);

//função que insere uma palavra do dicionário no hash
void insere_no_hash (struct tabela_hash * hash, char palavra[]);

//faz a criação da tabela, colocando incialmente todos os espaços como NULL
struct tabela_hash cria_hash (void);

//lê todas as entradas do dicionário, chamando a função de inserir no hash
void preenche_hash (struct tabela_hash * hash, int n_palavras);

//verifica se a palavra dada está no dicionário
enum cor compara_no_hash (struct tabela_hash * hash, char palavra[max_len]);

//verifica todas as possibilidades de remoção de um único caractere de uma palavra, testando se existe correspondência no dicionário
enum cor come_letra (struct tabela_hash * hash, char palavra[max_len]);

//verifica todas as possibilidades de inserção de um único caractere de uma palavra, testando se há correspondência no dicionário
enum cor insere_letra (struct tabela_hash * hash, char palavra[max_len]);

//verifica todas as possibilidades de substituição única de caractere de uma palavra, conferindo se há alguma correspondência no dicionário
enum cor troca_letra (struct tabela_hash * hash, char palavra[max_len]);

//chama as 4 funções anteriores para classificar a palavra dada com a cor correta
void classifica_palavra (struct tabela_hash * hash);

//chama a função classifica_palavra para todas as palavras na entrada
void corretor (struct tabela_hash * hash, int numero_palavras);

//função auxiliar, no desnvolvimento, conferia o quanto a função hash espalhava as palavras do dicionário
void quantidade_hash (struct tabela_hash hash);

//libera toda a memória associada ao hash
void libera_hash (struct tabela_hash hash);

