#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//obs: em muitas situações eu tive a opção de colocar else ao inves de else if, porém achei mais claro a última.

struct no {
    char dado;
    struct no * proximo;
};

struct no * criar_sequencia() {
    //meramente cria a sequencia
    return NULL;
}

void imprimir (struct no * sequencia) {
    //imprime toda a sequencia
    if (sequencia != NULL) {
        printf("%c ", sequencia->dado);
        imprimir(sequencia->proximo);

    } else {
        printf("\n");
    }
}

void insere_base (struct no ** sequencia, char base, int posicao) {
    //insere a nova base na posição especificada
    if (posicao == 0) {
        struct no * nova_base = malloc(sizeof(struct no));

        nova_base->dado = base;
        
        if ((*sequencia) == NULL) {
            nova_base->proximo = NULL;
        } else {
            nova_base->proximo = (*sequencia);
        }
        (*sequencia) = nova_base;
    }

    if (posicao > 0) {
        posicao--;
        insere_base(&(*sequencia)->proximo, base, posicao);
    }
    
}

char remove_base (struct no ** sequencia, int posicao) {
    //remove a base da posição indicada e retorna o dado dela
    char dado_removido;
    if (posicao == 1) {
        struct no * removido = (*sequencia)->proximo;
        struct no * proximo_do_removido = removido->proximo;

        dado_removido = removido->dado;

        free(removido);

        (*sequencia)->proximo = proximo_do_removido;

        return dado_removido;
    }

    if (posicao == 0) {
        struct no * temporario;
        dado_removido = (*sequencia)->dado;

        temporario = (*sequencia)->proximo;

        free((*sequencia));
        
        (*sequencia) = temporario;

        return dado_removido;
    }

    posicao--;
    return remove_base(&(*sequencia)->proximo, posicao);
}

void fim_programa (struct no * sequencia) {
    //da free em toda a sequência
    if (sequencia != NULL) {
        fim_programa(sequencia->proximo);
        free(sequencia);
    }
}

struct no * busca_posicao (struct no * sequencia, int posicao) {
    //retorna a base correspondente a posição na lista indicada
    if (posicao == 0)  {
        return sequencia;
    }
    posicao--;
    return busca_posicao(sequencia->proximo, posicao);
}

void inverte (struct no ** sequencia, int tamanho, int posicao_inicio) {
    //retona o pedaço da sequência ja invertido
    int posicao_fim = posicao_inicio + tamanho - 1;
    float meio = ((float)posicao_fim + (float)posicao_inicio)/2;

    //vetor com as bases para imprimir
    char * ordem_padrao = malloc(tamanho*sizeof(char));

    //colocando as bases no vetor na ordem origianl
    for (int i = 0; i < tamanho; i++) {
        struct no * base = busca_posicao((*sequencia), posicao_inicio + i);
        ordem_padrao[i] =  base->dado;
    }

    //fazendo a inversão das bases
    for (int i = 0; posicao_inicio + i < meio; i++) {
        char removido_esquerda = remove_base(sequencia, posicao_inicio + i);
        char removido_direita = remove_base(sequencia, posicao_fim - i - 1);

        insere_base(sequencia, removido_direita, posicao_inicio + i);
        insere_base(sequencia, removido_esquerda, posicao_fim - i);
    }

    //confere se se trata de um prefixo ou sufixo e imprime o correto
    if (posicao_inicio == 0) {
        printf("prefixo ");

    } else {
        printf("sufixo ");
    }

    //impressão
    for (int i = 0; i < tamanho; i++) {
        printf("%c ", ordem_padrao[i]);
    }
    printf("-> ");
    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%c ", ordem_padrao[i]);
    }
    printf("\n");

    free(ordem_padrao);
}

void transpoe (struct no ** sequencia, int posicao_inicio, int posicao_fim, int deslocamento){
    //função que faz a transposição das subsequências
    struct no * extremo_direito = busca_posicao((*sequencia), posicao_fim);
    struct no * extremo_esquerdo = busca_posicao((*sequencia), posicao_inicio);
    struct no * anterior_inicial = busca_posicao((*sequencia), posicao_inicio - 1);
    struct no * posterior_inicial = busca_posicao((*sequencia), posicao_fim + 1);
    
    //impressão da subsequência a ser transposta
    for (int i = 0; posicao_inicio + i <= posicao_fim; i++) {
        if (i == 0) {
            printf("subsequencia %c ", extremo_esquerdo->dado);

        } else if (posicao_inicio + i == posicao_fim) {
            printf("%c ", extremo_direito->dado);

        } else {
            struct no * base = busca_posicao((*sequencia), posicao_inicio + i);
            printf("%c ", base->dado);
        }
    }
    //base anterior e posterior ao destino final do bloco transposto
    struct no * anterior_final;
    struct no * posterior_final;

    //faz o print a ajusta as bases conforme o sinal do deslocamento
    if (deslocamento > 0) {
        printf(">> %d\n", deslocamento);

        anterior_final = busca_posicao((*sequencia), posicao_fim + deslocamento);
        posterior_final = busca_posicao((*sequencia), posicao_fim + deslocamento + 1);

    } else if (deslocamento < 0) {
        printf("<< %d\n", -1 * deslocamento);

        anterior_final = busca_posicao((*sequencia), posicao_inicio + deslocamento - 1);
        posterior_final = busca_posicao((*sequencia), posicao_inicio + deslocamento);
    }

    //faz a transposição das bases
    anterior_inicial->proximo = posterior_inicial;
    anterior_final->proximo = extremo_esquerdo;
    extremo_direito->proximo = posterior_final;
}

int main() {
    struct no * sequencia;
    int tamanho_sequencia = 0;
    sequencia = criar_sequencia();
    char chave[20];

    do {
        //lê os inputs e seleciona a função correta
        scanf("%s", chave);
        
        if (strcmp(chave, "inserir") == 0) {
            char base;
            int posicao;
            scanf(" %c %d", &base, &posicao);

            insere_base(&sequencia, base, posicao);
            printf("%c inserido em %d\n", base, posicao);

            tamanho_sequencia++;
            
        } else if (strcmp(chave, "remover") == 0) {
            int posicao;
            char removido;
            scanf(" %d", &posicao);

            removido = remove_base(&sequencia, posicao);
            printf("%c removido de %d\n", removido, posicao);

            tamanho_sequencia--;

        } else if (strcmp(chave, "inverter-prefixo") == 0) {
            int tamanho;
            scanf("%d", &tamanho);

            inverte(&sequencia, tamanho, 0);

        } else if (strcmp(chave, "inverter-sufixo") == 0) {
            int tamanho;
            scanf("%d", &tamanho);
            int posicao_inicio = tamanho_sequencia - tamanho;

            inverte(&sequencia, tamanho, posicao_inicio);

        } else if (strcmp(chave, "transpor") == 0) {
            int posicao_inicio, posicao_fim, deslocamento;
            scanf("%d %d %d", &posicao_inicio, &posicao_fim, &deslocamento);

            transpoe(&sequencia, posicao_inicio, posicao_fim, deslocamento);

        } else if (strcmp(chave, "imprimir") == 0) {
            printf("sequencia ");
            imprimir(sequencia);

        }

    } while (strcmp(chave, "sair") != 0);

    fim_programa(sequencia);
    return 0;
}