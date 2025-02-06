#ifndef JEU_H
#define JEU_H

#include "ressources.h"
#include "pacman.h"
#include "plateau.h"
#include "ghost.h"
#include "audio.h"
#include "menus.h"

#define TEMPS_MODE_FRIGHTENED 11 // en secondes
#define POURCENTAGE_FIN_FRIGHTENED 20

typedef struct {
    Map* map;
    SDL_Texture** tils;
    Pacman* pacman;
    Ghost** ghosts;
    TTF_Font** font;
    SDL_Texture * skin_vies;
    unsigned int score;
    int nb_vies; // Le nombre de vies restantes au pacman/joueur
    int nb_ghosts; // Le nombre de ghost en circulation sur la map 
    int nb_gums; // Le nombre de gums restants sur la map
    int niveau; // Le niveau de la partie en cours
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
 * @param ghost L'instance de structure de fantôme à tester
 * @param pacman Une instance de structure de joueur
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param running Le booleen qui peut arrêter la boucle principale
 * @param musique La structure contenant toutes les infos pour les musiques
 * @return 1 si collision avec un fantôme, 0 sinom
 */
int is_collision_pacman_ghost (SDL_Renderer* ren, Ghost* ghost, Pacman *pacman, Partie* partie, int* running,Musique* musique);

/**
 * Tout est dans le titre !
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void annimation_mort_pacman (SDL_Renderer* ren, Partie* partie, Musique* musique);

/**
 * Efface et affiche sur le renderer l'écran de jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 */
void affiche_ecran_jeu (SDL_Renderer* ren, Partie* partie);

/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musique La structure contenant toutes les infos pour les musiques
 * @param niveau Le niveau de la partie à créer
 */
void nouvelle_partie (SDL_Renderer* ren,Musique* musique, int niveau);

/**
 * Affiche sur le renderer le logo
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param logo La texture du logo
 */
void affiche_logo (SDL_Renderer* ren, SDL_Texture* logo);

/**
 * Tout est dans le titre !
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void ecran_game_over (SDL_Renderer* ren, Partie* partie, Musique* musique);

/**
 * Place les pacman et les fantômes à leur position de départ avant le début de la partie
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 */
void placament_pacman_et_ghost (Partie* partie);

/**
 * La boucle qui tourne durant toute la partie
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void boucle_de_jeu(SDL_Renderer* ren, Partie* partie,Musique* musique);

/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void debut_jeu (SDL_Renderer* ren, Partie* partie, Musique* musique);

/**
 * Libère la mémoire réservé à la partie
 * @param partie La partie qui vient juste de se terminer
 */
void free_partie (Partie* partie);

/**
 * Met à niveau le score si le pacman est sur <gum> ou <cherry>. Déclanche le mode <frightened> si <Big Gum> rencontré
 * @param partie La partie en cours
 * @return 1 Si le mode frightened vient d'être activé, 0 sinon
 */
int update_score (Partie* partie);

/**
 * Affiche sur le renderer un gros titre (avec la couleur) et le score
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param titre Le titre à afficher
 * @param color La couleur du titre à afficher
 */
void affiche_titre_et_score (SDL_Renderer* ren, Partie* partie, char *titre, char *color);

/**
 * Tout est dans le titre !
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param partie La partie qui vient d'être lancée (avec tous ses atributs)
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void ecran_victoire (SDL_Renderer* ren, Partie* partie, Musique* musique);

/**
 * Initialise les durées des différents modes scatter et chase en fonction du niveau
 * @param duree_mode_scatter Le tableau avec les différentes durées des modes scatter
 * @param duree_mode_chase Le tableau avec les différentes durées des modes chase
 * @param num_mode_max Le max du nombre de durées par mode (normalement toujours en scatter)
 * @param niveau Le niveau actuel de la partie
 */
void init_temps_modes_chase_scatter (int duree_mode_scatter[4], int duree_mode_chase[3], int *num_mode_max, int niveau);

#endif