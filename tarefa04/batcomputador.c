#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_MINIMO 8

struct vetor_dinamico {

    int * vetor;
    int ponta_vetor; //é o indice da próxima alocação
    int * endereco_lacunas; //vetor que guarda as posicoes que receberam free
    int quantidade_lacunas;
    
    int memoria_utilizada;
    int memoria_disponivel;

};

void configuracao_inicial (struct vetor_dinamico * batvetor, int numero_operacoes) {
    //faz as alocações de memória iniciais e coloca os parâmetros iniciais
    batvetor->vetor = malloc(TAMANHO_MINIMO * sizeof(int));
    batvetor->ponta_vetor = 0;
    batvetor->endereco_lacunas = malloc(numero_operacoes * sizeof(int));
    batvetor->quantidade_lacunas = 0;
    batvetor->memoria_utilizada = 0;
    batvetor->memoria_disponivel = TAMANHO_MINIMO;
    
}

void fim_do_programa (struct vetor_dinamico * batvetor) {
    //libera todas as memórias alocadas
    free(batvetor->endereco_lacunas);
    free(batvetor->vetor);
    free(batvetor);
}

void bat_print (struct vetor_dinamico * batvetor) {
    int endereco;
    scanf(" %d", &endereco);

    int tamanho_lista = batvetor->vetor[endereco];

    for (int i = 1; i <= tamanho_lista; i++) {

        printf("%d ", batvetor->vetor[endereco + i]);
    }

    printf("\n");
}

void bat_uso (struct vetor_dinamico * batvetor) {
    printf("%d de %d\n", batvetor->memoria_utilizada, batvetor->memoria_disponivel);
}

void dobra_memoria (struct vetor_dinamico * batvetor, int tamanho_lista) {
    //dobra a memória até que seja possível a alocação
    int * temporario;

    int memoria_necessaria = batvetor->ponta_vetor + tamanho_lista + 1;

    int memoria_final = batvetor->memoria_disponivel;
    
    do {
        memoria_final *= 2;

    } while (memoria_necessaria > memoria_final);

    //copia a memoria com o tamanho dobrado
    temporario = malloc(memoria_final*sizeof(int));

    for (int i = 0; i < batvetor->ponta_vetor; i++) {

        temporario[i] = batvetor->vetor[i];
    }
    
    free(batvetor->vetor);
    batvetor->vetor = temporario;
    batvetor->memoria_disponivel = memoria_final;
}

void alloc_simples (struct vetor_dinamico * batvetor, int tamanho_lista) {
    //faz o alloc na ponta do batvetor, tomando cuidado com o limite de memória
    if (batvetor->ponta_vetor + tamanho_lista > batvetor->memoria_disponivel) {

        dobra_memoria(batvetor, tamanho_lista);
    }

    batvetor->vetor[batvetor->ponta_vetor] = tamanho_lista;
    printf("%d\n", batvetor->ponta_vetor);

    batvetor->ponta_vetor ++;
    batvetor->memoria_utilizada ++;

    for (int i = 0; i < tamanho_lista; i++) {

        scanf(" %d", &batvetor->vetor[batvetor->ponta_vetor]);
        batvetor->ponta_vetor++;
        batvetor->memoria_utilizada++;
    }
}

void remove_lacuna (struct vetor_dinamico * batvetor, int endereco) {
    //remove, da lista de endereços, o endereço da lacuna, mantendo a ordenação
    int posicao_endereco;

    for (int i = 0; i < batvetor->quantidade_lacunas; i++) {
        if (batvetor->endereco_lacunas[i] == endereco) {
            posicao_endereco = i;
            break;
        }
    }

    for (int j = posicao_endereco; j < batvetor->quantidade_lacunas - 1; j++) {
        batvetor->endereco_lacunas[j] = batvetor->endereco_lacunas[j + 1];
    }
    batvetor->quantidade_lacunas--;
}

