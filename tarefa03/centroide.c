#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct vetor {

    double * coordenadas;
    double norma;

};

void calcula_norma(struct vetor * v, int dimensao) {
    //função que calcula a norma do vetor associado ao ponto dado
    double soma = 0;

    for (int i = 0; i < dimensao; i++) {
        soma += pow(v->coordenadas[i],2);
    }

    (*v).norma = sqrt(soma);
}

void le_vetor (struct vetor * v, int dimensao) {
    //função que lê as coordenadas de cada ponto e insere a norma do vetor associado
    v->coordenadas = malloc(dimensao * sizeof(double));
    
    if (v->coordenadas == NULL) {
        exit(1);
    }

    for (int i = 0; i < dimensao; i++) {
        scanf(" %lf", &v->coordenadas[i]);
    }   

    calcula_norma(v, dimensao);
}

void constroi_centroide(struct vetor * centroide, struct vetor * lista_vetores, int quantidade_vetores, int dimensao) {
    //monta o centroide com base nos pontos/vetores existentes na lista de pontos/vetores
    for (int coordenada_atual = 0; coordenada_atual < dimensao; coordenada_atual++) {
        centroide->coordenadas[coordenada_atual] = 0;

        for (int vetor_atual = 0; vetor_atual < quantidade_vetores; vetor_atual++) {
            centroide->coordenadas[coordenada_atual] += (lista_vetores[vetor_atual].coordenadas[coordenada_atual]/quantidade_vetores);
            
        }
    }
}

void imprime_centroide(struct vetor * centroide, int dimensao) {
    //imprime as atuais coordenadas do centroide (para o caso "nenhum" e "normal")
    for (int i = 0; i < dimensao; i++) {
        printf(" %0.3lf", centroide->coordenadas[i]);
    }

    printf("\n");
}

void min_max (struct vetor * lista_vetores, struct vetor * centroide, int quantidade_vetores, int dimensao) {
    //função de impressão segundo a normalização min-max
    double min, max;
    double expressao;

    for (int coordenada_atual = 0; coordenada_atual < dimensao; coordenada_atual++) {
        min = lista_vetores[0].coordenadas[coordenada_atual];
        max = lista_vetores[0].coordenadas[coordenada_atual];

        for (int vetor_atual = 0; vetor_atual < quantidade_vetores; vetor_atual++) {
            if (lista_vetores[vetor_atual].coordenadas[coordenada_atual] < min) {
                min = lista_vetores[vetor_atual].coordenadas[coordenada_atual];

            }
            if (lista_vetores[vetor_atual].coordenadas[coordenada_atual] > max) {
                max = lista_vetores[vetor_atual].coordenadas[coordenada_atual];
            }
        }

        if (max == min) {
            expressao = 0;

        } else {
            expressao = (centroide->coordenadas[coordenada_atual] - min)/(max - min);
            expressao = 2*expressao - 1;
        }

        printf(" %0.3lf", expressao);
    }

    printf("\n");
}

void vetores_unitarios (struct vetor * lista_vetores, int quantidade_vetores, int dimensao) {
    //função que transforma os pontos de cada struct da lista em coordenadas unitárias
    for (int vetor_atual = 0; vetor_atual < quantidade_vetores; vetor_atual++) {

        for (int coordenada = 0; coordenada < dimensao; coordenada++) {
            lista_vetores[vetor_atual].coordenadas[coordenada] /= lista_vetores[vetor_atual].norma;
        }
    }
}

int main() {
    struct vetor * lista_vetores, *centroide;
    int dimensao, quantidade_vetores;

    scanf("%d %d", &dimensao, &quantidade_vetores);

    //alocando os espaços necessários na memória e preenchendo as coordenadas de cada ponto e do centroide
    centroide = malloc(sizeof(struct vetor));
    centroide->coordenadas = malloc(dimensao * sizeof(double));
    lista_vetores = malloc(quantidade_vetores * sizeof(struct vetor));
    for (int i = 0; i < quantidade_vetores; i++) {
        le_vetor(lista_vetores + i, dimensao);
    }

    //construção do centroide de coordenadas padrão
    constroi_centroide(centroide, lista_vetores, quantidade_vetores, dimensao);

    //chamadas das funções que imprimem os dois primeiros tipos de saída
    printf("nenhum:");
    imprime_centroide(centroide,dimensao);
    printf("janela:");
    min_max(lista_vetores,centroide,quantidade_vetores,dimensao);

    //faz a transição dos pontos para vetores unitários e faz a impressão da saída
    vetores_unitarios(lista_vetores,quantidade_vetores,dimensao);
    constroi_centroide(centroide,lista_vetores,quantidade_vetores,dimensao);
    printf("normal:");
    imprime_centroide(centroide,dimensao);
    
    //liberando as memórias alocadas com o  free
    for(int i = 0; i < quantidade_vetores; i++) {
        free(lista_vetores[i].coordenadas);
    }

    free(lista_vetores);
    free(centroide->coordenadas);
    free(centroide);

    return 0;
}
