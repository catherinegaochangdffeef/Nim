#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"



int Lire_Entier(int bi, int bs)
{
    int n;
    do
    {
        scanf("%d", &n);
    }
    while ((n<bi)||(n>bs));
    return n;
}

int caseBannie(struct T_Case c, T_Tab_Case tab)
{
    int i;
    for(i=0; i<tab.taille; i++)
    {
        if(tab.tab[i].x==c.x && tab.tab[i].y==c.y)
            return 1;
    }
    return 0;

}

void Parametres(int *pointeurnlig, int *pointeurncol, int *pointeurnban, int *pointeurniveau, int *pointeurnext)
{
    printf("Entrez un nombre de lignes compris entre 5 et 30: " );
    *pointeurnlig=Lire_Entier(VMIN,VMAX);
    printf("Entrez un nombre de colonnes compris entre 5 et 30: ");
    *pointeurncol=Lire_Entier(VMIN,VMAX);
    printf("Nombre de cases bannies generees: ");
    *pointeurnban=Hasard(max(*pointeurnlig, *pointeurncol));
    printf("Niveau de difficulte de 1 a 4: ");
    *pointeurniveau=Lire_Entier(1,4);
    printf("Qui commence?\nL'ordinateur (1) ou le joueur (2): ");
    *pointeurnext=Lire_Entier(1,2);
}

int Hasard(int val)
{
    srand(time(NULL));
    int nb=rand()%val;
    printf("%d\n",nb);
    return nb;
}

int max(int a, int b)
{
    if(a>b) return a;
    else return b;
}

void Hasard_Ban(int nlig, int ncol, T_Tab_Case T, int aBannir)
{
    struct T_Case _case;
    int k, test;
    T.taille=0;
    for (k = 0; k < aBannir; k++)
    {
        do
        {
            _case.x=rand()%nlig;
            _case.y=rand()%ncol;
            test=Bannissable(nlig, ncol, T, _case);
        }
        while(test==0);
        T.tab[k]=_case;
        T.taille++;
    }

}
//Fonction qui d�finit les contraintes des cases bannies
int Bannissable(int nlig, int ncol, T_Tab_Case T, struct T_Case _case) 
{
    int bannissable;
    //si banissable=0, pas bannissable
    bannissable=0;
    if(_case.y == 0 && _case.x == ncol-1)
        bannissable=1;
    else if(_case.y == nlig-1 && _case.x == 0)
        bannissable=1;
    else if(_case.x > 0 &&_case.x < ncol-1 && _case.y < nlig-1 && _case.y > 0 )
        bannissable=1;
    if (caseBannie(_case, T))
        bannissable = 0;
    struct T_Case caseTmp = _case;
    caseTmp.x++;
    caseTmp.y--;
    if (caseBannie(caseTmp, T))
        bannissable = 0;
    caseTmp = _case;
    caseTmp.x--;
    caseTmp.y++;
    if (caseBannie(caseTmp, T))
        bannissable = 0;
    return bannissable;
}

void AfficheGrille(int nlig,int ncol, T_Tab_Case T, struct T_Case pion)
{
    int i, j;
    printf ("   ");
    for(i=1;i<= ncol;i++)
    {
        printf("%3d ",i);

    }
    printf("\n");
    for(i=0;i< nlig;i++)
    {
        if(i<10)
            printf("%d |",i+1);
        else
            printf("%d|", i+1);
        for(j=0;j< ncol;j++)
        {
            struct T_Case curr;
            curr.x = j;
            curr.y = i;
            if (j==pion.x && i==pion.y)
                printf(" O |");            
            else if (caseBannie(curr, T))
                printf(" X |");            

            else
                printf(" - |");

        }
        printf("\n");
    }
}

void Voisines(int nlig, int ncol, T_Tab_Case *t, T_Tab_Case ban, struct T_Case _case)
{
    struct T_Case caseDroite, caseDroiteDroite, caseBas, caseBasBas;
    t->taille=0;
    caseDroite = caseDroiteDroite = caseBas = caseBasBas = _case;
    caseDroite.x=_case.x+1;
    caseBas.y=_case.y+1;
    caseBasBas.y=_case.y+2;
    caseDroiteDroite.x=_case.x+2;
    if(!caseBannie(caseDroite, ban) && caseDroite.x < ncol)
    {
        t->tab[t->taille] = caseDroite;
        t->taille++;

        if(!caseBannie(caseDroiteDroite, ban) && caseDroiteDroite.x < ncol)
        {
            t->tab[t->taille] = caseDroiteDroite;
            t->taille++;
            
        }

    }
    if(!caseBannie(caseBas, ban) && caseBas.y < nlig)
    {
        t->tab[t->taille] = caseBas;
        t->taille++;
        if(!caseBannie(caseBasBas, ban) && caseBasBas.y < nlig)
        {
            t->tab[t->taille] = caseBasBas;
            t->taille++;
            
        }
    }
}


void Calcul_Nimber(int nim[][VMAX],int nlig,int ncol)
{
    int x,y;
    int nimber, nimber_tempal = 0;
    for(x=ncol-1;x>=0;x--)
    {
        nimber = nimber_tempal;
        for(y=nlig-1;y>=0;y--)
        {
            nim[x][y]=nimber;
            nimber++;
            nimber%=3;
        }
        nimber_tempal+=2;
        nimber_tempal%=3;
    }

}





