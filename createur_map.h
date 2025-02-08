#ifndef CREATEUR_MAP_H
#define CREATEUR_MAP_H

#include "ressources.h"
#include "plateau.h"
#include "audio.h"

#define NB_BUTTONS_CREATEUR_MAP 5
#define TAILLE_BARRE_MENU_X 250

typedef enum {
    SELECTION_VIDE_INTERNE,
    SELECTION_MUR,
    SELECTION_VIDE_EXTERNE,
    SELECTION_GUM,
    SELECTION_BIG_GUM,
    SELECTION_NULL
} SelectionType_createur_map;

typedef struct {
    Button button_base;
    SelectionType_createur_map type;
} SelectionButton_createur_map;

/**
 * La boucle de fonctionnement du créateur de map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void main_loop_createur_map (SDL_Renderer* ren, Musique* musique);

/**
 * Initialise les boutons du créateur de map
 * @param selectionButtons Le tableau contenant tous les boutons
 * @param button_height Dimention des boutons
 * @param button_width Dimention des boutons
 * @param button_margin_y Distance entre les boutons
 */
void init_buttons_createur_map (SelectionButton_createur_map selectionButtons[NB_BUTTONS_CREATEUR_MAP], int button_height, int button_margin_y, int button_width);

/**
 * Affiche les boutons du créateur de map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param boutons Le tableau contenant tous les boutons
 */
void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map boutons[NB_BUTTONS_CREATEUR_MAP]);

#endif
