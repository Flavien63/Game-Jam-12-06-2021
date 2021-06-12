#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "perso.h"

//gcc perso.c perso.h -o perso

#define LONGUEUR 15    //300
#define LARGEUR 10     //200
#define HAUTEUR_SAUT 2 //10
#define LARGEUR_PERSO 2
#define HAUTEUR_PERSO 2 //10
#define GRAVITE 1

int grille[LONGUEUR][LARGEUR];
etat_perso_t *etat_joueur;

void init_grille()
{

    int i, j;
    for (i = 0; i < LONGUEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
        {
            grille[i][j] = 0;
        }
    }
    for (j = 0; j < LONGUEUR; j++)
    {
        grille[j][LARGEUR - 1] = 1;
    }
    grille[etat_joueur->x + 1][etat_joueur->y] = 90;
    grille[etat_joueur->x + 1][etat_joueur->y - 1] = 90;
    grille[etat_joueur->x][etat_joueur->y] = 90;
    grille[etat_joueur->x][etat_joueur->y - 1] = 90;
}

void affichage()
{
    int i, j;
    for (j = 0; j < LARGEUR; j++)
    {
        for (i = 0; i < LONGUEUR; i++)
        {
            if (grille[i][j] == 1)
            {
                printf("■");
            }
            else if (grille[i][j] == 90)
            {
                printf("●");
            }
            else if (grille[i][j] == 20)
            {
                printf("▼");
            }
            else
            {
                printf(" ");
            }
            //printf("%d", grille[i][j]);
        }
        printf("\n");
    }
}

//Renvoie 1 si le perso a bouge, 0 sinon
int deplacement_perso(int vertical, int horizontal)
{
    int bouge = 0;

    if (vertical == 1) //appuye sur la touche sauter
    {
        if (etat_joueur->saut == 0) //n'est pas deja entrain de sauter
        {
            if (touche_sol(etat_joueur)) //est ce que le joueur a un pied sur le sol
            {
                etat_joueur->saut = HAUTEUR_SAUT; //memoire du saut
            }
        }
    }
    /****** SAUT *******/
    if (etat_joueur->saut > 0) //saute
    {
        bouge += decalage_perso_haut();
        if (bouge) //en train de sauter
        {
            etat_joueur->saut--;
        }
        else
        { //bloque par obstacle, arret du saut
            etat_joueur->saut = 0;
        }
    }
    else
    {
        bouge += gravite();
    }

    /****** DEPLACEMENT GAUCHE - DROITE *******/
    if (horizontal == -1) //deplacement gauche
    {
        bouge += decalage_perso_gauche();
    }
    else if (horizontal == 1) //deplacement droite
    {
        bouge += decalage_perso_droite();
    }
    if (bouge >= 2)
    {
        etat_joueur->saut = 0;
        etat_joueur->mort = !etat_joueur->mort;
        //printf("etat mort %d\n", etat_joueur->mort);
    }
    return bouge;
}

//Renvoie 1 s'il peut sauter, 0 sinon (ie obstacle au dessus)
int decalage_perso_haut()
{
    int peut_sauter = rien_haut();
    if (peut_sauter && etat_joueur->y - 1 >= 0) //pas d'obstacle au dessus
    {
        effacement_perso();
        --etat_joueur->y;
        peut_sauter += placement_perso();
    }
    return peut_sauter;
}

//Renvoie 1 si le perso c'est deplace sur la droite, 0 sinon (ie obstacle)
int decalage_perso_droite()
{
    int succes = rien_droite();
    if (succes)
    {
        int indice_cote = etat_joueur->x + LARGEUR_PERSO;

        effacement_perso();
        ++etat_joueur->x;
        succes += placement_perso();
    }
    return succes;
}

//Renvoie 1 si le perso c'est deplace sur la gauche, 0 sinon (ie obstacle)
int decalage_perso_gauche()
{
    int succes = rien_gauche();
    if (succes)
    {
        int indice_cote = etat_joueur->x - 1;

        effacement_perso();
        --etat_joueur->x;
        succes += placement_perso();
    }
    return succes;
}

//droite = 1 si on veut checker a droite du perso, 0 si on veut a gauche
//Renvoie 1 si il ya que du vide sur le cote, 0 sinon
int rien_cote(int droite)
{
    int air_cote = 0;
    int i = 0;
    int indice_cote = etat_joueur->x + droite * LARGEUR_PERSO + (1 - droite) * (-1);

    while (i < HAUTEUR_PERSO && !air_cote)
    {
        air_cote = air_cote + grille[indice_cote][etat_joueur->y - i];
        ++i;
    }
    if (air_cote / HAUTEUR_PERSO > 9) //tout les blocks a cote ne sont pas de la dirt
    {
        air_cote = 0;
    }
    return !air_cote;
}

