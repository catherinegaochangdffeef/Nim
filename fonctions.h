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
    struct T_Case tab[100];
}T_Tab_Case;

int Lire_Entier(int, int);
void Parametres(int *pointeurnlig, int *pointeurncol, int *pointeurnban, int *pointeurniveau, int *pointeurnext);
int Hasard(int);
int max(int,int);
void Hasard_Ban(int, int, int, T_Tab_Case *T);
int Bannissable(int, int, int, T_Tab_Case *T, struct T_Case);
void AfficheGrille(int,int, int, T_Tab_Case *T, struct T_Case );
void  Calcul_Nimbers(int,int*,int*,int*, T_Tab_Case );




#endif // ENTETES_H_INCLUDED
