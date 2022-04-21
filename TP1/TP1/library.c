#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"

//To be completed:
//1-abstract machine
//2-counter for nodes
//3-decoration


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
    *node=(Line* )malloc(sizeof(Line));

    (*node)->number=i;
    (*node)->first=NULL;
    (*node)->next=NULL;
}

void createColumnNode(Node2 **node, int value, int column){
    *node=(Node2 *)malloc(sizeof(Node2));

    (*node)->val= value;
    (*node)->col= column;
    (*node)->next= NULL;
}

int lineExists(Line* matrix, int line){
    //the function searches for a line in the matrix (by its number) and returns a pointer to it if it exists

    //will be used in the transposing function
    Line* P=matrix;

    while(P!=NULL){
        if(P->number == line){
            return 1;
        }
        P=P->next;
    }

    return 0;

}

void insertLineNode(Line** matrix, Line* node){
    Line *P=*matrix, *tmp;

    //if the matrix is empty
    if(*matrix == NULL){
        *matrix=node;
        return; //stopping the function from continuing
    }

    if(node->number < P->number){
        *matrix=node;
        node->next = P;
        return;
    }

    while(P->next != NULL && P->next->number < node->number){
        //firstly I look up the correct position to insert the node
        P=P->next;
    }
    tmp=P->next; //tmp=NULL
    P->next = node; //
    node->next = tmp;
}

void insertColumnNode(Line *matrix, int line, Node2 *node){
    //this function will be used in the transpose function
    //it will insert a column node in a line



    while(matrix->number != line){
        matrix=matrix->next;
    }

    Node2 *Q = matrix->first, *tmp;
    //Q is now the first column in this line

    //if the line is a newly created one (so it is empty)
    if(Q==NULL){
        matrix->first=node;
        return; //to stop the function from continuing
    }

    if(node->col < Q->col){ //the node will become the first column, it will be linked to tmp
        matrix->first = node;
        node->next = Q;
        return; //to stop the function from continuing
    }


    while(Q->next != NULL && Q->next->col < node->col){
        //firstly I look up the correct position to insert the node
        Q=Q->next;
    }
    tmp=Q->next;
    Q->next = node;
    node->next = tmp;

}

void removeNullLines(Line **matrix){
    Line *P1=*matrix, *P2;
    while(P1!=NULL){
        if(P1->first!=NULL){
            P2=P1;
            P1=P1->next;

        } else { //if the line is not null then we advance P1 and P2 normally

            if(P1 == *matrix){ //the null line is the first line
                *matrix=P1->next; //The next line becomes the head
                free(P1);
                P1=*matrix;

            } else { //the null line is in the middle or the end
                P2->next=P1->next;
                free(P1);
                P1=P2->next;
            }
        }
    }
}

void removeColumnNode(Line** matrix, int line, int column){
    //the node is supposed already existent in the matrix
    Line *P=(*matrix), *P2;
    Node2 *Q, *previous;

    while(P->number != line){
        P2=P;
        P=P->next;
    }

    Q=P->first;

    while(Q->col != column){
        previous=Q;
        Q=Q->next;
    }

    if(Q==P->first){
        //Q is the first node in the line
        P->first = Q->next;
    } else {
        previous->next = Q->next;
    }
    free(Q);
    //what if the node is in the last line
    //to fix later

    if(P->first == NULL){
        if(P == *matrix){
            *matrix = P->next;

        } else {
            P2->next = P->next;
        }
        free(P);
    }
}

void deleteMatrix(Line **matrix){
    Line *P1=*matrix, *P2;
    Node2 *Q1, *Q2;

    while(P1!=NULL){
        Q1=P1->first;

        while(Q1!=NULL){
            Q2=Q1;
            Q1=Q1->next;
            free(Q2);
        }

        P2=P1;
        P1=P1->next;
        free(P2);
    }
}

int min(int a, int b){
    return a<b ? a : b;
}

void addValue(Line* matrix, int value, int line, int column){
    //the node is supposed already existent in the matrix
    Line *P=matrix;
    Node2 *Q, *previous;

    while(P->number != line){
        P=P->next;
    }

    Q=P->first;

    while(Q->col != column){
        previous=Q;
        Q=Q->next;
    }

    Q->val += value;
    if(Q->val == 0){
        if(Q==P->first){
            //Q is the first node in the line
            P->first = Q->next;
        } else {
            previous->next = Q->next;
        }

        free(Q);
    }
}

