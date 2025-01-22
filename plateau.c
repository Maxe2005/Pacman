#include "plateau.h"

void init_map (int map[MAP_Y][MAP_X]){
    int valeurs[MAP_Y][MAP_X] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
    {1,3,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,3,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
    {1,2,2,2,2,1,3,2,2,1,2,2,3,1,2,2,2,2,1},
    {1,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1},
    {1,1,1,1,2,1,0,0,0,0,0,0,0,1,2,1,1,1,1},
    {1,1,1,1,2,1,0,1,1,0,1,1,0,1,2,1,1,1,1},
    {1,1,1,1,2,2,0,1,0,0,0,1,0,2,2,1,1,1,1},
    {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
    {1,1,1,1,2,1,0,0,0,0,0,0,0,1,2,1,1,1,1},
    {1,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1},
    {1,2,2,2,2,1,3,2,2,1,2,2,3,1,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,3,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,3,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
            map[i][j] = valeurs[i][j];
        }
    }
}


void init_tils (SDL_Texture* tils[4], SDL_Renderer* ren){
    tils[0] = loadTexture("ressources/wall.bmp", ren);
    tils[1] = loadTexture("ressources/gum.bmp", ren);
    tils[2] = loadTexture("ressources/bigGum.bmp", ren);
    tils[3] = loadTexture("ressources/cherry.bmp", ren);
}


void affiche_map (int map[MAP_Y][MAP_X], SDL_Texture* tils[4], SDL_Renderer* ren){
    int marge_x = 0;
    int marge_y = TAILLE_BANDEAU_HAUT;
    int taille_case = (FEN_Y-marge_y)/MAP_Y;

    for (int j = 0; j<MAP_Y; j++){
        for (int i = 0; i<MAP_X; i++){
            if (map[j][i] > 0){
                renderTexture(tils[map[j][i] - 1], ren, 
                    marge_x + i*taille_case, marge_y + j*taille_case,
                    taille_case, taille_case);
            }
        }
    }
}
