#include "main.h"
int grille[200][300];
etat_perso_t *etat_perso;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        return EXIT_FAILURE; 
    }
    SDL_Window   * window;
    int width = 1500;
    int height = 1000;

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width, height, 
            SDL_WINDOW_RESIZABLE); 
    
    if (window == 0) 
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        /* on peut aussi utiliser SDL_Log() */
    }
    SDL_Renderer *renderer;
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }
    initialiser(grille);
    dessingrille(grille,renderer);
    afficherEcran(renderer);
    int running=1;
    SDL_Event event;
    int dephorizon=0;
    int depvertical=0;
    int bouge; //bouge 0 : rien, bouge 1 : actualiser
    int vm=0;
    int flag=0; //flag 1: redessiner, flag 0 : rien
    
    while (running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_WINDOWEVENT:
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_CLOSE:
                            running=0;
                            break;
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            width = event.window.data1;
                            height = event.window.data2;
                            flag=1;
                            break;
                         case SDL_WINDOWEVENT_EXPOSED:
                            flag=1;
                            break;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT :
                            dephorizon=dephorizon-1
                            break;
                        case SDLK_RIGHT :
                            dephorizon=dephorizon+1
                            break;
                        case SDLK_UP :
                            depvertical=1;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT :
                    running=0;
                    break;
            }
            break;
        }
        if (flag)
        {
            bouge=deplacement_perso(depvertical,dephorizon);
            depvertical=0;
            dephorizon=0;
            if (etat_perso->santé!=vm)
            {
                vm=etat_perso->santé;
                charger_carte();//a faire
                flag=1;
            }
            if (bouge==1)
            {
                actualiserdessin(grille,etat_perso,renderer,couleurs); 
            }
            if (flag==1)
            {
                dessingrille(grille,renderer,couleurs);
            }
        }
        SDL_Delay(10);
    }
    SDLL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
