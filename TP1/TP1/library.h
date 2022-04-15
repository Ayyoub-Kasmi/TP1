#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
typedef struct Maillon_vecteur{

      int val;
      int ligne;
      int colonne;
      struct Maillon_vecteur *next;
    }Maillon_vecteur;
void Lecture (Maillon_vecteur **tete,int li,int cl);
void Afficher(Maillon_vecteur *tete,int l,int c);
void Extract(Maillon_vecteur *tete,int li,int cl,int ip,int jp,int id,int jd);
void Diviser(Maillon_vecteur *tete,int li,int cl,int n,int m);
void operations_logiques(Maillon_vecteur *tete1,Maillon_vecteur *tete2,int li,int cl);
void transposer(Maillon_vecteur *tete,int li,int cl);
//void multiplication(Maillon_vecteur *tete1,Maillon_vecteur *tete2,int li1,int lc,int ch);


#endif // LIBRARY_H_INCLUDED

