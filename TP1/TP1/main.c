#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"


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

  Maillon_vecteur *head,*ras,*v;
  int li,cl,ip,jp,id,jd,n,m,choix,b,ch;

  do{
  printf("***************************   Menu !  **************************************** \n");
  printf("2)************ Affichage d\'une matrice ************************************** \n");
  printf("3)************ Extraction d\'une sous matrice********************************* \n");
  printf("4)************ Division d\'une matrice en sous-blocs de taille egale********** \n");
  printf("5)************ Addition de deux ou plusieurs matrices************************* \n");
  printf("6)************ Multiplication par vecteur, multiplication de deux matrices**** \n");
  printf("7)************ Transposée d\'une matrice************************************** \n");
  printf("8)************Operations logiques : NON, ET, OU, OU exclusif****************** \n");
  printf("Donner le nombre de lignes : ");
   scanf("%d",&li);
   printf("Donner le nombre de colonnes : ");
   scanf("%d",&cl);
   /*1)*/ Lecture(&head,li,cl); // la lecture c'est pas un choix car elle est obligatoire !
<<<<<<< Updated upstream
<<<<<<< Updated upstream
   Afficher(head,li,cl);

=======
          Afficher(head,li,cl);
>>>>>>> Stashed changes
=======
          Afficher(head,li,cl);
>>>>>>> Stashed changes
   printf("Donner votre choix : ");
   scanf("%d",&choix);
 switch (choix){

   case 2:  Afficher(head,li,cl);
          break;
 //***********************************************************************************************
   case 3 :
   printf("donner le nemuro de la ligne de la premiere case : ");
   scanf("%d",&ip);
   printf("donner le nemuro de la colonne de la premiere case : ");
   scanf("%d",&jp);
   printf("donner le nemuro de la ligne de la derniere case : ");
   scanf("%d",&id);
   printf("donner le nemuro de la colonne de la derniere case : ");
   scanf("%d",&jd);
   Extract(head,li,cl,ip,jp,id,jd);
   break;
 //************************************************************************************************
     case 4 :
     printf("\n donner n : ");
     scanf("%d",&n);
     printf("\n donner m : ");
     scanf("%d",&m);
     Diviser(head,li,cl,n,m);
     break;
     //************************************************************************************************
     case 8 :
     Lecture(&ras,li,cl);
     Afficher(ras,li,cl);
     operations_logiques(head,ras,li,cl);
     break;
 //***********************************************************************************************
    case 7 : transposer2(&v,head,li,cl);
             Afficher(v,li,cl);
              break;
 //***********************************************************************************************
     case 6 :
   printf(" \n Pour multiplication par vecteur donner 1 , pour multiplication par matrice donner 2 \n");
   scanf("%d",&ch);
        if (ch==1){
        printf("donner le vecteur : \n");
        Lecture(&ras,cl,1);
        Afficher(ras,cl,1);
        multiplication(head,ras,li,cl,ch);
        }
        else if (ch==2){

        }
        break;

 //***********************************************************************************************
 default : printf("\n Le choix n\'exsiste pas ! \n");
           break;

 }// end switch
 //************************************************************************************************
    printf("si vous voulez repeter le programme entrer 1 sinon entrer 0 :  ");
    scanf("%d",&b);
  }while (b!=0);
    printf(" \n Merci de votre participatoin (: \n");

    return 0;
}

/* Algorithme de multiplication:

    matrice1(m1, m2), matrice2(m2, n2), coordonné: (i,k) x (k,j)

    for(i: 1 => m1)

        //ici chercher le premier maillion de la ligne i, soit "debut"

        for(j: 1 => n2)

            P2=tete2;
            P1=debut;

            for(k: 1 => m2)
                //ici chercher le maillon avec la colonne j (une fonction pour la recherche)

                SI( //verifier si k est le meme )
                |   valeur += valeur(P1) * valeur(P2)
                |   P1 = suivant(P1), P2 = suivant(P2)
                |
                FSI

                SI (ligne(P1) <= k) alors : P1= suivant(P1)
                SI (col(P2) <= k) alors :  chercher le maillon de la ligne suivante
                (ici la remarque est que la ligne ou la colonne ne doit pas etre incrementé sauf
                    quand sa valeur est <= K, sinon on vas depacer le k)

*/
