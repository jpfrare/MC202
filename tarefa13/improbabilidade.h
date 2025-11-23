#include <stdio.h>
#include <stdlib.h>

enum status {CIMA, BAIXO};

struct alavanca_circuito {
    int id_alavanca;
    enum status posicao;
};

struct no {
    int id_circuito;
    struct no * proximo;
};

struct circuito {
    int peso;
    int numero_alavancas; //quantidade de alavancas no circuito
    struct alavanca_circuito * alavancas_componentes; //quais alavancas compoem o circuito, e suas exigencias para que ele funcione
    int quantidade_operante; //quantidade de alavancas que contribuem para o funcionamento do circuito
};

struct circuitos {
    struct circuito * circuitos;
    int numero_circuitos;

    enum status * posicoes_alavancas; //configuração atual das alavancas, posicoes_alavancas[i] se refere a alavanca de id i
    struct no ** localizacao_alavancas; // localiação alavancas[i] mostra em quais circuitos está a alavanca i;
    int total_alavancas;

    int improbabilidade;
};

//lê e preenche todas as informações do sistema na estrutura de dados correta
struct circuitos * cria_sistema ();

//libera a memória alocada de uma lista ligada
void libera_lista (struct no * lista);

//libera todas as memórias alocadas durante a criação do sistema
void libera_sistema (struct circuitos * sistema);

//troca o estado de uma alavanca para CIMA, contabilizando a nova improbabilidade do sistema
int sobe_alavanca (struct circuitos * sistema, int id_alavanca);

//troca o estado de uma alavanca para BAIXO, contabilizando a nova improbabilidade do sistema
int desce_alavanca (struct circuitos * sistema, int id_alavanca);

//imprime a maior improbabilidade do sistema e a sequência de alavancas correspondente
void imprime_resposta(enum status * resposta_final, int maior_improbabilidade, int numero_alavancas);

/*decide, inicialmente, qual a melhor configuração inicial, baseado na improbabilidade, para o sistema: 
se são todas as alavancas para cima ou para baixo
*/
void situacao_inicial (struct circuitos * sistema);

//analisa os circuitos que não estão operantes e soma seus pesos no caso de ele depender de uma alavanca com id maior que id_atual
int analisa_caminhos (struct circuitos * sistema, int id_atual);

/*função de backtracking, analisa, a partir de dada alavanca, quais serão as possíevis improbabilidades dada a escolha de sua posição, 
chamando recursivamente a função ou não para cada possibilidade*/
void sequencias (struct circuitos * sistema, enum status * resposta_final, int * maior_improbabilidade, int id_atual);