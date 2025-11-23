#include <stdio.h>
#include <string.h>

#define MAXN 100
#define MAXC 30


struct identidade {
    //registro organizado dos indivíduos

    char nome_completo[MAXC];
    char primeiro_nome[MAXC];
    char sobrenome[MAXC];

};

void Nome (struct identidade *pessoa) {
    //com base no nome completo da pessoa, separa o primeiro nome do sobrenome
    int i,j;
    int tamanho;
    tamanho = strlen(pessoa->nome_completo);

    for (i = 0; pessoa->nome_completo[i] != '_'; i++) {
        pessoa->primeiro_nome[i] = pessoa->nome_completo[i];
    }

    pessoa->primeiro_nome[i] = '\0';
    i++;

    for (j = 0; i < tamanho; j++, i++) {
         pessoa->sobrenome[j] = pessoa->nome_completo[i];
    }

    pessoa->sobrenome[j] = '\0';

}

void Procura_Nomes (struct identidade pessoas[], char chave[], char busca[], int n) {
    //função que busca, na lista de nomes, a busca (nome ou osbrenome) com base na chave (homonimos ou parentes)
    int i;

    if (strcmp(chave,"homonimos") == 0) {
        for (i = 0; i < n; i++) {
            if (strcmp(pessoas[i].primeiro_nome,busca) == 0) {
                printf("%s\n", pessoas[i].nome_completo);
            }
        }

    } else if (strcmp(chave,"parentes") == 0) {
        for (i = 0; i < n; i++) {
            if (strcmp(pessoas[i].sobrenome,busca) == 0) {
                printf("%s\n", pessoas[i].nome_completo);
            }
        }
    }

}


int main()  {
    struct identidade pessoas[MAXN];
    int n;
    char chave[MAXC], busca[MAXC];
    

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", pessoas[i].nome_completo);
        Nome(&pessoas[i]);
    }

    scanf("%s %s", chave, busca);

    Procura_Nomes(pessoas,chave,busca,n);

    return 0;
}   