int nodeExists(Line* matrix, int line, int column, Node2** target){
    //this function will be used in the sum function
    //line and column represent the coordinates of the node
    Line *P=matrix;
    Node2 *Q;
    *target=NULL;

    //step1: checking if the line exists
    while(P!=NULL && P->number < line){
        //advancing until finding or passing the correct line
        P=P->next;
        if(P==NULL){
            return 0;
        }
    }

    if(P->number != line){ //if we passed the correct line
        return 0;
    }

    Q=P->first;
    while(Q!=NULL && Q->col < column){
        //advancing until finding or passing the correct column
        Q=Q->next;
        if(Q==NULL){
            return 0;
        }
    }

    if(Q->col == column){
            *target=Q;
        return 1;
    } else {return 0;};

}

//Task 1:


void createMatrix(FILE *file, Line** matrix, int m, int n){ //nota: reverify the changing from local to global size variables (m1 n1)
    //n and m represent the size of the m*n matrix;
    int value; //used to read values to fill the matrix
    Line *P;
    Node2 *Q;

    *matrix=NULL;

    for(int i=1; i<=m; i++){ //for each line
        createLineNode(&P, i);
        insertLineNode(matrix, P);

        for(int j=1; j<=n; j++){ //for each column
            printf("Enter the value of [%d][%d]: ", i, j);
            fscanf(file, "%d", &value); // reading the value to insert
            if(value==0){
                continue;
            }

            createColumnNode(&Q, value, j);
            insertColumnNode(*matrix, i, Q);

        }
    }

    removeNullLines(matrix);

}


//Task 2:
//to be completed: empty line (verify the validity of printNullLine) and zeros at the end of the line
void printNullLines(int number, int columns){ //Used to print the NULL lines
    for(int i=0; i<number; i++){
        for(int j=0; j<columns; j++){
            printf("%3d ", 0);
        }
        printf("\n");
    }
}

void printZeros(int number){
    for(int i=1; i<number; i++){
        printf("%3d ",0);
    }
}


//nota: do not mess with columns variable, because you will need to show matrices of different sizes
//nota: the loop will remain a while loop, because you won't necessarily do m1 or n1 iteration(because of unallocated null nodes!)
void showMatrix(Line* matrix, int lines, int columns){
    //you might consider checking if matrix is null, if yes then you will only print null lines
    Line *P;
    Node2 *cell;
    int dif; //to calculate difference between two lines or columns: dif1 for lines, dif2 for columns
    printf("\n"); //Auxiliary line jump

    if(matrix == NULL){
        printNullLines(lines, columns);
        return; //stopping the function from executing the next piece of code
    }

    //check if there're null line before the first line
    if(matrix->number!=1){
        printNullLines(matrix->number -1 ,columns);
    }

    while(matrix!=NULL){
        cell=matrix->first; //Head of the line

        //check if there're zeros before the line's head
        if(cell->col!=1){
            printZeros(cell->col);
        }
        //printing the zeros in the middle of the line
        while(cell->next!=NULL){ //The problem is with the size, so do we always need a size variable
            printf("%3d ", cell->val);
            dif=(cell->next->col) - cell->col;
            if(dif!=1){
                printZeros(dif);
            }
            cell=cell->next;
        }
        printf("%3d ",cell->val); //printing the last element

        //checking if there're zeros after the last element
        if(cell->col!=columns){
            printZeros(columns - cell->col +1);
        }
        printf("\n");

        //checking the null lines in the middle
        if(matrix->next!=NULL){
            dif=(matrix->next->number)-matrix->number;
            if(dif!=1){
                printNullLines(dif-1, columns);
            }
        }
        P=matrix; //saving the old value of matrix in P
        matrix=matrix->next;
    }

    //checking if there're null lines in the end
    if(P->number!=lines){
            printNullLines(lines - P->number, columns);
        }
}

//Task 3:

