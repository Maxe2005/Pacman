#ifndef PACMAN_H
#define PACMAN_H

#include "ressources.h"

typedef struct
{
    int position_x;
    int position_y;
    SDL_Texture* skin[4];
} Pacman ;

/** Charge les textures dans le tableau "skin" de Pacman
 * @param pacman Une instance de structure de joueur
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_pacman (Pacman pacman, SDL_Renderer* ren);

#endif
