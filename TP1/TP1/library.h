#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

//For the second presentation
typedef struct Line{
    int number; //line number
    struct Node2* first; //first element in the line
    struct Line* next; //to move to the next line
} Line;

typedef struct Node2 {
    int val;
    int col;
    struct Node2* next;
} Node2;

//The functions:

int createMatrix(Line** head, int m, int n);
int showMatrix(Line* matrix, int lines, int columns);

int extractMatrix(Line* matrix, int L1, int C1, int L2, int C2);
int divideMatrix(Line* matrix, int m1, int n1, int m2, int n2);

int sumMatrices(Line* matrix1, int m, int n);

int multiplyMatrixVector(Line* matrix, Line* vector, int m, int n);
int multiplyMatrixMatrix(Line *matrix1, Line* matrix2, int m1, int n1, int m2, int n2);

int transpose(Line* matrix, int lines, int columns);

int logicalOperationMatrix(Line* matrix1, Line* matrix2, int m, int n);
#endif // LIBRARY_H_INCLUDED