void contabiliza_lacuna (struct vetor_dinamico * batvetor, int endereco) {
    //insere novos enderecos de lacunas de forma a manter o vetor ordenado
    int i;

    if (batvetor->quantidade_lacunas == 0) {
        batvetor->endereco_lacunas[0] = endereco;
        batvetor->quantidade_lacunas++;
        i = 0;

    } else {
        for (i = batvetor->quantidade_lacunas - 1; batvetor->endereco_lacunas[i] > endereco; i--) {

            batvetor->endereco_lacunas[i + 1] = batvetor->endereco_lacunas[i];
        }

        i++;
        batvetor->endereco_lacunas[i] = endereco;
        batvetor->quantidade_lacunas++;
    }
    //vê se existe uma lacuna imediatamente a esquerda ou a direita da lacuna inserida, caso exista, concatena essas lacunas
    if (i + 1 < batvetor->quantidade_lacunas) {
        int endereco_frente;

        endereco_frente = batvetor->endereco_lacunas[i + 1];
        

        if (endereco + batvetor->vetor[endereco] + 1 == endereco_frente) {
            int valor_frente;

            valor_frente = batvetor->vetor[endereco_frente];
            batvetor->vetor[endereco] += valor_frente + 1;

            remove_lacuna(batvetor, endereco_frente);
        }
    }

    if (i > 0) {
        int endereco_atras;

        endereco_atras = batvetor->endereco_lacunas[i - 1];
        if (endereco_atras + batvetor->vetor[endereco_atras] + 1 == endereco) {

            batvetor->vetor[endereco_atras] += batvetor->vetor[endereco] + 1;

            remove_lacuna(batvetor, endereco);
        }
    }
}

int preenche_lacuna_vetor (struct vetor_dinamico * batvetor, int tamanho_lista) {
    //verifica se existe uma lacuna na qual a lista pode ser encaixada e o faz
    int tamanho_lacuna;
    int endereco_lacuna;
    int verifica = 1; //variavel que verifica se é possível uma alocação em lacuna, 0 para sim, 1 para não

    for (int i = 0; i < batvetor->quantidade_lacunas; i++) {
        endereco_lacuna = batvetor->endereco_lacunas[i];
        tamanho_lacuna = batvetor->vetor[endereco_lacuna];

        if (tamanho_lacuna >= tamanho_lista) {
            verifica = 0;
            break;
        }
    }

    if (verifica == 1) {
        //se não houver lacuna da qual a lista cabe, retorna 1
        return verifica;

    } else {
        if (tamanho_lacuna == tamanho_lista) {
            //se a lacuna for do tamanho da lista
            printf("%d\n", endereco_lacuna);
            batvetor->memoria_utilizada++;

            for (int i = 1; i <= tamanho_lista; i++) {
                scanf(" %d", &batvetor->vetor[endereco_lacuna + i]);
                batvetor->memoria_utilizada++;

            }
            //remove completamente a lacuna
            remove_lacuna(batvetor, endereco_lacuna);

        } else {
            //se a lacuna for maior que o tamanho da lista
            int i;

            batvetor->vetor[endereco_lacuna] = tamanho_lista;
            printf("%d\n", endereco_lacuna);
            batvetor->memoria_utilizada++;

            for (i = 1; i <= tamanho_lista; i++) {
                scanf(" %d", &batvetor->vetor[endereco_lacuna + i]);
                batvetor->memoria_utilizada++;

            }
            //substitui, no vetor de lacunas, a lacuna anterior pela a parcialmente preenchida
            remove_lacuna(batvetor, endereco_lacuna);

            tamanho_lacuna = tamanho_lacuna - tamanho_lista - 1;
            
            endereco_lacuna = endereco_lacuna + i;
            batvetor->vetor[endereco_lacuna] = tamanho_lacuna;

            contabiliza_lacuna(batvetor, endereco_lacuna);
        }

        return verifica;
    }
}

