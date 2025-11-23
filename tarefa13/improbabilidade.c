#include "improbabilidade.h"

struct circuitos * cria_sistema () {
    struct circuitos * sistema = malloc(sizeof(struct circuitos));

    scanf("%d %d", &sistema->numero_circuitos, &sistema->total_alavancas);

    //alocando memória para o conjunto de circuitos
    sistema->posicoes_alavancas = calloc(sistema->total_alavancas, sizeof(enum status)); //estou supondo que inicialmente todas as alavancas estão p/ cima
    sistema->circuitos = malloc(sistema->numero_circuitos * sizeof(struct circuitos));
    sistema->localizacao_alavancas = calloc(sistema->total_alavancas, sizeof(struct no *));
    sistema->improbabilidade = 0;

    for (int i = 0; i < sistema->numero_circuitos; i++) { //preenchendo o circuito com as informações
        struct circuito circuito; 

        scanf("%d %d", &circuito.peso, &circuito.numero_alavancas);
        circuito.alavancas_componentes = malloc(circuito.numero_alavancas * sizeof(struct alavanca_circuito));
        circuito.quantidade_operante = 0; //variavel que impede contabilizar o peso mais de uma vez

        for (int j = 0; j < circuito.numero_alavancas; j++) {
            struct alavanca_circuito alavanca;
            struct no * no = malloc(sizeof(struct no));
            no->id_circuito = i;
            char sinal;

            scanf(" %c%d", &sinal, &alavanca.id_alavanca);

            //registrando que a alavanca j faz parte do circuito i
            no->proximo = sistema->localizacao_alavancas[alavanca.id_alavanca];
            sistema->localizacao_alavancas[alavanca.id_alavanca] = no;

            //guardando informações da alavanca
            if (sinal == '-') {
                alavanca.posicao = BAIXO;

            } else { //neste caso, o circuito está operante pois supus que todas as alavancas estão inicialmente para cima
                alavanca.posicao = CIMA;

                if (circuito.quantidade_operante == 0) {
                    sistema->improbabilidade += circuito.peso;
                }

                circuito.quantidade_operante++;
            }

            circuito.alavancas_componentes[j] = alavanca;
        }

        sistema->circuitos[i] = circuito;
    }

    return sistema;
}

void libera_lista (struct no * lista) {
    if (lista != NULL) {
        libera_lista(lista->proximo);
        free(lista);
    }
}

void libera_sistema (struct circuitos * sistema) {
    for (int i = 0; i < sistema->numero_circuitos; i++) {
        free(sistema->circuitos[i].alavancas_componentes);
    }
    for (int i = 0; i < sistema->total_alavancas; i++) {
        libera_lista(sistema->localizacao_alavancas[i]);
    }
    free(sistema->localizacao_alavancas);
    free(sistema->circuitos);
    free(sistema->posicoes_alavancas);
    free(sistema);
}

int sobe_alavanca (struct circuitos * sistema, int id_alavanca) {
    int improbabilidade_nova = sistema->improbabilidade;

    if (sistema->posicoes_alavancas[id_alavanca] == CIMA) { //já estava pra cima, não vai mudar nada
        return improbabilidade_nova;
    }

    sistema->posicoes_alavancas[id_alavanca] = CIMA; //sobe a alavanca
    
    struct no * atual = sistema->localizacao_alavancas[id_alavanca]; 

    while (atual != NULL) {
        struct circuito * circuito_atual = &sistema->circuitos[atual->id_circuito];

        //temos que procurar qual a exigencia do circuito em relacao a essa alavanca para que o circuito opere
        int indice_circuito;

        for (indice_circuito = 0;  indice_circuito < circuito_atual->numero_alavancas; indice_circuito++) {
            if (circuito_atual->alavancas_componentes[indice_circuito].id_alavanca == id_alavanca) {

                if (circuito_atual->alavancas_componentes[indice_circuito].posicao == BAIXO) { //era exigida que a alavanca estivesse para baixo
                    circuito_atual->quantidade_operante--;

                    if (circuito_atual->quantidade_operante == 0) { //circuito desligado
                        improbabilidade_nova -= circuito_atual->peso;
                    }

                } else if (circuito_atual->alavancas_componentes[indice_circuito].posicao == CIMA) { //é exigida que essa alavanca esteja para cima
                    circuito_atual->quantidade_operante++;

                    if (circuito_atual->quantidade_operante == 1) { //circuito ligado
                        improbabilidade_nova += circuito_atual->peso;
                    }
                }

                break;
            }
        }

        atual = atual->proximo;
    }

    return improbabilidade_nova;
}

