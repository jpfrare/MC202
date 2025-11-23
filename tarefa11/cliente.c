#include "grafo.h"

int main() {
    int n_lampadas, n_conexoes, origem;
    scanf("%d %d %d", &n_lampadas, &n_conexoes, &origem);
    struct grafo * grafo = cria_grafo(n_lampadas);
    preenche_grafo(grafo, n_conexoes);

    int * pais = busca_em_largura(grafo, origem, n_lampadas);
    struct no ** distancias = organiza_distancias(pais, n_conexoes, n_lampadas, origem);

    saida(distancias, grafo, n_conexoes);

    libera_distancias(distancias, n_conexoes);
    free(pais);
    libera_grafo(grafo, n_lampadas);

    return 0;
}