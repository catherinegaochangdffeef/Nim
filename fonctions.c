#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entetes.h"
#define VMIN 5
#define VMAX 30

int Lire_Entier(int bi, int bs)
{
    int n;
    do
    {
        scanf("%d", &n);
    }
    while (( n < bi) || (n > bs));
    return n;
}

void Parametres(int *nlig, int *ncol, int *nban, int *niveau, int *next)
{
    printf("Entrez un nombre de lignes compris entre 5 et 30: " );
    *nlig=Lire_Entier(VMIN,VMAX);
    printf("Entrez un nombre de colonnes compris entre 5 et 30: ");
    *ncol=Lire_Entier(VMIN,VMAX);
    printf("Nombre de cases bannies generees: ");
    *nban=Hasard(max(*nlig, *ncol));
    printf("Niveau de difficulte de 1 a 4: ");
    *niveau=Lire_Entier(1,4);
    printf("Qui commence?\nL'ordinateur (1) ou le joueur (2): ");
    *next=Lire_Entier(1,2);
}

int Hasard(int val)
{
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

int Bannissable(int k, int nlig, int ncol, T_Tab_Case *T, struct T_Case _case)
{
    int m, bannissable, diagonal;
    bannissable=0; //Si banissable=0, pas bannissable
    diagonal=0; //Si diagonal=1, bannissable
    if(_case.y == 1 && _case.x == ncol) //coin en bas � gauche
        bannissable=1;
    else if(_case.y == nlig && _case.x == 1) //coin en haut � droite
        bannissable=1;
    else if(_case.x > 1 && _case.y < nlig && _case.y > 1 && _case.x < ncol) //hors bordures
        bannissable=1;
    //else bannissable=0;
    for(m = 0; m < k; m++)
    {
        if (_case.y==(*T).tab[m].y+1 && _case.x==(*T).tab[m].x-1) //diagonale haut droite
            diagonal=1;
        else if (_case.y==(*T).tab[m].y-1 && _case.x==(*T).tab[m].x+1) //diagonale bas gauche
            diagonal=1;
        else if (_case.y==(*T).tab[m].y && _case.x==(*T).tab[m].x) //case bannie sur elle-m�me
            diagonal=1;
    }
    if(diagonal==1) bannissable=0;
    return bannissable;
}

void AfficheGrille(int nlig, int ncol, int nban, T_Tab_Case *T, struct T_Case pion)
{
    int i, j, k, case_deja_faite;
    printf ("   ");
    for(i=1;i<= ncol;i++)
    {
        printf("%3d ",i);

    }
    printf("\n");
    for(j=1;j<= nlig;j++)
    {
        if(j < 10) printf("%d |",j);
        else printf("%d|", j);
        for(i=1;i<= ncol;i++)
        {
            case_deja_faite=0;
            if (j==pion.x && i==pion.y)
                {
                    printf(" O |");
                    case_deja_faite=1;
                }
            for(k=0;k<=nban;k++)
            {

                if ((j==(*T).tab[k].x) && (i==(*T).tab[k].y))
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


//remplacer la table par 0,1,2,3
void Calcul_Nimbers(int nim[][VMAX], int nlig, int ncol)
{
    int x,y;
    int nimber, nimber_tempal = 0;
    for(x=ncol-1;x>=0;x--)//commercer par le dernier case,vertical
    {
        nimber = nimber_tempal;
        for(y=nlig-1;y>=0;y--)//commercer par le dernier case,honrizontal
        {
            nim[x][y]=nimber;
            nimber++;
            nimber%=3;//modulo pour cotroler inferieur � 3
        }
        nimber_tempal+=2;
        nimber_tempal%=3;
    }

}

void Voisines(int nlig, int ncol, int nban, int *nb_vois, T_Tab_Case *vois, T_Tab_Case T, struct T_Case _case)
{
    int i,j,k;
    int bannie=0; //bannie=0 quand pas banni
    *nb_vois=0;
    for(i=(_case.x)+1; i<=(_case.x)+2; i++) //boucle qui teste pour les 2 cases en dessous de la case du pion
        {
            if(nban!=0) //s'il y a des cases bannies
            {
                for(j = 0; j <= nban; j++)
                {
                    if((T.tab[j].x==i) && (T.tab[j].y==_case.y))
                    {
                        bannie=1; //bannie prend la valeur 1
                        break;
                    }
                }
            }
            if((bannie == 0)&&(i <= nlig))
            {
                (*nb_vois)++; //incr�mentation de nb_vois
                (*vois).tab[*nb_vois-1].x=i; //stockage de la coordonn�e x de la case voisine
                (*vois).tab[*nb_vois-1].y=_case.y; //stockage de la coordonn�e y de la case voisine
            }
        }
    bannie=0;
    for(k=(_case.y)+1; k<=(_case.y)+2; k++)//boucle qui teste pour les 2 cases � droite de la case du pion
        {
            if(nban!=0) //s'il y a des cases bannies
            {
                for(j = 0; j <= nban; j++)
                {
                    if((T.tab[j].x==_case.x) && (T.tab[j].y==k))
                    {
                        bannie=1; //bannie prend la valeur 1
                        break;
                    }
                }
            }
            if((bannie == 0)&&(k <= ncol))
            {
                (*nb_vois)++; //incr�mentation de nb_vois
                (*vois).tab[*nb_vois-1].x=_case.x; //stockage de la coordonn�e x de la case voisine
                (*vois).tab[*nb_vois-1].y=k; //stockage de la coordonn�e y de la case voisine
            }
        }
}

struct T_Case Coup_Joueur(struct T_Case pion, T_Tab_Case ban, int nlig, int ncol, int nban)
{
    int i, choice, nb_vois;
    T_Tab_Case vois;
    printf("A ton tour!\n");
    Voisines(nlig, ncol, nban, &nb_vois, &vois, ban, pion);
    if(nb_vois==1)
    {
        printf("Il n'y a qu'une seule possibilite: (%d,%d)\nvalider --->", vois.tab[0].x, vois.tab[0].y);
        scanf("%d", &choice);
        pion.x=vois.tab[0].x;
        pion.y=vois.tab[0].y;
    }
    else
    {
        printf("Veuillez choisir la destination: ");
        for(i = 1; i <= nb_vois; i++)
        {
            printf("%d: (%d,%d) ", i, vois.tab[i-1].x, vois.tab[i-1].y);
        }
        do
        {
            printf("\n--->");
            while(getchar()!='\n');
            scanf("%d", &choice);
        }
        while(choice<1 || choice>nb_vois);
        pion.x=vois.tab[choice-1].x;
        pion.y=vois.tab[choice-1].y;
    }
    return pion;
}

struct T_Case Coup_Ordi_Hasard(struct T_Case pion, T_Tab_Case ban, int nlig, int ncol, int nban)
{
    int choice, nb_vois;
    T_Tab_Case vois;
    Voisines(nlig, ncol, nban, &nb_vois, &vois, ban, pion);
    choice=rand()%nb_vois;
    printf("L'ordinateur deplace le pion en: (%d,%d)\n",vois.tab[choice].x,vois.tab[choice].y);
    pion.x=vois.tab[choice].x;
    pion.y=vois.tab[choice].y;
    return pion;
}

struct T_Case Coup_Ordi_Gagnant(struct T_Case pion, T_Tab_Case ban, int nlig, int ncol, int nban, int nim[][VMAX])
{
    int choice, i, x, y, nb_vois;
    T_Tab_Case vois;
    Voisines(nlig, ncol, nban, &nb_vois, &vois, ban, pion);
    choice=rand()%nb_vois;
    for(i=1;i<nb_vois;i++)
    {
        if(nim[vois.tab[i].x-1][vois.tab[i].y-1==0])
        {
            choice=i;
            break;
        }
    }
    pion.x=vois.tab[choice].x;
    pion.y=vois.tab[choice].y;
    printf("L'ordinateur deplace le pion en (%d,%d)\n",vois.tab[choice].x, vois.tab[choice].y);
    return pion;
}












