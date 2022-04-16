#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"


//*******************************************************************************************************************************
 // 1)Lecture d'une matrice et cr�ation de la liste
void Lecture (Maillon_vecteur **tete,int li,int cl){
    Maillon_vecteur *p,*q;
    int i,j,n;
    *tete=NULL;
    for (i=1;i<=li;i++){ // begin for i
        for (j=1;j<=cl;j++){ // begin for j
            printf("T[%d,%d]=",i,j);
            scanf(" %d",&n);

            if (n==0){
                continue;
            } else { //begin else

                q=(Maillon_vecteur *)malloc(sizeof(Maillon_vecteur));

                q->val=n;
                q->ligne=i;
                q->colonne=j;
                q->next=NULL;

                if(*tete==NULL){
                    *tete=q;
                    p= *tete;
                }

                p->next=q;
                p=q;

            } // end else
        } // end j
    } // end i
}
//*******************************************************************************************************************************
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

void afficher_ligne_null(int n, int m){
//afficher n lignes de colonnes m

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            printf("0\t|");
        }
        printf("\n");
    }
}
//*******************************************************************************************************************************
//2)Affichage d'une matrice

void Afficher(Maillon_vecteur *tete,int l,int c){

    Maillon_vecteur *z, *p;
    int i,j;

    if (tete==NULL){
        printf(" \n La matrice est nulle ! \n");
        affiche_M_nule(l,c);

    } else {
        z=tete;
        for (i=1;i<=l;i++){
            for (j=1;j<=c;j++){
                if (z->ligne==i && z->colonne==j){
                    printf("%d\t|",z->val);
                    p=z;
                    z=z->next;
                    if(z==NULL){
                        j=c+1;
                        i=l+1;
                        //c'est une methode pour arreter les deux boucles "pour"

                        //afficher les 0 restantes dans la meme ligne, s'ils existent
                        for(int tmp= p->colonne+1; tmp<=l; tmp++){
                            printf("0\t|");
                        }
                    }
                } else printf("0\t|");


            } //fin pour j

            printf("\n");
        } //fin pour i

        //afficher les lignes nulles restantes:
        afficher_ligne_null(l-p->ligne, c);
    }

}
  //***********************************************************************************************************
  //3)Extraction d�une sous matrice
