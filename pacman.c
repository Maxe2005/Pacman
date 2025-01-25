#include "pacman.h"


void init_textures_pacman (Pacman *pacman, SDL_Renderer* ren){
    pacman->skin[0] = loadTexture("ressources/pakuman_0.bmp", ren);
    pacman->skin[1] = loadTexture("ressources/pakuman_1.bmp", ren);
    pacman->skin[2] = loadTexture("ressources/pakuman_2.bmp", ren);
    pacman->skin[3] = loadTexture("ressources/pakuman_3.bmp", ren);
}

void premier_placement_pacman (Pacman *pacman, int map[MAP_Y][MAP_X]){
    if (map[pacman->position_y][pacman->position_x] == 1){
        printf("Erreur dans le premier placement de pacman sur la map");
    }
    map[pacman->position_y][pacman->position_x] = 0;
    pacman->position_px_x = ORIGINE_X + pacman->position_x*TAILLE_CASE;
    pacman->position_px_y = ORIGINE_Y + pacman->position_y*TAILLE_CASE;
}

void affiche_pacman (Pacman *pacman, SDL_Renderer* ren) {
    SDL_Texture* tex;
    if (pacman->direction == 'd'){
        tex = pacman->skin[0];
    }
    if (pacman->direction == 'g'){
        tex = pacman->skin[2];
    }
    if (pacman->direction == 'h'){
        tex = pacman->skin[1];
    }
    if (pacman->direction == 'b'){
        tex = pacman->skin[3];
    }
    renderTexture(tex, ren, pacman->position_px_x, pacman->position_px_y, TAILLE_CASE, TAILLE_CASE);
}

