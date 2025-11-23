#include <stdio.h>
#include "arvores_quartenarias.h"

int main() {
    struct no * mapa = NULL;
    int tamanho_espaco;
    char chave;
    int x,y;

    scanf("%d", &tamanho_espaco);

    do { //loop de comandos do programa
        scanf("%c", &chave);

        if (chave == 'i') {
            struct coordenada origem_atual;
            origem_atual.x = 0;
            origem_atual.y = 0;
            scanf(" %d %d", &x, &y);

            struct no * cidade = cria_no(CIDADE, x, y);

            printf("Cidade %s inserida no ponto (%d,%d).\n", cidade->nome, cidade->ponto.x, cidade->ponto.y);

            mapa = inserir_cidade(mapa, cidade, origem_atual, tamanho_espaco);
            
        } else if (chave == 'b') {
            scanf(" %d %d", &x, &y);

            int resultado = busca_pontual(mapa, x, y);

            if (resultado == 0) {
                printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", x,y);
            }

        } else if (chave == 'r') {
            scanf( "%d %d", &x, &y);

            remocao(&mapa, x, y);

        } else if (chave == 'o') {
            int raio;
            scanf( "%d %d %d", &x, &y, &raio);

            printf("Cidades a distancia %d de (%d,%d):", raio, x, y);
            busca_por_regiao(mapa, x, y, raio);
            printf("\n");
        }        
        
    } while (chave != 's');

    printf("Sistema encerrado.\n");

    destroi(mapa);

    return 0;
}