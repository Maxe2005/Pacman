#ifndef CREATEUR_MAP_H
#define CREATEUR_MAP_H

#include "ressources.h"
#include "plateau.h"
#include "audio.h"

#define NB_BUTTONS 9
#define NB_BUTTONS_SELECTION_REMPLISSAGE 5
#define TAILLE_BARRE_MENU_X 250
#define ZOOM_MAX 5 // Le nombre de cases minimum avec le zoom au maximum*
#define VITESSE_ZOOM 2
#define VITESSE_MOVE_ZOOM 1
#define FONT_SIZE 32
#define MAX_TEXT_LENGTH 10
#define CURSOR_BLINK_TIME 500

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
 * @param buttons Un regroupement de tous les boutons
 * @param selectionButtons Le tableau contenant tous les boutons
 * @param button_height Dimention des boutons
 * @param button_width Dimention des boutons
 * @param button_grille Le bouton pour afficher et cacher la grille d'aide
 * @param button_enregistrer Permet de sauvgarder la map créée
 * @param button_zoom_plus Augmente le zoom sur la map actuelle
 * @param button_zoom_moins Diminue le zoom sur la map actuelle
 */
void init_buttons_createur_map (Button* buttons[NB_BUTTONS], int button_height, int button_width, SelectionButton_createur_map selectionButtons[NB_BUTTONS_SELECTION_REMPLISSAGE], 
                                Button* button_grille, Button* button_enregistrer, Button* button_zoom_plus, Button* button_zoom_moins);

/**
 * Affiche les boutons du créateur de map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param boutons_selection Le tableau contenant les boutons de selection
 * @param boutons Le tableau contenant tous les boutons
 */
void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map boutons_selection[NB_BUTTONS_SELECTION_REMPLISSAGE], Button* boutons[NB_BUTTONS]);

/**
 * Affiche un quadrillage par dessus la map pour se repérer dessus
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param map La map en cours d'édition
 */
void affiche_quadrillage (SDL_Renderer* ren, Map* map);

/**
 * Modifie la map avec la séléction actuelle
 * @param map La map en cours d'édition, affichée (et potentiellement zoomée)
 * @param map_totale La map complète en cours d'édition, non affichée
 * @param x_souris_cases La position de la souris en cases sur la map
 * @param y_souris_cases La position de la souris en cases sur la map
 * @param position_zoom_x Le départ du zoom en x sur la map complète (donc le bord de la map affichée)
 * @param position_zoom_y Le départ du zoom en y sur la map complète (donc le bord de la map affichée)
 */
void modif_case (Map* map, Map* map_totale, int x_souris_cases, int y_souris_cases, int position_zoom_x, int position_zoom_y);

/**
 * Test si la souris est sur le bouton
 * @param button Le bouton
 * @param x_souris_px La position de la souris sur l'axe x en pixels
 * @param y_souris_px La position de la souris sur l'axe y en pixels
 */
int is_souris_sur_button (Button button, int x_souris_px, int y_souris_px);

/**
 * Copy profonde de la map source
 * @param src La map source
 */
Map copyMap(const Map *src);

/**
 * Modifie la map affichée pour coller au zoom
 * @param map La map affichée
 * @param map_totale La map complète non affichée
 * @param zoom la valeur du zoom
 * @param position_zoom_x Le départ du zoom en x sur la map complète (donc le bord de la map affichée)
 * @param position_zoom_y Le départ du zoom en y sur la map complète (donc le bord de la map affichée)
 */
void nouveau_zoom (Map* map, Map* map_totale, int zoom, int position_zoom_x, int position_zoom_y);

#endif