void extractMatrix(Line* matrix, int L1, int C1, int L2, int C2){
    Line *P1;
    Node2 *Q1, *Q2;
    int dif;

    //showing a a sub matrix
    //here we have to consider 3 details: 0 before, 0 within, 0 in the end

    /* solution for lines [i]:
    //first step is to check with i until line.number>=L1
    //check if there're null lines before the current i
    //then print the lines normally (including null lines) until (line->next.number)>L2
    //then verify if there're still null lines remaining

    */

    //if every single line is already null
    if(matrix==NULL){
        printNullLines(L2-L1+1, C2-C1+1);
        return; //to stop the function from continuing to the rest of the code
    }

    while(matrix->number<L1){
        //advancing until reaching the beginning line
        matrix=matrix->next;
    }

    //checking if there're null lines to print before the current line
    if(matrix->number > L1){
        printNullLines(matrix->number - L1, C2-C1+1);
    }

    while(matrix!=NULL && matrix->number <= L2){ //or while matrix->number <= L2

        //<--- printing columns from the current line --->
        Q1=matrix->first; //as the line is non null, there's one element at least

        while(Q1!=NULL && Q1->col < C1){
            //advancing until finding the starting column
            Q1=Q1->next;
        }
        if(Q1==NULL){
            printZeros(C2-C1+2);
            P1=matrix; //saving the previous value in P1
            matrix=matrix->next;
            continue;
        }

        //checking if there're zeros to print before the current column
        if(Q1->col > C1){
            printZeros(Q1->col - C1 +1);
        }

        //printing the middle elements
        //for the zeros to be in the middle, the current node and the next node must be both within C1-C2 (goto line 282)
        while(Q1!=NULL && Q1->col <= C2){
            printf("%3d ", Q1->val);

            if(Q1->next!=NULL && Q1->next->col <= C2){
                dif=(Q1->next->col) - Q1->col; //here is a problem when the next is null
                if(dif!=1){
                    printZeros(dif);
                }
            };
            Q2=Q1; //saving the older value of Q1 in Q2 if Q1 moves to
            Q1=Q1->next;

        }

        //checking if there're remaining zeros to the end of the column
        if(Q2!=Q1 && Q2->col < C2){
            printZeros(C2 - Q2->col +1);
        }
        printf("\n");
        //<--- the line is printed --->

        //checking if there're null lines in the middle
        if(matrix->next!=NULL && matrix->next->number <= L2){ //the next line is less than the max line
            dif=(matrix->next->number)-matrix->number;
            if(dif!=1){
                printNullLines(dif-1, C2-C1+1);
            }
        }

        P1=matrix; //saving the previous value in P1
        matrix=matrix->next;
    }

    //checking if there're null lines remaining
    if(P1->number < L2){
        printNullLines(L2 - P1->number, C2-C1+1);
    }
    /* solution for columns [j]:
    //first step is to check with j until cell.col>=C1
    //then I check if I have no zeros before the current j
    //then I print the line normally (including zeros) until I reach (cell.col->next)>C2
    //then I verify if I have zeros remaining to the end (the end here is C2 and not n1)
    */
}

//Task 4:

void divideMatrix(Line* matrix, int m1, int n1, int m2, int n2){
    //verifying if the matrix's size is dividable by m and n
    if(m1%m2 != 0 || n1%n2 != 0){
        printf("The matrix can not be divided!\n");
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
                extractMatrix(matrix, Lmin, Cmin, Lmax, Cmax);
                printf("\n");
                Cmin+=cl; Cmax+=cl;
            }
            Lmin+=li; Lmax+=li;
        }

    }
}

//Task 5:

void sumMatrices(FILE *file, Line* matrix1, int m, int n){
    //the approach will be in this way:
    //I have matrix1, I get matrix 2. I will pick the nodes from matrix2 line by line and then, from their coordinates, I will
    //decide:
        //1- if a node with the same coordinates does not exist in matrix1:
            //use the previous insertColumnNode to add this node to matrix1
        //2- otherwise:
            //a node with the same coordinates exist, so we sum their values, BUT:
                //if the sum is a zero then we should remove the node

    Line *matrix2, *P1, *P2;
    Node2 *Q1, *Q2, *tmp;

    int counter;
    printf("\nHow many matrices to add?: ");
    scanf("%d", &counter);
    printf("This is the counter: %d\n\n", counter);
    counter=3;
    for(int i=0; i<counter; i++){
        printf("Creating matrix %d: \n", i+2);
        createMatrix(file, &matrix2, m, n);
        printf("\n\nThis is matrix %d: \n\n", i+2);
        showMatrix(matrix2, m, n);
        P2=matrix2;
        while(P2!=NULL){
            Q2=P2->first;

            while(Q2!=NULL){
                if( nodeExists(matrix1, P2->number, Q2->col, &tmp) ){ //nodeExists was changed here, check the modifications
                    //a node with the same coordinates exists in matrix1
                    //Now Q2 points to the new node
                    //I look up the node in matrix 1 and change its value
                    addValue(matrix1, Q2->val, P2->number, Q2->col);

                } else {
                    //a node with the same coordinates does not exist, so the current node will be added to matrix1
                    //verify that that the line exists, if it does not then create it
                    if(!lineExists(matrix1, P2->number)){

                        createLineNode(&P1, P2->number);
                        insertLineNode(&matrix1, P1);
                    }

                    //create a node identical to Q2
                    createColumnNode(&Q1, Q2->val, Q2->col);

                    //insert the node
                    insertColumnNode(matrix1,P2->number, Q1); //mistake: the line is supposed to be P1 and not P2. Change the function so that
                                              //it is possible to insert nodes using line numbers and not line address, because
                                              //P1 is not accessible in this case

                }

                Q2=Q2->next;
            }

            P2=P2->next;
        }

        //now matrix1 contains the sum
        //we remove matrix2
        deleteMatrix(&matrix2);
    }

    printf("\nThis is the final result of the sum: \n");
    showMatrix(matrix1, m, n);
}



