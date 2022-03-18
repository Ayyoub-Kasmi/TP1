#include <stdio.h>
#include <stdlib.h>
#include "library.h"

//Task 1:

void createMatrix(Line** head, int m, int n){
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
    //printf("This is my head: ", matrix->number);

    while(matrix!=NULL){
        if(matrix->first==NULL){
            P->next=matrix->next;
            //free(matrix);
        }
        P=matrix;
        matrix=matrix->next;
    }
} //END FUNCTION


//Task 2:
//to be completed: empty line (verify the validity of printNllLine) and zeros at the end of the line
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

