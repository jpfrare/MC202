#include "improbabilidade.h"

int main() {
    struct circuitos * sistema = cria_sistema();
    situacao_inicial(sistema);
    
    enum status * resposta_final = malloc(sistema->total_alavancas * sizeof(enum status));
    int * maior_improbabilidade = malloc(sizeof(int));
    *maior_improbabilidade = sistema->improbabilidade;

    sequencias(sistema, resposta_final, maior_improbabilidade, 0);
    imprime_resposta(resposta_final, *maior_improbabilidade, sistema->total_alavancas);

    free(maior_improbabilidade);
    free(resposta_final);
    libera_sistema(sistema);

    return 0;
}