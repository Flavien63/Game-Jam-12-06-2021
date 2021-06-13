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

//Renvoie 1 si le perso a bouge, 2 si il a bouge et pris des degats, 3 si gagne (ie coupe), 0 sinon (ie pas bouge)
int deplacement_perso(int vertical, int horizontal, int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int bouge = 0;
    int j = 0;
    effacement_perso(grille, etat_joueur);

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
        for (j = 0; j < SAUT; ++j)
            bouge = decalage_perso_haut(grille, etat_joueur) || bouge;

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
        for (j = 0; j < GRAVITE; ++j)
        {
            bouge = gravite(grille, etat_joueur) || bouge;
        }
    }

    /****** DEPLACEMENT GAUCHE - DROITE *******/
    if (horizontal == -1) //deplacement gauche
    {
        for (j = 0; j < DEPLACEMENT_COTE; j++)
        {
            bouge = decalage_perso_gauche(grille, etat_joueur) || bouge;
        }
    }
    else if (horizontal == 1) //deplacement droite
    {
        for (j = 0; j < DEPLACEMENT_COTE; j++)
        {
            bouge = decalage_perso_droite(grille, etat_joueur) || bouge;
        }
    }

    bouge += placement_perso(grille, etat_joueur);

    if (bouge >= 2)
    {
        //etat_joueur->saut = 0;
        etat_joueur->mort = !etat_joueur->mort;
        //effacement_perso(grille, etat_joueur);
        //etat_joueur->y = etat_joueur->y - 1;
        //placement_perso(grille, etat_joueur);
        //printf("etat mort %d\n", etat_joueur->mort);
        printf("%d \n", etat_joueur->mort);
    }

    return bouge;
}

//Renvoie 1 s'il peut sauter, 0 sinon (ie obstacle au dessus)
int decalage_perso_haut(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int peut_sauter = rien_haut(grille, etat_joueur);
    if (peut_sauter && etat_joueur->y - 1 >= 0) //pas d'obstacle au dessus
    {
        etat_joueur->y -= 1;
    }
    return peut_sauter;
}

//Renvoie 1 si le perso c'est deplace sur la droite, 0 sinon (ie obstacle)
int decalage_perso_droite(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int succes = rien_droite(grille, etat_joueur);
    if (succes)
    {

        etat_joueur->x += 1;
    }
    return succes;
}

//Renvoie 1 si le perso c'est deplace sur la gauche, 0 sinon (ie obstacle)
int decalage_perso_gauche(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int succes = rien_gauche(grille, etat_joueur);
    if (succes)
    {
        etat_joueur->x -= 1;
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
    else if (air_cote > 0 && air_cote <= 19) //si ya un block de dirt
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
    int air_dessus = 1;
    int dessus_tete = etat_joueur->y - HAUTEUR_PERSO;
    int j;
    int case_dessus_tete = 0;

    if (dessus_tete >= 0) // verifie que c'est bien dans la matrice
    {
        /*   int dessus_tete_gauche = grille[dessus_tete][etat_joueur->x];     //case en dessous pied gauche
        int dessus_tete_droite = grille[dessus_tete][etat_joueur->x + 1]; //case en dessous pied droit
        air_dessus = ((dessus_tete_gauche == 0) && (dessus_tete_droite == 0));
        air_dessus = air_dessus || ((dessus_tete_gauche > 19) && (dessus_tete_droite > 19));
        air_dessus = air_dessus || ((dessus_tete_gauche > 19) && (dessus_tete_droite == 0));
        air_dessus = air_dessus || ((dessus_tete_gauche == 0) && (dessus_tete_droite > 19));*/
        for (j = 0; j < LARGEUR_PERSO; j++)
        {
            case_dessus_tete = ((grille[dessus_tete][etat_joueur->x + j] == 0) || (grille[dessus_tete][etat_joueur->x + j] > 19));
            air_dessus = air_dessus && case_dessus_tete;
        }
    }
    return air_dessus;
}

int mort(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int mort = 0;
    int sous_pied = etat_joueur->y + 1;

    if (sous_pied < LARGEUR) // verifie que c'est bien dans la matrice
    {
        int sol_gauche = grille[sous_pied][etat_joueur->x];     //case en dessous pied gauche
        int sol_droite = grille[sous_pied][etat_joueur->x + 1]; //case en dessous pied droit
        mort = ((sol_gauche >= 20 && sol_gauche <= 29) || (sol_droite >= 20 && sol_droite <= 29));
    }
    return mort;
}

//Renvoie 1 si le perso a au moins un pied sur le sol, 0 sinon
int touche_sol(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int touche_sol = 0;
    int sous_pied = etat_joueur->y + 1;
    int case_sous_pied;
    int j;

    if (sous_pied < LARGEUR) // verifie que c'est bien dans la matrice
    {
        /*   int sol_gauche = grille[sous_pied][etat_joueur->x];     //case en dessous pied gauche
        int sol_droite = grille[sous_pied][etat_joueur->x + 1]; //case en dessous pied droit
        touche_sol = ((sol_gauche >= 1 && sol_gauche <= 19) || (sol_droite >= 1 && sol_droite <= 19));
        */
        for (j = 0; j < LARGEUR_PERSO; j++)
        {
            case_sous_pied = ((grille[sous_pied][etat_joueur->x + j] > 0) && (grille[sous_pied][etat_joueur->x + j] <= 19));
            touche_sol = touche_sol || case_sous_pied;
        }
    }

    return touche_sol;
}

//Retourne 1 si la gravite agit, 0 sinon (touche deja le sol)
int gravite(int grille[LONGUEUR][LARGEUR], etat_perso_t *etat_joueur)
{
    int succes = 0;
    if (!touche_sol(grille, etat_joueur) && (etat_joueur->y + 1 < LARGEUR))
    {
        succes = 1;
        etat_joueur->y += 1;
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
    int x, y;
    int valeur_case;
    for (i = 0; i < HAUTEUR_PERSO; i++)
    {
        for (j = 0; j < LARGEUR_PERSO; j++)
        {
            valeur_case = grille[etat_joueur->y - i][etat_joueur->x + j];
            if (valeur_case == 32)
            {
                etat_joueur->fin_niveau = 1;
            }
            else
            {
                degat = degat || (case_change_etat(valeur_case));
            }
            y = etat_joueur->y - i;
            x = etat_joueur->x + j;
            grille[y][x] = dessine_perso(i, j);
        }
    }
    return degat;
}

int dessine_perso(int i, int j)
{
    int partie_perso;
    if (j >= 2 && j <= 3)
    {
        if (i >= 0 && i <= 2)
        {
            partie_perso = 91; //jambes
        }
        else if (j >= 4 && j <= 7)
        {
            partie_perso = 93; //t-shirt
        }
        else if (j >= 8 && j <= 9)
        {
            partie_perso = 94; //tete
        }
    }
    else if (j == 0 || j == 4)
    {
        if (i >= 4 && i <= 7)
        {
            partie_perso = 92; //bras
        }
    }
    else
    {
        partie_perso = 90;
    }
    return partie_perso;
}

int case_change_etat(int valeur_case)
{
    return (valeur_case > 19 && valeur_case <= 30); // tout ce qui n'est pas de la dirt
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
