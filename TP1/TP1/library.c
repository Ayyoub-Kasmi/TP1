#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"

//************************************  ABSTRACT MACHINE ************************************************************//
//*******************************************************************************************************************//

// CREATE - DELETE :
void allocateLine(Line** line){
    *line = (Line* )malloc(sizeof(Line));
}

void allocateColumn(Node2** column){
    *column = (Node2* )malloc(sizeof(Node2));
}

void freeLine(Line* line){
    free(line);
}

void freeColumn(Node2* column){
    free(column);
}

// UPDATE :

    // Line node:

void affectLineNumber(Line* line, int number){
    line->number = number;
}

void affectAddressLineLine(Line* line1, Line* line2){
    line1->next = line2;
}

void affectAddressLineColumn(Line* line, Node2* column){
    line->first = column;
}

    // Column node:

void affectColumnNumber(Node2* column, int number){
    column->col = number;
}

void affectAddressColumn(Node2* column1, Node2* column2){
    column1->next = column2;
}

void affectValue(Node2* column, int value){
    column->val = value;
}

// ACCESS:

    // Line node :
int lineNumber(Line* line){
    return line->number;
}

Line* nextLine(Line* line){
    return line->next;
}

Node2* firstColumn(Line* line){
    return line->first;
}

    // Column node:
int columnNumber(Node2* column){
    return column->col;
}

int columnValue(Node2* column){
    return column->val;
}

Node2* nextColumn(Node2* column){
    return column->next;
}


//******************************************* AUXILARY FUNCTIONS ****************************************************//
//*******************************************************************************************************************//

                        //These are helping functions that will be used in the program's main functions

void createLineNode(Line** node, int i){
    allocateLine(node);

    affectLineNumber(*node, i);
    affectAddressLineLine(*node, NULL);
    affectAddressLineColumn(*node, NULL);
}

void createColumnNode(Node2 **node, int value, int column){
    allocateColumn(node);

    affectValue(*node, value);
    affectColumnNumber(*node, column);
    affectAddressColumn(*node, NULL);
}

int insertLineNode(Line** matrix, Line* node){
    //insert a line node in a matrix

    Line *P=*matrix, *tmp;
    int counter=0;

    //if the matrix is empty
    if(*matrix == NULL){
        *matrix=node;
        return counter; // andstopping the function from continuing
    }

    if(lineNumber(node) < lineNumber(P)){
        *matrix=node;

        affectAddressLineLine(node,P);
        return counter;
    }

    while(nextLine(P) != NULL && lineNumber(nextLine(P)) < lineNumber(node)){
        //firstly I look up the correct position to insert the node
        P=nextLine(P);
        counter++;
    }
    tmp=nextLine(P); //tmp=NULL
    affectAddressLineLine(P, node);
    affectAddressLineLine(node, tmp);

    return counter;
}

int insertColumnNode(Line *matrix, int line, Node2 *node){
    //insert a column node in line

    int counter=0;
    while(lineNumber(matrix) != line){
        matrix=nextLine(matrix);
        counter++;
    }

    Node2 *Q = firstColumn(matrix), *tmp;
    //Q is now the first column in this line

    //if the line is a newly created one (so it is empty)
    if(Q==NULL){
        affectAddressLineColumn(matrix, node);
        return counter; //to stop the function from continuing
    }

    if(columnNumber(node) < columnNumber(Q)){ //the node will become the first column, it will be linked to tmp
        affectAddressLineColumn(matrix, node);
        affectAddressColumn(node, Q);
        return counter; //to stop the function from continuing
    }

    while(nextColumn(Q) != NULL && columnNumber( nextColumn(Q) ) < columnNumber(node) ){
        //firstly I look up the correct position to insert the node
        Q=nextColumn(Q);
        counter++;
    }
    tmp=nextColumn(Q);
    affectAddressColumn(Q, node);
    affectAddressColumn(node, tmp);

    return counter;
}

int lineExists(Line* matrix, int line){
    //This function checks if this a line exists in matrix

    //will be used in the transposing function
    Line* P=matrix;

    while(P!=NULL){
        if(lineNumber(P) == line){
            return 1;
        }
        P=nextLine(P);
    }

    return 0;

}

