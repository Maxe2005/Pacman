#ifndef PLATEAU_H
#define PLATEAU_H

#include "ressources.h"

#define MAP_X 28
#define MAP_Y 31
#define ORIGINE_X 0
#define ORIGINE_Y TAILLE_BANDEAU_HAUT
#define TAILLE_CASE (int)((FEN_Y-TAILLE_BANDEAU_HAUT)/MAP_Y)

/**
 * Initialise le contenu de la map. C'est à dire la position des tils (murs, gum, ...)
 * @param map La map vide à remplire
 */
void init_map (int map[MAP_Y][MAP_X]);


/**
 * Initialise les textures des tils dans un tableau
 * @param tils Le tableau vide à remplire
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_tils (SDL_Texture* tils[4], SDL_Renderer* ren);


/**
 * Affiche les tils de la map sur le renderer
 * @param map La map à afficher
 * @param tils Le tableau contenant les textures des différents tils
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */ 
void affiche_map (int map[MAP_Y][MAP_X], SDL_Texture* tils[4], SDL_Renderer* ren);

#endif