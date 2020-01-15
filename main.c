#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"



int main()
{
    int nlig=0, ncol=0, nban=0, niveau=0, next=0, z, i, j, h, k, nim[VMAX][VMAX];
    struct T_Case pion;
     T_Tab_Case ban,vois;
    pion.x=1;
    pion.y=1;
    printf("Initialisation des parametres du jeu: \n");
    Parametres(&nlig, &ncol, &nban, &niveau, &next);
    //printf("%d %d %d %d %d", nlig,ncol,nban,niveau,next); //pour v�rifier si on retrouve les valeurs saisies
    printf("Lancement de la partie!\n");
    Hasard_Ban(nlig, ncol, nban, &ban);
    for(z=0; z<nban; z++) printf("%d,%d\n", ban.tab[z].x, ban.tab[z].y);
    AfficheGrille(nlig,ncol, nban, &ban, pion);
    Calcul_Nimbers(nim[VMAX][VMAX],&nlig,&ncol,&nban,ban );





    return 0;
}