int nodeExists(Line* matrix, int line, int column, Node2** target){
    // This function checks if a column node exists in a matrix and exports its pointer to "target", and returns status (found or not)
    //line and column represent the coordinates of the node
    Line *P=matrix;
    Node2 *Q;
    *target=NULL;

    //step1: checking if the line exists
    while(P!=NULL && lineNumber(P) < line){
        //advancing until finding or passing the correct line
        P=nextLine(P);
        if(P==NULL){
            return 0;
        }
    }

    if(lineNumber(P) != line){ //if we passed the correct line
        return 0;
    }

    Q=firstColumn(P);
    while(Q!=NULL && columnNumber(Q) < column){
        //advancing until finding or passing the correct column
        Q=nextColumn(Q);
        if(Q==NULL){
            return 0;
        }
    }

    if(columnNumber(Q) == column){
            *target=Q;
        return 1;
    } else {return 0;};

}

int removeNullLines(Line **matrix){
    Line *P1=*matrix, *P2;
    int counter=0;
    while(P1!=NULL){
        if(firstColumn(P1)!=NULL){
            P2=P1;
            P1=nextLine(P1);
            counter++;

        } else { //if the line is not null then we advance P1 and P2 normally

            if(P1 == *matrix){ //the null line is the first line
                *matrix=nextLine(P1); //The next line becomes the head
                free(P1);
                P1=*matrix;

            } else { //the null line is in the middle or the end
                affectAddressLineLine(P2, nextLine(P1));
                free(P1);
                P1=nextLine(P2);
            }
            counter++;
        }
    }
    return counter;
}

void removeColumnNode(Line** matrix, int line, int column){
    //the node is supposed already existent in the matrix
    Line *P=(*matrix), *P2;
    Node2 *Q, *previous;

    while(lineNumber(P) != line){
        P2=P;
        P=nextLine(P);
    }

    Q=firstColumn(P);

    while(columnNumber(Q) != column){
        previous=Q;
        Q=nextColumn(Q);
    }

    if(Q==firstColumn(P)){
        //Q is the first node in the line
        affectAddressLineColumn(P, nextColumn(Q));
    } else {
        affectAddressColumn(previous, nextColumn(Q));
    }
    free(Q);
    //what if the node is in the last line
    //to fix later

    if(firstColumn(P) == NULL){
        if(P == *matrix){
            *matrix = nextLine(P);

        } else {
            affectAddressLineLine(P2, nextLine(P));
        }
        free(P);
    }
}

void printNullLines(int number, int columns){ //Used to print the NULL lines
    for(int i=0; i<number; i++){
        for(int j=0; j<columns; j++){
            printf("%3d ", 0);
        }
        printf("\n");
    }
}

void printLinesOfOnes(int number, int columns){ //Used to print the NULL lines
    for(int i=0; i<number; i++){
        for(int j=0; j<columns; j++){
            printf("%3d ", 1);
        }
        printf("\n");
    }
}

void printZeros(int number){
    for(int i=1; i<number; i++){
        printf("%3d ",0);
    }
}

void printOnes(int number){
    for(int i=1; i<number; i++){
        printf("%3d ",1);
    }
}

int deleteMatrix(Line **matrix){
    Line *P1=*matrix, *P2;
    Node2 *Q1, *Q2;
    int counter = 0;

    while(P1!=NULL){
        counter++;
        Q1=firstColumn(P1);

        while(Q1!=NULL){
            counter++;
            Q2=Q1;
            Q1=nextColumn(Q1);
            free(Q2);
        }

        P2=P1;
        P1=nextLine(P1);
        free(P2);
    }

    return counter;
}

int min(int a, int b){
    return a<b ? a : b;
}

int max(int a, int b){
    return a>b ? a : b;
}

int addValue(Line* matrix, int value, int line, int column){
    // The node is supposed already existent in the matrix
    // This function will add a value to a node and delete it if the result is null

    Line *P=matrix;
    Node2 *Q;
    int counter=0;

    while(lineNumber(P) != line){
        P=nextLine(P);
        counter++;
    }

    Q=firstColumn(P);

    while(columnNumber(Q) != column){
        counter++;
        Q=nextColumn(Q);
    }

    affectValue(Q, columnValue(Q)+value);
    if(columnValue(Q) == 0){
        removeColumnNode(&matrix, line, column);
    }

    return counter;
}

