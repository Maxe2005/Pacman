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
    
    int map[MAP_Y][MAP_X];
    init_map(map);
    SDL_Texture* tils[4];
    init_tils(tils, ren);
    TTF_Font* font[1];
    init_font(font);

    Pacman pacman;
    init_textures_pacman(&pacman, ren);
    pacman.position_x = 1;
    pacman.position_y = 1;
    pacman.direction = 'd';
    premier_placement_pacman(&pacman, map);

    int score = 0;
    char text_score[15];
    SDL_Color white = {255, 255, 255, 255} ;
    int running = 1;
    
    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        affiche_map(map, tils, ren);
        affiche_pacman(&pacman, ren);
        sprintf(text_score, "Score : %d", score);
        printText(50, 15, text_score, 300, 70, font[0], white, ren);
        updateDisplay(ren);

        pacman.next_direction = processKeyboard(&running);

        

    }

    QuitSDL;
    return 0;
}
