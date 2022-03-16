#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main()
{
    int m, n; //size of the m*n matrix
    Node2 head; //in fact we need to choose wether head is of type Node1 or Node2 according to the chosen presentation
    printf("Enter the size of the matrix (lines, columns): ");
    scanf("%d %d", &m, &n);

    //implementing the second presentation
    createMatrix(head);

    return 0;
}
