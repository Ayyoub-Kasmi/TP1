#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "library.h"

 typedef struct Maillon_vecteur{

      int val;
      int ligne;
      int colonne;
      struct Maillon_vecter *next;
    }Maillon_vecteur;

    //***************************   Menu !  ****************************************
    // 1)************ Lecture d'une matrice et création de la liste ****************
    // 2)************ Affichage d’une matrice **************************************
    // 3)************ Extraction d’une sous matrice*********************************
    // 4)************ Division d’une matrice en sous-blocs de taille égale**********
    // 5)************ Addition de deux ou plusieurs matrices.***********************
    // 6)************ Multiplication par vecteur, multiplication de deux matrices***
    // 7)************ Transposée d’une matrice**************************************
    // 8)************Opérations logiques : NON, ET, OU, OU exclusif*****************


int main()
{
    // 1) Lecture d'une matrice et création de la liste
   Maillon_vecteur *p=NULL;
   p=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
   Maillon_vecteur *tete;
   if (p!=NULL){
    tete=p;
   }
   int i,j,li,cl;
   printf("Donner le nombre de lignes : ");
   scanf("%d",&li);
   printf("Donner le nombre de collones : ");
   scanf("%d",&cl);
  for (i=1;i<=li;i++){ // begin for i
     for (j=1;j<=cl;j++){ // begin for j
      p->ligne=i;
      p->colonne=j;
      printf("T[%d,%d]=",p->ligne,p->colonne);
      scanf("%d",&p->val);
      if (p->val==0){
        continue;
      }
        p->next=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
        p=p->next;
    }//end for j
   }//end for i
   p->next=NULL;

  /* // 2)Affichage d’une matrice
   Maillon_vecteur *q=tete;
  for (i=1;i<=li;i++){ // begin for i
     for (j=1;j<=cl;j++){// begin for j
      printf("%d | ",q->val);
      q=q->next;
     } // end for j
     printf("\n");
   }//end for i*/

   // 3)Extraction d’une sous matrice

   int ip,jp,id,jd;
   Maillon_vecteur *E=tete;
   printf("donner le nemuro de la ligne de la premiere case : ");
   scanf("%d",&ip);
   printf("donner le nemuro de la colonne de la premiere case : ");
   scanf("%d",&jp);
   printf("donner le nemuro de la ligne de la derniere case : ");
   scanf("%d",&id);
   printf("donner le nemuro de la colonne de la derniere case : ");
   scanf("%d",&jd);
   for (i=1;i<=li;i++){ // for i
    for (j=1;j<=cl;j++){ // for j
    if (E->ligne>=ip && E->colonne<=jd)
    {
        printf("%d | ",E->val);
    }
    if (E->ligne==id && E->colonne==jd)
    {
        E->next=NULL;
        break;

    }
    E=E->next;

    } // end for j
    printf("\n");
    if (E->ligne==id && E->colonne==jd)
        break;
   } // end for i

   // 4) Division d’une matrice en sous-blocs de taille égale
    return 0;
}
