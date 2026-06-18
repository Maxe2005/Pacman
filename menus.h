#ifndef MENUS_H
#define MENUS_H

#include "ressources.h"
#include "createur_map.h"
#include "jeu.h"
#include "pacman.h"
#include "plateau.h"
#include "ghost.h"
#include "audio.h"


#define LEVEL_COUNT 20
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_MARGIN 30
#define SCROLL_SPEED 30  // Vitesse du scroll
#define SCROLL_OFFSET_MIN -100
#define NB_CATEGORIES 2
#define NB_BOUTONS_ACCUEIL 4

typedef struct {
    Button button_base;
    int level;
} Button_niveau;

typedef enum {
    SELECTION_ACCUEIL,
    SELECTION_JEU,
    SELECTION_SUPER_MODE,
    SELECTION_AUCUNE
} SelectionType;

typedef struct {
    Button button_base;
    Mix_Music* music;
} MusicButton;

typedef struct {
    Button button_base;
    SelectionType type;
} SelectionButton;



/**
 * Affiche sur le renderer le bouton start
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param font La font du texte à afficher
 */
void affiche_bouton_start(SDL_Renderer* ren, TTF_Font * font);

/**
 * Permet de changer la musique en jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void ecran_musique (SDL_Renderer* ren, Musique* musique);

/**
 * Permet de choisir le niveau de la partie à venir
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void ecran_niveaux (SDL_Renderer* ren, Musique* musique);

/**
 * Tout est dans le titre !
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void ecran_remerciements (SDL_Renderer* ren, Musique* musique);

/**
 * Affiche sur le renderer le logo
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param logo La texture du logo
 */
void affiche_logo (SDL_Renderer* ren, SDL_Texture* logo);

/**
 * Affiche les boutons de l'écran d'accueil
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param buttons Le tableau de boutons à afficher
 */
void affiche_boutons_accueil(SDL_Renderer* ren, Button* buttons[], int nb_buttons);

/**
 * Gère les événements des boutons de l'écran d'accueil
 * @param buttons Le tableau de boutons
 * @param musique La structure contenant toutes les infos pour les musiques
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param running Un pointeur sur un entier qui permet de quitter la boucle de jeu
 */
void handle_events_accueil(Button* buttons[], Musique* musique, SDL_Renderer* ren, int *running);

/**
 * Gère les évènements sur les boutons dans le menu musique
 * @param musics L'ensemble des boutons de musiques de la page
 * @param selections L'ensemble des boutons de selection de la page
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void handle_events(MusicButton musics[], SelectionButton selections[], Musique* musique);

/**
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musics L'ensemble des boutons de musiques de la page
 * @param selections L'ensemble des boutons de selection de la page
 */
void draw_buttons(SDL_Renderer* renderer, MusicButton musics[], SelectionButton selections[]);

/**
 * Initialise les boutons de l'écran d'accueil
 * @param buttons Le tableau de boutons à initialiser
 * @param button_musique Le bouton musique
 * @param button_niveaux Le bouton niveaux
 * @param button_remerciements Le bouton remerciements
 * @param button_createur_map Le bouton createur de map
 */
void init_buttons_accueil(Button* buttons[], Button* button_musique, Button* button_niveaux, Button* button_remerciements, Button* button_createur_map);

#endif
