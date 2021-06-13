#ifndef dessiner_h
#define dessiner_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "couleurs.h"
#include "perso.h"
#include "init_level.h"

void dessingrille(int grille[200][300], SDL_Renderer *renderer, int couleurs[100][3],int t);

void actualiserdessin(int grille[200][300],etat_perso_t *etat, SDL_Renderer *renderer, int couleurs[100][3],int t);

char* nomniveau(int n,int vm);

void menu(SDL_Renderer *renderer,int taille, int couleurs_vie[100][3], int grille[200][300], etat_perso_t *etat);

void niveau(SDL_Renderer *renderer,int taille,char* mot);

char* numniv(int n);
#endif
