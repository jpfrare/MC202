#include "grafo.h"
#include "implementacao.h"

int main() {
    struct grafo * grafo = cria_e_preenche_grafo();

    melhor_cenario(grafo);

    libera_grafo(grafo);
}