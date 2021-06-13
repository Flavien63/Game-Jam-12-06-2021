#include "dessiner.h"

void dessingrille(int grille[200][300], SDL_Renderer *renderer, int couleurs[100][3],int t)
{
    SDL_Rect rect;
    int k, i, c;
    for (k = 0; k < 200; k++)
    {
        for (i = 0; i < 300; i++)
        {
            c = grille[k][i];
            SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
            rect.x = (3+t) * i;
            rect.y = (3+t) * k;
            rect.w = (3+t);
            rect.h = (3+t);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void actualiserdessin(int grille[200][300], etat_perso_t *etat, SDL_Renderer *renderer, int couleurs[100][3],int t)
{
    SDL_Rect rect;
    int k, i, c;
    for (k = (etat->x) - 1 - DEPLACEMENT_COTE; k < ((etat->x) + LARGEUR_PERSO + 1 + DEPLACEMENT_COTE); k++)
    {
        for (i = (etat->y) + 1 + GRAVITE + ACCELERATION_MAX + HAUTEUR_SAUT; i > ((etat->y) - HAUTEUR_PERSO - ACCELERATION_MAX - GRAVITE - 1); i--)
        {
            if ((k >= 0 && k < LARGEUR) && (i >= 0 && i < LONGUEUR))
            {
                c = grille[i][k];
                SDL_SetRenderDrawColor(renderer, couleurs[c][0], couleurs[c][1], couleurs[c][2], 255);
                rect.x = (3+t) * k;
                rect.y = (3+t) * i;
                rect.w = (3+t);
                rect.h = (3+t);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

char *nomniveau(int n, int vm)
{

    char *nom = malloc(17 * sizeof(char));
    nom[0] = '\0';
    strcat(nom, "level");
    char nb[3] = "";
    sprintf(nb, "%d", n);
    strcat(nom, nb);
    if (vm)
        strcat(nom, "_death.txt");
    else
        strcat(nom, "_alive.txt");
    return nom;
}

void menu(SDL_Renderer *renderer,int taille, int couleurs_vie[100][3], int grille[200][300], etat_perso_t * etat)
//taille=0 : 900*600 taille=1 : 1200*800 taille=2 : 1500*1000
{
    import_file(grille, "menu.txt", 0, etat);
    dessingrille(grille, renderer, couleurs_vie, taille);
    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
    }
    SDL_Rect rect;
    int lx=900+300*taille;
    int ly=600+200*taille;
    TTF_Font *font1;
    font1 = TTF_OpenFont("arial.ttf", 100);
    int iW, iH;
    SDL_Color couleur = {0, 255, 255, 255};
    
    SDL_Surface *surf = TTF_RenderText_Blended(font1, "Changer la resolution", couleur);
    SDL_Texture *texttext = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_QueryTexture(texttext, NULL, NULL, &iW, &iH);
    rect.x = lx/4;
    rect.y = ly/6;
    rect.w = lx/2;
    rect.h = ly/6;
    SDL_RenderCopy(renderer, texttext, NULL, &rect);
    
    surf=TTF_RenderText_Blended(font1, "Jouer", couleur);
    texttext = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_QueryTexture(texttext, NULL, NULL, &iW, &iH);
    rect.x = lx/4;
    rect.y = 5*ly/12;
    rect.w = lx/2;
    rect.h = ly/5;
    SDL_RenderCopy(renderer, texttext, NULL, &rect);
    
    surf=TTF_RenderText_Blended(font1, "Quitter", couleur);
    texttext = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_QueryTexture(texttext, NULL, NULL, &iW, &iH);
    rect.x = lx/4;
    rect.y = 8*ly/12;
    rect.w = lx/2;
    rect.h = ly/5;
    SDL_RenderCopy(renderer, texttext, NULL, &rect);

    TTF_CloseFont(font1);
}

void niveau(SDL_Renderer *renderer,int taille,char* mot)
{
    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
    }
    SDL_Rect rect;
    int lx=900+300*taille;
    int ly=600+200*taille;
    rect.x=0;
    rect.y=0;
    rect.w=lx;
    rect.h=ly;
    SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    SDL_RenderFillRect(renderer, &rect);
    TTF_Font *font1;
    font1 = TTF_OpenFont("arial.ttf", 100);
    int iW, iH;
    SDL_Color couleur = {109, 7, 26, 255};
    SDL_Surface *surf=TTF_RenderText_Blended(font1, mot, couleur);
    SDL_Texture *texttext = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_QueryTexture(texttext, NULL, NULL, &iW, &iH);
    rect.x = lx/4;
    rect.y = ly/3;
    rect.w = lx/2;
    rect.h = ly/5;
    SDL_RenderCopy(renderer, texttext, NULL, &rect);
}

char* numniv(int n)
{
    char *nom = malloc(9 * sizeof(char));
    nom[0] = '\0';
    strcat(nom, "niveau");
    char nb[3] = "";
    sprintf(nb, "%d", n);
    strcat(nom, nb);
    return nom;
}