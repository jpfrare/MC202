struct ponto {
    int i;
    int j;
};

struct no {
    struct ponto * posicao;
    struct no * anterior;
    struct no * proximo;
};

struct no * criar_cobra();

void aumenta_cobra (struct no **cobra, int i, int j, char **matriz, int *tamanho_cobra);

void destroi_cobra(struct no *cobra);

int batera(struct no *cobra, int i_procurado, int j_procurado);

int move_cobra(struct no **cobra, char chave[], char **matriz, int n_linhas, int n_colunas, int *tamanho_cobra);

char ** constroi_matriz(int n_linhas, int n_colunas);

void imprime_matriz(char ** matriz, int n_linhas, int n_colunas);

void destroi_matriz(char ** matriz, int n_linhas);