void Extract(Maillon_vecteur *tete,int li,int cl,int ip,int jp,int id,int jd){
    int i,j;
    Maillon_vecteur *p;
    // 3)Extraction d�une sous matrice
    if (tete==NULL){
        printf("l\'extraction est impossible car la matrice est nulle ! \n");
    } else { //begin else 1
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
//**************************************************************************************************************

void Diviser(Maillon_vecteur *tete,int li,int cl,int n,int m){
    int ip,jp,id,jd,x,y,k=1;
    x=li/n;
    y=cl/n;
    ip=1;
    id=x;
    if (tete==NULL){ // if 1
        printf("La division est impossible ! \n");
    } // end if 1
    else { //else 1
        if (li%n!=0 && cl%m!=0){// if 2
            printf("La division est impossible ! \n");
        }//end if 2
        else {//else 2
            while (id<=li){// begin while 1
                jp=1;
                jd=y;
                while (jd<=cl){ // begin while 2
                    printf("Sous_matrice nemuro %d : \n ",k);
                    Extract(tete,li,cl,ip,jp,id,jd);
                    printf("\n");
                    jp+=y;
                    jd+=y;
                    k++;
                }//end while 2
                ip+=x;
                id+=x;
            }// end while 1
        }// end else 2
    }// else 2
}//end function

  //*********************************************************************************************************
   //8)operations logiques
void operations_logiques(Maillon_vecteur *tete1,Maillon_vecteur *tete2,int li,int cl){
    Maillon_vecteur *p,*f;
    int i,j,s;

    printf("*************** NON : 1 *************** \n");
    printf("**************** ET : 2 *************** \n");
    printf("**************** OU : 3 *************** \n");
    printf("*************** OUX : 4 *************** \n");

    printf("Donner votre choix : \n");
    scanf("%d",&s);
    switch (s){//begin switch
    case 1: // begin case 1
        if (tete1==NULL){//if0
            printf("La matrice est NULL");
            affiche_M_nule(li,cl);
        }//end if0
        else {//begin else 0
        p=tete1;
        printf("La Matrice NON de la premiere matrice  : \n");
        for (i=1;i<=li;i++){//begin for i
            for (j=1;j<=cl;j++){//begin for j
                if (p->ligne==i && p->colonne==j){// begin if 1
                printf("%d\t|",~p->val);
                p=p->next;
            }//end if 1
            else printf("0\t|");
        }//end for j
        printf("\n");
      }// end for i
    }// end else 0
       break;
//******************************

    case 2: // begin case 2
       if (tete1==NULL || tete2==NULL){
        printf("La matrice ET : \n");
        affiche_M_nule(li,cl);
       }
    else { // big else
            p=tete1;
            f=tete2;
         printf("La matrice ET : \n");
       for (i=1;i<=li;i++){//begin for i
        for (j=1;j<=cl;j++){//begin for j
           if ((p->ligne==i && p->colonne==j) && (f->ligne==i && f->colonne==j)){//begin if1
            printf("%d\t|",p->val & f->val);
            p=p->next;
            f=f->next;
           }//end if1
           else if ((p->ligne==i && p->colonne==j) && (f->ligne!=i || f->colonne!=j)){// if2
            printf("0\t|");
            p=p->next;
           }//end if2
           else if((f->ligne==i && f->colonne==j) && (p->ligne!=i || p->colonne!=j)){//if3
            printf("0\t|");
            f=f->next;
           }//end if3
           else if((p->ligne!=i || p->colonne!=j) && (f->ligne!=i || f->colonne!=j)){//if4
            printf("0\t|");
           }//end if4

         }//end for j
         printf("\n");
        }// end for i

        }// end big else
         break;
//*************************
    case 3 : //begin ou
        if (tete1==NULL && tete2==NULL){
          printf("La matrice OU : \n");
          affiche_M_nule(li,cl);
        }
        else if (tete1==NULL && tete2!=NULL){
          printf("La matrice OU : \n");
          Afficher(tete2,li,cl);
        }
        else if (tete1!=NULL && tete2==NULL){
            printf("La matrice OU : \n");
          Afficher(tete1,li,cl);
        }
        else if (tete1!=NULL && tete2!=NULL){//begin big else
         p=tete1;
         f=tete2;
         printf("La matrice OU : \n");
       for (i=1;i<=li;i++){//begin for i
        for (j=1;j<=cl;j++){//begin for j
           if ((p->ligne==i && p->colonne==j) && (f->ligne==i && f->colonne==j)){//begin if1
            printf("%d\t|",p->val | f->val);
            p=p->next;
            f=f->next;
           }//end if1
           else if ((p->ligne==i && p->colonne==j) && (f->ligne!=i || f->colonne!=j)){// if2
            printf("%d\t|",p->val);
            p=p->next;
           }//end if2
           else if((f->ligne==i && f->colonne==j) && (p->ligne!=i || p->colonne!=j)){//if3
            printf("%d\t|",f->val);
            f=f->next;
           }//end if3
           else if((p->ligne!=i || p->colonne!=j) && (f->ligne!=i || f->colonne!=j)){//if4
            printf("0\t|");
           }//end if4

         }//end for j
         printf("\n");
        }// end for i

        }//end big else
        break;
//****************************

      case 4: //begin oux
          if (tete1==NULL && tete2==NULL){
            printf("La matrice OUX : \n");
            affiche_M_nule(li,cl);
          }
          else if (tete1==NULL && tete2!=NULL){
            printf("La matrice OUX : \n");
            Afficher(tete2,li,cl);
          }
          else if (tete1!=NULL && tete2==NULL){
            printf("La matrice OUX : \n");
            Afficher(tete1,li,cl);
          }
              else if (tete1!=NULL && tete2!=NULL){// big else
             p=tete1;
             f=tete2;
             printf("La matrice OUX : \n");
                for (i=1;i<=li;i++){//begin for i
                for (j=1;j<=cl;j++){//begin for j
                   if ((p->ligne==i && p->colonne==j) && (f->ligne==i && f->colonne==j)){//begin if1
                    printf("%d\t|",p->val ^ f->val);
                    p=p->next;
                    f=f->next;
                   }//end if1
                   else if ((p->ligne==i && p->colonne==j) && (f->ligne!=i || f->colonne!=j)){// if2
                    printf("%d\t|",p->val ^ 0);
                    p=p->next;
                   }//end if2
                   else if((f->ligne==i && f->colonne==j) && (p->ligne!=i || p->colonne!=j)){//if3
                    printf("%d\t|",f->val ^ 0);
                    f=f->next;
                   }//end if3
                   else if((p->ligne!=i || p->colonne!=j) && (f->ligne!=i || f->colonne!=j)){//if4
                    printf("0\t|");
                   }//end if4

                 }//end for j
                 printf("\n");
                }// end for i

                  }// end big else
                  break;

             default : printf("Le choix %d n\'exsiste pas ! \n",s);
                       break;


            }// end switch
  }
  //*********************************************************************************************************
   //7)Transpos�e d'une matrice
   void transposer(Maillon_vecteur *tete,int li,int cl){
    Maillon_vecteur *p,*l;
    int i,j,k;
    if (tete==NULL){
       printf("La matrice transpose de la matrice nulle : \n");
       affiche_M_nule(cl,li);
    }
    else {//big eles
     l=tete;
     k=1;
    while (k<=cl){//begin while
      p=l;
     for (i=1;i<=li;i++){//begin i
      for (j=1;j<=cl;j++){//begin j
       if (j==k){//if k=j
        if (p->ligne==i && p->colonne==j){//if2
         printf("%d\t|",p->val);
         p=p->next;
        }//end if2
        else printf("0\t|");
       }//end if k=j
       else {// if k<>j
        if (p->ligne==i && p->colonne==j){// if 111
            p=p->next;
        }// end if 111

       }// end if k<>j

      }//end j
     }// end i
     printf("\n");
      k++;
      if (l->ligne == l->next->ligne){//begin dernier if
        l=l->next;
      }//end dernier if

    }//end while

    }//end big else


   }
   //******************************************************************************************************
   //8)Multiplication par vecteur, multiplication de deux matrices
void multiplication(Maillon_vecteur *tete1,Maillon_vecteur *tete2,int li1,int lc,int ch){
    Maillon_vecteur *p,*f;
    int i,j,s;
   //***********************************
    if (ch==1){
    if (tete1==NULL || tete2==NULL){
        printf("\n Le produit est nulle ! \n");
        affiche_M_nule(li1,1);
    } else {
        i=1;
        p=tete1;
        printf("Le vecteur multiplication est : \n");
        while (i<=li1){//begin big while
            f=tete2;
            s=0;
            for (j=1;j<=lc;j++){//begin for j
                if (p->ligne==i && p->colonne==j && f->ligne==j){ // 00
                    s=s+ p->val*f->val;
                    p=p->next;
                    f=f->next;
                }// end 00
                else if (p->ligne==i && p->colonne==j && f->ligne!=j)
                    p=p->next;
                else if ((p->ligne!=i || p->colonne!=j) && f->ligne==j)
                    f=f->next;

            }//end for j
            printf("%d\t|",s);
            printf("\n");
            i++;
        }//end big while
    }
}
//************************************
   else if (ch==2){




   }
   else printf("Le choix %d n\'exsiste pas ! \n",ch);





  }
   //******************************************************************************************************


