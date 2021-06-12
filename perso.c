#include "perso.h"

/*void init_grille(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
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
}*/
/*
void affichage(int grille[LONGUEUR][LARGEUR])
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
}*/

//Renvoie 1 si le perso a bouge, 0 sinon
int deplacement_perso(int vertical, int horizontal, int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int bouge = 0;

    if (vertical == 1) //appuye sur la touche sauter
    {
        if (etat_joueur->saut == 0) //n'est pas deja entrain de sauter
        {
            if (touche_sol(grille, etat_joueur)) //est ce que le joueur a un pied sur le sol
            {
                etat_joueur->saut = HAUTEUR_SAUT; //memoire du saut
            }
        }
    }
    /****** SAUT *******/
    if (etat_joueur->saut > 0) //saute
    {
        if (horizontal == 0)
        {

            bouge += decalage_perso_haut(grille, etat_joueur);
            if (bouge) //en train de sauter
            {
                etat_joueur->saut--;
            }
            else
            { //bloque par obstacle, arret du saut
                etat_joueur->saut = 0;
            }
        }/*
        else if (horizontal == 1)
        {
            decalage_perso_diagonale_haut(grille, etat_joueur, 1);
        }
        else if (horizontal == -1)
        {
            decalage_perso_diagonale_haut(grille, etat_joueur, 0);
        }*/
    }
    else
    {
        bouge += gravite(grille, etat_joueur);

        /****** DEPLACEMENT GAUCHE - DROITE *******/
        if (horizontal == -1) //deplacement gauche
        {
            bouge += decalage_perso_gauche(grille, etat_joueur);
        }
        else if (horizontal == 1) //deplacement droite
        {
            bouge += decalage_perso_droite(grille, etat_joueur);
        }
        if (bouge >= 2)
        {
            //etat_joueur->saut = 0;
            etat_joueur->mort = !etat_joueur->mort;
            //effacement_perso(grille, etat_joueur);
            //etat_joueur->y = etat_joueur->y - 1;
            //placement_perso(grille, etat_joueur);
            //printf("etat mort %d\n", etat_joueur->mort);
        }
    }
    return bouge;
}

/*
int decalage_perso_diagonale_haut(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur, int droite)
{

    int peut_bouger = rien_haut(grille, etat_joueur);
    peut_bouger = peut_bouger && ((1 - droite) * rien_gauche(grille, etat_joueur) || droite * rien_droite(grille, etat_joueur));
    int x_cote = etat_joueur->x + (1 - droite) * (-1) + droite * LARGEUR_PERSO;
    int y_dessus = etat_joueur->y + (1 - droite) * (-1) + droite * LARGEUR_PERSO;
    if (x_cote >= 0 && x_cote <= LONGUEUR && y_dessus >= 0) //pas d'obstacle en diagonale
    {
        peut_bouger = peut_bouger && grille[y_dessus][x_cote];
    }
    else
    {
        peut_bouger = 0;
    }

    if (peut_bouger)
    {
        effacement_perso(grille, etat_joueur);
        --etat_joueur->y;
        if (droite)
        {
            ++etat_joueur->x;
        }
        else
        {
            --etat_joueur->x;
        }
        peut_bouger += placement_perso(grille, etat_joueur);
    }
    return peut_bouger;
}*/

//Renvoie 1 s'il peut sauter, 0 sinon (ie obstacle au dessus)
int decalage_perso_haut(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int peut_sauter = rien_haut(grille, etat_joueur);
    if (peut_sauter && etat_joueur->y - 1 >= 0) //pas d'obstacle au dessus
    {
        effacement_perso(grille, etat_joueur);
        --etat_joueur->y;
        peut_sauter += placement_perso(grille, etat_joueur);
    }
    return peut_sauter;
}

//Renvoie 1 si le perso c'est deplace sur la droite, 0 sinon (ie obstacle)
int decalage_perso_droite(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int succes = rien_droite(grille, etat_joueur);
    if (succes)
    {

        effacement_perso(grille, etat_joueur);
        ++etat_joueur->x;
        succes += placement_perso(grille, etat_joueur);
    }
    return succes;
}