void bat_alloc (struct vetor_dinamico * batvetor){
    //une os casos de alloc simples e de preenchimento de lacuna, note que em caso de "verifica" ser 0, é o em que a lista foi alocada em uma lacuna
    int tamanho_lista, verifica;
    scanf(" %d", &tamanho_lista);

    verifica = preenche_lacuna_vetor(batvetor, tamanho_lista);

    if (verifica == 0) {
        return;

    } else {
        alloc_simples(batvetor, tamanho_lista);
    }
}

void libera_memoria (struct vetor_dinamico * batvetor) {
    //libera memória ate que a parte ocupada do batvetor represente mais que um quarto dele
    int * temporario;
    int memoria_final = batvetor->memoria_disponivel;

    do {
        memoria_final /= 2;

    } while ((batvetor->ponta_vetor <= (memoria_final)/4) && memoria_final > TAMANHO_MINIMO);

    //copia a memória com o vetor reduzido a metade
    temporario = malloc(memoria_final * sizeof(int));

    for (int i = 0; i < batvetor->ponta_vetor; i++) {
        temporario[i] = batvetor->vetor[i];

    }
    free(batvetor->vetor);
    batvetor->vetor = temporario;
    batvetor->memoria_disponivel = memoria_final;
}

void ajusta_ponta_vetor (struct vetor_dinamico * batvetor, int endereco, int valor_endereco) {
    //se um free for feito em uma lista imediatamente anterior a ponta do batvetor, traz a ponta para o inicio dessa lista
    batvetor->ponta_vetor = endereco;

    if (batvetor->quantidade_lacunas > 0) {
        int possivel_endereco;
        int valor_possivel_endereco;

        possivel_endereco = batvetor->endereco_lacunas[batvetor->quantidade_lacunas - 1];

        valor_possivel_endereco = batvetor->vetor[possivel_endereco];

        if (batvetor->ponta_vetor == possivel_endereco + valor_possivel_endereco + 1) {

            batvetor->quantidade_lacunas--;
            batvetor->ponta_vetor = possivel_endereco;

        }
    }
}

void bat_free (struct vetor_dinamico * batvetor) {
    /*funcao que, pratticamente, reúne todas as funções de manipualção de lacunas; atualiza a memória utilizada, coloca o endereco dado no vetor
    de endereços e trata os casos particulares (remoção de lista na extremidade do batvetor, concatenação de lacunas adjacentes e etc) */
    int endereco;
    scanf(" %d", &endereco);
    int valor_endereco = batvetor->vetor[endereco];

    batvetor->memoria_utilizada -= (valor_endereco + 1);

    if (endereco + valor_endereco + 1 == batvetor->ponta_vetor) {
        ajusta_ponta_vetor(batvetor, endereco, valor_endereco);

        //libera metade da memoria se a ponta estiver antes do ou no primeiro quarto da memoria
        if (batvetor->ponta_vetor <= batvetor->memoria_disponivel/4) {
            libera_memoria(batvetor);
        }

    } else {
        contabiliza_lacuna(batvetor, endereco);
    }
}

int main () {
    struct vetor_dinamico * batvetor;
    int numero_operacoes;
    char chave[10];
    batvetor = malloc(sizeof(struct vetor_dinamico));

    scanf("%d", &numero_operacoes);

    configuracao_inicial(batvetor, numero_operacoes);

    //interface do programa
    for (int i = 0; i < numero_operacoes; i++) {
        scanf("%s", chave);

        if (strcmp(chave, "bat-alloc") == 0) {
            bat_alloc(batvetor);

        } else if (strcmp(chave, "bat-print") == 0) {
            bat_print(batvetor);

        } else if (strcmp(chave, "bat-uso") == 0) {
            bat_uso(batvetor);

        } else if (strcmp(chave, "bat-free") == 0) {
            bat_free(batvetor);

        }
    }

    fim_do_programa(batvetor); 

    return 0;
}