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
    time_t start_time;
} Message;

typedef struct {
    SDL_Color text;
    SDL_Color bg_text_descriptif;
    SDL_Color green;
    SDL_Color light_green;
    SDL_Color red;
    SDL_Color light_red;
    SDL_Color bt_texte;
    SDL_Color bt_base;
    SDL_Color bt_selected;
    SDL_Color bt_touch;
    SDL_Color bande_laterale_1;
    SDL_Color bande_laterale_2;
} Colors;

typedef struct {
    char text[MAX_TEXT_LENGTH + 1]; // +1 pour le /0 comme fin de chaine
    char displayText[MAX_TEXT_LENGTH + 2]; // +2 pour le /0 et le curseur
    Button* entree_text;
    Button* consigne;
    Button* annuler;
    Button* valider;
    int cursorVisible;
    Uint32 lastCursorToggle;
} Sous_menu_enregistrement;

typedef struct {
    char width_text[MAX_NB_LENGTH + 1]; // +1 pour le /0 comme fin de chaine
    char height_text[MAX_NB_LENGTH + 1]; // +1 pour le /0 comme fin de chaine
    char displayWidth[MAX_NB_LENGTH + 2]; // +2 pour le /0 et le curseur
    char displayHeight[MAX_NB_LENGTH + 2]; // +2 pour le /0 et le curseur
    int is_typing_width; // 1 = saisie largeur en cours, 0 = saisie hauteur
    Button* entree_width;
    Button* entree_height;
    Button* text_entree_width;
    Button* text_entree_height;
    Button* consigne;
    Button* annuler;
    Button* valider;
    int cursorVisible;
    Uint32 lastCursorToggle;
} Sous_menu_modif_taille_map;

typedef struct {
    int button_height; // Dimention des boutons
    int button_width; // Dimention des boutons
    Button* buttons[NB_BUTTONS]; // Tableau contenant tous les boutons
    SelectionButton_createur_map* buttons_selection_remplissage [NB_BUTTONS_SELECTION_REMPLISSAGE]; // Tableau contenant les boutons de selection de remplissage de la map
    Button* button_modif_taille_map; // Le bouton pour modifier la taille de la map
    Button* button_grille; // Le bouton pour afficher et cacher la grille d'aide
    Button* button_enregistrer; // Le bouton pour sauvgarder la map créée
    Button* button_zoom_plus; // Le bouton pour augmenter le zoom sur la map actuelle
    Button* button_zoom_moins; // Le bouton pour diminuer le zoom sur la map actuelle
    Button* button_symetrie_verticale; // Le bouton pour activer et désactiver la symétrie verticale dans le remplissage
    Button* button_symetrie_horizontale; // Le bouton pour activer et désactiver la symétrie horizontale dans le remplissage
    SDL_Texture** tils; // Tableau contenant les textures des différents éléments de la map
    Message* message; // Un message à afficher (soit une erreur, une alerte ou bien une confirmation que tout c'est bien passé)
    Sous_menu_enregistrement* sous_menu_enregistrement; // Les boutons du sous-menu enregistrement
    Sous_menu_modif_taille_map* sous_menu_modif_taille_map; // Les boutons du sous-menu de modification de la taille de la map
    Colors* color; // Les couleurs utilisées pour l'affichage
    Map* map; // La map en cours d'édition, affichée (et potentiellement zoomée)
    Map* map_totale; // La map complète en cours d'édition, non affichée
    int position_maison_ghosts[4]; // Un encadrement de la position de la maison des ghosts (non accessible à la modification) : (xmin, ymin, xmax, ymax)
    int x_souris_px; // La position de la souris en pixels sur la map
    int y_souris_px; // La position de la souris en pixels sur la map
    int x_souris_cases; // La position de la souris en cases sur la map
    int y_souris_cases; // La position de la souris en cases sur la map
    int cercle_pointe_erreur_x; // La position du centre du cercle ou ce trouve une erreur (-1 <=> pas d'erreur)
    int cercle_pointe_erreur_y; // La position du centre du cercle ou ce trouve une erreur (-1 <=> pas d'erreur)
    int zoom; // La valeur du zoom (0 = pas de zoom)
    int position_zoom_x; // Le départ du zoom en x sur la map complète (donc le bord gauche de la map affichée)
    int position_zoom_y; // Le départ du zoom en y sur la map complète (donc le bord haut de la map affichée)
    int is_grille_on; // 1 = la grille est affichée, 0 = la grille est cachée
    int is_symetrie_verticale; // 1 = la symétrie verticale est activée, 0 = la symétrie verticale est désactivée
    int is_symetrie_horizontale; // 1 = la symétrie horizontale est activée, 0 = la symétrie horizontale est désactivée
    int is_souris_sur_map; // 1 = la souris est sur la map, 0 = la souris n'est pas sur la map
    int is_en_cours_de_modif; // 1 = une modification est en cours, 0 = aucune modification n'est en cours
    int is_enregistrement; // 1 = le sous-menu d'enregistrement est ouvert, 0 = le sous-menu d'enregistrement est fermé
    int is_modif_taille_map; // 1 = le sous-menu de modification de la taille de la map est ouvert, 0 = le sous-menu de modification de la taille de la map est fermé
} Session_modif_map;


