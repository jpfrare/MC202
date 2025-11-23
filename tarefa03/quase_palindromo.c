#include <stdio.h>
#define Max 400


int tamanho_string(char palavra[]) {
    //calcula o tamanho de uma string
    int tamanho = 0;

    while (palavra[tamanho] != '\0') {
        tamanho++;
    }

    return tamanho;

}
int quase_palindromo (char palavra[], int k, int inicio, int fim) {
    //função pricipal do programa, calcula quantos "erros de palíndromo" a palavra têm

    if (inicio < fim) {
        if (palavra[inicio] != palavra[fim]) {

            return (1 + quase_palindromo(palavra, k, inicio + 1, fim - 1));

        } else {

            return (0 + quase_palindromo(palavra, k, inicio + 1, fim - 1));

        }
    }
    return 0;
}

int main() {
    char palavra[400];
    int k, tamanho, erros = 0;

    scanf("%d %s", &k, palavra);

    tamanho = tamanho_string(palavra);

    erros = quase_palindromo(palavra, k, 0, tamanho - 1);

    if (erros*2 <=  k) {
        printf("sim\n");

    } else {
        printf("nao\n");

    }

    return 0;
}