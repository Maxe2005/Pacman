#ifndef GHOST_H
#define GHOST_H

#include "ressources.h"
#include "plateau.h"

#define VITESSE_GHOST 2

typedef struct
{
    int position_x;
    int position_y;
    int position_px_x;
    int position_px_y;
    int target_x;
    int target_y;
    char direction_g; //direction du ghost
    SDL_Texture* skin[4]; 
} Ghost ;

/** Charge les textures dans le tableau "skin" de Ghost
 * @param ghost Une instance de structure du fantome
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_ghost (Ghost *ghost, SDL_Renderer* ren);

/**
 * Vérifie si le ghost est bien placé et initialise ses position en pixel
 * @param ghost Une instance de structure du fantome
 * @param map La map sur laquel va être affiché le ghost
 * @param x La position sur la map de ghost au début
 * @param y La position sur la map de ghost au début
 */
void premier_placement_ghost (Ghost *ghost, int map[MAP_Y][MAP_X], const int x, const int y);

/**
 * Place la ghost sur le renderer avec le bon skin
 * @param ghost Une instance de structure du fantome
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void affiche_ghost (Ghost *ghost, SDL_Renderer* ren);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 */
void aller_a_droite_g (Ghost *ghost);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 */
void aller_a_gauche_g (Ghost *ghost);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 */
void aller_en_haut_g (Ghost *ghost);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 */
void aller_en_bas_g (Ghost *ghost);

/**
 * Génère un nombre aléatoire compris entre les valeurs min et max (incluses).
 * @param min La valeur minimale possible (borne incluse).
 * @param max La valeur maximale possible (borne incluse).
 * @return Un entier aléatoire compris entre min et max.
 */
int nb_alea(int min, int max);

/**
 * Opérations logique pour le déplacement continu du ghost
 * @param ghost Une instance de structure du fantome à déplacer
 * @param map La map sur laquelle va être affiché le ghost
 * @return 0 si tout c'est bien passé, 1 si erreur
 */
int avance_ghost (Ghost *ghost, int map[MAP_Y][MAP_X]);


#endif