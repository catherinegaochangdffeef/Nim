#ifndef ENTETES_H_INCLUDED
#define ENTETES_H_INCLUDED
#define VMIN 5
#define VMAX 30

//Cr�ation du type T_Case
struct T_Case
{
    int x; //Indice de ligne
    int y; //Indice de colonne
};

//Cr�ation du type T_Tab_Case
typedef struct
{
    struct T_Case tab[100];
}T_Tab_Case;

//Fonction qui permet de saisir un entier
int Lire_Entier(int bi, int bs);

//Fonction qui �tablit les param�tres de jeu
void Parametres(int *nlig, int *ncol, int *nban, int *niveau, int *next);

//Fonction qui choisit un nombre au hasard
int Hasard(int val);

//Fonction qui retourne le maximum entre 2 valeurs donn�es
int max(int a,int b);

//Fonction qui stocke les coordonn�es des cases bannies dans un tableau
void Hasard_Ban(int nlig, int ncol, int nban, T_Tab_Case *T);

//Fonction qui teste les conditions pour bannir les cases
int Bannissable(int k, int nlig, int ncol, T_Tab_Case *T, struct T_Case);

//Fonction qui permet l'affichage de la grille
void AfficheGrille(int nlig,int ncol, int nban, T_Tab_Case *T, struct T_Case );

//Fonction
void Calcul_Nimbers(int nim[][VMAX],int nlig,int ncol);

//Fonction qui stocke les coordonn�es des cases voisines pour une case � un moment donn�
void Voisines(int nlig, int ncol, int nban, int *nb_vois, T_Tab_Case *vois, T_Tab_Case T, struct T_Case);

//Fonction qui permet au joueur de jouer
struct T_Case Coup_Joueur(struct T_Case pion, T_Tab_Case ban, int nlig, int ncol, int nban);

//Fonction qui permet � l'ordinateur de jouer au hasard
struct T_Case Coup_Ordi_Hasard(struct T_Case pion, T_Tab_Case ban,int nlig, int ncol, int nban);

//Fonction qui permet � l'ordinateur de jouer un coup gagnant
struct T_Case Coup_Ordi_Gagnant(struct T_Case pion, T_Tab_Case ban, int nlig, int ncol, int nban, int nim[][VMAX]);



#endif // ENTETES_H_INCLUDED
