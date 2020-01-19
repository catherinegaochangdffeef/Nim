#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entetes.h"

int main()
{
    int nlig=0, ncol=0, nban=0, niveau=0, next=0, nim[VMAX][VMAX], probabilite;
    struct T_Case pion;
    srand(time(NULL));
    pion.x=1;
    pion.y=1;
    printf("Initialisation des parametres du jeu: \n");
    Parametres(&nlig, &ncol, &nban, &niveau, &next);
    printf("Lancement de la partie!\n");
    T_Tab_Case ban;
    Hasard_Ban(nlig, ncol, nban, &ban);
    AfficheGrille(nlig, ncol, nban, &ban, pion);
    Calcul_Nimbers(nim,nlig,ncol);
    while(1)
    {
        if(next%2==0)
        {
            pion=Coup_Joueur(pion,ban,nlig,ncol,nban);
        }
        else if(next%2==1)
        {
            if(niveau==1)
            {
                pion=Coup_Ordi_Hasard(pion,ban,nlig,ncol,nban);
            }
            else if(niveau==2)
            {
                probabilite=rand()%3;
                if(probabilite==0)
                    pion=Coup_Ordi_Gagnant(pion,ban,nlig,ncol,nban,nim);
                else
                    pion=Coup_Ordi_Hasard(pion,ban,nlig,ncol,nban);
            }
            else if(niveau==3)
            {
                probabilite=rand()%3;
                if(probabilite==0)
                    pion=Coup_Ordi_Gagnant(pion,ban,nlig,ncol,nban,nim);
                else
                    pion=Coup_Ordi_Gagnant(pion,ban,nlig,ncol,nban,nim);
            }
            else
                pion=Coup_Ordi_Gagnant(pion,ban,nlig,ncol,nban,nim);
        }
        AfficheGrille(nlig,ncol,nban,&ban,pion);

        if(pion.x==nlig&&pion.y==ncol)
        {
        if(next%2==0)
            printf("Felicitation! Tu as gagne.");
        else
            printf("Dommage! Tu as perdu.");
        return 0;
        }
    next++;
    }
}
