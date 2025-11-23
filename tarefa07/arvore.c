#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct no * preenche_arvore() {
    //preenche a árvore, lendo caractere por caractere (as expressões com '!' são colocadas na direita por razão de facilidade na hora de imprimir)

    char caractere;
    scanf("%c", &caractere);

    struct no * galho = malloc(sizeof(struct no));
    if (caractere == '!') {
        galho->valor = caractere;
        galho->direita = preenche_arvore();
        galho->esquerda = NULL;

    } else if (caractere == '(') {
        galho->esquerda = preenche_arvore();
        scanf("%c", &galho->valor);

        while (galho->valor == ')') {
            //evita erros quando existem parenteses dentro de parenteses (i.e, ignora os ')')
            scanf("%c", &galho->valor);
        }

        galho->direita = preenche_arvore();

    } else {
        galho->valor = caractere;
        galho->esquerda = NULL;
        galho->direita = NULL;
    }

    return galho;
}

void destroi(struct no * arvore) {
    //libera o galho (ou toda a árvore) escolhido de forma recursiva

    if (arvore != NULL) {
        destroi(arvore->esquerda);
        destroi(arvore->direita);
        free(arvore);
    }
}

void imprime_arvore(struct no * arvore) {
    //imprime a árvore de forma infixa, com cuidado ao adicionar os conjuntos de parênteses

    if (arvore != NULL) {
        if (arvore->direita == NULL && arvore->esquerda == NULL) {
            printf("%c", arvore->valor);

        }else if (arvore->valor == '!') {
            //para o caso de expressão de negação
            printf("%c", arvore->valor);
            imprime_arvore(arvore->direita);
        
        } else {
            printf("(");
            imprime_arvore(arvore->esquerda);
            printf("%c", arvore->valor);
            imprime_arvore(arvore->direita);
            printf(")");
        }
    }
}

struct no * leis_de_morgan(struct no * arvore) {
    //função que aplica as leis de morgan

    if (arvore != NULL) {

        if (arvore->valor == '!') {
            
            if ((arvore->direita->valor == '&') || (arvore->direita->valor == '|')) {
                //para o caso de ser a negação de um "E" ou "OU"

                if (arvore->direita->valor == '&') {
                    arvore->valor = '|';

                } else if (arvore->direita->valor == '|') {
                    arvore->valor = '&';
                } 

                arvore->direita->valor = '!';

                arvore->esquerda = malloc(sizeof(struct no));
                arvore->esquerda->valor = '!';
                arvore->esquerda->esquerda = NULL;
                arvore->esquerda->direita = arvore->direita->esquerda;
                arvore->direita->esquerda = NULL;

            } else if (arvore->direita->valor == '!') {
                //quando existe dupla negação
                struct no * temp = arvore->direita->direita;
                free(arvore->direita);
                free(arvore);
                arvore = temp;
                arvore = leis_de_morgan(arvore);
            }
        }
    //recursivamente aplica as leis de morgan para as subárvores
    arvore->esquerda = leis_de_morgan(arvore->esquerda);
    arvore->direita = leis_de_morgan(arvore->direita);
    }

    return arvore;
}

int eh_equivalente(struct no * arvore_1, struct no * arvore_2) {
    //confere se uma expressão é equivalente a outra (adaptação da função de verificar se duas árvores são iguais, que consta nos slides da aula)

    int resultado_1, resultado_2, resultado_3, resultado_4, resultado_5, resultado_6, resultado_7;
    if (arvore_1 == NULL && arvore_2 == NULL) {
        return 1;
    }

    if (arvore_1 == NULL || arvore_2 == NULL) {
        return 0;
    }

    resultado_1 = (arvore_1->valor == arvore_2->valor);
    resultado_2 = eh_equivalente(arvore_1->esquerda, arvore_2->esquerda);
    resultado_3 = eh_equivalente(arvore_1->esquerda, arvore_2->direita);
    resultado_4 = eh_equivalente(arvore_1->direita, arvore_2->esquerda);
    resultado_5 = eh_equivalente(arvore_1->direita, arvore_2->direita);
    
    resultado_6 = ((resultado_2 || resultado_3) && (resultado_4 || resultado_5));
    resultado_7 = resultado_1 && resultado_6;

    return resultado_7;
}