//Task 6: Multiplication

//A: multiply a matrix by a vector

void multiplyMatrixVector(Line* matrix, Line* vector, int m, int n){
    //create a matrix of size m*1

    //I will use this function instead of using multiplyMatrixMatrix for the same purpose because this one is optimized
    Line *result=NULL, *P1=matrix, *P2, *tmpL;
    Node2 *Q1, *tmpC;
    int value;

    while(P1!=NULL){
        Q1=P1->first;
        value=0;
        P2=vector;

        //for optimization: check if vector is null or if matrix is null, to not do calculations at all and save time
        while(Q1!=NULL && P2!=NULL){

            if(Q1->col == P2->number){
                value+=Q1->val * P2->first->val;
                Q1=Q1->next;
                P2=P2->next;
            } else if(Q1->col < P2->number){
                Q1=Q1->next;
            } else {
                P2=P2->next;
            }

        }

        if(value!=0){
            //create a line node for the new non null value
            createLineNode(&tmpL, P1->number);
            insertLineNode(&result, tmpL);

            //create a column node to store the value
            createColumnNode(&tmpC, value, 1);
            insertColumnNode(result, tmpL->number, tmpC);
        }
        P1=P1->next;
    }

    showMatrix(result, m, 1);
}

//B: multiply a matrix by a matrix

void multiplyMatrixMatrix(Line *matrix1, Line* matrix2, int m1, int n1, int m2, int n2){
    //idea: add a c file as a readme file where you explain the method used to solve this problem

    Line *result=NULL, *P1=matrix1, *P2, *tmpL;
    Node2 *Q1, *Q2, *tmpC;
    int value, i=0, min=1, tmp, found, size, nonNullColumns[n1];

    //question: should I suppose that the sizes are correct?

    //I will only use the classical method of multiplication
    //I will do a complicated work here! so get ready for it

    //To add here: if one of the matrices is already null, the result is null
    //the following code will consider that both matrices are non null

    //1- I will look up the non null columns in the matrix and at the same time, the maximum non null column.
    //The reason for doing this is to avoid passing through null columns multiple times during multiplication.
    //The idea is that I will use a min variable, initialized to 1, and then increment it to the next available column value
    //(with skipping null columns!! using the tmp variable), then going until there's no higher column value available

    tmp=1;
    do{
        min=tmp; //we start with min=1
        tmp=n2;
        P2=matrix2;
        found=0; //boolean variable
        while(P2!=NULL){ //looking for non null columns in each line
            Q2=P2->first;

            //printf("This is min: %d\n", min);
            while(Q2!=NULL){

                if(Q2->col == min){ //non null column found!
                    found=1;
                }

                if(Q2->col > min && Q2->col <= tmp){
                    tmp=Q2->col; //updating tmp with a value that is directly greater than "min" but less than the previous value,
                                 //which will give us the value of the next min!
                    //printf("This is tmp: %d\n", tmp);
                }
                Q2=Q2->next;
            }

            P2=P2->next;
        }
        if(found){
            //storing the value of the non null
            nonNullColumns[i]=min;
            i++;
        }
    }while(min!=tmp); //min and tmp can only be equal didn't change during the iteration, which means that we reached the last column

    size=i; //the size of the vector nonNULLColumns

    //now, we have a vector containing the non null columns of matrix2
    //2- starting the multiplication:
    //I will go through the column nodes Q2 of matrix2 at first, and for each node I find, I multiply it by the corresponding Q1
    //and add the result to the variable value. After getting the final value of the multiplication of the column by the line, if
    //the value is non null then I will create a node in the matrix result which has the coordinates of the multiplied line*column

    for(i=0; i<size; i++){
        P1=matrix1;
        int k=1; //to delete

        while(P1!=NULL){
            value=0;
            Q1=P1->first;
            P2=matrix2;

            while(P2!=NULL){
                if(nodeExists(matrix2, P2->number, nonNullColumns[i], &Q1)){
                    if(nodeExists(matrix1, P1->number, P2->number, &Q2)){
                        //if(Q1->col == 3 && Q2->col == 2) printf("The product of %d and %d is: %d\n", Q1->val, Q2->val, Q1->val * Q2->val);
                        value+=Q1->val * Q2->val;
                    }
                }

                P2=P2->next;
            }

            if(value!=0){
                if(!lineExists(result, P1->number)){
                    createLineNode(&tmpL, P1->number);
                    insertLineNode(&result, tmpL);
                }

                createColumnNode(&tmpC, value, nonNullColumns[i]);
                insertColumnNode(result, P1->number, tmpC);

                //if(k== 2) printf("This is value: %d\n", value);
            }

            k++; //to delete, k represents the i-nth line of matrix1
            P1=P1->next;
        }


    }

    showMatrix(result, m1, n2);
}

