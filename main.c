#include "ressources.h"
#include "pacman.h"
#include "ghost.h"
#include "jeu.h"
#include "plateau.h"


int main (int argc, char *argv[]){
    srand(time(NULL));
    // Initialisation globale fenêtre
    initSDL();
    initTTF();
    SDL_Window* window = createWindow("Pacman C²HAMD", FEN_X, FEN_Y);
    SDL_Renderer* ren = createRenderer(window);
    
    // Initialisation map, textures pour map et font pour titres
    int map[MAP_Y][MAP_X];
    init_map(map);
    SDL_Texture* tils[4];
    init_tils(tils, ren);
    TTF_Font* font[1];
    init_font(font);

    // Initialisation Pacman
    Pacman pacman;
    init_textures_pacman(&pacman, ren);
    premier_placement_pacman(&pacman, map, 1, 1);

    // Initialisation variables globales
    /*unsigned int score = 0;
    char text_score[15];
    SDL_Color white = {255, 255, 255, 255} ;
    char dir;
    int running = 1;

    clock_t start_time = clock();
    const double temps_reaction_pacman = 1000.0 / 1000.0 * CLOCKS_PER_SEC; //temps_reaction_pacman convertion de milisecondes à clocks
    */
    
    debut_jeu (ren,map,tils,&pacman,font);
        



    

    QuitSDL;
    return 0;
}

