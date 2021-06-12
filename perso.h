#ifndef __PERSO_H__
#define __PERSO_H__
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
 
#define LONGUEUR 300
#define LARGEUR 200
#define HAUTEUR_SAUT 10
#define LARGEUR_PERSO 2
#define HAUTEUR_PERSO  10
#define GRAVITE 1

typedef struct etat_perso
{
    int x;
    int y;
    int saut;
    int mort; //0 dans le niveau vie, 1 dans le niveau mort
} etat_perso_t;

void init_grille(int grille[LONGUEUR][LARGEUR], etat_perso_t *);
void affichage(int grille[LONGUEUR][LARGEUR]);

int rien_haut(int grille[LONGUEUR][LARGEUR], etat_perso_t *);

int rien_cote(int droite,int grille[LONGUEUR][LARGEUR], etat_perso_t *);
int rien_droite(int grille[LONGUEUR][LARGEUR], etat_perso_t *);
int rien_gauche(int grille[LONGUEUR][LARGEUR], etat_perso_t *);

int decalage_perso_haut(int grille[LONGUEUR][LARGEUR], etat_perso_t *);
int decalage_perso_droite(int grille[LONGUEUR][LARGEUR], etat_perso_t *);
int decalage_perso_gauche(int grille[LONGUEUR][LARGEUR], etat_perso_t *);

int touche_sol(int grille[LONGUEUR][LARGEUR], etat_perso_t *);
int deplacement_perso(int vertical, int horizontal,int grille[LONGUEUR][LARGEUR], etat_perso_t *);
int gravite(int grille[LONGUEUR][LARGEUR], etat_perso_t *);

void effacement_perso(int grille[LONGUEUR][LARGEUR], etat_perso_t *);
int placement_perso(int grille[LONGUEUR][LARGEUR], etat_perso_t *);

int case_change_etat(int valeur_case);

#endif