//Task7: create the transposed matrix from the original matrix:


void transpose(Line* matrix, int lines, int columns){

    Line *P1=matrix, *P2, *transposed=NULL;
    Node2 *Q1, *Q2;

    //in this function we do not necessarily have to pay attention to null values

    //the plan is this:
    //1- using P and Q, I will pass by all the "existing" nodes in the matrix, to save effort
    //2- When I reach a node, check if there's a line in the new matrix having the same value of col of the current node
        //if the line exists
            //I will add the node to the line respecting the order of the existing nodes in the line (according to the col values)
            //attribute P.number to node.col
        //if the line does not exist
            //create a new line (insertion following the order) with the number equal to col value of the node
            //attribute P.number to node.col

    // I will need to insert a line node, and insert a column node

    //printf("Trial: show me matrix: %d\n", P1->first->col);
    while(P1!=NULL){ //passing through all the lines of the matrix
        Q1 = P1->first; //the first node of the existing line

        while(Q1!=NULL){ //going through the nodes of the current line

            //if there's a line with the value Q->col
            if(lineExists(transposed, Q1->col)){ //consider removing tmp from the function
                //the line exists and tmp has the pointer to the line

                //create a node
                createColumnNode(&Q2, Q1->val, P1->number);
                insertColumnNode(transposed, Q1->col, Q2);
            } else {
                //the line does not exist
                createLineNode(&P2, Q1->col);
                insertLineNode(&transposed, P2);

            }
                //to improve later: this part of creating the node is common between the two cases (whether or not the line exists)
                //so consider make it outside the condition
                createColumnNode(&Q2, Q1->val, P1->number);
                insertColumnNode(transposed, Q1->col, Q2);

            Q1=Q1->next;
        }

        P1=P1->next;
    }

    //now, the matrix "transposed" should be ready
    //I will only show it the current the time, I might consider change the type of the function to Line* and show the matrix
    //from the main

    showMatrix(transposed, columns, lines);
}

void logicalOperation(Line* matrix, int value, int line, int column, int oper){
    //make a logical operation on a node of coordinates [line, column]
    //the node is supposed already existent in the matrix

    Line *P=matrix;
    Node2 *Q, *previous;

    while(P->number != line){
        P=P->next;
    }

    Q=P->first;

    while(Q->col != column){
        previous=Q;
        Q=Q->next;
    }

    switch(oper){ //operations are: 1-negation 2-AND 3-OR 4-XOR
        case 1:
            Q->val = -Q->val;
            break;

        case 2:
            Q->val = Q->val & value;
            break;

        case 3:
            Q->val = Q->val | value;
            break;
        case 4:
            Q->val = Q->val ^ value; //verify the operator char
            break;
    }

    if(Q->val == 0){
        if(Q==P->first){
            //Q is the first node in the line
            P->first = Q->next;
        } else {

            previous->next = Q->next;
        }

        free(Q);
    }
}

