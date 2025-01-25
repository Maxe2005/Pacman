#ifndef PACMAN_H
#define PACMAN_H

#include "ressources.h"
#include "plateau.h"

typedef struct
{
    int position_x;
    int position_y;
    int position_px_x;
    int position_px_y;
    char direction;
    char next_direction;
    SDL_Texture* skin[4];
} Pacman ;

/** Charge les textures dans le tableau "skin" de Pacman
 * @param pacman Une instance de structure de joueur
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_pacman (Pacman *pacman, SDL_Renderer* ren);

/**
 * Vérifie si le pacman est bien placé et initialise ses position en pixel
 * @param pacman Une instance de structure de joueur
 * @param map La map sur laquel va être affiché le pacman
 */
void premier_placement_pacman (Pacman *pacman, int map[MAP_Y][MAP_X]);

/**
 * Place la pacman sur le renderer avec le bon skin
 * @param pacman Une instance de structure de joueur
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void affiche_pacman (Pacman *pacman, SDL_Renderer* ren);

#endif
