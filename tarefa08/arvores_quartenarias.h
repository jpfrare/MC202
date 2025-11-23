#define max_nome 11

enum regiao {NOROESTE, NORDESTE, SUDESTE, SUDOESTE};

enum tipo_de_no  {CIDADE, NO_INTERNO};

//registro auxiliar do registro de nó
struct coordenada {
    int x;
    int y;
};

//registro principal do programa, utiliza o mecanismo de tagged union para otimzação de memória
struct no {
    struct coordenada ponto; //no caso de ser nó interno, guarda o centro da região da qual ele contém
    enum tipo_de_no tipo;

    union {
        struct {char nome[max_nome]; }; //cidade
        struct {struct no * NO;
                struct no * NE;
                struct no * SO;
                struct no * SE; }; //NO_INTERNO
    };
};

//função de finalização do programa, dá free recursivamente em todas as cidades e nós internos alocados
void destroi(struct no * mapa);

//função apêndice da função de inserir cidade, que cria ou um nó interno ou uma cidade, baseado em seu tipo
struct no * cria_no(enum tipo_de_no tipo, int x, int y);

//função apêndice da função de inserir cidade, escolhe a direção correta da cidade para inserção na árvore (mapa)
enum regiao busca_direcao_correta(struct no * mapa, struct no * cidade);

//função que insere uma cidade no mapa, em caso de inserção no mesmo espaço, cria um nó interno
struct no * inserir_cidade(struct no * mapa, struct no * novo_no, struct coordenada origem_atual, int tamanho_espaco);

//função que realiza busca de uma cidade em determinado ponto, utiliza da estrutura de árvores quaternárias para buscar de forma eficiente 
int busca_pontual(struct no * mapa, int x, int y);

//função que remove uma cidade do mapa, caso sobre apenas uma cidade após a remoção, substitui esta cidadde no seu nó interno
void remocao(struct no ** mapa, int x, int y);

//função que busca as cidades na regiçao determinada, também usa a estrutura de árvore quaternária para otimizar a busca
void busca_por_regiao(struct no * mapa, int x_centro, int y_centro, int raio);
