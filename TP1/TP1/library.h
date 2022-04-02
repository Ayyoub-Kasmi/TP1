#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED



#endif // LIBRARY_H_INCLUDED

 /* Maillon_vecteur *tete=NULL,*q,*p;
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
     } // end else
     } // end j
  } // end i */
//************************************************************************************************************
  /*printf("donner le nemuro de la ligne de la premiere case : ");
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
       } // end else 1 */
       //*************************************************************************************************
       // 8)Opérations logiques : NON, ET, OU, OU exclusif
   /*  p=tete;
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
    } // end i   */
    //***************************************************************************************************
