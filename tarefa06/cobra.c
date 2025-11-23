#include "cobra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funções relacionadas a cobra
struct no * criar_cobra() {
    //cria a cobra
    return NULL;
}

void aumenta_cobra (struct no **cobra, int i, int j, char **matriz, int *tamanho_cobra) {
    //aumenta o tamanho da cobra pela cabeça, registra na matriz e soma 1 no tamanho da cobra
    struct no * novo = malloc(sizeof(struct no));
    novo->posicao = malloc(sizeof(struct ponto));
    novo->posicao->i = i;
    novo->posicao->j = j;

    novo->anterior = NULL;

    if ((*cobra) == NULL) {
        novo->proximo = NULL;
    } else {
        novo->proximo = (*cobra);
        (*cobra)->anterior = novo;
    }
    (*cobra) = novo;

    matriz[i][j] = '#';
    *tamanho_cobra = *tamanho_cobra + 1;
}

void destroi_cobra(struct no *cobra) {
    //dá free na cobra
    if (cobra != NULL) {
        free(cobra->posicao);
        destroi_cobra(cobra->proximo);
        free(cobra); 
    }
}

int batera(struct no *cobra, int i_procurado, int j_procurado) {
    //confere se a cobra baterá nela mesma, retorna 1 se sim e 0 se não
    if (cobra != NULL) {
        if (cobra->posicao->i == i_procurado && cobra->posicao->j == j_procurado) {
            return 1;

        } else {
            return batera(cobra->proximo, i_procurado, j_procurado);
        }

    } else {
        return 0;
    }
}

int move_cobra(struct no **cobra, char chave[], char **matriz, int n_linhas, int n_colunas, int *tamanho_cobra) {
    //se o movimento que a cobra fizer resultará nela batendo nela mesma, retorna 1, caso contrário, retorna 0
    int i_movimento = (*cobra)->posicao->i;
    int j_movimento = (*cobra)->posicao->j;
    int vai_bater;

    //determina a proxima posição da cabeça da cobra, faz ajustes caso as novas posições ultrapassem os limites da matriz
    if (strcmp(chave, "w") == 0) {
        i_movimento--;
        if (i_movimento < 0) {
            i_movimento = n_linhas - 1;
        }

    } else if (strcmp(chave, "s") == 0) {
        i_movimento++;
        if (i_movimento == n_linhas) {
            i_movimento = 0;
        }

    } else if (strcmp(chave, "a") == 0) {
        j_movimento--;
        if (j_movimento < 0) {
            j_movimento = n_colunas - 1;
        }

    } else if (strcmp(chave, "d") == 0) {
        j_movimento++;
        if (j_movimento == n_colunas) {
            j_movimento = 0;
        }
    }

    //confere se a cobra vai bater nela mesma com o próximo movimento
    vai_bater = batera((*cobra), i_movimento, j_movimento);
    if (vai_bater == 1) {
        return vai_bater;

    //se o próximo movimento alcançar uma fruta, o tamanho da cobra será aumentado
    } else if (matriz[i_movimento][j_movimento] == '*') {
        aumenta_cobra(cobra, i_movimento, j_movimento, matriz, tamanho_cobra);

    } else {
        //faz a cobra se mover para a posição escolhida, mudando as posições de todas as outras partes do corpo
        matriz[i_movimento][j_movimento] = '#';
        struct no * atual = (*cobra);
        int i_atual = (*cobra)->posicao->i, j_atual = (*cobra)->posicao->j;

        int i_novo = i_movimento;
        int j_novo = j_movimento;

        while (atual->proximo != NULL) {
            atual->posicao->i = i_novo;
            atual->posicao->j = j_novo;

            i_novo = i_atual;
            j_novo = j_atual;
            
            i_atual = atual->proximo->posicao->i;
            j_atual = atual->proximo->posicao->j;

            atual = atual->proximo;
        }

        matriz[i_atual][j_atual] = '_';
        atual->posicao->i = i_novo;
        atual->posicao->j = j_novo;
    }

    return 0;
}

//funções relacionadas a matriz
char ** constroi_matriz(int n_linhas, int n_colunas) {
    //faz a matriz do problema
    char ** matriz = malloc(n_linhas*sizeof(char *));

    for (int i = 0; i < n_linhas; i ++) {
        matriz[i] = malloc(n_colunas*sizeof(char));
    }

    for (int i = 0; i < n_linhas; i ++) {
        for (int j = 0; j < n_colunas; j++) {
            matriz[i][j] = '_';
        }
    }

    return matriz;
}

void imprime_matriz(char ** matriz, int n_linhas, int n_colunas) {
    //faz a impressão da matriz
    for (int i = 0; i < n_linhas; i++) {
        for (int j = 0; j < n_colunas; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void destroi_matriz(char ** matriz, int n_linhas) {
    //dá free na matriz
    for (int i = 0; i < n_linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

