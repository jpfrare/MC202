struct no {
    char valor;
    struct no * esquerda;
    struct no * direita;
};

struct no * preenche_arvore();

void destroi(struct no * arvore);

void imprime_arvore(struct no * arvore);

struct no * leis_de_morgan(struct no * arvore);

int eh_equivalente(struct no * arvore_1, struct no * arvore_2);

struct no * simplifica_equivalencia(struct no * arvore);

struct no * simplifica_operacoes(struct no * arvore);

struct no * otimizar(struct no * arvore);