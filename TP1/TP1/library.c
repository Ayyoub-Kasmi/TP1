#include <stdio.h>
#include <stdlib.h>
#include "library.h"


//Task 1:


void createMatrix(FILE *file, Line** head, int m, int n){ //nota: reverify the changing from local to global size variables (m1 n1)
    //n and m represent the size of the m*n matrix;
    int value; //used to read values to fill the matrix
    Line *matrix, *P, *Q;
    Node2 *cell, *tmp;

    for(int i=1; i<=m; i++){ //for each line
        P=(Line* )malloc(sizeof(Line)); //create the node of the line

        //initializing the node
        P->number=i; //assigning the line number to it
        P->next=NULL;
        P->first=NULL;

        if(i==1){
            matrix=P; //This is the head of the whole matrix
            *head=matrix;
            Q=P; //The first value of Q will be the head
        } else {
            Q->next=P;
            Q=P;
        }

        for(int j=1; j<=n; j++){ //for each column
            printf("Enter the value of [%d][%d]: ", i, j);
            fscanf(file, "%d", &value); // reading the value to insert
            if(value==0){
                continue;
            }

            cell=(Node2* )malloc(sizeof(Node2)); //create a cell in the line
            //initializing the node
            cell->val=value;
            cell->col=j;
            cell->next=NULL;

            //decide whether to link the node to a Line node or a node existing before it
            if(P->first==NULL){ //if the line has no element
                P->first=cell;
                tmp=cell;
            } else {
                tmp->next=cell;
                tmp=cell;
            }
        } //END FOR LOOP (j)
    } //END FOR LOOP (i)


    //removing if a line is empty
    //To work on -> here

    matrix= *head;
    P=*head;


    //You idiot: you must firstly verify that the beginning of the matrix is not null, then you verify the middle lines
    while(matrix!=NULL){
        if(matrix->first==NULL){
                //printf("is the head null? %d\n", matrix->first==NULL);
                //printf("Here is the pointer to the next of the current head so: %p", matrix->next->first);
            if(matrix== *head){ //this is the case of null lines in the beginning
                *head=matrix->next; //The next line become the head
                //printf("Here is the col value of head: %d \n", (*head)->number);
                P=*head;
                free(matrix);
                matrix=P;
                //in this case I'm supposed to move matrix back to P
            } else { //this is the case of null lines in the middle
                P->next=matrix->next;
                free(matrix);
                matrix=P->next;
                //in this case I'm supposed to move matrix to P->next
            }
            //printf("The value of matrix before delete: %d\n", matrix->number);
            //matrix=P->next; //your mistake is here: if you have two consecutive null lines then you will only free the first one
                            //and your matrix will immediately move to the 3rd line, while P will point to the 2nd line which is
                            //still null! so deal with starting null lines first then the middle and ending ones
            //matrix=P; //this step is temporary to fix the above note, I moved matrix to P
        } else { //if the line is not null then we advance P and matrix normally
            P=matrix;
            matrix=matrix->next;
        }
    }
    //here ends the function
    //printf("The current head:")

    //matrix->next=NULL; //to avoid problems
} //END FUNCTION


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
    Line *P;
    Node2 *cell;
    int dif; //to calculate difference between two lines or columns: dif1 for lines, dif2 for columns
    printf("\n"); //Auxiliary line jump

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
    if(matrix->number>L2){
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
        //We will start with the normal case

        //say we divided the matrix into some m lines, now we print column divisions for each line then we move to
        //the next line partition

        //we will need parameters to know in which partition we are
        int Lmin= 1, Lmax = m2, Cmin, Cmax;  //later on, we increment each parameter by m1 or n1

        //now we got the coordinates, let's print the sub matrix
        int i=1;
        while(Lmax<=m1){
            Cmin=1;
            Cmax=n2;
            while(Cmax <= n1){
                printf("Matrix %d: \n", i);
                i++;
                extractMatrix(matrix, Lmin, Cmin, Lmax, Cmax);
                printf("\n");
                Cmin+=n2; Cmax+=n2;
            }
            Lmin+=m2; Lmax+=m2;
        }

    }
}

//Task 5:
//Do I have to keep the original matrices or use matrix1 as a destination?
//I will use matrix1 as a destination at the moment