int performLogicalOperation(Line* matrix, int value, int line, int column, int oper){
    //perform logical operation on a node of coordinates [line, column]
    //the node is supposed already existent in the matrix

    Line *P=matrix;
    Node2 *Q;
    int counter=0;

    while(lineNumber(P) != line){
        P=nextLine(P);
        counter++;
    }

    Q=firstColumn(P);

    while(columnNumber(Q) != column){
        Q=nextColumn(Q);
        counter++;
    }

    switch(oper){ //operations are: 1-negation 2-AND 3-OR 4-XOR
        case 1:
            affectValue(Q, !columnValue(Q));
            break;

        case 2:
            affectValue(Q, columnValue(Q) & value);
            break;

        case 3:
            affectValue(Q, columnValue(Q) | value);
            break;
        case 4:
            affectValue(Q, columnValue(Q) ^ value);
            break;
    }

    if(columnValue(Q) == 0){
            removeColumnNode(&matrix, line, column);
    }

    return counter;
}

int negateMatrix(Line* matrix, int lines, int columns){
    // This function is based on the showMatrix() function: print 0 if the node exists, 1 otherwise

    Line *P;
    Node2 *cell;
    int dif; //to calculate difference between two lines or columns: dif1 for lines, dif2 for columns
    int counter=0;
    printf("\n");

    if(matrix == NULL){
        printLinesOfOnes(lines, columns);
        return counter; // and stopping the function from executing the next piece of code
    }

    //check if there're null line before the first line
    if(lineNumber(matrix)!=1){
        printLinesOfOnes(lineNumber(matrix) -1 ,columns);
    }

    while(matrix!=NULL){
        cell=firstColumn(matrix); //Head of the line

        //check if there're zeros before the line's head
        if(columnNumber(cell)!=1){
            printOnes(columnNumber(cell));
        }
        //printing the zeros in the middle of the line
        while(cell->next!=NULL){ //The problem is with the size, so do we always need a size variable
            printf("%3d ", 0);
            dif=(columnNumber(nextColumn(cell))) - columnNumber(cell);
            if(dif!=1){
                printOnes(dif);
            }
            cell=nextColumn(cell);
            counter++;
        }
        printf("%3d ",0); //printing the last element

        //checking if there're zeros after the last element
        if(columnNumber(cell)!=columns){
            printOnes(columns - columnNumber(cell) +1);
        }
        printf("\n");

        //checking the null lines in the middle
        if(nextLine(matrix)!=NULL){
            dif=(lineNumber(nextLine(matrix)))-lineNumber(matrix);
            if(dif!=1){
                printLinesOfOnes(dif-1, columns);
            }
        }
        P=matrix; //saving the old value of matrix in P
        matrix=nextLine(matrix);
        counter++;
    }

    //checking if there're null lines in the end
    if(lineNumber(P)!=lines){
            printLinesOfOnes(lines - lineNumber(P), columns);
        }
    return counter;
}

// *************************************************** MAIN FUNCTIONS *********************************************************//

//Task 1:
//*********************************** CREATE MATRIX ***************************************//

int createMatrix(Line** matrix, int m, int n){

    //n and m represent the size of the m*n matrix
    int value; //used to read values to fill the matrix
    Line *P;
    Node2 *Q;
    int counter=0;

    *matrix=NULL;

    for(int i=1; i<=m; i++){ //for each line
        createLineNode(&P, i);
        counter+= insertLineNode(matrix, P);

        for(int j=1; j<=n; j++){ //for each column
            printf("Enter the value of [%d][%d]: ", i, j);
            scanf("%d", &value); // reading the value to insert
            if(value==0){
                continue;
            }

            createColumnNode(&Q, value, j);
            counter+= insertColumnNode(*matrix, i, Q);

        }
    }

    counter+= removeNullLines(matrix);
    return counter;
}


//Task 2:
//*********************************** SHOW MATRIX ***************************************//

