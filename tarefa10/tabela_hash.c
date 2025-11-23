#include "tabela_hash.h"

int funcao_hash (char palavra[]) {
    int len = strlen(palavra);
    int resultado = 0;

    for (int i = 1; i < len; i++) {
        resultado = (256 * resultado + palavra[i])%tam_hash;
    }

    return resultado;
}

void insere_no_hash (struct tabela_hash * hash, char palavra[]) {
    struct no * elemento = malloc(sizeof (struct no));
    strcpy(elemento->palavra, palavra);
    elemento->proximo = NULL;

    int indice = funcao_hash(palavra);

    if (hash->vetor[indice] == NULL) {
        hash->vetor[indice] = elemento;

    } else {
        struct no * temporario = hash->vetor[indice];
        hash->vetor[indice] = elemento;
        hash->vetor[indice]->proximo = temporario;
    }
}

struct tabela_hash cria_hash (void) {
    struct tabela_hash hash;
    
    for (int i = 0; i < tam_hash; i++) {
        hash.vetor[i] = NULL;
    }
    return hash;
}

void preenche_hash (struct tabela_hash * hash, int n_palavras) {
    for (int i = 0; i < n_palavras; i++) {
        char palavra[max_len];
        scanf("%s", palavra);

        insere_no_hash(hash, palavra);
    }
}

enum cor compara_no_hash (struct tabela_hash * hash, char palavra[max_len]) {
    int valor_hash = funcao_hash(palavra);

    struct no * atual = hash->vetor[valor_hash];

    while (atual != NULL) { //confere se há correspondências com palavras de mesmo hash
        if (strcmp(atual->palavra, palavra) == 0) {
            return VERDE;
        }

        atual = atual->proximo;
    }

    return VERMELHO;
}

enum cor come_letra (struct tabela_hash * hash, char palavra[max_len]) {
    int len = strlen(palavra);
    int k = 0;

    for (int i = 0; i < len; i++) { //i é o indice da letra, da palavra, que será "comida"
        char nova_palavra[max_len];

        for (int j = 0; j <= len; j++) {
            if (j != i) {
                nova_palavra[k] = palavra[j];
                k++;
            }
        }

        if (compara_no_hash(hash, nova_palavra) == VERDE) {
            printf("%s: amarelo\n", palavra);
            return AMARELO;
        }

        k = 0;
    }

    return VERMELHO;
}

enum cor insere_letra (struct tabela_hash * hash, char palavra[max_len]) {
    int len = strlen(palavra);
    int k = 0;

    for (int i = 0; i <= len; i++) { //i é onde será inserida uma letra a mais
    char nova_palavra[max_len];
        for (int j = 0; k <= len; k++) { //copiando caractere a caractere na nova string, reservando espaço para a letra adicional
            if (i != k) {
                nova_palavra[k] = palavra[j];
                j++;
            }
        }

        nova_palavra[len + 1] = '\0';

        for (char letra = 'a'; letra <= 'z'; letra++) { //colocando todas as possibilidades de caractere possíveis para a letra inserida
            nova_palavra[i] = letra;

            if (compara_no_hash(hash, nova_palavra) == VERDE) {
                printf("%s: amarelo\n", palavra);
                return AMARELO;
            }
        }

        k = 0;
    }

    return VERMELHO;
}

enum cor troca_letra (struct tabela_hash * hash, char palavra[max_len]) {
    int len = strlen(palavra);
    char nova_palavra[max_len];

    strcpy(nova_palavra, palavra);

    for (int i = 0; i < len; i++) {
        char letra_original = palavra[i];

        for (char letra = 'a'; letra <= 'z'; letra++) {
            if (letra != letra_original) {
                nova_palavra[i] = letra;

                if (compara_no_hash(hash, nova_palavra) == VERDE) {
                    printf("%s: amarelo\n", palavra);
                    return AMARELO;
                }
            }
        }

        nova_palavra[i] = letra_original;
    }

    return VERMELHO;
}


void classifica_palavra (struct tabela_hash * hash) {
    char palavra[max_len];
    
    scanf("%s", palavra);

    if (compara_no_hash(hash, palavra) == VERDE) {
        printf("%s: verde\n", palavra);
        return;
    }

    if (troca_letra(hash, palavra) == AMARELO) return;

    if (come_letra(hash, palavra) == AMARELO) return;

    if (insere_letra(hash, palavra) == AMARELO) return;

    printf("%s: vermelho\n", palavra);
}

void corretor (struct tabela_hash * hash, int numero_palavras) {
    for (int i = 0; i < numero_palavras; i++) {
        classifica_palavra(hash);
    }
}

void quantidade_hash (struct tabela_hash hash) {
    for (int i = 0; i < tam_hash; i++) {
        printf("%d: ", i);
        int contador = 0;
        
        struct no * atual = hash.vetor[i];

        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }

        printf("%d\n", contador);
    }
}

void libera_hash (struct tabela_hash hash) {
    for (int i = 0; i < tam_hash; i++) {

        struct no * atual = hash.vetor[i];

        while(atual != NULL) {
            struct no * temporario = atual;
            atual = atual->proximo;
            free(temporario);
        }
    }
}