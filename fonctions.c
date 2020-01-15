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

void Hasard_Ban(int nlig, int ncol, int nban, T_Tab_Case *T)
{
    struct T_Case _case;
    _case.x=ncol;
    _case.y=nlig;
    int k, test;
    for (k = 0; k < nban; k++)
    {
        do
        {
            _case.x=rand()%nlig+1;
            _case.y=rand()%ncol+1;
            test=Bannissable(k, nlig, ncol, T, _case);
        }
        while(test==0);
        (*T).tab[k].x=_case.x;
        (*T).tab[k].y=_case.y;
    }

}

int Bannissable(int k, int nlig, int ncol, T_Tab_Case *T, struct T_Case _case) //Fonction qui d�finit les contraintes des cases bannies
{
    int m, bannissable, diagonal;
    //si banissable=0, pas bannissable
    bannissable=0;
    diagonal=0;
    if(_case.y == 1 && _case.x == ncol) bannissable=1;
    else if(_case.y == nlig && _case.x == 1) bannissable=1;
    else if(_case.x > 1 && _case.y < nlig && _case.y > 1 && _case.x < ncol) bannissable=1;
    for(m = 0; m < k; m++)
    {
        if (_case.y==(*T).tab[m].y+1 && _case.x==(*T).tab[m].x-1) diagonal=1;
        else if (_case.y==(*T).tab[m].y-1 && _case.x==(*T).tab[m].x+1) diagonal=1;
        else if (_case.y==(*T).tab[m].y && _case.x==(*T).tab[m].x) diagonal=1;

    }
    if(diagonal==1) bannissable=0;
    return bannissable;
}

void AfficheGrille(int nlig,int ncol, int nban, T_Tab_Case *T, struct T_Case pion)
{
    int i, j, h, k, case_deja_faite;
    printf ("   ");
    for(i=1;i<= ncol;i++)
    {
        printf("%3d ",i);

    }
    printf("\n");
    for(h=1;h<= nlig;h++)
    {
        if(h<10) printf("%d |",h);
        else printf("%d|", h);
        for(i=1;i<= ncol;i++)
        {
            case_deja_faite=0;
            if (h==pion.x && i==pion.y)
                {
                    printf(" O |");
                    case_deja_faite=1;
                }
            for(k=0;k<=nban;k++)
            {

                if ((h==(*T).tab[k].x) && (i==(*T).tab[k].y))
                {
                    printf (" X |");
                    case_deja_faite=1;
                }



            }
            if (case_deja_faite==0) printf(" - |");

        }
        printf("\n");
    }
}

void Voisines(int nlig, int ncol, int nban, int nb_vois, T_Tab_Case *t, T_Tab_Case T, struct T_Case _case)
{
    int i,j,z;
    int bannie=0;
    for(i=(_case.x)+1; i<=(_case.x)+2; i++)
        {
            if(nban!=0)
            {
                for(j=0; j<nban; j++)
                {

                    if(T.tab[j].x==i && T.tab[j].y==_case.y)
                        bannie=1;

                }

            }
            if(bannie==0)
            {

                nb_vois++;
                (*t).tab[nb_vois-1].x=i;
                (*t).tab[nb_vois-1].y=_case.y;
            }
        }


    for(i=(_case.y)+1; i<=(_case.y)+2; i++)
        {
            if(nban!=0)
            {
                for(j=0; j<nban; j++)
                {
                    if(T.tab[j].x==_case.x && T.tab[j].y==i)
                        bannie=1;
                }

            }
            if(bannie==0)
            {

                nb_vois++;
                (*t).tab[nb_vois-1].x=_case.x;
                (*t).tab[nb_vois-1].y=i;
            }
        }

}

/*void Calcul_Nimbers(int nim[][VMAX],int*nlig,int*ncol,int*nban, T_Tab_Case nban )
{
    int i,k,j,h,nimber_voisine;
    int nb_vois=0;
    struct T_Tab_Case vois;
    struct T_Case _case ;
    for(i=0;i<nlig;i++)
   {
       for(k=0;k<ncol;k++)
       {
           nim[i][k]=2;
       }
   }
    nim[*nlig-1][*ncol-1]=0;
    if(*nban!=0)
    {
        for(j=0;j<=*nban;j++)
        {
        nim[ban.tab[z].x-1][ban.tab[z].y-1]=4;
        }
    }

    for(i=nlig;i>=1;i=i-1)
    {
        for(k=ncol;k>=1;k=k-1)
        {
            _case.x=k;
            _case.y=i;
            if(nim[i-1][k-1]!=5)
            {
                   Voisines(_case,&nb_vois,nban,ban,*nlig,*ncol);
                   nimber_voisin=1;
                   if(nb_vois!=0)
                   {
                       for(h=0;h<nb_vois;h++)
                       {
                           if(nim[vois.tab[h].x-1][vois.tab[h].y-1]==0)
                           {
                               nimber_voisine=0;
                           }
                       }
                       if(nimber_voisine==1)
                       {
                           nim[i-1][k-1]=0;
                       }
                       else{
                           nim[i-1][k-1];
                       }
                   }

            }
        }
    }
}
*/
void 




