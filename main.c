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
    char text_score[500];
    SDL_Color white = {255, 255, 255, 255} ;
    char dir;
    int running = 1;

    clock_t start_time = clock();
    const double temps_reaction_pacman = 1000.0 / 1000.0 * CLOCKS_PER_SEC; //temps_reaction_pacman convertion de milisecondes à clocks
    
    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        affiche_map(map, tils, ren);
        affiche_pacman(&pacman, ren);
        sprintf(text_score, "Score : %d / dir: %c nextdir: %c/ (x,y) : (%d,%d) / px (x,y) : (%d,%d)",
                score, pacman.direction, pacman.next_direction, pacman.position_x, pacman.position_y, pacman.position_px_x, pacman.position_px_y);
        printText(10, 20, text_score, 980, 60, font[0], white, ren);
        updateDisplay(ren);

        dir = processKeyboard(&running);
        if (dir != ' '){
            pacman.next_direction = dir;
        }
        avance_pacman(&pacman, map);
        /*
        clock_t current_time = clock();
        if ((double)(current_time - start_time) >= temps_reaction_pacman) {
            avance_pacman(&pacman, map);
            start_time = current_time;
        }*/



    }

    QuitSDL;
    return 0;
}

