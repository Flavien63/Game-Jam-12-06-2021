#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "perso.h"

//gcc perso.c perso.h -o perso

#define LONGUEUR 300
#define LARGEUR 200
#define HAUTEUR_SAUT 10
#define LARGEUR_PERSO 2
#define HAUTEUR_PERSO 10

int map[LONGUEUR][LARGEUR];
etat_perso_t *etat_joueur;

int main()
{
    printf("%d\n", !2);
    return 0;
}

int deplacement_perso(int vertical, int horizontal)
{
    int i;
    int j;

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
        if (decalage_perso_haut())
        { //en train de sauter
            etat_joueur->saut--;
        }
        else
        { //bloque par obstacle, arret du saut
            etat_joueur->saut = 0;
        }
    }
    else
    {
        //gravite();
    }

    /****** DEPLACEMENT GAUCHE - DROITE *******/
    if (horizontal == -1) //deplacement gauche
    {
        decalage_perso_gauche();
    }
    else if (horizontal == 1) //deplacement droite
    {
        decalage_perso_droite();
    }
}

//Renvoie 1 s'il peut sauter, 0 sinon (ie obstacle au dessus)
int decalage_perso_haut()
{
    int i;
    int j;
    int peut_sauter = rien_haut();
    if (peut_sauter) //pas d'obstacle au dessus
    {
        for (i = 1; i <= HAUTEUR_PERSO; i++)
        {
            for (j = 0; j < LARGEUR_PERSO; j++)
            { //recopie les cases du perso sur la ligne au dessus
                map[etat_joueur->x + j][etat_joueur->y - HAUTEUR_PERSO] = map[etat_joueur->x + j][etat_joueur->y - HAUTEUR_PERSO + i];
            }
        }
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
        int i;
        int j;

        for (i = 0; i < HAUTEUR_PERSO; i++)
        {
            for (j = 0; j < LARGEUR_PERSO; j++)
            {
                map[indice_cote - j][etat_joueur->y - i] = map[indice_cote - j - 1][etat_joueur->y - i];
            }
        }
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
        int i;
        int j;

        for (i = 0; i < HAUTEUR_PERSO; i++)
        {
            for (j = 0; j < LARGEUR_PERSO; j++)
            {
                map[indice_cote + j][etat_joueur->y - i] = map[indice_cote + j + 1][etat_joueur->y - i];
            }
        }
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
        air_cote = air_cote + map[indice_cote][etat_joueur->y - i];
        ++i;
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
        int dessus_tete_gauche = map[etat_joueur->x][dessus_tete];         //case en dessous pied gauche
        int dessus_tete_droite = map[etat_joueur->x + 1][dessus_tete + 1]; //case en dessous pied droit
        air_dessus = ((dessus_tete_gauche == 0) && (dessus_tete_droite == 0));
    }
    return air_dessus;
}

//Renvoie 1 si le perso a au moins un pied sur le sol, 0 sinon
int touche_sol(etat_perso_t *etat_joueur)
{
    int touche_sol = 0;
    int sous_pied = etat_joueur->y + 1;

    if (sous_pied < LARGEUR) // verifie que c'est bien dans la matrice
    {
        int sol_gauche = map[etat_joueur->x][sous_pied];     //case en dessous pied gauche
        int sol_droite = map[etat_joueur->x + 1][sous_pied]; //case en dessous pied droit
        touche_sol = ((sol_gauche >= 1 && sol_gauche <= 9) || (sol_droite >= 1 && sol_droite <= 9));
    }
    return touche_sol;
}
