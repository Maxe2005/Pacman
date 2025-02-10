#ifndef MENUS_H
#define MENUS_H

#include "ressources.h"
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
#define HEADER_HEIGHT 100
#define SCROLL_OFFSET_MIN -100
#define NB_CATEGORIES 2

typedef struct {
    SDL_Rect rect;
    int hovered;
} Button;

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
    Musique* music;
    char* label;
} MusicButton;

typedef struct {
    Button button_base;
    SelectionType type;
    const char* label;
} SelectionButton;

typedef struct {
    SDL_Rect rect;
    const char* texte;
} Ligne_texte;

/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param audio La structure contenant toutes les infos pour les audios
 */
void ecran_acceuil (SDL_Renderer* ren, Audio* audio);

/**
 * Affiche sur le renderer le bouton start
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param font La font du texte à afficher
 */
void affiche_bouton_start(SDL_Renderer* ren, TTF_Font * font);

/**
 * Permet de changer la audio en jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param audio La structure contenant toutes les infos pour les audios
 */
void ecran_audio (SDL_Renderer* ren, Audio* audio);

/**
 * Permet de choisir le niveau de la partie à venir
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param audio La structure contenant toutes les infos pour les audios
 */
void ecran_niveaux (SDL_Renderer* ren, Audio* audio);

/**
 * Tout est dans le titre !
 */
void ecran_remerciements (SDL_Renderer* ren, Audio* audio);

/**
 * Affiche un bouton
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param button Une instance de bouton
 * @param color_text La couleur du texte du bouton
 * @param color1 La couleur de base du font du bouton
 * @param color2 La couleur quand la souris est sur le bouton
 */
void renderButton(SDL_Renderer *renderer, Button *button, const char* texte, SDL_Color color_text, SDL_Color color1, SDL_Color color2);

/**
 * Affiche un en-tête en début de page
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param titre Le texte affiché dans le header 
 */
void renderHeader(SDL_Renderer *renderer, char *titre);

/**
 * Gère les évènements sur les boutons dans le menu audio
 * @param e L'évènement à gérer
 * @param buttons L'ensemble des boutons de la page
 */
void handle_events(SDL_Event* e, MusicButton musics[], SelectionButton selections[], Audio* audio);

/**
 * 
 */
void draw_buttons(SDL_Renderer* renderer, MusicButton musics[], SelectionButton selections[]);

/**
 * Affiche une ligne de texte
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param ligne La ligne à afficher
 * @param font la police
 */
void renderTexte(SDL_Renderer *renderer, Ligne_texte *ligne,TTF_Font *font);

#endif
