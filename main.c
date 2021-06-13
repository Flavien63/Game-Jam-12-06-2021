#include "main.h"

int main()
{
    Uint8 *keystates;
    int grille[200][300];
    etat_perso_t *etat_perso;
    etat_perso = malloc(sizeof(etat_perso_t));
    etat_perso->x = 0;
    etat_perso->y = 0;
    etat_perso->saut = 0;
    etat_perso->mort = 0;
    int couleurs_vie[100][3];
    tableau_vivant(couleurs_vie);
    int couleurs_mort[100][3];
    tableau_mort(couleurs_mort);
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window;
    int width = 900;
    int height = 600;

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SDL_Log() */
    }
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
    import_file(grille, "level1_alive.txt",1,etat_perso);
    placement_perso(grille, etat_perso);
    dessingrille(grille, renderer, couleurs_vie);
    SDL_RenderPresent(renderer);
    int running = 1;
    SDL_Event event;
    int dephorizon = 0;
    int depvertical = 0;
    int bouge; //bouge 0 : rien, bouge 1 : actualiser
    int vm = 0;
    int flag = 0; //flag 1: redessiner, flag 0 : rien
    char *nomfichier;
    int n = 1;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    running = 0;
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    width = event.window.data1;
                    height = event.window.data2;
                    flag = 1;
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    flag = 1;
                    break;
                }
                break;
            case SDL_QUIT:
                running = 0;
                break;
            }
            break;
        }
        keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_LEFT])
        {
            dephorizon = dephorizon - 1;
        }
        if (keystates[SDL_SCANCODE_RIGHT])
        {
            dephorizon = dephorizon + 1;
        }
        if (keystates[SDL_SCANCODE_UP])
        {
            depvertical = 1;
        }
        bouge = deplacement_perso(depvertical, dephorizon, grille, etat_perso);
        depvertical = 0;
        dephorizon = 0;
        if (etat_perso->mort != vm)
        {
            vm = etat_perso->mort;
            nomfichier = nomniveau(n, vm);
            import_file(grille, nomfichier,0,etat_perso);
            placement_perso(grille, etat_perso);
            flag = 1;
        }
        if (bouge == 1)
        {
            if (vm)
                actualiserdessin(grille, etat_perso, renderer, couleurs_mort);
            else
                actualiserdessin(grille, etat_perso, renderer, couleurs_vie);
            SDL_RenderPresent(renderer);
        }
        if (bouge==3)
        {
            n=n+1;
            vm=0;
            nomfichier=nomniveau(n,vm);
            import_file(grille,nomfichier,1,etat_perso);
        }
        if (flag == 1)
        {
            if (vm)
                dessingrille(grille, renderer, couleurs_mort);
            else
                dessingrille(grille, renderer, couleurs_vie);
            SDL_RenderPresent(renderer);
            flag=0;
        }

        SDL_Delay(17);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}