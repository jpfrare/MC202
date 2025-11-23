#include "grafo.h"

struct grafo * cria_grafo (int numero_lampadas) {
    struct grafo * grafo = malloc(sizeof(struct grafo));
    grafo->lista_adj = calloc(numero_lampadas, sizeof(struct no *));
    grafo->status = calloc(numero_lampadas, sizeof(enum status));

    return grafo;
}

void preenche_grafo (struct grafo * grafo, int numero_conexoes) {
    for (int i = 0; i < numero_conexoes; i++) {
        int vertice1, vertice2;
        scanf("%d %d", &vertice1, &vertice2);

        struct no * aresta1 = malloc(sizeof (struct no));
        aresta1->numero = vertice2;
        aresta1->proximo = NULL;

        struct no * aresta2 = malloc(sizeof (struct no));
        aresta2->numero = vertice1;
        aresta2->proximo = NULL;

        //inserindo na lista ligada
        aresta1->proximo = grafo->lista_adj[vertice1];
        grafo->lista_adj[vertice1] = aresta1;

        aresta2->proximo = grafo->lista_adj[vertice2];
        grafo->lista_adj[vertice2] = aresta2;
    }
}

void libera_lista(struct no * lista) {
    if (lista != NULL) {
        libera_lista(lista->proximo);
        free(lista);
    }
}

void libera_grafo (struct grafo * grafo, int numero_lampadas) {
    for (int i = 0; i < numero_lampadas; i++) {
        libera_lista(grafo->lista_adj[i]);
    }
    free(grafo->lista_adj);
    free(grafo->status);
    free(grafo);
}

struct fila criar_fila (int numero_lampadas) {
    struct fila fila;
    fila.fila = NULL;
    fila.fim_fila = NULL;

    return fila;
}

void enfileirar (struct fila * fila, int vertice) {
    struct no * aresta;
    aresta = malloc(sizeof (struct no));

    aresta->numero = vertice;
    aresta->proximo = NULL;

    if (fila->fim_fila == NULL) { //colocando no fim da fila
        fila->fim_fila = aresta;
        fila->fila = aresta;

    } else {
        fila->fim_fila->proximo = aresta;
        fila->fim_fila = aresta;
    }
}

int desenfileirar (struct fila * fila) {
    struct no * temporario = fila->fila;
    int retorno = temporario->numero;
    fila->fila = fila->fila->proximo;
    
    if (fila->fila == NULL) {
        fila->fim_fila = NULL;
    }

    free(temporario);
    return retorno;
}

void libera_fila (struct fila * fila) {
    libera_lista(fila->fila);
}

int calcula_distancia (int * pais, int vertice, int origem) {
    int distancia = 0;
    int pai = vertice;

    while (pai != origem) {
        pai = pais[pai];
        distancia++;
    }

    return distancia;
}

void queima_lampada (struct grafo * grafo, int vertice1, int vertice2, int * pais, int origem) {
    //origem do ciclo é o ponto do ciclo que tem a menor distância à origem
    int distancia1 = 0, distancia2 = 0; 

    grafo->status[vertice1] = QUEIMADO;
    grafo->status[vertice2] = QUEIMADO;

    distancia2 = calcula_distancia(pais, vertice2, origem);
    distancia1 = calcula_distancia(pais, vertice1, origem);

    //afererindo qual dos vértices está mais distante da origem do ciclo
    int maior_distancia = distancia1, vertice_maior = vertice1;
    int menor_distancia = distancia2, vertice_menor = vertice2;

    if (distancia2 > distancia1) {
        maior_distancia = distancia2;
        menor_distancia = distancia1;

        vertice_maior = vertice2;
        vertice_menor = vertice1;
    }

    int pai_vertice_maior = vertice_maior;
    int pai_vertice_menor = vertice_menor;

    //queima a diferença de caminho entre os dois vértices e a origem do ciclo
    for (int distancia_relativa = maior_distancia - menor_distancia; distancia_relativa > 0; distancia_relativa--) { 
        pai_vertice_maior = pais[pai_vertice_maior];
        grafo->status[pai_vertice_maior] = QUEIMADO; 
    }

    //como as distâncias até a origem do ciclo ja foram compensadas, queima ambos até o pai comum (origem do ciclo)
    while (pai_vertice_maior != pai_vertice_menor) {
        pai_vertice_maior = pais[pai_vertice_maior];
        pai_vertice_menor = pais[pai_vertice_menor];
        grafo->status[pai_vertice_maior] = QUEIMADO;
        grafo->status[pai_vertice_menor] = QUEIMADO;
    }

    grafo->status[pai_vertice_maior] = QUEIMADO; //queimando a origem do ciclo
}

