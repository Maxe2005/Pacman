#include "ressources.h"
#include "pacman.h"
#include "ghost.h"
#include "jeu.h"
#include "plateau.h"


int main (int argc, char *argv[]){
    srand(time(NULL));
    initSDL();
    initTTF();
    SDL_Window* window = createWindow("Pacman MACC", FEN_X, FEN_Y);
    SDL_Renderer* ren = createRenderer(window);
    
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        int map[MAP_Y][MAP_X];
        init_map(map);
        SDL_Texture* tils[4];
        init_tils(tils, ren);
        affiche_map(map, tils, ren);
        updateDisplay(ren);

        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // L'utilisateur a cliqué sur la croix ou demandé la fermeture
                running = 0;
            }
        }

    }

    // Nettoyage
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
