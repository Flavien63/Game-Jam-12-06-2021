#include "main.h"

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
    int grille[200][300];
    import_file(grille,"level1_alive");
    dessingrille(grille,renderer,couleurs);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
