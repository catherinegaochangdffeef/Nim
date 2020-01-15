#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"



int main()
{
    int nlig=0, ncol=0, nban=0, niveau=0, next=0,nim[VMAX][VMAX];
    struct T_Case pion;
    T_Tab_Case ban;
    struct T_Case ban_tab[VMAX];
    ban.tab = ban_tab;
    pion.x=0;
    pion.y=0;
    printf("Initialisation des parametres du jeu: \n");
    Parametres(&nlig, &ncol, &ban.taille, &niveau, &next);
    //printf("%d %d %d %d %d", nlig,ncol,nban,niveau,next); //pour v�rifier si on retrouve les valeurs saisies
    Hasard_Ban(nlig, ncol, ban, ban.taille);
    Calcul_Nimber(nim,nlig,ncol );
    printf("Lancement de la partie!\n");
    AfficheGrille(nlig,ncol, ban, pion);





    return 0;
}