//Renvoie 1 si il y a que de l'air a droite du perso, 0 sinon
int rien_droite()
{
    return rien_cote(1);
}
//Renvoie 1 si il ya que de l'air a gauche du perso, 0 sinon
int rien_gauche()
{
    return rien_cote(0);
}

//Revoie 1 si il y a de l'air au dessus du perso
int rien_haut()
{
    int air_dessus = 0;
    int dessus_tete = etat_joueur->y - HAUTEUR_PERSO;

    if (dessus_tete >= 0) // verifie que c'est bien dans la matrice
    {
        int dessus_tete_gauche = grille[etat_joueur->x][dessus_tete];     //case en dessous pied gauche
        int dessus_tete_droite = grille[etat_joueur->x + 1][dessus_tete]; //case en dessous pied droit
        air_dessus = ((dessus_tete_gauche == 0) && (dessus_tete_droite == 0));
        air_dessus = air_dessus || ((dessus_tete_gauche > 9) && (dessus_tete_droite > 9));
        air_dessus = air_dessus || ((dessus_tete_gauche > 9) && (dessus_tete_droite == 0));
        air_dessus = air_dessus || ((dessus_tete_gauche == 0) && (dessus_tete_droite > 9));
    }
    return air_dessus;
}

//Renvoie 1 si le perso a au moins un pied sur le sol, 0 sinon
int touche_sol()
{
    int touche_sol = 0;
    int sous_pied = etat_joueur->y + 1;

    if (sous_pied < LARGEUR) // verifie que c'est bien dans la matrice
    {
        int sol_gauche = grille[etat_joueur->x][sous_pied];     //case en dessous pied gauche
        int sol_droite = grille[etat_joueur->x + 1][sous_pied]; //case en dessous pied droit
        touche_sol = ((sol_gauche >= 1 && sol_gauche <= 9) || (sol_droite >= 1 && sol_droite <= 9));
    }
    return touche_sol;
}

//Retourne 1 si la gravite agit, 0 sinon (touche deja le sol)
int gravite()
{
    int succes = 0;
    if (!touche_sol() && etat_joueur->y + GRAVITE < LARGEUR)
    {
        succes = 1;
        effacement_perso();
        etat_joueur->y = etat_joueur->y + GRAVITE;
        succes += placement_perso();
    }
    return succes;
}

void effacement_perso()
{
    int i, j;
    for (i = 0; i < HAUTEUR_PERSO; i++)
    {
        for (j = 0; j < LARGEUR_PERSO; j++)
        {
            grille[etat_joueur->x + j][etat_joueur->y - i] = 0;
        }
    }
}

//Renvoie 1 si le perso est place sur une case >9 ie pic ...
int placement_perso()
{
    int degat = 0;
    int i, j;
    for (i = 0; i < HAUTEUR_PERSO; i++)
    {
        for (j = 0; j < LARGEUR_PERSO; j++)
        {
            degat = degat || (case_change_etat(grille[etat_joueur->x + j][etat_joueur->y - i]));
            grille[etat_joueur->x + j][etat_joueur->y - i] = 90;
        }
    }
    return degat;
}

int case_change_etat(int valeur_case)
{
    return (valeur_case > 9); // tout ce qui n'est pas de la dirt
}


/*
int main()
{

    etat_joueur = (etat_perso_t *)malloc(sizeof(etat_perso_t));
    etat_joueur->x = 2;
    etat_joueur->y = 8;
    etat_joueur->saut = 0;
    etat_joueur->mort = 0;
    init_grille();

    grille[2][6] = 20;

    grille[5][7] = 20;
    grille[5][8] = 20;

    affichage();
    printf("%d\n", deplacement_perso(1, 0));
    affichage();

    printf("%d\n", deplacement_perso(0, 0));
    affichage();

    printf("%d\n", deplacement_perso(0, 0));
    affichage();

    deplacement_perso(0, 0);
    affichage();

    deplacement_perso(0, 0);
    affichage();

    printf("%d\n", deplacement_perso(0, 1));
    affichage();

    printf("%d\n", deplacement_perso(0, 1));
    affichage();

    printf("%d\n", deplacement_perso(0, 1));
    affichage();

    printf("%d\n", deplacement_perso(0, 0));
    affichage();

    deplacement_perso(0, -1);
    affichage();

    //printf("2 || 1 : %d\n", 1 || 2);
    return 0;
}
*/