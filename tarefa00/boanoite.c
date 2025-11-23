#include <stdio.h>

int main() {
    int c;
    int i;
    char nome[30];

    scanf("%d", &c);

    for (i = 0; i < c; i++){
    scanf("%s", nome);
    printf("Boa noite, %s.\n", nome);
    }
    
    return 0;
}