/**
 * La boucle de fonctionnement du créateur de map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void main_loop_createur_map (SDL_Renderer* ren, Musique* musique);

/**
 * Initialise les boutons du créateur de map
 * @param session La session de modification de la map
 */
void init_buttons_createur_map (Session_modif_map* session);

/**
 * Affiche les boutons du créateur de map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param boutons_selection Le tableau contenant les boutons de selection
 * @param boutons Le tableau contenant tous les boutons
 * @param session La session de modification de la map
 */
void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map* boutons_selection[NB_BUTTONS_SELECTION_REMPLISSAGE], Button* boutons[NB_BUTTONS], Session_modif_map* session);

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
 * @param sous_menu_enregistrement Le sous-menu d'enregistrement
 */
void init_boutons_enregistrer (Sous_menu_enregistrement* sous_menu_enregistrement);

/**
 * Initialise tous les boutons du sous-menu de modification de la taille de la map
 * @param sous_menu_modif_taille_map Le sous-menu de modification de la taille de la map
 */
void init_boutons_modif_taille_map (Sous_menu_modif_taille_map* sous_menu_modif_taille_map);

/**
 * Modifie la taille de la map
 * @param map La map à modifier
 * @param x La nouvelle largeur
 * @param y La nouvelle hauteur
 * @return La nouvelle map modifiée
 */
Map modif_taille_map (Map* map, int x, int y);

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

/**
 * Libère la mémoire allouée pour la session de modification de la map
 * @param session La session de modification de la map
 */
void free_session(Session_modif_map* session);

/**
 * Initialise les couleurs de la session
 * @param session La session de modification de la map
 */
void init_couleurs_session (Session_modif_map* session);

/**
 * Affiche l'interface du créateur de map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param session La session de modification de la map
 * @param current_time Le temps actuel
 */
void affiche_interface_createur_map(SDL_Renderer* ren, Session_modif_map* session, time_t current_time);

/**
 * Gère les événements du créateur de map
 * @param event L'événement SDL
 * @param session La session de modification de la map
 * @param running Variable indiquant si la boucle principale est en cours
 * @param musique La structure contenant toutes les infos pour les musiques
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void handle_events_createur_map(SDL_Event event, Session_modif_map* session, int* running, Musique* musique, SDL_Renderer* ren);

/**
 * Gère les événements du sous-menu d'enregistrement
 * @param event L'événement SDL
 * @param session La session de modification de la map
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void handle_events_enregistrement(SDL_Event event, Session_modif_map* session, Musique* musique);

/**
 * Gère les événements du sous-menu de modification de la taille de la map
 * @param event L'événement SDL
 * @param session La session de modification de la map
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void handle_events_modif_taille_map(SDL_Event event, Session_modif_map* session, Musique* musique);

/**
 * Initialise la session de modification de la map
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param session La session de modification de la map
 */
void init_session (SDL_Renderer* ren, Session_modif_map* session);

/**
 * Regarde si la souris est sur un bouton de séléction et effectue l'action associée
 * @param x La position de la souris en x
 * @param y La position de la souris en y
 * @param selections Le tableau contenant les boutons de selection
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void clic_souris (int x, int y, SelectionButton_createur_map* selections[NB_BUTTONS_SELECTION_REMPLISSAGE], Musique* musique);


#endif
