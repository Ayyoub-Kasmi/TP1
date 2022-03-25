#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int m1, n1, m2, n2; //sizes of the m*n matrices (in this TP we will use 2 matrices at max)
//I will use the sizes as global variables

int main()
{
    Line *matrix1, *matrix2, *matrix3; //in fact we need to choose whether head is of type Node1 or Node2 according to the chosen presentation
    printf("Enter the size of the matrix (lines, columns): ");
    scanf("%d %d", &m1, &n1);
    m2=m1;n2=n1; //to be deleted later

    //implementing the second presentation

    //Task1
    createMatrix(&matrix1, m1, n1);

    //Task2
    showMatrix(matrix1, n1);

    //Task3
    /*
    int L1, C1, L2, C2; //the indexes of the starting and ending cells

    printf("Enter the coordinates of the starting cell (line, column): ");
    scanf("%d %d", &L1, &C1);
    printf("Enter the coordinates of the ending cell (line, column): ");
    scanf("%d %d", &L2, &C2);

    matrix2=extractMatrix(matrix1, L1, C1, L2, C2);
    showMatrix(matrix2, C2-C1+1);   */

    //Task4
    /*
    printf("\n\nThis is matrix2\n\n");
    createMatrix(&matrix2, m, n);
    sumMatrix(matrix1, matrix2);
    showMatrix(matrix1, n);     */

    //Task5
    printf("\n\nThis is matrix2\n\n");
    createMatrix(&matrix2, m1, n1);
    //multiplyMatrixVector(Line* matrix1);
    matrix3=multiplyMatrixMatrix(matrix1, matrix2, m1, n1, m2, n2);
    showMatrix(matrix3, n2);
    return 0;
}
