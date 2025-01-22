#include "pacman.h"


void init_textures_pacman (Pacman pacman, SDL_Renderer* ren){
    pacman.skin[0] = loadTexture("ressources/pakuman_0.bmp", ren);
    pacman.skin[1] = loadTexture("ressources/pakuman_1.bmp", ren);
    pacman.skin[2] = loadTexture("ressources/pakuman_2.bmp", ren);
    pacman.skin[3] = loadTexture("ressources/pakuman_3.bmp", ren);
}
