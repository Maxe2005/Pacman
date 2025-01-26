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
void affiche_map_tils (int map[MAP_Y][MAP_X], SDL_Texture* tils[4], SDL_Renderer* ren);

/**
 * Dessine sur le renderer un arc de cercle composé de points
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param centerX La position du centre (en pixels) de l'arc de cercle
 * @param centerY La position du centre (en pixels) de l'arc de cercle
 * @param radius Le rayon (en pixels) de l'arc de cercle
 * @param startAngle L'angle de départ (en radiants) de l'arc de cercle
 * @param endAngle L'angle d'arrivée (en radiants) de l'arc de cercle
 * @param thickness L'epaisseur de l'arc de cercle (en pixels)
 * @param nb_pts Le nombres de points composants l'arc de cercle (donc sa résolution)
 */
void drawArc(SDL_Renderer* renderer, const int centerX, const int centerY, const int radius, const double startAngle, const double endAngle, const int thickness, const int nb_pts);

/**
 * Dessine sur le renderer une ligne horizontale
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param x La position (en pixels) du premier point de la ligne (celui à gauche sur le rendu)
 * @param y La position (en pixels) du premier point de la ligne (celui à gauche sur le rendu)
 * @param length La taille (en pixels) de la ligne
 */
void drawLineHorizontal (SDL_Renderer* renderer, const int x, const int y, const int length);

/**
 * Dessine sur le renderer une ligne verticale
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param x La position (en pixels) du premier point de la ligne (celui en haut sur le rendu)
 * @param y La position (en pixels) du premier point de la ligne (celui en haut sur le rendu)
 * @param length La taille (en pixels) de la ligne
 */
void drawLineVertical (SDL_Renderer* renderer, const int x, const int y, const int height);

#endif