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
  //***********************************************************************************************

    // Afficher matrice nulle
   void affiche_M_nule(int a,int b){
     int  k,h;
     for (k=1;k<=a;k++){
        for (h=1;h<=b;h++){
            printf("0 | ");
        }
        printf("\n");
     }
   }
  //***********************************************************************************************
     // 1) Lecture d'une matrice et création de la liste
  Maillon_vecteur lecture(Maillon_vecteur **head,Maillon_vecteur *z,int li,int cl){
    Maillon_vecteur *v;
    int i,j,m,cpt;
    *head=NULL;
    for (i=1;i<=li;i++){ // begin for i
     for (j=1;j<=cl;j++){ // begin for j
     printf("T[%d,%d]=",i,j);
     scanf("%d",&m);
     z->next=NULL;
     if (m==0){
        continue;
     }
     else { //begin else
       v=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
       if(*head==NULL){ // begin if tete==null
       z=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
        *head=z;
       } // end if tete==null
       z->val=m;
       z->ligne=i;
       z->colonne=j;
       if (i==li && j==cl){
        z->next=NULL;
        free(v);
       }
       else {
        z->next=v;
       z=z->next;
       }
       cpt++;
     } // end else
     } // end j
  } // end i
  }

  //***********************************************************************************************

   //2)Affichage d'une matrice

  void Afficher(Maillon_vecteur *tete,Maillon_vecteur *z,int l,int c){
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
  //************************************************************************************************
  // 3)Extraction d’une sous matrice




  //***********************************************************************************************

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

  Maillon_vecteur *tete=NULL,*q,*p;
  int i,j,li,cl,n;

// 1) Lecture d'une matrice et création de la liste
   printf("Donner le nombre de lignes : ");
   scanf("%d",&li);
   printf("Donner le nombre de colonnes : ");
   scanf("%d",&cl);
  for (i=1;i<=li;i++){ // begin for i
     for (j=1;j<=cl;j++){ // begin for j
     printf("T[%d,%d]=",i,j);
     scanf("%d",&n);
     //p->next=NULL;
     if (n==0){
        continue;
     }
       q=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
       q->val=n;
       q->ligne=i;
       q->colonne=j;
       if(tete==NULL){ // begin if tete==null
       //p=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));
        p=q;
        tete=q;
       } // end if tete==null

       //if (i==li && j==cl){
       // q->next=NULL;
        //free(q);
      // }
       else {
        p->next=q;
        p=p->next;
       }

     } // end j
  } // end i
  p->next=NULL;
   Afficher(tete,p,li,cl);



 /* Maillon_vecteur *tete=NULL,*q,*p;
  int i,j,li,cl,cpt=0,n;
   printf("Donner le nombre de lignes : ");
   scanf("%d",&li);
   printf("Donner le nombre de colonnes : ");
   scanf("%d",&cl);
   lecture(&tete,p,li,cl);
   printf("\n");
   printf("cpt = %d",cpt);
   printf("\n \n \n");

   Afficher(tete,p,li,cl);

   /* while (p!=NULL){
    printf("%d->",p->val);
    p=p->next;
   }*/


   //Extract(tete,p,li,cl);

   // 3)Extraction d’une sous matrice
   /*int ip,jp,id,jd;
   if (tete==NULL){
       printf("l\'extraction est impossible car la matrice est nulle ! \n");
    }
    else { //begin else 1
    p=tete;
   printf("donner le nemuro de la ligne de la premiere case : ");
   scanf("%d",&ip);
   printf("donner le nemuro de la colonne de la premiere case : ");
   scanf("%d",&jp);
   printf("donner le nemuro de la ligne de la derniere case : ");
   scanf("%d",&id);
   printf("donner le nemuro de la colonne de la derniere case : ");
   scanf("%d",&jd);
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
*/



    return 0;
}
