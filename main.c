#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"



int main()
{
    int nlig=0, ncol=0, nban=0, niveau=0, next=0,nim[VMAX][VMAX],probabilite;
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
   
    printf("Lancement de la partie!\n");
    AfficheGrille(nlig,ncol, ban, pion);
    Calcul_Nimber(nim,nlig,ncol);
    while(1)
    {
        if(next%2==0)
        {
            pion=Coup_jouer(pion,nban,ban,nlig,ncol);

        }
        else
        {
            if(niveau==1)
            {
                pion=Coup_Ordi_Hasard(pion,nban,nlig,ncol);
            
            }
            else if(niveau==2)
            {
                probabilite=rand()%3;
                if(probabilite==0)
                    pion=Coup_Ordi_Gagnant(pion,nban,ban,nlig,ncol,nim);
                else
                    pion=Coup_Ordi_Hasard(pion,nban,ban,nlig,ncol);
            }
            else if(niveau==3)
            {
                probabilite=rand()%3;
                if(probabilite==0)
                    pion=Coup_Ordi_Gagnant(pion,nban,ban,nlig,ncol,nim);
            }
            else
                pion=Coup_Ordi_Gagnant(pion,nban,ban,nlig,ncol,nim);
        }
    
if(pion.x==nlig&&pion.y==ncol)
   {
       if(next%2==0)
            printf("Tu as gagne!");
       else
            printf("Tu es perdu!");
       return 0;
   }
   next++;
    }
}
