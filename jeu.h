#ifndef JEU_H
#define JEU_H

#include "ressources.h"
#include "pacman.h"
#include "plateau.h"
#include "ghost.h"

/**
 * Initialise les différentes polices de caractère avec les tailles correspondantes
 * @param font Le tableau de police vide à remplire
 */
void init_font (TTF_Font* font[1]);

/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param map La map à afficher
 * @param tils Le tableau contenant les textures des différents tils
 * @param pacman Une instance de structure de joueur
 * @param font tableau de police 
 * 
 */
void debut_jeu (SDL_Renderer* ren,int map[MAP_Y][MAP_X],SDL_Texture** tils,Pacman* pacman,TTF_Font *font[1]);




/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param map La map à afficher
 * @param tils Le tableau contenant les textures des différents tils
 * @param pacman Une instance de structure de joueur
 * @param texte Le score qui s'affiche dans le bandeau en haut
 * @param score La valeur du score qui s'affiche en haut
 * @param font Un tableau de police 
 * @param running Un booléen qui permet la boucle de jeu
 */
void boucle_de_jeu(SDL_Renderer* ren,int map[MAP_Y][MAP_X],SDL_Texture** tils,Pacman* pacman,char text_score[15],unsigned int score,TTF_Font *font[1],int* running);


#endif