#include <stdio.h>

#define Max 1000

int Sum (int vector[], int index) {
    //função que soma os elementos de um vetor até o indice dado
    int sum = 0;

    for (int i = 0; i <= index; i++) {
        sum += vector[i];
    }

    return sum;
}

void Inverse (int vector[], int inverse[], int lenght) {
    //função que inverte o vetor
    for (int i = 0; i < lenght; i++) {
        inverse[i] = vector[lenght - 1 - i];
    }
}

void Partial (int vector[], int sumvector[], int inverse[], int lenght) {
    //função que realiza as somas parciais e inverte o vetor resultante
    for (int i = 0; i < lenght; i++) {
        sumvector[i] = Sum(vector,i);
    }

    Inverse(sumvector,inverse,lenght);
}

void readvector (int vector[], int lenght) {
    //função que lê o vetor
    for (int i = 0; i < lenght; i++) {
        scanf("%d", &vector[i]);
    }
}

void printvector (int vector[], int lenght) {
    //função que imprime o vetor
    for (int i = 0; i < lenght - 1; i++) {
        printf("%d ", vector[i]);
    }

    printf("%d\n", vector[lenght - 1]);
}

int main() {
    int lenght;
    int vector[Max], sumvector[Max], inverse[Max];

    scanf("%d", &lenght);

    readvector(vector,lenght);

    Partial(vector,sumvector,inverse,lenght);

    printvector(inverse,lenght);

    return 0;


}