int showMatrix(Line* matrix, int lines, int columns){

    Line *P;
    Node2 *cell;
    int dif; //to calculate difference between two lines or columns
    int counter=0; //count the number of nodes passed through
    printf("\n");

    if(matrix == NULL){
        printNullLines(lines, columns);
        return counter; // and stopping the function from executing the next piece of code
    }

    //check if there're null line before the first line
    if(lineNumber(matrix)!=1){
        printNullLines(lineNumber(matrix) -1 ,columns);
    }

    while(matrix!=NULL){
        counter++;
        cell=firstColumn(matrix); //Head of the line

        //check if there're zeros before the line's head
        if(columnNumber(cell)!=1){
            printZeros(columnNumber(cell));
        }
        //printing the zeros in the middle of the line
        while(cell->next!=NULL){
            counter++;
            printf("%3d ", columnValue(cell));
            dif=(columnNumber(nextColumn(cell))) - columnNumber(cell);
            if(dif!=1){
                printZeros(dif);
            }
            cell=nextColumn(cell);
        }
        printf("%3d ",columnValue(cell)); //printing the last element

        //checking if there're zeros after the last element
        if(columnNumber(cell)!=columns){
            printZeros(columns - columnNumber(cell) +1);
        }
        printf("\n");

        //checking the null lines in the middle
        if(nextLine(matrix)!=NULL){
            dif=(lineNumber(nextLine(matrix)))-lineNumber(matrix);
            if(dif!=1){
                printNullLines(dif-1, columns);
            }
        }
        P=matrix; //saving the old value of matrix in P
        matrix=nextLine(matrix);
    }

    //checking if there're null lines in the end
    if(lineNumber(P)!=lines){
            printNullLines(lines - lineNumber(P), columns);
        }

    return counter;
}

//Task 3:
//*********************************** EXTRACT MATRIX ***************************************//

int extractMatrix(Line* matrix, int L1, int C1, int L2, int C2){
    Line *P1=NULL;
    Node2 *Q1, *Q2;
    int dif, counter=0;

    //if the matrix is already null
    if(matrix==NULL){
        printNullLines(L2-L1+1, C2-C1+1);
        return counter; //to stop the function from continuing to the rest of the code
    }

    while(lineNumber(matrix)<L1){
        //advancing until reaching the beginning line
        matrix=nextLine(matrix);
        counter++;
    }

    //checking if there're null lines to print before the current line
    if(lineNumber(matrix) > L1){
        printNullLines(lineNumber(matrix) - L1, C2-C1+1);
    }

    while(matrix!=NULL && lineNumber(matrix) <= L2){

        //<--- printing columns from the current line --->

        Q1=firstColumn(matrix); //as the line is non null, there's one element at least
        Q2=Q1;
        while(Q1!=NULL && columnNumber(Q1) < C1){
            //advancing until finding the starting column
            Q1=nextColumn(Q1);
            counter++;
        }

        if(Q1==NULL){
            printZeros(C2-C1+2);
            P1=matrix; //saving the previous value in P1
            matrix=nextLine(matrix);
            printf("\n");
            continue; //go to the next line
        }

        //checking if there're zeros to print before the current column
        if(columnNumber(Q1) > C1){
            printZeros(min(columnNumber(Q1), C2) - C1 +1);
        }

        //printing the middle elements
        while(Q1!=NULL && columnNumber(Q1) <= C2){
            printf("%3d ", columnValue(Q1));

            if(nextColumn(Q1)!=NULL && columnNumber(nextColumn(Q1)) <= C2){
                dif=(columnNumber(nextColumn(Q1))) - columnNumber(Q1); //here is a problem when the next is null
                if(dif!=1){
                    printZeros(dif);
                }
            };
            Q2=Q1;
            Q1=nextColumn(Q1);
            counter++;
        }

        //checking if there're remaining zeros to the end of the column
        if(Q2!=Q1 && columnNumber(Q2) < C2){
            printZeros(C2 - max(columnNumber(Q2), C1-1) +1);
        }
        printf("\n");

        //<--- the line is printed --->

        //checking if there're null lines in the middle
        if(nextLine(matrix)!=NULL && lineNumber(nextLine(matrix)) <= L2){ //the next line is less than the max line
            dif=(lineNumber(nextLine(matrix)))-lineNumber(matrix);
            if(dif!=1){
                printNullLines(dif-1, C2-C1+1);
            }
        }

        P1=matrix; //saving the previous value of "matrix" in P1
        matrix=nextLine(matrix);
        counter++;
    }

    //checking if there're null lines remaining
    if(P1!=NULL){ // As P1 was initialized by NULL, it will only change if the program enters the previous while loop
        if(lineNumber(P1) < L2){
            printNullLines(L2 - lineNumber(P1), C2-C1+1);
        }
    }

    return counter; // The number of nodes passed through
}

