#ifndef __PERSO_H__
#define __PERSO_H__

typedef struct etat_perso
{
    int x;
    int y;
    int saut;
    int mort;  //0 dans le niveau vie, 1 dans le niveau mort
}etat_perso_t;

void init_grille();
void affichage();

int rien_haut();

int rien_cote(int droite);
int rien_droite();
int rien_gauche();


int decalage_perso_haut();
int decalage_perso_droite();
int decalage_perso_gauche();



int touche_sol();
int deplacement_perso(int vertical, int horizontal);
int gravite();

void effacement_perso();
void placement_perso();




#endif