#include "plateform.h"
#include "perso.h"
//droite = 1 si on veut checker a droite du plateform, 0 si on veut a gauche
//Renvoie 1 si il ya que du vide sur le cote, 0 sinon
int rien_cote_plateform(int droite, int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform, etat_perso_t *etat_joueur)
{
    int air_cote = 0;
    int i = 0;
    int indice_cote = etat_plateform->x + droite * LARGEUR_PLATEFORM + (1 - droite) * (-1);

    while (i < HAUTEUR_PLATEFORM && (air_cote == 0 || air_cote > 19))
    {
        air_cote = grille[etat_plateform->y - i][indice_cote];
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
    else if (air_cote >= 90 && air_cote < +99)
    {
        if (droite == 1)
        {
            decalage_perso_droite(grille, etat_joueur);
        }
        else
        {
            decalage_perso_gauche(grille, etat_joueur);
        }
    }

    return air_cote;
}

//Renvoie 1 si il y a que de l'air a droite du plateform, 0 sinon
int rien_droite_plateform(int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform, etat_perso_t *etat_joueur)
{
    return rien_cote_plateform(1, grille, etat_plateform, etat_joueur);
}
//Renvoie 1 si il ya que de l'air a gauche du plateform, 0 sinon
int rien_gauche_plateform(int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform, etat_perso_t *etat_joueur)
{
    return rien_cote_plateform(0, grille, etat_plateform, etat_joueur);
}

int decalage_plateform_droite(int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform, etat_perso_t *etat_joueur)
{
    int succes = rien_cote_plateform(1, grille, etat_plateform, etat_joueur);
    if (succes)
    {
        etat_plateform->y += 1;
    }
    return succes;
}

int decalage_plateform_gauche(int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform, etat_perso_t *etat_joueur)
{
    int succes = rien_cote_plateform(1, grille, etat_plateform, etat_joueur);
    if (succes)
    {
        etat_plateform->y -= 1;
    }
    return succes;
}

int deplacement_plateform(int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform, etat_perso_t *etat_joueur)
{
    if (etat_plateform->x == etat_plateform->x_g)
    {
        etat_plateform->droite = 1;
    }
    else if (etat_plateform->x == etat_plateform->x_d)
    {
        etat_plateform->droite = 0;
    }
    effacement_plateform(init_grille, etat_plateform);
    if (etat_plateform->droite)
    {
        decalage_plateform_droite(grille, etat_plateform, etat_joueur);
    }
    else if (etat_plateform->droite == 0)
    {
        decalage_plateform_gauche(grille, etat_plateform, etat_joueur);
    }

    placement_plateform(grille, etat_plateform);

    return 0;
}

etat_plateform_t *creation_plateform()
{
    etat_plateform_t *plateform = malloc(sizeof(etat_plateform_t *));
    plateform->x_d = 50;
    plateform->y_d = 100;
    plateform->x_g = 150;
    plateform->y_g = 100;
    plateform->droite = 0;
    plateform->x = 70;
    plateform->y = 100;
    return plateform;
}

void effacement_plateform(int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform)
{
    //    int degat = 0;
    int i, j;
    for (i = 0; i < HAUTEUR_PLATEFORM; i++)
    {
        for (j = 0; j < LONGUEUR_PLATEFORM; j++)
        {
            //      degat = degat || (case_change_etat(grille[etat_joueur->x + j][etat_joueur->y - i]));
            grille[etat_plateform_t->x + j][etat_plateform_t->y - i] = 0;
        }
    }
    //return degat;
}
void placement_plateform(int grille[LONGUEUR][LARGEUR], etat_plateform_t *etat_plateform)
{
    //int degat = 0;
    int i, j;
    for (i = 0; i < HAUTEUR_PLATEFORM; i++)
    {
        for (j = 0; j < LONGUEUR_PLATEFORM; j++)
        {
            // degat = degat || (case_change_etat(grille[etat_joueur->x + j][etat_joueur->y - i]));
            grille[etat_plateform_t->x + j][etat_plateform_t->y - i] = 40;
        }
    }
    //return degat;
}
