#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "library.h"

 typedef struct Maillon_vecteur{

      int val;
      int ligne;
      int colonne;
      struct Maillon_vecteur *next;
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

  Maillon_vecteur *head,*f;
  int li,cl;
  printf("Donner le nombre de lignes : ");
   scanf("%d",&li);
   printf("Donner le nombre de colonnes : ");
   scanf("%d",&cl);
  Lecture(&head,li,cl);
  Afficher(head,li,cl);
  Extract(head,li,cl);



    return 0;
}