//Task 4:
//*********************************** DIVIDE MATRIX ***************************************//

int divideMatrix(Line* matrix, int m1, int n1, int m2, int n2){
    //verifying if the matrix's size is dividable by m and n

    int counter=0; //counting the number of nodes
    if(m1%m2 != 0 || n1%n2 != 0){
        printf("The matrix can not be divided!\n");
        return counter;
    } else { //The matrix can be divided

        //The approach is as following: the matrix is divided into sub-lines, and each line is divided into sub=columns
        int li= m1/m2 , cl = n1/n2, Lmin= 1, Lmax = li, Cmin, Cmax;

        //now we got the coordinates, let's print the sub matrix
        int i=1;
        //divide
        while(Lmax<=m1){
            Cmin=1;
            Cmax=cl;
            while(Cmax <= n1){
                printf("Matrix %d: \n", i);
                i++;
                counter += extractMatrix(matrix, Lmin, Cmin, Lmax, Cmax);
                printf("\n");
                Cmin+=cl; Cmax+=cl;
            }
            Lmin+=li; Lmax+=li;
        }

    }

    return counter;
}

//Task 5:
//*********************************** SUM MATRICES ***************************************//

int sumMatrices(Line* matrix1, int m, int n){
    //the approach will be in this way:
    //We have matrix1 and matrix 2. we pick the nodes from matrix2 one by one and then:
        //1- if a node with the same coordinates does not exist in matrix1:
            //use insertColumnNode() to insert this node in matrix1
        //2- otherwise:
            //a node with the same coordinates exist, so we sum their values, BUT:
                //if the sum is a zero then we should remove the node

    Line *matrix2, *P1, *P2;
    Node2 *Q1, *Q2, *tmp;

    int numberOfMatrices, counter=0;
    printf("\nHow many matrices to add to the first matrix: ");
    scanf("%d", &numberOfMatrices);

    for(int i=0; i<numberOfMatrices; i++){
        printf("\nCreating matrix %d: \n", i+2);
        createMatrix(&matrix2, m, n);

        printf("\n\nThis is matrix %d: \n\n", i+2);
        showMatrix(matrix2, m, n);

        P2=matrix2;
        while(P2!=NULL){
            counter++;
            Q2=firstColumn(P2);

            while(Q2!=NULL){
                counter++;
                if( nodeExists(matrix1, lineNumber(P2), columnNumber(Q2), &tmp) ){ //the tmp parameter is only a placeholder for the function to run, it won't be used here

                    //a node with the same coordinates exists in matrix1
                    counter+= addValue(matrix1, columnValue(Q2), lineNumber(P2), columnNumber(Q2));

                } else {
                    //a node with the same coordinates does not exist, so it will be inserted in matrix1
                    if(!lineExists(matrix1, lineNumber(P2))){

                        createLineNode(&P1, lineNumber(P2));
                        counter+= insertLineNode(&matrix1, P1);
                    }

                    //create a node identical to Q2
                    createColumnNode(&Q1, columnValue(Q2), columnNumber(Q2));

                    //insert the node
                    counter+= insertColumnNode(matrix1,lineNumber(P2), Q1);
                }

                Q2=nextColumn(Q2);
            }

            P2=nextLine(P2);
        }

        // now matrix1 contains the  result of the sum
        // matrix2 will be removed
        counter+= deleteMatrix(&matrix2);
    }

    printf("\nThis is the final result of the sum: \n");
    counter+= showMatrix(matrix1, m, n);

    return counter;
}

