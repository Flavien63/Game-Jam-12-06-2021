#include "dessiner.h"

void dessingrille(int grille[200][300], SDL_Renderer *renderer, int couleurs[100][3])
{
    SDL_Rect rect;
    int k,i,c;
    for(k=0;k<200;k++)
    {
        for (i=0;i<300;i++)
        {
            c = grille[k][i];
            SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
            rect.x = 5*i;
            rect.y = 5*k;
            rect.w = 5;
            rect.h = 5;
            SDL_RenderFillRect(renderer, &rect );
        }
    }
}

void actualiserdessin(int grille[200][300],etat_perso_t* etat, SDL_Renderer *renderer, int couleurs[100][3])
{
    SDL_Rect rect;
    int k=etat->x -2;
    int i=etat->y +1;
    int c;
     for(k;k<(etat->x +4);k++)
    {
        for (i;i>(etat->y -12);i--)
        {
            c = grille[i][k];
            SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
            rect.x = 5*i;
            rect.y = 5*k;
            rect.w = 5;
            rect.h = 5;
            SDL_RenderFillRect(renderer, &rect );
        }
    }
}