void sumMatrix(Line* matrix1, Line* matrix2, int m, int n){
    Line *P1, *P2;
    Node2 *Q1, *Q2;

    P1=matrix1;
    P2=matrix2;

    while(P1!=NULL){
        Q1=P1->first;
        Q2=P2->first;

        while(Q1!=NULL){
            Q1->val+=Q2->val;
            //for the case of zero, here, if I find the sum is zero then this node must be removed!

            Q1=Q1->next;
            Q2=Q2->next;
        }

        P1=P1->next;
        P2=P2->next;
    }
}
//Task 6: Multiplication

//A: multiply a matrix by a vector
//void multiplyMatrixVector(Line* matrix1)

//B: multiply a matrix by a matrix
void createNullMatrix(Line** head, int m, int n){
    /*This function will be identical to createMatrix, the only difference is that values will be automatically
    zeros instead of inserting values from the user *///n and m represent the size of the m*n matrix;

    //you used this function for multiplication operation
    Line *matrix, *P, *Q;
    Node2 *cell, *tmp;

    for(int i=1; i<=m; i++){ //for each line
        P=(Line* )malloc(sizeof(Line)); //create the node of the line

        //initializing the node
        P->number=i; //assigning the line number to it
        P->next=NULL;
        P->first=NULL;

        if(i==1){
            matrix=P; //This is the head of the whole matrix
            *head=matrix;
            Q=P; //The first value of Q will be the head
        } else {
            Q->next=P;
            Q=P;
        }

        for(int j=1; j<=n; j++){ //for each column

            cell=(Node2* )malloc(sizeof(Node2)); //create a cell in the line
            //initializing the node
            cell->val=0;
            cell->col=j;
            cell->next=NULL;

            //decide whether to link the node to a Line node or another node before it
            if(P->first==NULL){ //if the line has no element
                P->first=cell; // the problem here is that Q is of type Node1 and not Node2 so Q.first can't be used with "cell"
                tmp=cell;
            } else {
                tmp->next=cell;
                tmp=cell;
            }
        } //END FOR LOOP (j)
    } //END FOR LOOP (i)

}

Line* multiplyMatrixMatrix(Line *matrix1, Line* matrix2, int m1, int n1, int m2, int n2){
    //idea: add a c file as a readme file where you explain the method used to solve this problem
    Line *result, *tmp, *P1=matrix1, *P2;
    Node2 *cell ,*Q1, *Q2;

    createNullMatrix(&result, m1, n2); //to create a matrix of zeros
    //each element in a matrix1 line is multiplied by a matrix2 line corresponding his column number

    /* old code:

    tmp=result;
    while(P1!=NULL){ //"parcour" the matrix1 lines
        Q1=P1->first; //the first element of the line of matrix1
        //cell=tmp->first;
        while(Q1!=NULL){ //going through the columns of the line
            cell=tmp->first; //cell is the current cell where the result of the multiplication is stored
            P2=matrix2;
            Q2=P2->first; //yes
            while(Q2!=NULL){
                cell->val+=(Q1->val)*(Q2->val);
                printf("Here is the values of Q1, Q2, cell: %d %d %d\n",Q1->val, Q2->val, cell->val);
                cell=cell->next;
                Q2=Q2->next;
            }

            Q1=Q1->next; //yes
            P2=P2->next; //yes
        }

        tmp=tmp->next;
        P1=P1->next;
    } */

    //new code: 3/24/2022
    tmp=result;
    while(P1!=NULL){
        Q1=P1->first;
        P2=matrix2;

        while(Q1!=NULL){
            Q2=P2->first;
            cell=tmp->first;

            while(Q2!=NULL){
                //printf("Hello world!\n");
                //printf("This is the value of Q2: %d\n\n", Q2->val);
                cell->val+=(Q1->val)*(Q2->val);
                Q2=Q2->next;
                cell=cell->next;
            }
            printf("Horray!\n");
            P2=P2->next; //Q2 is null, let's multiply the next Q1 with the next line P2
            Q1=Q1->next;

        }

        P1=P1->next; //advancing to the next line of matrix1
        tmp=tmp->next; //advancing to the next line of result
    }

    return result;
}