void printOnes(int number){
    for(int i=1; i<number; i++){
        printf("%3d ",1);
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

void negateMatrix(Line* matrix, int lines, int columns){
    //you might consider checking if matrix is null, if yes then you will only print null lines
    Line *P;
    Node2 *cell;
    int dif; //to calculate difference between two lines or columns: dif1 for lines, dif2 for columns
    printf("\n"); //Auxiliary line jump

    if(matrix == NULL){
        printLinesOfOnes(lines, columns);
        return; //stopping the function from executing the next piece of code
    }

    //check if there're null line before the first line
    if(matrix->number!=1){
        printLinesOfOnes(matrix->number -1 ,columns);
    }

    while(matrix!=NULL){
        cell=matrix->first; //Head of the line

        //check if there're zeros before the line's head
        if(cell->col!=1){
            printOnes(cell->col);
        }
        //printing the zeros in the middle of the line
        while(cell->next!=NULL){ //The problem is with the size, so do we always need a size variable
            printf("%3d ", 0);
            dif=(cell->next->col) - cell->col;
            if(dif!=1){
                printOnes(dif);
            }
            cell=cell->next;
        }
        printf("%3d ",0); //printing the last element

        //checking if there're zeros after the last element
        if(cell->col!=columns){
            printOnes(columns - cell->col +1);
        }
        printf("\n");

        //checking the null lines in the middle
        if(matrix->next!=NULL){
            dif=(matrix->next->number)-matrix->number;
            if(dif!=1){
                printLinesOfOnes(dif-1, columns);
            }
        }
        P=matrix; //saving the old value of matrix in P
        matrix=matrix->next;
    }

    //checking if there're null lines in the end
    if(P->number!=lines){
            printLinesOfOnes(lines - P->number, columns);
        }
}

void logicalOperationMatrix(Line* matrix1, Line* matrix2, int m, int n){
    //the approach will be in this way:
    //I have matrix1, I get matrix 2. I will pick the nodes from matrix2 line by line and then, from their coordinates, I will
    //decide:
        //1- if a node with the same coordinates does not exist in matrix1:
            //use the previous insertColumnNode to add this node to matrix1
        //2- otherwise:
            //a node with the same coordinates exist, so we sum their values, BUT:
                //if the sum is a zero then we should remove the node

    Line *P1, *P2=matrix2;
    Node2 *Q1, *Q2, *tmp, *tmp2;

    int oper; //the operator of the logical operation will be referenced to by a number
    printf("\nChoose the logical operation(Enter the number corresponding to the operation): \n");
    printf("1: NEGATION \n 2: AND \n 3: OR \n 4: XOR\n");
    printf("Operation: ");
    scanf("%d", &oper);

    switch(oper){

    case 1:
        //The idea here is simple: I will use exactly the showMatrix function but in a reversed way: I print 0 if the node
        //exists, and 1 if the node does not exist

        printf("This is the negated matrix: \n");
        negateMatrix(matrix1, m, n);
        break;

    case 2:
        //the reason of separating this case from the other cases is because I will go through the nodes of matrix1 and not
        //matrix2, and that's because x&0=0
        P1=matrix1;

        while(P1!=NULL){
            Q1=P1->first;

            while(Q1!=NULL){
                tmp=Q1; //I will use it to avoid problems after deleting a node

                Q1=Q1->next;
                if(nodeExists(matrix2, P1->number, tmp->col, &tmp2)){

                    logicalOperation(matrix1, tmp->val, P1->number, tmp->col, 2);

                } else {
                    removeColumnNode(&matrix1, P1->number, tmp->col);

                }

            }

            P1=P1->next;
        }

        break;

    default: //case 3 and 4
        while(P2!=NULL){
            Q2=P2->first;

            while(Q2!=NULL){

                if( nodeExists(matrix1, P2->number, Q2->col, &tmp) ){ //nodeExists was changed here, check the modifications
                    //a node with the same coordinates exists in matrix1
                    //Now Q2 points to the new node
                    //I look up the node in matrix 1 and change its value
                    logicalOperation(matrix1, Q2->val, P2->number, Q2->col, oper);

                } else { // x && 0 = 0, so don't create a node for &&; x || 0 = x; so create a node with value=x
                    switch(oper){

                    case 3: //verify: x XOR 0 = x
                        if(!lineExists(matrix1, P2->number)){

                            createLineNode(&P1, P2->number);
                            insertLineNode(&matrix1, P1);
                        }

                        createColumnNode(&Q1, Q2->val, Q2->col); //the node is identical to Q2, because x OR 0 = x XOR 0 = X
                        insertColumnNode(matrix1,P2->number, Q1);
                        break;

                    } //End switch

                }

                Q2=Q2->next;
            }

            P2=P2->next;
        }
        break;

    }

    showMatrix(matrix1, m, n);
}
