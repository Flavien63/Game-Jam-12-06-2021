#include "dessiner.h"

void dessingrille(int grille[200][300], SDL_Renderer *renderer, int couleurs[100][3])
{
    SDL_Rect rect;
    int k, i, c;
    for (k = 0; k < 200; k++)
    {
        for (i = 0; i < 300; i++)
        {
            c = grille[k][i];
            SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
            rect.x = 3 * i;
            rect.y = 3 * k;
            rect.w = 3;
            rect.h = 3;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void actualiserdessin(int grille[200][300], etat_perso_t *etat, SDL_Renderer *renderer, int couleurs[100][3])
{
    SDL_Rect rect;
    int k,i,c;
    for (k=(etat->x) - 1; k < ((etat->x) + 4); k++)
    {
        for (i=(etat->y) + 1; i > ((etat->y) - 11); i--)
        {
            c = grille[i][k];
            SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
            rect.x = 3 * k;
            rect.y = 3 * i;
            rect.w = 3;
            rect.h = 3;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}


char* nomniveau(int n,int vm)
{
	 
    char* nom=malloc(17*sizeof(char));
	 nom[0]='\0';
    strcat(nom,"level");
	 char nb[3]="";
	 sprintf(nb,"%d",n);
	 strcat(nom,nb);
    if (vm) strcat(nom,"_death.txt");
    else strcat(nom,"_alive.txt");
    return nom;
}
