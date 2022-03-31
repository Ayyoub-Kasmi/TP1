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

   void affiche_M_nule(int a,int b){
     int  k,h;
     for (k=1;k<=a;k++){
        for (h=1;h<=b;h++){
            printf("0 | ");
        }
        printf("\n");
     }
   } // end afficher 0

int main()
{


   // 4) Division d’une matrice en sous-blocs de taille égale


    // 5)addition

  /*  p=tete;
    f=head;
    printf("La matrice d\'addition est : \n");
    for (i=1;i<=li;i++){ // begin i
        for (j=1;j<=cl;j++){ // begin j
         printf("%d | ",p->val + f->val);
         p=p->next;
         f=f->next;

        } // end j
        printf("\n");
    } // end i

    // 8)Opérations logiques : NON, ET, OU, OU exclusif
     p=tete;
     f=head;
    printf("La matrice de ''NON'' est : \n");
    for (i=1;i<=li;i++){ // begin i
        for (j=1;j<=cl;j++){ // begin j
         printf("%d | ",~p->val*-1);
         p=p->next;
        } // end j
        printf("\n");
    } // end i


     p=tete;
    f=head;
    printf("La matrice de ''ET'' est : \n");
    for (i=1;i<=li;i++){ // begin i
        for (j=1;j<=cl;j++){ // begin j
         printf("%d | ",p->val&f->val);
         p=p->next;
         f=f->next;

        } // end j
        printf("\n");
    } // end i

     p=tete;
    f=head;
    printf("La matrice de ''OU'' est : \n");
    for (i=1;i<=li;i++){ // begin i
        for (j=1;j<=cl;j++){ // begin j
         printf("%d | ",p->val|f->val);
         p=p->next;
         f=f->next;

        } // end j
        printf("\n");
    } // end i

     p=tete;
     f=head;
    printf("La matrice de ''OU EXLUSIF'' est : \n");
    for (i=1;i<=li;i++){ // begin i
        for (j=1;j<=cl;j++){ // begin j
         printf("%d | ",p->val^f->val);
         p=p->next;
         f=f->next;

        } // end j
        printf("\n");
    } // end i



*/

Maillon_vecteur *tete=NULL,*q,*p,*l;
int i,j,li,cl,cpt=0,n;

// 1) Lecture d'une matrice et création de la liste
   printf("Donner le nombre de lignes : ");
   scanf("%d",&li);
   printf("Donner le nombre de colonnes : ");
   scanf("%d",&cl);
  for (i=1;i<=li;i++){ // begin for i
     for (j=1;j<=cl;j++){ // begin for j
     printf("T[%d,%d]=",i,j);
     scanf("%d",&n);
     p->next=NULL;
     if (n==0){
        continue;
     }
     else { //begin else
       q=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
       if(tete==NULL){ // begin if tete==null
        p=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
        tete=p;
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
       cpt++;
     } // end else
     } // end j
  } // end i
  /*if (n==0){

  }*/
   printf("\n");
   printf("cpt = %d",cpt);
   printf("\n \n \n");

   // 2)Affichage d’une matrice

   p=tete;
   if (cpt==0){
   printf(" \n La matrice est nulle ! \n");
   affiche_M_nule(li,cl);
   free(tete);
   }
   else {
   for (i=1;i<=li;i++){
        for (j=1;j<=cl;j++){
    if (p->ligne==i && p->colonne==j){
    printf("%d\t|",p->val);
    p=p->next;
    }
    else printf("0\t|");


    }
    printf("\n");
   }
   }
/*
   while (p!=NULL){
    printf("%d->",p->val);
    p=p->next;
   }*/


   // 3)Extraction d’une sous matrice
   p=tete;
   int ip,jp,id,jd;
   printf("donner le nemuro de la ligne de la premiere case : ");
   scanf("%d",&ip);
   printf("donner le nemuro de la colonne de la premiere case : ");
   scanf("%d",&jp);
   printf("donner le nemuro de la ligne de la derniere case : ");
   scanf("%d",&id);
   printf("donner le nemuro de la colonne de la derniere case : ");
   scanf("%d",&jd);
   if (jp>jd){
    printf("l\'extraction est impossible ! \n");
   }
   else {
   printf("L\'extraction de la sous matrice : \n");
   for (i=1;i<=li;i++){ //begin for i
    for (j=1;j<=cl;j++){ // begin for j
      if (i>=ip && i<=id && j>=jp && j<=jd)  {// begin if 1
       if (p->ligne==i && p->colonne==j){ // if a

        printf("%d\t|",p->val);

        } // end if a
        else {

            printf("0\t|");

        }


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
   }




    return 0;
}
