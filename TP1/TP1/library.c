#include <stdio.h>
#include <stdlib.h>
#include "library.h"

//Task 1:


void createMatrix(Line** head, int m, int n){ //nota: reverify the changing from local to global size variables (m1 n1)
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
            scanf("%d", &value); // reading the value to insert
            if(value==0){
                continue;
            }

            cell=(Node2* )malloc(sizeof(Node2)); //create a cell in the line
            //initializing the node
            cell->val=value;
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

    //checking if a line is empty

    //To work on -> here

    matrix= *head;
    P=matrix;

    while(matrix!=NULL){
        if(matrix->first==NULL){
            P->next=matrix->next;
            free(matrix);
        }
        P=matrix;
        matrix=matrix->next;
    }
} //END FUNCTION


//Task 2:
//to be completed: empty line (verify the validity of printNullLine) and zeros at the end of the line
void printNullLine(int number, int columns){ //Used to print the NULL lines
        for(int j=1; j<columns; j++){
            printf("0 ");
        }
        printf("\n");
}

void printZeros(int number){
    for(int i=1; i<number; i++){
        printf("0 ");
    }
}


//nota: do not mess with columns variable, because you will need to show matrices of different sizes
//nota: the loop will remain a while loop, because you won't necessarily do m1 or n1 iteration(because of unallocated null nodes!)
void showMatrix(Line* matrix, int columns){
    Node2 *cell;
    int difference; //to calculate difference between two lines or columns
    printf("\n"); //Auxiliary line jump
    while(matrix!=NULL){
        cell=matrix->first; //Head of the line

        while(cell->next!=NULL){ //The problem is with the size, so do we always need a size variable
            printf("%d ", cell->val);
            difference=(cell->next->col) - cell->col;
            if(difference!=1){
                printZeros(difference);
            }
            cell=cell->next;
        }
        printf("%d",cell->val); //printing the last element
        printf("\n");
        matrix=matrix->next;
    }
}

//Task 3:
//Here I will create a new matrix and keep the original

Line* extractMatrix(Line* matrix, int L1, int C1, int L2, int C2){
    Line *P1, *P2, *tmp1, *newMatrix;
    Node2 *Q1, *Q2, *tmp2;
    int i=1, j=1;

    newMatrix=(Line* )malloc(sizeof(Line)); //allocation of a temporary node
    P1=matrix;
    tmp1=newMatrix;

    //finding the starting line
    while(P1->number < L1){
        P1=P1->next; //advancing in lines until finding the line L1
    }

    while(P1->number <= L2){ //from L1 to L2
        P2=(Line* )malloc(sizeof(Line));
        P2->number=i; //updating the line number of newMatrix
        P2->first=NULL;
        tmp1->next=P2;
        tmp1=P2;

        Q1=P1->first;
        while(Q1->col < C1){    //Finding the starting cell for each line
            Q1=Q1->next; //advancing in columns until finding the column C1
        }

        while(Q1->col <= C2){ //from C1 to C2
            Q2=(Node2* )malloc(sizeof(Node2));
            Q2->val=Q1->val;
            Q2->col=j;

            if(P2->first==NULL){
                P2->first=Q2;
                tmp2=Q2;
            } else {
                tmp2->next=Q2;
                tmp2=Q2;
            }
            j++;
            Q1=Q1->next;
            if(Q1==NULL){
                break;
            }
        }

        Q2->next=NULL; //Here!

        i++;
        P1=P1->next;
        if(P1==NULL){
            break;
        }
    }
    P2->next=NULL;
    tmp1=newMatrix;
    newMatrix=newMatrix->next;
    free(tmp2);
    return newMatrix;
}

//Task 4:
//Waiting for an answer from the teacher for more clarity
//divideMatrix

//Task 5:
//Do I have to keep the original matrices or use matrix1 as a destination?
//I will use matrix1 as a destination at the moment

void sumMatrix(Line* matrix1, Line* matrix2){
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

