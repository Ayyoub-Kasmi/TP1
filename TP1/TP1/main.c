#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"

//******************************************* IMPLEMENTING THE SECOND PRESENTATION *******************************************//

int main()
{

    Line *matrix1, *matrix2; //in fact we need to choose whether head is of type Node1 or Node2 according to the chosen presentation
    int m1, n1, m2, n2;

    printf("*******************Implementing matrices using linked lists********************\n");
    printf("*******************************************************************************\n");

    printf("\nCreating the first matrix: \n\n");
    printf("Enter the size of the matrix (lines, columns): ");
    scanf("%d %d", &m1, &n1);
    printf("\n");

    createMatrix(&matrix1, m1, n1);
    printf("\nMatrix: \n");
    showMatrix(matrix1, m1, n1);

    printf("\n******************\n");
    printf("\nChoose what to do: \n\n");
    // create a first matrix is obligatory

    printf("1) Extract a sub matrix \n");
    printf("2) Divide the matrix into sub matrices\n");
    printf("3) Sum matrices\n");
    printf("4) Multiply the matrix by a vector\n");
    printf("5) Multiply the matrix by a matrix\n");
    printf("6) Transpose the matrix\n");
    printf("7) Logical operations\n");

    int choice;
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice){

        case 1: // Extract a sub matrix

            printf("\n********** EXTRACT A SUB MATRIX **********\n");

            int L1, C1, L2, C2; //the indexes of the starting and ending cells

            printf("\nEnter the coordinates of the starting cell (line, column): ");
            scanf("%d %d", &L1, &C1);

            printf("Enter the coordinates of the ending cell (line, column): ");
            scanf("%d %d", &L2, &C2);

            printf("\n");
            printf("The extracted matrix : \n");
            printf("\nThe number of visited nodes: %d", extractMatrix(matrix1, L1, C1, L2, C2));
            break;
//****************************************************************************************************************************

        case 2: // Divide the matrix into sub matrices

            printf("\n********** DIVIDE A MATRIX INTO SUB MATRICES **********\n");

            printf("Enter m and n: ");
            scanf("%d %d", &m2, &n2);
            printf("\n\n");
            printf("\nThe number of visited nodes: %d", divideMatrix(matrix1, m1, n1, m2, n2));
                //m1 and n1 are the size of the original matrix, m2 and n2 are the size of the sub matrix

            break;
//****************************************************************************************************************************

        case 3: //sum matrices

            printf("\n********** SUM MATRICES **********\n");
            printf("The sum matrix : \n");
            printf("\nThe number of visited nodes: %d", sumMatrices(matrix1, m1, n1));

            break;
//****************************************************************************************************************************

        case 4: // multiply matrix by vector

            printf("\n********** MULTIPLLY MATRIX BY VECTOR **********\n");

            printf("\n\nCreating the vector: \n\n");
            createMatrix(&matrix2, n1, 1);
            showMatrix(matrix2, n1, 1);

            printf("\nThis is the result of the multiplication: \n");
            printf("\nThe number of visited nodes: %d", multiplyMatrixVector(matrix1, matrix2, m1, n1));

            break;
//****************************************************************************************************************************

        case 5: // multiply matrix by matrix

            printf("\n********** MULTIPLLY MATRIX BY MATRIX **********\n");

            printf("\n\nCreating the second matrix:\n\n");
            m2=n1;
            printf("Enter the number of columns of the second matrix: ");
            scanf("%d", &n2);
            createMatrix(&matrix2, n1, n2);
            showMatrix(matrix2, n1, n2);

            printf("\nThis is the result of the multiplication: \n");
            printf("\nThe number of visited nodes: %d", multiplyMatrixMatrix(matrix1, matrix2, m1, n1, n1, n2));

            break;
//****************************************************************************************************************************

        case 6: // transpose the matrix

            printf("\n********** TRANSPOSE MATRIX ***********\n");

            printf("\n This is the transposed matrix: \n");
            printf("\nThe number of visited nodes: %d", transpose(matrix1, m1, n1));

            break;
//****************************************************************************************************************************

        case 7: // logical operations

            printf("\n*********** LOGICAL OPERATOR **********\n");

            printf("\n\nThis is matrix2\n\n");
            createMatrix(&matrix2, m1, n1);
            showMatrix(matrix2, m1, n1);
            printf("\nThe number of visited nodes: %d", logicalOperationMatrix(matrix1, matrix2, m1, n1));

            break;
//****************************************************************************************************************************
        default : printf("\n\nThe choice does not exist ! \n\n");
    }

    printf("\n\n Thank you for your using the software, I hope you enjoyed it :) \n");
    return 0;
}
