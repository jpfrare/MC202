#include <stdio.h>
#include <string.h>

#define MAX_MEDICOS 50
#define MAX_PACIENTES 100
#define MAX_CARACTERES 30
#define MAX_DOENCAS 150

struct _condicao {
    char cid[4];
    char nome[100];

};

struct _medico {
    int crm;
    char nome[MAX_CARACTERES];
};

struct _paciente {
    char nome[MAX_CARACTERES];
    struct _condicao doenca;
    struct _medico medico;
};

void dados_doencas (struct _condicao doencas[]) {
    //função que preenche a lista de condições por meio do arquivo txt indicado
    FILE *fp = fopen("./dados/doencas.txt", "r");
    int inteiro;

    fscanf(fp, "%d", &inteiro);

    for (int i = 0; i < inteiro; i++) {
        fscanf(fp,"%s", doencas[i].cid);
        fscanf(fp," %[^\n]", doencas[i].nome);
    }

    fclose(fp);
}

void dados_medicos (struct _medico doutores[]) {
    //função que preenche a lista de médicos por meio do arquivo txt indicado
    FILE *fp = fopen("./dados/medicos.txt", "r");
    int inteiro;

    fscanf(fp, "%d", &inteiro);

    for (int i = 0; i < inteiro; i++) {
        fscanf(fp,"%d", &doutores[i].crm);
        fscanf(fp," %[^\n]", doutores[i].nome);
    }

    fclose(fp);
}

void registrar (struct _paciente *paciente, struct _condicao doencas[], struct _medico doutores[],char nome[], char cid[], int crm) {
    //função que adiciona o paciente a lista, associando-o à condição e médico corretos

    strcpy(paciente->nome,nome);

    for (int i = 0; i < MAX_DOENCAS; i++) {
        if (strcmp(cid,doencas[i].cid) == 0){
            paciente->doenca = doencas[i];
            break;
        }
    }

    for (int i = 0; i < MAX_MEDICOS; i++) {
        if (doutores[i].crm == crm) {
            paciente->medico = doutores[i];
            break;
        }
    }

}

void alterar (struct _paciente pacientes[], struct _condicao doencas[], char nome[], char cid[]) {
    //procura o paciente na lista, procura o código do novo  diagnóstico e faz a substituição
    int i,j;

    for (i = 0; i < MAX_PACIENTES; i ++) {
        if (strcmp(pacientes[i].nome, nome) == 0) {
            break;
        }
    }

    for (j = 0; j < MAX_DOENCAS; j++) {
        if (strcmp(doencas[j].cid, cid) == 0) {
            break;
        }
    }
    pacientes[i].doenca = doencas[j];
}

void remover (struct _paciente pacientes[], char nome[], int tamanho) {
    //remove o paciente da lista de pacientes, sobreescrevendo a sua posição com o conteúdo da próxima e assim sucessivamente
    int i;

    for (i = 0; i < MAX_PACIENTES; i++) {
        if (strcmp(pacientes[i].nome, nome) == 0) {
            break;
        }
    }

    for (i = i; i < tamanho; i++) {
        pacientes[i] = pacientes[i+1]; 
    }

}

int main() {
    struct _condicao doencas[MAX_DOENCAS];
    struct _medico doutores[MAX_MEDICOS];
    struct _paciente pacientes[MAX_PACIENTES];
    char chave[10], nome[MAX_CARACTERES], cid[4];
    int n, crm;
    int tamanho = 0;
     
    dados_medicos(doutores);
    dados_doencas(doencas);

    //a variável n não foi utilizada pois ela não foi implementada nem no loop do programa, nem nas sáidas
    scanf("%s %d", chave, &n);

    while (1) {
        //loop básico do programa, a variável tamanho é o indice do último elemento da lista final de pacientes
        scanf("%s", chave);

        if (strcmp(chave,"registrar") == 0) {
            scanf(" %s %s %d", nome, cid, &crm);
            registrar(&pacientes[tamanho], doencas, doutores, nome, cid, crm);
            tamanho++;

        } else if (strcmp(chave, "remover") == 0) {
            scanf(" %s", nome);
            remover(pacientes, nome, tamanho);
            tamanho--; 

        }else if (strcmp(chave, "alterar") == 0) {
            scanf(" %s %s", nome, cid); 
            alterar(pacientes,doencas,nome,cid);

        } else if (strcmp(chave, "fechar") == 0) {
            break;
        }
    }

    for (int i = 0; i < tamanho; i++) {
        //saída do programa
            printf("%s atendido por %s: %s\n", pacientes[i].nome, pacientes[i].medico.nome, pacientes[i].doenca.nome);

    }

    return 0;
    
}