#ifndef GHOST_H
#define GHOST_H

#include "ressources.h"
#include "plateau.h"
#include "pacman.h"

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
    char etat_precedent[10];// L'état précédent du ghost : chase, scatter, frightened ou eaten
    char etat[10]; // L'état du ghost : chase, scatter, frightened ou eaten
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
 * Opérations logique pour le déplacement continu du ghost
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 * @return 0 si tout c'est bien passé, 1 si erreur
 */
int avance_ghost (Ghost *ghost, Map *map, Pacman* pacman, Ghost* Blinky);

/**
 * Gère la téléportation toriques de bord de map des ghost
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void gestion_map_torique_g (Ghost *ghost, Map *map);

/**
 * Défini le point target de Blinky en mode chase
 * @param ghost Une instance de structure de fantôme
 * @param pacman Une instance de structure de joueur
 */
void chase_target_Blinky (Ghost *ghost, Pacman* pacman);

/**
 * Défini le point target de Pinky en mode chase
 * @param ghost Une instance de structure de fantôme
 * @param pacman Une instance de structure de joueur
 */
void chase_target_Pinky (Ghost *ghost, Pacman* pacman);

/**
 * Défini le point target de Inky en mode chase
 * @param ghost Une instance de structure de fantôme
 * @param pacman Une instance de structure de joueur
 * @param Blinky L'instance de fantôme de Blinky (car le target de Inky dépend de la position de Blinky)
 */
void chase_target_Inky (Ghost *ghost, Pacman* pacman, Ghost* Blinky);

/**
 * Défini le point target de Clyde en mode chase
 * @param ghost Une instance de structure de fantôme
 * @param pacman Une instance de structure de joueur
 * @param map La map sur laquelle va être affiché le ghost
 */
void chase_target_Clyde (Ghost *ghost, Pacman* pacman, Map *map);

/**
 * Défini le point target de Blinky en mode scatter
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void scatter_target_Blinky (Ghost *ghost, Map *map);

/**
 * Défini le point target de Pinky en mode scatter
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void scatter_target_Pinky (Ghost *ghost, Map *map);

/**
 * Défini le point target de Inky en mode scatter
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void scatter_target_Inky (Ghost *ghost, Map *map);

/**
 * Défini le point target de Clyde en mode scatter
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void scatter_target_Clyde (Ghost *ghost, Map *map);

/**
 * Définie la nouvelle direction du fantôme en fonction de leurs états différents
 * @param ghost Une instance de structure de fantôme
 * @param choix_valides Un tableau avec des direction pratiquables (sans murs)
 * @param nb_choix Le nombre de directions dans <choix_valides>
 * @param pacman Une instance de structure de joueur
 * @param Blinky L'instance de fantôme de Blinky (car le target de Inky dépend de la position de Blinky)
 * @param map La map sur laquelle va être affiché le ghost
 */
void choix_direction (Ghost *ghost, char choix_valides[4], const int nb_choix, Pacman* pacman, Ghost* Blinky, Map *map);

/**
 * Regarde la direction actuelle du fantôme et de fait se déplacer dans cette direction
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void suivre_direction (Ghost *ghost, Map *map);

/**
 * Regarde la direction actuelle du fantôme et de fait se déplacer dans la direction inverse
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void faire_demi_tour (Ghost *ghost, Map *map);

/**
 * Modifie la direction du fantôme pour aller vers le point target
 * @param ghost Une instance de structure de fantôme
 * @param choix_valides Un tableau avec des direction pratiquables (sans murs)
 * @param nb_choix Le nombre de directions dans <choix_valides>
 * @param map La map sur laquelle va être affiché le ghost
 */
void choix_direction_vers_target (Ghost *ghost, char choix_valides[4], const int nb_choix, Map *map);

/**
 * Calcule la distance entre 2 points sur la map
 * @param x1 abscisse du premier point 
 * @param y1 ordonnée du premier point 
 * @param x2 abscisse du deuxième point 
 * @param y2 ordonnée du deuxième point
 * @return La distance entre ces deux points
 */
int distance_entre_2_points (int x1, int y1, int x2, int y2);

/**
 * Fait les actions à effectuer lors d'un changement d'état
 * @param ghost Une instance de structure de fantôme
 * @param map La map sur laquelle va être affiché le ghost
 */
void changement_etat (Ghost *ghost, Map *map);

#endif