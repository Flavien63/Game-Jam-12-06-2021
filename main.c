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
    etat_perso->fin_niveau = 0;
    int couleurs_vie[100][3];
    tableau_vivant(couleurs_vie);
    int couleurs_mort[100][3];
    tableau_mort(couleurs_mort);
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
       // Initialisation de SDL_Mixer
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1; 
    }   

    Mix_Music* music = Mix_LoadMUS("musique-dascenseur.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1; 
    }   
    
    Mix_Music* music_vie = Mix_LoadMUS("vie.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1; 
    }   
   
    Mix_Music* music_mort = Mix_LoadMUS("mort.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }
    Mix_PlayMusic(music, -1); // Joue notre musique   


    SDL_Window *window;
    int width = 900;
    int height = 600;
    int taille = 0;

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SDL_Log() */
    }
    SDL_SetWindowTitle(window, "Des morts et des bulles");
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
    SDL_Event event;
    menu(renderer, taille, couleurs_vie, grille, etat_perso);
    SDL_RenderPresent(renderer);
    int play = 1; //vaut 1 tant qu'on a pas clique sur le bouton play
    int running = 1;
    int px, py;
    int flag; //si flag=1, redessiner, sinon rien
    while ((running) && (play))
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    play = 0;
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    flag = 1;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                px = event.button.x;
                py = event.button.y;
                if ((px < 3 * width / 4) && (px > width / 4))
                {
                    if ((py > height / 6) && (py < 2 * height / 6))
                    {
                        taille = (taille + 1) % 3;
                        width = 900 + 300 * taille;
                        height = 600 + 200 * taille;
                        menu(renderer, taille, couleurs_vie, grille, etat_perso);
                        SDL_SetWindowSize(window, width, height);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                        flag = 1;
                    }
                    else
                    {
                        if ((py > 5 * height / 12) && (py < 7 * height / 12))
                        {
                            play = 0;
                        }
                        else
                        {
                            if ((py > 4 * height / 6) && (py < 5 * height / 6))
                            {
                                running = 0;
                            }
                        }
                    }
                }
                break;
            case SDL_QUIT:
                running = 0;
                break;
            }
            break;
        }
        if (flag)
        {
            SDL_RenderPresent(renderer);
            flag = 0;
        }
    }
    niveau(renderer, taille, numniv(1));
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    import_file(grille, "level1_alive.txt", 1, etat_perso);
    placement_perso(grille, etat_perso);
    dessingrille(grille, renderer, couleurs_vie, taille);
    SDL_RenderPresent(renderer);
    int dephorizon = 0;
    int depvertical = 0;
    int bouge; //bouge 0 : rien, bouge 1 : actualiser
    int vm = 0;
    char *nomfichier;
    int n = 1;
    int c = 0; 
    Mix_HaltMusic();
    Mix_PlayMusic(music_vie, -1);
    
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
        c = c + 1;
        bouge = deplacement_perso(depvertical, dephorizon, grille, etat_perso);
        depvertical = 0;
        dephorizon = 0;
        if (c > 600)
        {
            flag = 1;
            c = 0;
        }
        if (etat_perso->mort != vm)
        {
            Mix_RewindMusic();
            Mix_HaltMusic();
            if (etat_perso->mort)
               Mix_PlayMusic(music_mort, -1);
            else
               Mix_PlayMusic(music_vie, -1);

            vm = etat_perso->mort;
            nomfichier = nomniveau(n, vm);
            import_file(grille, nomfichier, 0, etat_perso);
            placement_perso(grille, etat_perso);
            flag = 1;
        }
        if (bouge == 1)
        {
            if (vm)
                actualiserdessin(grille, etat_perso, renderer, couleurs_mort, taille);
            else
                actualiserdessin(grille, etat_perso, renderer, couleurs_vie, taille);
            SDL_RenderPresent(renderer);
        }
        if (etat_perso->fin_niveau == 1)
        {
            n = n + 1;
            if (n <= NB_NIVEAU)
            {
                niveau(renderer, taille, numniv(n));
                SDL_RenderPresent(renderer);
                SDL_Delay(2000);
                vm = 0;
                nomfichier = nomniveau(n, vm);
                import_file(grille, nomfichier, 1, etat_perso);
                placement_perso(grille, etat_perso);
                etat_perso->fin_niveau = 0;
                flag = 1;
            }
            else
            {
                running = 0;
                niveau(renderer, taille, "bravo ! C'est fini");
                SDL_RenderPresent(renderer);
                SDL_Delay(2000);
            }
        }
        if (flag == 1)
        {
            if (vm)
                dessingrille(grille, renderer, couleurs_mort, taille);
            else
                dessingrille(grille, renderer, couleurs_vie, taille);
            SDL_RenderPresent(renderer);
            flag = 0;
        }

        SDL_Delay(17);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
