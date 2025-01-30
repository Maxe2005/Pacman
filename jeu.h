#ifndef JEU_H
#define JEU_H

#include "ressources.h"
#include "plateau.h"
#include "pacman.h"

/**
 * Initialise les différentes polices de caractère avec les tailles correspondantes
 * @param font Le tableau vide à remplire
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

#endif