#include <stdio.h>

double probabilidade (int distancia_maria, int passos_restantes) {
    //função principal do programa

    if (distancia_maria < 0) {
        return 0;

    } else if (distancia_maria == 0 && passos_restantes >= 0) {
        return 1;

    } else {
        return 
        probabilidade (distancia_maria - 1, passos_restantes - 1)/6 +
        probabilidade (distancia_maria - 2, passos_restantes - 1)/6 +
        probabilidade (distancia_maria - 3, passos_restantes - 1)/6 +
        probabilidade (distancia_maria - 4, passos_restantes - 1)/6 +
        probabilidade (distancia_maria - 5, passos_restantes - 1)/6 +
        probabilidade (distancia_maria - 6, passos_restantes - 1)/6;
    }
    


}

int main() {
    int passos_restantes, distancia_maria;
    double resultado;

    scanf("%d %d", &passos_restantes, &distancia_maria);

    resultado = probabilidade(distancia_maria,passos_restantes);

    printf("%.3lf \n", resultado);

    return 0;
}