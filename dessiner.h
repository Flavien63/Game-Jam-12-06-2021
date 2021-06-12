#ifndef dessiner_h
#define dessiner_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void dessingrille(int grille[n][m], SDL_Renderer *renderer, couleurs[nb][3]);

void actualiserdessin(int grille[n][m],etat_perso_t etat, SDL_Renderer *renderer, couleurs[nb][3]);

#endif