struct no * simplifica_equivalencia(struct no * arvore) {
    //função que simplifica as equivalências contidas na árvore

    int resultado = eh_equivalente(arvore->esquerda, arvore->direita);

    while ((resultado == 1) && !(arvore->esquerda == NULL)) {
        //quando há uma ou múltiplas expressões equivalentes em seguida
        struct no * temp = arvore->esquerda;
        destroi(arvore->direita);

        free(arvore);
        arvore = temp;

        resultado = eh_equivalente(arvore->esquerda, arvore->direita);
    }

    return arvore;
}

struct no * simplifica_operacoes(struct no * arvore) {
    //função que efetivamente resolve as operações (i.e, aplica a operação que está no nó atual para as demais ramificações), o uso do switch case foi feito para efeitos de organização
    
    switch (arvore->valor) {
            case '!':
                if (arvore->direita->valor == 'T') {
                    arvore->valor = 'F';
                    free(arvore->direita);
                    arvore->direita = NULL;

                } else if (arvore->direita->valor == 'F') {
                    arvore->valor = 'T';
                    free(arvore->direita);
                    arvore->direita = NULL;
                }
                break;

            case '&':
                if(arvore->direita->valor == 'F' || arvore->esquerda->valor == 'F') {
                    destroi(arvore->esquerda);
                    destroi(arvore->direita);
                    arvore->esquerda = NULL;
                    arvore->direita = NULL;
                    arvore->valor = 'F';

                } else if (arvore->direita->valor == 'T' && arvore->esquerda->valor == 'T'){
                    destroi(arvore->esquerda);
                    destroi(arvore->direita);
                    arvore->esquerda = NULL;
                    arvore->direita = NULL;
                    arvore->valor = 'T';

                } else if (arvore->esquerda->valor == 'T') {
                    struct no * temp = arvore->direita;
                    free(arvore->esquerda);
                    free(arvore);
                    arvore = temp;
                    arvore = otimizar(arvore);

                } else if (arvore->direita->valor == 'T') {
                    struct no * temp = arvore->esquerda;
                    free(arvore->direita);
                    free(arvore);
                    arvore = temp;
                    arvore = otimizar(arvore);
                }
                break;

            case '|':

                if (arvore->esquerda->valor == 'T' || arvore->direita->valor == 'T') {
                    destroi(arvore->esquerda);
                    destroi(arvore->direita);
                    arvore->esquerda = NULL;
                    arvore->direita = NULL;
                    arvore->valor = 'T';

                } else if (arvore->esquerda->valor == 'F' && arvore->direita->valor == 'F') {
                    destroi(arvore->esquerda);
                    destroi(arvore->direita);
                    arvore->esquerda = NULL;
                    arvore->direita = NULL;
                    arvore->valor = 'F';

                } else if (arvore->esquerda->valor == 'F'){
                    struct no * temp = arvore->direita;
                    destroi(arvore->esquerda);
                    free(arvore);
                    arvore = temp;
                    arvore = otimizar(arvore);

                } else if (arvore->direita->valor == 'F') {
                    struct no * temp = arvore->esquerda;
                    destroi(arvore->direita);
                    free(arvore);
                    arvore = temp;
                    arvore = otimizar(arvore);
                }
                break;
    }

    return arvore;
}

struct no * otimizar(struct no * arvore) {
    //função principal de resolução do problema, contém os casos bases e recursivamente chama as demais funções de simplificação

    if (arvore == NULL) {
        return arvore;
    }

    if (arvore->esquerda == NULL && arvore->direita == NULL) {
        return arvore;
    }

    //confere se existem equivalências na expressão
    arvore = simplifica_equivalencia(arvore);

    //"desce" até as folhas, chamando as operações de simplificação de "cima para baixo"
    arvore->esquerda = otimizar(arvore->esquerda);
    arvore->direita = otimizar(arvore->direita);

    //faz a simplificação
    arvore = simplifica_operacoes(arvore);

    return arvore;
}
