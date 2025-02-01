#ifndef JEU_H
#define JEU_H

#include "ressources.h"
#include "pacman.h"
#include "plateau.h"
#include "ghost.h"

typedef struct {
    Map* map;
    SDL_Texture** tils;
    Pacman* pacman;
    Ghost** ghosts;
    TTF_Font** font;
    unsigned int score;
} Partie ;

/**
 * Initialise les différentes polices de caractère avec les tailles correspondantes
 * @param font Le tableau de police vide à remplire
 */
void init_font (TTF_Font* font[1]);

/**
 * Affiche dans le bandeau haut les vies sous forme de pacman
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param skin_vies La texture des vie (un skin de pacman)
 * @param nb_vies Le nombre de vie (restantes) à afficher
 */
void affiche_les_vies (SDL_Renderer* ren, SDL_Texture * skin_vies, const int nb_vies);

/**
 * Gère le actions à effectuer quand le pacman rentre en collision avec un ghost
 * @param pacman Une instance de structure de joueur
 */
void collision_avec_ghost (Pacman *pacman);

/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_partie (SDL_Renderer* ren);

/**
 * Affiche sur le renderer le bouton start
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param bouton_start La texture du bouton
 */
void affiche_bouton_start (SDL_Renderer* ren, SDL_Texture* bouton_start);

/**
 * Affiche sur le renderer le logo
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param logo La texture du logo
 */
void affiche_logo (SDL_Renderer* ren, SDL_Texture* logo);

/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void ecran_acceuil (SDL_Renderer* ren);


/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 */
void boucle_de_jeu(SDL_Renderer* ren, Partie* partie);

/**
 * Libère la mémoire réservé à la partie
 * @param partie La partie qui vient juste de se terminer
 */
void free_partie (Partie* partie);

#endif