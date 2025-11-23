#include <stdio.h>
#include <string.h>
#include "cobra.h"


int main() {
    char ** matriz;
    struct no * cobra;
    char chave[7];
    int n_linhas, n_colunas, bateu = 0, tamanho_cobra = 0;
    //bateu é a variável que confere se a cobra bateu em si mesma, se 0, não bateu, se 1, bateu

    scanf("%s", chave);

    if (strcmp(chave, "MATRIZ") == 0) {
        //entendo ser redundante conferir se a chave será "MATRIZ", poém acho mais organizado e fácil de entender
            scanf("%d %d", &n_linhas, &n_colunas);

            matriz = constroi_matriz(n_linhas, n_colunas);
    }

    while ((tamanho_cobra < (n_linhas * n_colunas)) && (bateu != 1)) {
        //lê os inputs e faz a ação correspondente
        scanf("%s", chave);

        if (strcmp(chave, "FRUTA") == 0) {
            int i_fruta, j_fruta;
            scanf("%d %d", &i_fruta, &j_fruta);

            matriz[i_fruta][j_fruta] = '*';
            imprime_matriz(matriz, n_linhas, n_colunas);

        } else if (strcmp(chave, "COBRA") == 0) {
            int i, j;
            scanf("%d %d", &i, &j);

            cobra = criar_cobra();
            aumenta_cobra(&cobra, i, j, matriz, &tamanho_cobra);

        } else {
            //se o comando for de se mover para alguma direção
            bateu = move_cobra(&cobra, chave, matriz, n_linhas, n_colunas, &tamanho_cobra);

            if (bateu == 0) {
                imprime_matriz(matriz, n_linhas, n_colunas);
            }
        }
    }

    if (tamanho_cobra == (n_linhas * n_colunas)) {
        //analisa os resultados do jogo
        printf("YOU WIN\n");

    } else if (bateu == 1){
        printf("GAME OVER\n");
    }

    destroi_cobra(cobra);
    destroi_matriz(matriz, n_linhas);

    return 0;
}