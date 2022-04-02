#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"

int main()
{
    FILE *file;
    file=fopen("C:\\Users\\ayyoubkasmi\\Documents\\GitHub\\TP1\\TP1\\TP1\\input.txt", "r");

    Line *matrix1, *matrix2; //in fact we need to choose whether head is of type Node1 or Node2 according to the chosen presentation
    int m1, n1, m2, n2;

    printf("Enter the size of the matrix (lines, columns): ");
    fscanf(file, "%d %d", &m1, &n1);
    m2=m1;n2=n1; //to be deleted later

    //implementing the second presentation


    //Task1
    createMatrix(file, &matrix1, m1, n1);

    //Task2
    showMatrix(matrix1, m1, n1);

    //Task3
/*
    int L1, C1, L2, C2; //the indexes of the starting and ending cells

    printf("Enter the coordinates of the starting cell (line, column): ");
    fscanf(file, "%d %d", &L1, &C1);
    printf("Enter the coordinates of the ending cell (line, column): ");
    fscanf(file, "%d %d", &L2, &C2);
    printf("\n\n");
    extractMatrix(matrix1, L1, C1, L2, C2);
*/

/*
    //Task4
    printf("\n***Dividing the matrix into n x m sub-matrices***\n");
    printf("Enter the sizes of the sub matrices: ");
    fscanf(file, "%d %d", &m2, &n2);
    printf("\n\n");
    divideMatrix(matrix1, m1, n1, m2, n2); //m1 and n1 are the size of the original matrix, m2 and n2 are the size of the sub matrix
*/
    //Task5

    printf("\n\nThis is matrix2\n\n");
    //createMatrix(file, &matrix2, m1, n1); //the 2nd matrix must have the same size as matrix1
    //showMatrix(matrix2, m1, n1);
    printf("\nThis is the sum: \n");
    sumMatrices(file, matrix1, m1, n1); //this function will modify the matrix
    //consider creating a "deleteMatrix" function to delete matrix2 after each sum and then create a new one inside the sumMatrix
    //function and read values from it


    //Task6
/*
    printf("\n\nThis is matrix2\n\n");
    createMatrix(file, &matrix2, m2, n2); //this is the vector
    showMatrix(matrix2, m2, n2);
    printf("\nThis is the result of the multiplication: \n");
    //multiplyMatrixVector(matrix1, matrix2, m1, n1);
    multiplyMatrixMatrix(matrix1, matrix2, m1, n1, m2, n2);
*/

    //Task7  => done!
/*
    printf("\n This is the transposed matrix: \n");
    transpose(matrix1, m1, n1);
*/
    fclose(file);
    return 0;
}
