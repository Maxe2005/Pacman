#ifndef PACMAN_H
#define PACMAN_H

#include "ressources.h"
#include "plateau.h"

#define VITESSE_PACMAN 2

typedef struct
{
    int position_x;
    int position_y;
    int position_px_x;
    int position_px_y;
    int taille_px;
    char direction;
    char next_direction;
    SDL_Texture* skin[9];  // 9 textures pour Pacman
    SDL_Texture* skin_mort[11]; // 11 textures pour l'animation de Pacman_mort
    int nb_vies;
    int pacman_frame; // pour la gestion des frames
    int pacman_frame_delay; // pour le délai entre les frames
    int is_dead; // Nouvelle variable pour savoir si Pacman est mort
} Pacman ;


/** Charge les textures dans le tableau "skin" de Pacman
 * @param pacman Une instance de structure de joueur
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_pacman (Pacman *pacman, SDL_Renderer* ren);

/** Charge les textures dans le tableau "skin_mort" de Pacman lorsqu'il rentre en collision avec un ghost
 * @param pacman Une instance de structure de joueur
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_textures_pacman_mort (Pacman *pacman, SDL_Renderer* ren);

/**
 * Vérifie si le pacman est bien placé et initialise ses position en pixel
 * @param pacman Une instance de structure de joueur
 * @param map La map sur laquel va être affiché le pacman
 */
void premier_placement_pacman (Pacman *pacman, Map *map);

/**
 * Converti une position en cases (sur le tableau) en une position en pixel (sur la fenêtre)
 * @param pacman Une instance de structure de joueur
 * @param map La map sur laquel va être affiché le pacman
 * @param difference La différence de position (en cases) par rapport à la position actuelle (en cases) du pacman
 * @return La position en pixel du pacman (avec la différence demandée)
 */
int conversion_case_pixel_en_x (Pacman *pacman, Map *map, int difference);

/**
 * Converti une position en cases (sur le tableau) en une position en pixel (sur la fenêtre)
 * @param pacman Une instance de structure de joueur
 * @param map La map sur laquel va être affiché le pacman
 * @param difference La différence de position (en cases) par rapport à la position actuelle (en cases) du pacman
 * @return La position en pixel du pacman (avec la différence demandée)
 */
int conversion_case_pixel_en_y (Pacman *pacman, Map *map, int difference);

/**
 * Place la pacman sur le renderer avec le bon skin
 * @param pacman Une instance de structure de joueur
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void affiche_pacman (Pacman *pacman, SDL_Renderer* ren);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle va être affiché le pacman
 */
void aller_a_droite (Pacman *pacman, Map *map);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle va être affiché le pacman
 */
void aller_a_gauche (Pacman *pacman, Map *map);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle va être affiché le pacman
 */
void aller_en_haut (Pacman *pacman, Map *map);

/**
 * Modifie la position en pixel de l'instance du pacman et sa direction
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle va être affiché le pacman
 */
void aller_en_bas (Pacman *pacman, Map *map);

/**
 * Opérations logique pour le déplacement continu du pacman
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle va être affiché le pacman
 * @return 0 si tout c'est bien passé, 1 si erreur
 */
int avance_pacman (Pacman *pacman, Map *map);

/**
 * Gère la téléportation toriques de bord de map du pacman
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle se déplace le pacman
 */
void gestion_map_torique (Pacman *pacman, Map *map);

#endif
