#ifndef CREATEUR_MAP_H
#define CREATEUR_MAP_H

#include "ressources.h"
#include "plateau.h"
#include "audio.h"

#define NB_BUTTONS 12
#define NB_BUTTONS_SELECTION_REMPLISSAGE 5
#define TAILLE_BARRE_MENU_X 550
#define ZOOM_MAX 5 // Le nombre de cases minimum avec le zoom au maximum
#define TAILLE_MAX_MAP 50
#define TAILLE_MIN_MAP ZOOM_MAX + 5
#define VITESSE_ZOOM 2
#define VITESSE_MOVE_ZOOM 1
#define FONT_SIZE 32
#define MAX_TEXT_LENGTH 10
#define CURSOR_BLINK_TIME 500
#define MAX_NB_LENGTH 2 // Nombre de colones et de lignes de la map <= 99

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

typedef struct {
    Button button_base;
    int temps_affichage; // en secondes
    SDL_Color couleur_message;
    SDL_Color couleur_fond;
    int is_visible;
} Message;

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
 * @param button_symetrie_verticale Active et désactive la symétrie verticale
 * @param button_symetrie_horizontale Active et désactive la symétrie horizontale
 */
void init_buttons_createur_map (Button* buttons[NB_BUTTONS], int button_height, int button_width, SelectionButton_createur_map selectionButtons[NB_BUTTONS_SELECTION_REMPLISSAGE], 
                                Button* button_modif_taille_map, Button* button_grille, Button* button_enregistrer, Button* button_zoom_plus, Button* button_zoom_moins, Button* button_symetrie_verticale, Button* button_symetrie_horizontale);

/**
 * Affiche les boutons du créateur de map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param boutons_selection Le tableau contenant les boutons de selection
 * @param boutons Le tableau contenant tous les boutons
 * @param is_symetrie_verticale Variable active et désactive de la symétrie verticale
 * @param is_symetrie_horizontale Variable active et désactive de la symétrie horizontale
 * @param color_texte La couleur du texte des boutons
 * @param color_base La couleur de base du fond du bouton
 * @param color_touch La couleur du fond du bouton quand la souris est sur le bouton
 * @param color_selected La couleur du fond du bouton quand le bouton est séléctionné
 */
void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map boutons_selection[NB_BUTTONS_SELECTION_REMPLISSAGE], Button* boutons[NB_BUTTONS], int is_symetrie_horizontale, int is_symetrie_verticale, SDL_Color color_texte, SDL_Color color_touch, SDL_Color color_base, SDL_Color color_selected);

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
 * @param zoom la valeur du zoom
 * @param position_zoom_x Le départ du zoom en x sur la map complète (donc le bord de la map affichée)
 * @param position_zoom_y Le départ du zoom en y sur la map complète (donc le bord de la map affichée)
 * @param is_symetrie_verticale Variable active et désactive de la symétrie verticale
 * @param is_symetrie_horizontale Variable active et désactive de la symétrie horizontale
 */
void modif_case (Map* map, Map* map_totale, int x_souris_cases, int y_souris_cases, int zoom, int position_zoom_x, int position_zoom_y, int is_symetrie_horizontale, int is_symetrie_verticale);

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

/**
 * Vérifie si la map est conforme (pas de cul de sac)
 * @param map La map complète non affichée
 * @param x Un pointeur à remplir avec la position de la première case trouvée qui n'est pas conforme si elle existe
 * @param y Un pointeur à remplir avec la position de la première case trouvée qui n'est pas conforme si elle existe
 * @return 1 si la map est conforme, 0 (et affecte des valeurs à x et y) sinon
 */
int is_map_conforme (Map* map, int* x, int* y);

/**
 * Initialise tous les boutons du sous-menu enregistrer
 * @param button_height Dimention des boutons
 * @param button_width Dimention des boutons
 * @param entree_text Le bouton qui permet d'entrer le nom de la map
 * @param consigne_enregistrement Un text indicant quoi faire dans le sous-menu enregistrer
 * @param annuler_enregistrement Bouton clicable pour quitter le sous-menu enregistrer
 * @param valider_enregistrement Bouton clicable pour finaliser l'enregistrement
 */
void init_boutons_enregistrer (int button_width, int button_height, Button* entree_text, Button* consigne_enregistrement, Button* annuler_enregistrement, Button* valider_enregistrement);

/**
 * Initialise tous les boutons du sous-menu de modification de la taille de la map
 * @param button_height Dimention des boutons
 * @param button_width Dimention des boutons
 * @param entree_width Le champs d'entrée de la nouvelle largeur
 * @param entree_height Le champs d'entrée de la nouvelle hauteur
 * @param annuler_taille_map Bouton clicable pour quitter le sous-menu de modification de la taille de la map
 * @param valider_taille_map Bouton clicable pour finaliser la nouvelle taille de map
 * @param consigne_modif_taille_map Le texte de consigne des remplissage des champs
 * @param text_entree_width Le texte définissant le champs <button_width>
 * @param text_entree_height Le texte définissant le champs <entree_height>
 */
void init_boutons_modif_taille_map (int button_width, int button_height, Button* entree_width, Button* entree_height, Button* valider_taille_map, Button* annuler_taille_map, Button* consigne_modif_taille_map, Button* text_entree_width, Button* text_entree_height);

/**
 * Initialise à partir des dimentions de la map sa taille case et les variables globales d'origines x et y
 * @param map La map source
 */
void init_taille_case_et_origine (Map* map);

/**
 * Libère les textures des tiles
 * @param tils Le tableau de pointeurs vers les textures
 * @param nb_tils Le nombre de textures dans le tableau
 */
void free_tils(SDL_Texture** tils, int nb_tils);

#endif
