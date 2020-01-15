#ifndef ENTETES_H_INCLUDED
#define ENTETES_H_INCLUDED
#define VMIN 5
#define VMAX 30
struct T_Case
{
    int x; //Indice de ligne
    int y; //Indice de colonne
};


typedef struct
{
    struct T_Case *tab;
    int taille;
}T_Tab_Case;

/*
 * fonction qui donne un entier entre deux bornes
*/
int Lire_Entier(int bi, int bs);
int caseBannie(struct T_Case c, T_Tab_Case tab);
void Parametres(int *pointeurnlig, int *pointeurncol, int *pointeurnban, int *pointeurniveau, int *pointeurnext);
int Hasard(int);
int max(int,int);
void Hasard_Ban(int nlig, int ncol, T_Tab_Case T, int aBannir);
int Bannissable(int nlig, int ncol, T_Tab_Case T, struct T_Case _case) ;
void AfficheGrille(int nlig,int ncol, T_Tab_Case T, struct T_Case pion);
void Voisines(int nlig, int ncol, T_Tab_Case *t, T_Tab_Case ban, struct T_Case _case);
void Calcul_Nimber(int nim[][VMAX],int nlig,int ncol);




#endif // ENTETES_H_INCLUDED
