#ifndef __PERSO_H__
#define __PERSO_H__

typedef struct etat_perso
{
    int x;
    int y;
    int saut;
}etat_perso_t;

int rien_haut();

int rien_cote(int droite);
int rien_droite();
int rien_gauche();


int decalage_perso_haut();
int decalage_perso_droite();
int decalage_perso_gauche();



int touche_sol(etat_perso_t *etat_joueur);
int deplacement_perso(int vertical, int horizontal);

#endif