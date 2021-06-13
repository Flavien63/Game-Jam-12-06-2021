#ifndef __PLATEFORM_H__
#define __PLATEFORM_H__

#include "perso.h"

#define LONGUEUR_PLATEFORM 20
#define HAUTEUR_PLATEFORM 10


typedef struct etat_plateform
{
    int x;
    int y;
    int x_g;
    int y_g;
    int x_d;
    int y_d;
    int droite;
}etat_plateform_t;

int rien_cote_plateform(int droite, int grille[LONGUEUR][LARGEUR], etat_plateform_t*, etat_perso_t*);
int rien_droite_plateform(int grille[LONGUEUR][LARGEUR], etat_plateform_t*, etat_perso_t*);
int rien_gauche_plateform(int grille[LONGUEUR][LARGEUR], etat_plateform_t*, etat_perso_t*);

int decalage_plateform_droite(int grille[LONGUEUR][LARGEUR], etat_plateform_t*etat_plateform, etat_perso_t * etat_perso);
int decalage_plateform_gauche(int grille[LONGUEUR][LARGEUR], etat_plateform_t*etat_plateform, etat_perso_t * etat_perso);


#endif
