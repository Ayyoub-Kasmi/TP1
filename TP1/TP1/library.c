#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "library.h"
typedef struct Maillon_vecteur{

      int val;
      int ligne;
      int colonne;
      struct Maillon_vecter *next;
    }Maillon_vecteur;

//***************************************************************************************************************************
void affiche_M_nule(int a,int b){
     int  k,h;
     for (k=1;k<=a;k++){
        for (h=1;h<=b;h++){
            printf("0 | ");
        }
        printf("\n");
     }
   }
//****************************************************************************************************************************
 // 1)Lecture d'une matrice et création de la liste
 void Lecture (Maillon_vecteur **tete,int li,int cl){
    Maillon_vecteur *p,*q;
    int i,j,n;
    *tete=NULL;
 for (i=1;i<=li;i++){ // begin for i
     for (j=1;j<=cl;j++){ // begin for j
     printf("T[%d,%d]=",i,j);
     scanf("%d",&n);
     if (n==0){
        continue;
     }
     else { //begin else
       q=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
       if(*tete==NULL){ // begin if tete==null
       p=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
        *tete=p;
       } // end if tete==null
       p->val=n;
       p->ligne=i;
       p->colonne=j;
       if (i==li && j==cl){
        p->next=NULL;
        free(q);
       }
       else {
        p->next=q;
       p=p->next;
       }
     } // end else
     } // end j
  } // end i
  }
//****************************************************************************************************************************
//2)Affichage d'une matrice

  void Afficher(Maillon_vecteur *tete,int l,int c){
    Maillon_vecteur *z;
    int i,j;
    if (tete==NULL){
   printf(" \n La matrice est nulle ! \n");
   affiche_M_nule(l,c);
   free(tete);
   }
   else {
        z=tete;
   for (i=1;i<=l;i++){
        for (j=1;j<=c;j++){
    if (z->ligne==i && z->colonne==j){
    printf("%d\t|",z->val);
    z=z->next;
    }
    else printf("0\t|");


    }
    printf("\n");
   }
   }

  }
  //****************************************************************************************************************************
  //3)Extraction d’une sous matrice
  void Extract(Maillon_vecteur *tete,int li,int cl){
   int ip,jp,id,jd,i,j;
   Maillon_vecteur *p;
  printf("donner le nemuro de la ligne de la premiere case : ");
   scanf("%d",&ip);
   printf("donner le nemuro de la colonne de la premiere case : ");
   scanf("%d",&jp);
   printf("donner le nemuro de la ligne de la derniere case : ");
   scanf("%d",&id);
   printf("donner le nemuro de la colonne de la derniere case : ");
   scanf("%d",&jd);
   // 3)Extraction d’une sous matrice
    if (tete==NULL){
       printf("l\'extraction est impossible car la matrice est nulle ! \n");
    }
    else { //begin else 1
    p=tete;
   if (jp>jd){ // petit if
    printf("l\'extraction est impossible ! \n");
   } // end petit if
   else { // begin else 2
   printf("L\'extraction de la sous matrice : \n");
   for (i=1;i<=li;i++){ //begin for i
    for (j=1;j<=cl;j++){ // begin for j
      if (i>=ip && i<=id && j>=jp && j<=jd)  {// begin if 1
       if (p->ligne==i && p->colonne==j){ // if a
        printf("%d\t|",p->val);
        } // end if a
        else { // else b
            printf("0\t|");
        } // end else b

      } // end if 1

       if (i==id && j==jd){  // begin if 2
      break;
      }  // end if 2

       if (p->ligne==i && p->colonne==j){ // if b
      p=p->next;
      } // end if b

    }// end for j
    printf("\n");
    if (i==id && j==jd)
        break;
   } // end for i
     } // end else 2
       } // end else 1
       }
  //****************************************************************************************************************************

