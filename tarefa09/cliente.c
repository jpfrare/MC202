#include "fila_prioridade.h"
#include <stdio.h>

int main() {
    int n_insercoes = 0;
    int c, n, m;
    scanf("%d %d %d", &c, &n, &m);

    struct heap * cache;
    struct vetor_acessos * acessos;
    struct objeto * objetos; //o indice i desse vetor possui o objeto de i
   
    cache = cria_cache(c, n);
    objetos = cria_objetos(n);
    acessos = cria_e_preenche_vetores(m, n, objetos);

    processa_acessos(cache, acessos, objetos, &n_insercoes);

    printf("%d\n", n_insercoes);

    fim_programa(cache, acessos, objetos, n);

   return 0;
}