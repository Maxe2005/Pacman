#ifndef GHOST_H
#define GHOST_H

#include "ressources.h"
#include "plateau.h"
#include "pacman.h"
#include "jeu.h"

#define VITESSE_GHOST 1

typedef struct
{
    char nom[6];
    int position_x;
    int position_y;
    int position_px_x;
    int position_px_y;
    int taille_px;
    int target_x;
    int target_y;
    char direction;
    int is_affiche; // Booleen définissant si le fantôme est sur le map
    SDL_Texture* skin[4];
} Ghost ;

/**
 * Initialise et répartit les différents ghosts
 * @param ghost L'instance de structure ghost à remplire
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param num_ghost Un numéro pour identifier les différents fantômes
 */
void init_ghost (Ghost *ghost, SDL_Renderer* ren, int num_ghost);

/** Charge les textures de Blinky (le fantôme rouge) dans le tableau "skin" de Ghost
 * @param ghost Une instance de structure du fantome
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_Blinky (Ghost *ghost, SDL_Renderer* ren);

/**
 * Converti une position en cases (sur le tableau) en une position en pixel (sur la fenêtre)
 * @param ghost Une instance de structure du fantome
 * @param map La map sur laquel va être affiché le ghost
 * @param difference La différence de position (en cases) par rapport à la position actuelle (en cases) du pacman
 * @return La position en pixel du pacman (avec la différence demandée)
 */
int conversion_case_pixel_en_x_g (Ghost *ghost, Map *map, int difference);

/**
 * Converti une position en cases (sur le tableau) en une position en pixel (sur la fenêtre)
 * @param ghost Une instance de structure du fantome
 * @param map La map sur laquel va être affiché le ghost
 * @param difference La différence de position (en cases) par rapport à la position actuelle (en cases) du pacman
 * @return La position en pixel du pacman (avec la différence demandée)
 */
int conversion_case_pixel_en_y_g (Ghost *ghost, Map *map, int difference);

/** Charge les textures de Inky (le fantôme cyan) dans le tableau "skin" de Ghost
 * @param ghost Une instance de structure du fantome
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_Inky (Ghost *ghost, SDL_Renderer* ren);

/** Charge les textures de Pinky (le fantôme rose) dans le tableau "skin" de Ghost
 * @param ghost Une instance de structure du fantome
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_Pinky (Ghost *ghost, SDL_Renderer* ren);

/** Charge les textures de Clyde (le fantôme orange) dans le tableau "skin" de Ghost
 * @param ghost Une instance de structure du fantome
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_Clyde (Ghost *ghost, SDL_Renderer* ren);

/**
 * Vérifie si le ghost est bien placé et initialise ses position en pixel
 * @param ghost Une instance de structure du fantome
 * @param map La map sur laquel va être affiché le ghost
 * @param x La position sur la map de ghost au début
 * @param y La position sur la map de ghost au début
 */
void premier_placement_ghost (Ghost *ghost, Map *map, const int x, const int y);

/**
 * Place la ghost sur le renderer avec le bon skin
 * @param ghost Une instance de structure du fantome
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void affiche_ghost (Ghost *ghost, SDL_Renderer* ren);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 * @param map La map sur laquel va être affiché le ghost
 */
void aller_a_droite_g (Ghost *ghost, Map *map);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 * @param map La map sur laquel va être affiché le ghost
 */
void aller_a_gauche_g (Ghost *ghost, Map *map);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 * @param map La map sur laquel va être affiché le ghost
 */
void aller_en_haut_g (Ghost *ghost, Map *map);

/**
 * Modifie la position en pixel de l'instance du ghost et sa direction
 * @param ghost Une instance de structure du fantome à déplacer
 * @param map La map sur laquel va être affiché le ghost
 */
void aller_en_bas_g (Ghost *ghost, Map *map);

/**
 * Génère un nombre aléatoire compris entre les valeurs min et max (incluses).
 * @param min La valeur minimale possible (borne incluse).
 * @param max La valeur maximale possible (borne incluse).
 * @return Un entier aléatoire compris entre min et max.
 */
int nb_alea(int min, int max);

/**
 * Le choix de la direction du ghost généré en aléatoire
 * @param ghost Une instance de structure de fantôme
 * @param choix_valides Un tableau contenants les direction vers lesquel le ghost peut se diriger
 * @param nb_choix Le nombre de cases de <choix_valides> remplies
 */
void choix_direction_aleatoire (Ghost *ghost, char choix_valides[4], const int nb_choix);

/**
 * Vérifie si le ghost est en contacte avec le pacman
 * @param ghost Une instance de structure de fantôme
 * @param pacman Une instance de structure de joueur
 */
void is_colision_pacman (Ghost *ghost, Pacman *pacman);

/**
 * Opérations logique pour le déplacement continu du ghost
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 * @return 0 si tout c'est bien passé, 1 si erreur
 */
int avance_ghost (Ghost *ghost, Map *map, Pacman *pacman);

/**
 * Gère la téléportation toriques de bord de map des ghost
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void gestion_map_torique_g (Ghost *ghost, Map *map);

#endif