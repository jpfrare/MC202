#include <stdio.h>
#define max 100

void ReadMatrix (int matrix[max][max], int nlines, int nrows) {
    //lê a matriz
    for (int i = 0; i < nlines; i++) {

        for (int j = 0; j < nrows; j++) {

            scanf("%d", &matrix[i][j]);
        }
    }
}

int IsMinLine (int matrix[max][max], int nrows, int line, int row) {
    //verifica se o elemento é o mínimo de sua linha
    int minLine = matrix[line][row];
    int ismin = 1;

    for (int j = 0; j < nrows; j++) {

        if (j != row && minLine >= matrix[line][j]) {

            ismin = 0;
            break;
        }
    }
    return ismin;
}

int IsMaxRow (int matrix[max][max], int nlines, int line, int row) {
     //verifica se o elemento é o máximo de sua coluna
     int maxRow = matrix[line][row];
     int ismax = 1;

     for (int i = 0; i < nlines; i++) {

        if (i != line && maxRow <= matrix[i][row]) {

            ismax = 0;
            break;
        }
     }
    return ismax;
}

int main () {
    int nlines, nrows;
    int matrix[max][max];
    int issaddle = 0;
    int saddle, saddlei, saddlej;

    scanf("%d %d", &nlines, &nrows);

    ReadMatrix(matrix, nlines, nrows);

    //procurando o ponto de sela:
    for (int i = 0; i < nlines; i++) {

        for (int j = 0; j < nrows; j++) {
            
            if (IsMinLine(matrix, nrows, i, j) == 1 && IsMaxRow(matrix, nlines, i, j) == 1) {
                issaddle = 1;

                saddle =  matrix[i][j];
                saddlei = i;
                saddlej = j;
                break;

            }
        }
    }

    //imprime se há (e qual é o) ponto de sela ou não
    if (issaddle == 1) {
        printf("(%d, %d) eh ponto de sela com valor %d\n", saddlei, saddlej, saddle);

    } else {
        printf("nao existe ponto de sela\n");
    }

    return 0;
}