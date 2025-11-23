#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arvores_quartenarias.h"


void destroi(struct no * mapa) {
    if (mapa != NULL) {
        if (mapa->tipo == CIDADE) {
            free(mapa);

        } else if (mapa->tipo == NO_INTERNO) {
            destroi(mapa->NO);
            destroi(mapa->NE);
            destroi(mapa->SE);
            destroi(mapa->SO);
            free(mapa);
        }
    }
}

struct no * cria_no(enum tipo_de_no tipo, int x, int y) {
    struct coordenada ponto;
    ponto.x = x;
    ponto.y = y;

    struct no * novo_no = malloc(sizeof(struct no));

    novo_no->ponto = ponto;

    novo_no->tipo = tipo;

    if (tipo == CIDADE) {
        scanf(" %s", novo_no->nome);

    } else {
        novo_no->NE = NULL;
        novo_no->NO = NULL;
        novo_no->SE = NULL;
        novo_no->SO = NULL; 
    }
    return novo_no;
}

enum regiao busca_direcao_correta(struct no * mapa, struct no * cidade) {
    if (cidade->ponto.x >= mapa->ponto.x && cidade->ponto.y >= mapa->ponto.y) {
       return NORDESTE;

    } else if (cidade->ponto.x <= mapa->ponto.x && cidade->ponto.y >= mapa->ponto.y) {
        return  NOROESTE;

    } else if (cidade->ponto.x >= mapa->ponto.x && cidade->ponto.y <= mapa->ponto.y) {
        return SUDESTE;

    } else { //if (cidade->ponto.x <= mapa->ponto.x && cidade->ponto.y <= mapa->ponto.y)
        return SUDOESTE;
    }
}

struct no * inserir_cidade(struct no * mapa, struct no * cidade, struct coordenada origem_atual, int tamanho_espaco) {

    if (mapa == NULL) {
        mapa = cidade;

    } else if (mapa->tipo == NO_INTERNO) {
        //procurará a direção correta para inserção da cidade, de forma recursiva
        enum regiao direcao;
        direcao = busca_direcao_correta(mapa, cidade);

        tamanho_espaco /= 2;

        origem_atual.x = mapa->ponto.x;
        origem_atual.y = mapa->ponto.y;

        if (direcao == NOROESTE) {
            origem_atual.x -= tamanho_espaco;
            mapa->NO = inserir_cidade(mapa->NO, cidade, origem_atual, tamanho_espaco);

        } else if (direcao == NORDESTE) {
            mapa->NE = inserir_cidade(mapa->NE, cidade,  origem_atual, tamanho_espaco);

        } else if (direcao == SUDESTE) {
            origem_atual.y -= tamanho_espaco;
            mapa->SE = inserir_cidade(mapa->SE, cidade,  origem_atual, tamanho_espaco);

        } else if (direcao == SUDOESTE) {
            origem_atual.x -= tamanho_espaco;
            origem_atual.y -= tamanho_espaco;
            mapa->SO = inserir_cidade(mapa->SO, cidade,  origem_atual, tamanho_espaco);
        }

    } else {
        //caso já haja uma cidade no espaço alocado, cria um nó interno que comportará as duas cidades
        struct no * no_interno = cria_no(NO_INTERNO, origem_atual.x + tamanho_espaco/2, origem_atual.y + tamanho_espaco/2);

        struct no * cidade0 = mapa; //cidade que estava ocupando esse espaço do mapa

        mapa = no_interno;
        origem_atual = no_interno->ponto;

        mapa = inserir_cidade(mapa, cidade0, origem_atual, tamanho_espaco);
        mapa = inserir_cidade(mapa, cidade, origem_atual, tamanho_espaco);
    }

    return mapa;
}

int busca_pontual(struct no * mapa, int x, int y) {

    if (mapa != NULL) {

        if (mapa->tipo == CIDADE) {
            if (mapa->ponto.x == x && mapa->ponto.y == y) {
                printf("Cidade %s encontrada no ponto (%d,%d).\n", mapa->nome, mapa->ponto.x, mapa->ponto.y);
                return 1;

            } else {
                return 0;
            }
        } else { //if mapa->tipo == NO_INTERNO
            //verá a região que contém o ponto buscado para continuar a procura
            struct no * proximo;

            if (x >= mapa->ponto.x && y >= mapa->ponto.y) {
                proximo = mapa->NE;
                
            } else if (x >= mapa->ponto.x && y <= mapa->ponto.y) {
                proximo = mapa->SE;

            } else if (x <= mapa->ponto.x && y >= mapa->ponto.y) {
                proximo = mapa->NO;

            } else { //if (x <= mapa->ponto.x && y <= mapa->ponto.y)
                proximo = mapa->SO;
            }

            return 0 + busca_pontual(proximo, x, y);
        }

    } else {
        //para evitar problemas de acesso de memória inválida
        return 0;
    }
}

