#ifndef PACMAN_H
#define PACMAN_H

#include "ressources.h"
#include "plateau.h"

#define VITESSE_PACMAN 3

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
 * @param x La position sur la map de pacman au début
 * @param y La position sur la map de pacman au début
 */
void premier_placement_pacman (Pacman *pacman, int map[MAP_Y][MAP_X], const int x, const int y);

/**
 * Place la pacman sur le renderer avec le bon skin
 * @param pacman Une instance de structure de joueur
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void affiche_pacman (Pacman *pacman, SDL_Renderer* ren);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 */
void aller_a_droite (Pacman *pacman);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 */
void aller_a_gauche (Pacman *pacman);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 */
void aller_en_haut (Pacman *pacman);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 */
void aller_en_bas (Pacman *pacman);

/**
 * Opérations logique pour le déplacement continu du pacman
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle va être affiché le pacman
 * @param score Le score global à modifier si <gum> ou <cherry> rencontré
 * @return 0 si tout c'est bien passé, 1 si erreur
 */
int avance_pacman (Pacman *pacman, int map[MAP_Y][MAP_X], int *score);

/**
 * Met à niveau le score si le pacman est sur <gum> ou <cherry>. Déclanche le mode <frightened> si <Big Gum> rencontré
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle se déplace le pacman
 * @param score Le score global à modifier si <gum> ou <cherry> rencontré
 */
void update_score (Pacman *pacman, int map[MAP_Y][MAP_X], int *score);

#endif
