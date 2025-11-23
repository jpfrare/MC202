#include <stdio.h>
#define Max 1000

int NumDigits (long num) {
    // calcula o número de digitos do numero "num"

    long divisor = 1;
    int numdigits = 0;

    while (num/divisor != 0) {
        divisor *= 10;
        numdigits++;

    }

    return numdigits;
}

void DigitsVector (int vector[], long num) {
    // coloca os digitos de um determinado número em um vetor (na ordem inversa)

    int numdigits = NumDigits(num);
    int divisor = 1;

    for (int i = 0; i < numdigits; i++) {
        vector[i] = (num/divisor)%10;
        divisor *= 10;

    }
}


int IsCapicua (long num) { 
    //confere se o numero é capicua

    int numdigits = NumDigits(num); 
    int vector[Max];
    int iscapicua =  1;

    DigitsVector(vector,num);

    for (int i = 0; i < numdigits; i++) {

        if (vector[i] != vector[numdigits - 1 - i])  {
            iscapicua = 0;
            break;
        }
    }

    return iscapicua;
}

int main () {
    int tests, iscapicua;
    long num;

    scanf("%d", &tests);

    for (int i = 0; i < tests; i++) {
        //verifica se cada número dos testes é capicua
        scanf("%ld", &num);
        iscapicua = IsCapicua(num);

        if (iscapicua == 1) {
            printf("%ld eh capicua\n", num);

        } else {
            printf("%ld nao eh capicua\n", num);
        }
    }

    return 0;
}