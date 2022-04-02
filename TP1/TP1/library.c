#include "library.h"

/*void allouer(Maillon_vecteur **maillon){
    *maillon=(Maillon_vecteur* )malloc(sizeof(Maillon_vecteur));
}
*/
void permuter(int *a, int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
    // 2)Affichage d’une matrice

  /* if (tete==NULL){
   printf(" \n La matrice est nulle ! \n");
   affiche_M_nule(li,cl);
   free(tete);
   }
   else {
        p=tete;
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
   */
   /* printf("donner le nemuro de la ligne de la premiere case : ");
   scanf("%d",&l1);
   printf("donner le nemuro de la colonne de la premiere case : ");
   scanf("%d",&c1);
   printf("donner le nemuro de la ligne de la derniere case : ");
   scanf("%d",&l2);
   printf("donner le nemuro de la colonne de la derniere case : ");
   scanf("%d",&c2);*/
}

