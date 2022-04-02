#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED


//For the first presentation

typedef struct Node1 {
    int val;
    int row;
    int col;
    struct Node1* next;
} Node1;

//For the second presentation
typedef struct Node2 {
    int val;
    int col;
    struct Node2* next;
} Node2;

typedef struct Line{
    int number; //line number
    struct Node2* first; //first element in the line
    struct Line* next; //to move to the next line
} Line;

//The functions:

void createMatrix(FILE *file, Line** head, int m, int n);
void showMatrix(Line* matrix, int lines, int columns);

void extractMatrix(Line* matrix, int L1, int C1, int L2, int C2);
void divideMatrix(Line* matrix, int m1, int n1, int m2, int n2);

void sumMatrices(FILE *file, Line* matrix1, int m, int n);

void multiplyMatrixVector(Line* matrix, Line* vector, int m, int n);
void multiplyMatrixMatrix(Line *matrix1, Line* matrix2, int m1, int n1, int m2, int n2);

void transpose(Line* matrix, int lines, int columns);

void logicalOperationMatrix(Line* matrix1, Line* matrix2, int m, int n);
#endif // LIBRARY_H_INCLUDED
