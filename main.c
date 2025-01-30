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
    SDL_Window* window = createWindow("Pacman MACC", FEN_X, FEN_Y);
    SDL_Renderer* ren = createRenderer(window);
    
    // Initialisation map, textures pour map et font pour titres
    //Map mape = init_map_dessin();
    //Map mape = init_map_tils();
    //Map *map = &mape;
    const char *nom_map = "Map_originale.csv";
    //save_map_text(nom_map, &map);
    Map *map = load_map_text(nom_map);

    SDL_Texture* tils[4];
    init_tils(tils, ren);
    TTF_Font* font[1];
    init_font(font);

    // Initialisation Pacman
    Pacman pacman;
    init_textures_pacman(&pacman, ren);
    premier_placement_pacman(&pacman, map, 14, 23);

    // Initialisation ghosts
    Ghost Pinky;
    init_textures_Pinky(&Pinky, ren);
    Ghost Blinky;
    init_textures_Blinky(&Blinky, ren);
    Ghost Inky;
    init_textures_Inky(&Inky, ren);
    Ghost Clyde;
    init_textures_Clyde(&Clyde, ren);
    Ghost* ghosts[4] = {&Pinky, &Blinky, &Inky, &Clyde};
    premier_placement_ghost(&Pinky, map, 12, 11);
    premier_placement_ghost(&Blinky, map, 13, 11);
    premier_placement_ghost(&Inky, map, 14, 11);
    premier_placement_ghost(&Clyde, map, 15, 11);

    // Initialisation des vies
    SDL_Texture * skin_vies = loadTexture("ressources/pacman/pakuman_0.bmp", ren);
    pacman.nb_vies = 3;

    // Initialisation variables globales
    unsigned int score = 0;
    char text_score[15];
    SDL_Color white = {255, 255, 255, 255} ;
    char dir;
    int running = 1;

    clock_t start_time = clock();
    const double temps_reaction_pacman = 500.0 / 1000.0 * CLOCKS_PER_SEC; //temps_reaction_pacman convertion de milisecondes à clocks
    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        sprintf(text_score, "Score : %d", score);
        printText(MARGE_BANDEAU_HAUT, MARGE_BANDEAU_HAUT, text_score, MARGE_BANDEAU_HAUT + 250, TAILLE_BANDEAU_HAUT - 2*MARGE_BANDEAU_HAUT, font[0], white, ren);
        affiche_les_vies(ren, skin_vies, pacman.nb_vies);
        affiche_map(map, tils, ren);
        affiche_pacman(&pacman, ren);
        for (int i = 0; i < 4; i++) {
            affiche_ghost(ghosts[i], ren);
        }/*
        affiche_ghost(&Blinky, ren);
        affiche_ghost(&Pinky, ren);
        affiche_ghost(&Inky, ren);
        affiche_ghost(&Clyde, ren);*/
        
        updateDisplay(ren);

        dir = processKeyboard(&running);
        if (dir != ' '){
            pacman.next_direction = dir;
        }
        avance_pacman(&pacman, map, &score);
        for (int i = 0; i < 4; i++) {
            avance_ghost(ghosts[i], map, &pacman);
        }/*
        avance_ghost(&Blinky, map, &pacman);
        avance_ghost(&Pinky, map, &pacman);
        avance_ghost(&Inky, map, &pacman);
        avance_ghost(&Clyde, map, &pacman);*/
        
        /*clock_t current_time = clock();
        if ((double)(current_time - start_time) >= temps_reaction_pacman) {
            avance_ghost(&ghost, map);
            start_time = current_time;
        }
*/


    }

    freeMap(map);
    QuitSDL;
    return 0;
}