//Task 6: Multiplication
//*********************************** SUM MATRICES ***************************************//

//A: multiply a matrix by a vector
int multiplyMatrixVector(Line* matrix, Line* vector, int m, int n){
    //create a matrix of size m*1

    Line *result=NULL, *P1=matrix, *P2, *tmpL;
    Node2 *Q1, *tmpC;
    int value, counter=0;

    if(matrix!=NULL && vector!=NULL){
        while(P1!=NULL){
            Q1=firstColumn(P1);
            value=0;
            P2=vector;

            while(Q1!=NULL && P2!=NULL){

                if(columnNumber(Q1) == lineNumber(P2)){
                    value+=columnValue(Q1) * columnValue(firstColumn(P2));
                    Q1=nextColumn(Q1);
                    P2=nextLine(P2);
                } else if(columnNumber(Q1) < lineNumber(P2)){
                    Q1=nextColumn(Q1);
                } else {
                    P2=nextLine(P2);
                }

                counter++;
            }

            if(value!=0){
                //create a line node for the new non null value
                createLineNode(&tmpL, lineNumber(P1));
                counter+= insertLineNode(&result, tmpL);

                //create a column node to store the value
                createColumnNode(&tmpC, value, 1);
                counter+= insertColumnNode(result, lineNumber(tmpL), tmpC);
            }
            P1=nextLine(P1);
            counter++;
        }

    }

    counter+= showMatrix(result, m, 1);
    return counter;
}


//B: multiply a matrix by a matrix
int multiplyMatrixMatrix(Line *matrix1, Line* matrix2, int m1, int n1, int m2, int n2){

    Line *result=NULL, *P1=matrix1, *P2, *tmpL;
    Node2 *Q1, *Q2, *tmpC;
    int value, i=0, min=1, found, size, nonNullColumns[n1], counter=0;

    // If one of the matrices is already null, the result is null
    if(matrix1==NULL || matrix2 == NULL)
        goto END;

    //1- I will look up the non null columns in the matrix
    //The reason for doing this is to avoid passing through null columns multiple times during multiplication.
    //The idea is that I will use a min variable, initialized to 1, and then increment it to the next available column value
    //then going until reaching the highest available column value. Therefore I will be only multiplying with non null columns

    int tmp=1;
    do{
        min=tmp; //we start with min=1
        tmp=n2;
        P2=matrix2;
        found=0; //boolean variable
        while(P2!=NULL){ //looking for non null columns in each line
            Q2=firstColumn(P2);

            //printf("This is min: %d\n", min);
            while(Q2!=NULL){

                if(columnNumber(Q2) == min){ //non null column found!
                    found=1;
                }

                if(columnNumber(Q2) > min && columnNumber(Q2) <= tmp){
                    tmp=columnNumber(Q2); //updating tmp with a value that is directly greater than "min" but less than the previous value,
                                 //which will give us the value of the next min!
                    //printf("This is tmp: %d\n", tmp);
                }
                Q2=nextColumn(Q2);
                counter++;
            }

            P2=nextLine(P2);
            counter++;
        }
        if(found){
            //storing the number of the non null column
            nonNullColumns[i]=min;
            i++;
        }
    }while(min!=tmp); //min and tmp can only be equal didn't change during the iteration, which means that we reached the last column

    size=i; //the size of the vector nonNULLColumns
    //now, we have a vector containing the non null columns of matrix2

    //2- starting the multiplication:
    //I will go through the column nodes Q2 of matrix2 at first, and for each node I find, I multiply it by the corresponding Q1
    //and add the result to the variable "value". After getting the final value of the multiplication of the column by the line, if
    //the value is non null then I will create a node in the matrix result which has the coordinates of the multiplied line*column

    for(i=0; i<size; i++){
        P1=matrix1;

        while(P1!=NULL){
            value=0;
            Q1=firstColumn(P1);
            P2=matrix2;

            while(P2!=NULL){
                if(nodeExists(matrix2, lineNumber(P2), nonNullColumns[i], &Q1)){
                    if(nodeExists(matrix1, lineNumber(P1), lineNumber(P2), &Q2)){
                        value+=columnValue(Q1) * columnValue(Q2);
                    }
                }

                P2=nextLine(P2);
                counter++;
            }

            if(value!=0){
                if(!lineExists(result, lineNumber(P1))){
                    createLineNode(&tmpL, lineNumber(P1));
                    counter+= insertLineNode(&result, tmpL);
                }

                createColumnNode(&tmpC, value, nonNullColumns[i]);
                counter+= insertColumnNode(result, lineNumber(P1), tmpC);

            }

            P1=nextLine(P1);
            counter++;
        }


    }
END:
    counter+= showMatrix(result, m1, n2);
    return counter;
}

