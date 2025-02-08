#ifndef RESSOURCES_H
#define RESSOURCES_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "gestionGraphique.h"
#include "audio.h"

#define FEN_X 800
#define FEN_Y 800
#define TAILLE_BANDEAU_HAUT 80
#define MARGE_BANDEAU_HAUT 10
#define PI 3.14159265358979323846
#define HEADER_HEIGHT 100

typedef struct {
    SDL_Rect rect;
    int hovered;
    const char* label;
} Button;

/**
 * Début du lancement du jeu
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void ecran_acceuil (SDL_Renderer* ren, Musique* musique);

/**
 * Affiche un en-tête en début de page
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param titre Le texte affiché dans le header 
 */
void renderHeader(SDL_Renderer *renderer, char *titre);

/**
 * Affiche un bouton
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param button Une instance de bouton
 * @param color_text La couleur du texte du bouton
 * @param colorh0 La couleur de base du font du bouton
 * @param colorh1 La couleur quand la souris est sur le bouton
 */
void renderButton(SDL_Renderer *renderer, Button *button, SDL_Color color_text, SDL_Color colorh0, SDL_Color colorh1);


#endif