int * busca_em_largura(struct grafo * grafo, int origem, int numero_lampadas) {
    enum opcao * visitado = calloc(numero_lampadas, sizeof(enum opcao));

    int * pais = malloc(numero_lampadas * sizeof(int));
    for (int i = 0; i < numero_lampadas; i ++) { //-1 diz que o elemento está desconectado do sistema que engloba a origem
        pais[i] = -1;
    }

    struct fila fila = criar_fila(numero_lampadas);

    enfileirar (&fila, origem);
    pais[origem] = origem;
    visitado[origem] = SIM;
    
    while (fila.fila != NULL) {
        int pai = desenfileirar(&fila);

        if (grafo->status[pai] == ACESO && (grafo->status[pais[pai]] == QUEIMADO || grafo->status[pais[pai]] == APAGADO)) {
            grafo->status[pai] = APAGADO; //apaga a lâmpada cujo pai esta queimado ou apagado
        }

        struct no * filho = grafo->lista_adj[pai];
        while (filho != NULL) {
            if (visitado[filho->numero] == NAO) {
                visitado[filho->numero] = SIM;
                pais[filho->numero] = pai;
                enfileirar(&fila, filho->numero);

            } else { //ja foi visitado
                if (pais[pai] != filho->numero && grafo->status[pai] != QUEIMADO) { /*não é um movimento de "retorno", é o encontro de dois caminhos
                                                                                    não faz nada se o pai já estiver queimado*/
                    queima_lampada(grafo, filho->numero, pai, pais, origem); //queima até o inico de ambos os caminhos
                }
            }

            filho = filho->proximo;
        }
    }

    libera_fila(&fila);
    free(visitado);
    return pais;
}

struct no ** organiza_distancias (int * pais, int numero_conexoes, int numero_lampadas, int origem) {
    struct no ** distancias = calloc (numero_conexoes, sizeof(struct no *));

    for (int i = numero_lampadas - 1; i >= 0; i--) { //a inserção é feita "de tras pra frente" para garantir que as listas ligadas estarão ordenadas
        if (pais[i] != -1) {
            int distancia = calcula_distancia(pais, i, origem);

            struct no * vertice = malloc(sizeof(struct no));
            vertice->numero = i;
            vertice->proximo = NULL;
            
            vertice->proximo = distancias[distancia];
            distancias[distancia] = vertice;
        }
    }

    return distancias;
}

void libera_distancias (struct no ** distancias, int numero_conexoes) {
    for (int i = 0; distancias[i] != NULL; i++) {
        libera_lista(distancias[i]);
    }
    free(distancias);
}

void saida (struct no ** distancias, struct grafo * grafo, int numero_conexoes) {
    for (int i = 0; distancias[i] != NULL; i++) {
        struct no * atual = distancias[i];

        while(atual != NULL) {
            int numero = atual->numero;
            enum status status = grafo->status[numero];
            char status_correspondente[10];

            if (status == APAGADO) {
                strcpy(status_correspondente, "apagada");

            } else if (status == ACESO) {
                strcpy(status_correspondente, "acesa");

            } else {
                strcpy(status_correspondente, "queimada");
            }

            printf("%d a distancia %d: %s\n", numero, i, status_correspondente);

            atual = atual->proximo;
        }
    }
}