int desce_alavanca (struct circuitos * sistema, int id_alavanca) {
    int improbabilidade_nova = sistema->improbabilidade;

    if (sistema->posicoes_alavancas[id_alavanca] == BAIXO) { //já estava pra baixo, não vai mudar nada
        return improbabilidade_nova;
    }

    sistema->posicoes_alavancas[id_alavanca] = BAIXO; //desce a alavanca
    
    struct no * atual = sistema->localizacao_alavancas[id_alavanca]; 

    while (atual != NULL) {
        struct circuito * circuito_atual = &sistema->circuitos[atual->id_circuito];

        //temos que procurar qual a exigencia do circuito em relacao a essa alavanca para que o circuito opere
        int indice_circuito;

        for (indice_circuito = 0;  indice_circuito < circuito_atual->numero_alavancas; indice_circuito++) {
            if (circuito_atual->alavancas_componentes[indice_circuito].id_alavanca == id_alavanca) {

                if (circuito_atual->alavancas_componentes[indice_circuito].posicao == CIMA) { //era exigida que a alavanca estivesse para cima
                    circuito_atual->quantidade_operante--;

                    if (circuito_atual->quantidade_operante == 0) { //circuito desligado
                        improbabilidade_nova -= circuito_atual->peso;
                    }

                } else if (circuito_atual->alavancas_componentes[indice_circuito].posicao == BAIXO) { //é exigida que essa alavanca esteja para baixo
                    circuito_atual->quantidade_operante++;

                    if (circuito_atual->quantidade_operante == 1) { //circuito ligado
                        improbabilidade_nova += circuito_atual->peso;
                    }
                }

                break;
            }
        }

        atual = atual->proximo;
    }

    return improbabilidade_nova;
}

void imprime_resposta(enum status * resposta_final, int maior_improbabilidade, int numero_alavancas) {
    printf("%d\n", maior_improbabilidade);

    for (int i = 0; i < numero_alavancas; i++) {
        char sinal = '-';

        if (resposta_final[i] == CIMA) {
            sinal = '+';
        }

        printf("%c%d ", sinal, i);
    }

    printf("\n");
}

void situacao_inicial (struct circuitos * sistema) {
    int improbabilidade_antiga = sistema->improbabilidade;

    for (int i = 0; i < sistema->total_alavancas; i++) { //confere se há mais improbabilidade com todas as alavancas para cima ou o contrário
        sistema->improbabilidade = desce_alavanca(sistema, i);
    }

    if (sistema->improbabilidade < improbabilidade_antiga) {
        for (int i = 0; i < sistema->total_alavancas; i++) {
            sistema->improbabilidade = sobe_alavanca(sistema, i);
        }
    }
}

int analisa_caminhos (struct circuitos * sistema, int id_atual) {
    int pesos_nao_operantes = 0;

    for (int i = 0; i < sistema->numero_circuitos; i++) {

        if (sistema->circuitos[i].quantidade_operante == 0) {

            for (int j = 0; j < sistema->circuitos[i].numero_alavancas; j++) {
                
                //vê se uma das alavancas necessárias para ligar o circuito está mais a frente da sequência de alavancas
                if (sistema->circuitos[i].alavancas_componentes[j].id_alavanca >= id_atual) {
                    pesos_nao_operantes += sistema->circuitos[i].peso;
                    break;
                }
            }
        }
    }

    return pesos_nao_operantes;
}

void sequencias (struct circuitos * sistema, enum status * resposta_final, int * maior_improbabilidade, int id_atual) {

    if (id_atual == sistema->total_alavancas) { //explorou recursivamente todo um caminho, confere se este resultou em uma improbabilidade maior que a ja obtida
        
        if (sistema->improbabilidade > *maior_improbabilidade) { //copia o vetor e atualiza a improbabilidade em caso positivo

            for (int i = 0; i < sistema->total_alavancas; i++) {
                resposta_final[i] = sistema->posicoes_alavancas[i];
            }

            *maior_improbabilidade = sistema->improbabilidade;

        } 
        return;
    }

    //testa a improbabilidade potencial na escolha de levantar a alavanca
    sistema->improbabilidade = sobe_alavanca(sistema, id_atual);
    int pesos_cima = analisa_caminhos(sistema, id_atual);
    int soma_cima = sistema->improbabilidade + pesos_cima;

    if (soma_cima > *maior_improbabilidade) { //chama a função recursviamente caso o caminho com a alavanca levantada possibilite maior improbabilidade
        sequencias(sistema, resposta_final, maior_improbabilidade, id_atual + 1);
    }

    //testa a improbabilidade potencial na escolha de descer a alavanca
    sistema->improbabilidade = desce_alavanca(sistema, id_atual);
    int pesos_baixo = analisa_caminhos(sistema, id_atual);
    int soma_baixo = sistema->improbabilidade + pesos_baixo;

    if (soma_baixo > *maior_improbabilidade) { //chama a função recursviamente caso o caminho com a alavanca abaixada possibilite maior improbabilidade
        sequencias(sistema, resposta_final, maior_improbabilidade, id_atual + 1);
    }

}