//Task7: create the transposed matrix from the original matrix:
//*********************************** SUM MATRICES ***************************************//

int transpose(Line* matrix, int lines, int columns){

    Line *P1=matrix, *P2, *transposed=NULL;
    Node2 *Q1, *Q2;
    int counter=0;

    //in this function we do not necessarily have to pay attention to null values

    while(P1!=NULL){
        Q1=firstColumn(P1);

        while(Q1!=NULL){

            if(!lineExists(transposed, columnNumber(Q1))){
                //the line does not exist, so create it
                createLineNode(&P2, columnNumber(Q1));
                counter+= insertLineNode(&transposed, P2);
            }

                createColumnNode(&Q2, columnValue(Q1), lineNumber(P1));
                counter+= insertColumnNode(transposed, columnNumber(Q1), Q2);

            Q1=nextColumn(Q1);
            counter++;
        }

        P1=nextLine(P1);
        counter++;
    }

    counter+= showMatrix(transposed, columns, lines);
    return counter;
}

//Task8: logical operations
//*********************************** LOGICAL OPERATIONS ***************************************//

int logicalOperationMatrix(Line* matrix1, Line* matrix2, int m, int n){

    Line *P1, *P2=matrix2;
    Node2 *Q1, *Q2, *tmp, *tmp2;
    int counter=0;

    int oper; // The logical operator will be referenced to by a number
    printf("\nChoose the logical operation(Enter the number corresponding to the operation): \n");
    printf("1: NEGATION \n2: AND \n3: OR \n4: XOR\n");
    printf("Operation: ");
    scanf("%d", &oper);

    switch(oper){

    case 1: //NRGATION

        printf("This is the negated matrix: \n");
        counter+= negateMatrix(matrix1, m, n);
        break;

    case 2: // AND

        P1=matrix1;

        while(P1!=NULL){
            Q1=firstColumn(P1);

            while(Q1!=NULL){
                tmp=Q1; //I will use tmp to avoid problems after deleting a node

                Q1=nextColumn(Q1);
                counter++;
                if(nodeExists(matrix2, lineNumber(P1), columnNumber(tmp), &tmp2)){

                    counter+= performLogicalOperation(matrix1, columnValue(tmp2), lineNumber(P1), columnNumber(tmp), 2);

                } else {
                    removeColumnNode(&matrix1, lineNumber(P1), columnNumber(tmp));

                }

            }

            P1=nextLine(P1);
            counter++;
        }

        counter+= showMatrix(matrix1, m, n);
        break;

    default: // OR, XOR
        while(P2!=NULL){
            Q2=firstColumn(P2);

            while(Q2!=NULL){

                if( nodeExists(matrix1, lineNumber(P2), columnNumber(Q2), &tmp) ){

                    performLogicalOperation(matrix1, columnValue(Q2), lineNumber(P2), columnNumber(Q2), oper);

                } else {

                        if(!lineExists(matrix1, lineNumber(P2))){

                            createLineNode(&P1, lineNumber(P2));
                            counter+= insertLineNode(&matrix1, P1);
                        }

                        createColumnNode(&Q1, columnValue(Q2), columnNumber(Q2)); //the node is identical to Q2, because x OR 0 = x, XOR 0 = X
                        counter+= insertColumnNode(matrix1,lineNumber(P2), Q1);
                }

                Q2=nextColumn(Q2);
                counter++;
            }

            P2=nextLine(P2);
            counter++;
        }

        counter+= showMatrix(matrix1, m, n);
        break;

    }

    return counter;
}
