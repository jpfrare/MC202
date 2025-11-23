#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main() {
    //cria a árvore, imprime a árvore, simplifica com as leis de morgan, imprime, resolve a expressão, imprime novamente
    struct no * arvore = NULL;

    arvore = preenche_arvore();
    imprime_arvore(arvore);
    printf("\n");

    arvore = leis_de_morgan(arvore);
    imprime_arvore(arvore);
    printf("\n");

    arvore = otimizar(arvore);
    imprime_arvore(arvore);
    printf("\n");

    destroi(arvore);

    return 0;
}