//Renvoie 1 si le perso c'est deplace sur la gauche, 0 sinon (ie obstacle)
int decalage_perso_gauche(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int succes = rien_gauche(grille, etat_joueur);
    if (succes)
    {
        effacement_perso(grille, etat_joueur);
        --etat_joueur->x;
        succes += placement_perso(grille, etat_joueur);
    }
    return succes;
}

//droite = 1 si on veut checker a droite du perso, 0 si on veut a gauche
//Renvoie 1 si il ya que du vide sur le cote, 0 sinon
int rien_cote(int droite, int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int air_cote = 0;
    int i = 0;
    int indice_cote = etat_joueur->x + droite * LARGEUR_PERSO + (1 - droite) * (-1);

    while (i < HAUTEUR_PERSO && (air_cote == 0 || air_cote > 19))
    {
        air_cote = grille[etat_joueur->y - i][indice_cote];
        ++i;
    }

    if (air_cote == 0)
    {
        air_cote = 1;
    }
    else if (air_cote > 0 && air_cote <= 19) //tout les blocks a cote ne sont pas de la dirt
    {
        air_cote = 0;
    }

    return air_cote;
}

//Renvoie 1 si il y a que de l'air a droite du perso, 0 sinon
int rien_droite(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    return rien_cote(1, grille, etat_joueur);
}
//Renvoie 1 si il ya que de l'air a gauche du perso, 0 sinon
int rien_gauche(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    return rien_cote(0, grille, etat_joueur);
}

//Revoie 1 si il y a de l'air au dessus du perso
int rien_haut(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int air_dessus = 0;
    int dessus_tete = etat_joueur->y - HAUTEUR_PERSO;

    if (dessus_tete >= 0) // verifie que c'est bien dans la matrice
    {
        int dessus_tete_gauche = grille[dessus_tete][etat_joueur->x];     //case en dessous pied gauche
        int dessus_tete_droite = grille[dessus_tete][etat_joueur->x + 1]; //case en dessous pied droit
        air_dessus = ((dessus_tete_gauche == 0) && (dessus_tete_droite == 0));
        air_dessus = air_dessus || ((dessus_tete_gauche > 19) && (dessus_tete_droite > 19));
        air_dessus = air_dessus || ((dessus_tete_gauche > 19) && (dessus_tete_droite == 0));
        air_dessus = air_dessus || ((dessus_tete_gauche == 0) && (dessus_tete_droite > 19));
    }
    return air_dessus;
}

//Renvoie 1 si le perso a au moins un pied sur le sol, 0 sinon
int touche_sol(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int touche_sol = 0;
    int sous_pied = etat_joueur->y + 1;

    if (sous_pied < LARGEUR) // verifie que c'est bien dans la matrice
    {
        int sol_gauche = grille[sous_pied][etat_joueur->x];     //case en dessous pied gauche
        int sol_droite = grille[sous_pied][etat_joueur->x + 1]; //case en dessous pied droit
        touche_sol = ((sol_gauche >= 1 && sol_gauche <= 19) || (sol_droite >= 1 && sol_droite <= 19));
    }
    return touche_sol;
}

//Retourne 1 si la gravite agit, 0 sinon (touche deja le sol)
int gravite(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int succes = 0;
    if (!touche_sol(grille, etat_joueur) && (etat_joueur->y + GRAVITE < LARGEUR))
    {
        succes = 1;
        effacement_perso(grille, etat_joueur);
        etat_joueur->y = etat_joueur->y + GRAVITE;
        succes += placement_perso(grille, etat_joueur);
    }
    return succes;
}

void effacement_perso(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int i, j;
    for (i = 0; i < HAUTEUR_PERSO; i++)
    {
        for (j = 0; j < LARGEUR_PERSO; j++)
        {
            grille[etat_joueur->y - i][etat_joueur->x + j] = 0;
        }
    }
}

//Renvoie 1 si le perso est place sur une case >9 ie pic ...
int placement_perso(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int degat = 0;
    int i, j;
    for (i = 0; i < HAUTEUR_PERSO; i++)
    {
        for (j = 0; j < LARGEUR_PERSO; j++)
        {
            degat = degat || (case_change_etat(grille[etat_joueur->y - i][etat_joueur->x + j]));
            grille[etat_joueur->y - i][etat_joueur->x + j] = 90;
        }
    }
    return degat;
}

int case_change_etat(int valeur_case)
{
    return (valeur_case > 19); // tout ce qui n'est pas de la dirt
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
