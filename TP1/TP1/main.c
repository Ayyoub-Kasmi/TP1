#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main()
{
    int m, n; //size of the m*n matrix
    Line *matrix1, *matrix2; //in fact we need to choose wether head is of type Node1 or Node2 according to the chosen presentation
    printf("Enter the size of the matrix (lines, columns): ");
    scanf("%d %d", &m, &n);

    //implementing the second presentation

    //Task1
    createMatrix(&matrix1, m, n);
    showMatrix(matrix1, n);

    //Task2
    int L1, C1, L2, C2; //the indexes of the starting and ending cells

    printf("Enter the coordinates of the starting cell (line, column): ");
    scanf("%d %d", &L1, &C1);
    printf("Enter the coordinates of the ending cell (line, column): ");
    scanf("%d %d", &L2, &C2);

    matrix2=extractMatrix(matrix1, L1, C1, L2, C2);
    showMatrix(matrix1, C2-C1+1);
    return 0;
}