void remocao(struct no ** mapa, int x, int y) {

    if (mapa != NULL) { //evita problemas de acesso de memória inválida

        struct coordenada ponto_mapa;
        ponto_mapa.x = (*mapa)->ponto.x;
        ponto_mapa.y = (*mapa)->ponto.y;

        if (x == ponto_mapa.x && y == ponto_mapa.y) { //neste caso, certamente o nó é do tipo CIDADE
            printf("Cidade %s removida do ponto (%d,%d).\n", (*mapa)->nome, x, y);
            free((*mapa));
            (*mapa) = NULL;

        } else { //neste caso, certamente o nó é do tipo NO_INTERNO
            if (x >= ponto_mapa.x && y >= ponto_mapa.y) {
                remocao(&(*mapa)->NE, x, y);

            } else if (x >= ponto_mapa.x && y <= ponto_mapa.y) {
                remocao(&(*mapa)->SE, x, y);

            } else if (x < ponto_mapa.x && y >= ponto_mapa.y) {
                remocao(&(*mapa)->NO, x, y);

            } else if (x <= ponto_mapa.x && y <= ponto_mapa.y) {
                remocao(&(*mapa)->SO, x , y);
            } 

            //verifica se, após a remoção, sobrou apenas uma cidade no nó interno, caso positivo, substitui o nó pela cidade
            struct no * temporario = NULL;
            int n_nao_nulls = 0;

            if ((*mapa)->SE != NULL) {
                n_nao_nulls++; 
                temporario = (*mapa)->SE;}
            
            if ((*mapa)->NO != NULL) {
                n_nao_nulls++; 
                temporario = (*mapa)->NO;}

            if ((*mapa)->NE != NULL) {
                n_nao_nulls++; 
                temporario = (*mapa)->NE;}

            if ((*mapa)->SO != NULL) {
                n_nao_nulls++; 
                temporario = (*mapa)->SO;}

            if (n_nao_nulls <= 1) {
                struct no * temporario2 = (*mapa);
                (*mapa) = temporario;
                free(temporario2);
            }
        }
    }
}

void busca_por_regiao(struct no * mapa, int x_centro, int y_centro, int raio) {
    if (mapa != NULL) {
        
        if (mapa->tipo == CIDADE) {

            struct coordenada vetor_distancia;
            vetor_distancia.x = mapa->ponto.x - x_centro;
            vetor_distancia.y = mapa->ponto.y - y_centro;

            if (pow(vetor_distancia.x, 2.0) + pow(vetor_distancia.y, 2.0) <= pow(raio, 2.0)) { //verifica se o ponto está dentro da região buscada
                printf(" %s", mapa->nome);
            }

        } else { //if mapa->tipo == NO_INTERNO

            //buscará, de forma otimizada, quais são as direções que contém a região buscada
            int x_maximo = x_centro + raio;
            int y_maximo = y_centro + raio;
            int x_minimo = x_centro - raio;
            int y_minimo = y_centro - raio;

            if (y_maximo >= mapa->ponto.y && x_maximo >= mapa->ponto.x) {
                busca_por_regiao(mapa->NE, x_centro, y_centro, raio);
            }

            if (y_maximo >= mapa->ponto.y && x_minimo <= mapa->ponto.x) {
                busca_por_regiao(mapa->NO, x_centro, y_centro, raio);
            }

            if (y_minimo <= mapa->ponto.y && x_minimo <= mapa->ponto.x) {
                busca_por_regiao(mapa->SO, x_centro, y_centro, raio);
            }

            if(y_minimo <= mapa->ponto.y && x_maximo >= mapa->ponto.x) {
                busca_por_regiao(mapa->SE, x_centro, y_centro, raio);
            }
        }
    }
}
