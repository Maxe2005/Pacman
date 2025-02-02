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
    SDL_Texture * skin_vies;
    unsigned int score;
    int nb_vies; // Le nombre de vies restantes au pacman/joueur
    unsigned int nb_ghosts; //Le nombre de ghost en circulation sur la map 
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
 * Vérifie si le ghost est en contacte avec le pacman et gère les actions à effectuer
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param ghosts Le tableau avec toutes les instance de structure de fantôme
 * @param pacman Une instance de structure de joueur
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param running Le booleen qui peut arrêter la boucle principale
 * @return 1 si collision avec un fantôme, 0 sinom
 */
int is_collision_pacman_ghost (SDL_Renderer* ren, Ghost** ghosts, Pacman *pacman, Partie* partie, int* running);

/**
 * Tout est dans le titre !
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 */
void annimation_mort_pacman (SDL_Renderer* ren, Partie* partie);

/**
 * Efface et affiche sur le renderer l'écran de jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 */
void affiche_ecran_jeu (SDL_Renderer* ren, Partie* partie);

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
 * Tout est dans le titre ! s
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 */
void affiche_ecran_game_over (SDL_Renderer* ren, Partie* partie);

/**
 * Place les pacman et les fantômes à leur position de départ avant le début de la partie
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 */
void placament_pacman_et_ghost (SDL_Renderer* ren, Partie* partie);

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

/**
 * Met à niveau le score si le pacman est sur <gum> ou <cherry>. Déclanche le mode <frightened> si <Big Gum> rencontré
 * @param pacman Une instance de structure de joueur à déplacer
 * @param map La map sur laquelle se déplace le pacman
 * @param score Le score global à modifier si <gum> ou <cherry> rencontré
 * @param nb_ghosts Le nombre de ghost en circulation sur la map 
 * @param ghosts Le tableau avec toutes les instance de structure de fantôme
 */
void update_score (Pacman *pacman, Map *map, int *score, int nb_ghosts, Ghost** ghosts);

#endif