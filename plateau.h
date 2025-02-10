#ifndef PLATEAU_H
#define PLATEAU_H

#include "ressources.h"

#define ORIGINE_X 10
#define ORIGINE_Y TAILLE_BANDEAU_HAUT
#define MAP_TYPE_DESSIN 1
#define MAP_TYPE_TILS 2

typedef struct {
    int x; // Nombre de colones de la map
    int y; // Nombre de lignes de la map
    int taille_case;
    int **contenu; // Un pointeur vers le contenu de la map
    int type; // Savoir si c'est une map dessinée ou avec tils
    int taille_perso; // Taille nécessaire pour la taille des personages (pacman et fantômes)
    int position_maison_ghosts_x; // Le point en haut (et à gauche si impaire) de la maison des fantômes
    int position_maison_ghosts_y; // Le point en haut (et à gauche si impaire) de la maison des fantômes
    int position_pacman_start_x; // La position du pacman en début de partie
    int position_pacman_start_y; // La position du pacman en début de partie
} Map ;

/**
 * Enregistre la map dans un fichier texte
 * @param filename Le nom du nouveau fichier
 * @param map La map à sauvegarder
 */
void save_map_text (const char *filename, Map *map);

/**
 * Charge la map contenue dans le fichier texte donné
 * @param filename Le nom du fichier de la map à ouvrir
 * @return Un pointeur vers la map (structure de Map) 
 */
Map *load_map_text (const char *filename);

/**
 * Enregistre la map dans un fichier binaire
 * @param filename Le nom du nouveau fichier
 * @param map La map à sauvegarder
 */
void save_map_binary (const char *filename, Map *map);

/**
 * Charge la map contenue dans le fichier binaire donné
 * @param filename Le nom du fichier de la map à ouvrir
 * @return Un pointeur vers la map (structure de Map) 
 */
Map *load_map_binary (const char *filename);

/**
 * Initialise le contenu de la map. C'est à dire la position des tils (murs, gum, ...)
 * @param map La map vide à remplire
 */
Map init_map_dessin ();
Map init_map_tils ();

/**
 * Initialise les textures des tils dans un tableau
 * @param tils Le tableau vide à remplire
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void init_tils (SDL_Texture* tils[11], SDL_Renderer* ren);


/**
 * Affiche les tils de la map sur le renderer
 * @param map La map à afficher
 * @param tils Le tableau contenant les textures des différents tils
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */ 
void affiche_map_tils (Map *map, SDL_Texture* tils[11], SDL_Renderer* ren);

/**
 * Dessine sur le renderer un arc de cercle composé de points
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param centerX La position du centre (en pixels) de l'arc de cercle
 * @param centerY La position du centre (en pixels) de l'arc de cercle
 * @param radius Le rayon (en pixels) de l'arc de cercle
 * @param startAngle L'angle de départ (en radiants) de l'arc de cercle
 * @param endAngle L'angle d'arrivée (en radiants) de l'arc de cercle
 * @param thickness L'epaisseur de l'arc de cercle (en pixels)
 * @param nb_pts Le nombres de points composants l'arc de cercle (donc sa résolution)
 */
void drawArc(SDL_Renderer* renderer, const int centerX, const int centerY, const int radius, const double startAngle, const double endAngle, const int thickness, const int nb_pts);

/**
 * Dessine sur le renderer une ligne horizontale
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param x La position (en pixels) du premier point de la ligne (celui à gauche sur le rendu)
 * @param y La position (en pixels) du premier point de la ligne (celui à gauche sur le rendu)
 * @param length La taille (en pixels) de la ligne
 */
void drawLineHorizontal (SDL_Renderer* renderer, const int x, const int y, const int length);

/**
 * Dessine sur le renderer une ligne verticale
 * @param renderer Un pointeur sur une structure contenant l'état du rendu
 * @param x La position (en pixels) du premier point de la ligne (celui en haut sur le rendu)
 * @param y La position (en pixels) du premier point de la ligne (celui en haut sur le rendu)
 * @param length La taille (en pixels) de la ligne
 */
void drawLineVertical (SDL_Renderer* renderer, const int x, const int y, const int height);

/**
 * Dessine la map sur le renderer
 * @param map La map à afficher
 * @param tils Le tableau contenant les textures des différents tils
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void affiche_map_draw (Map *map, SDL_Texture* tils[11], SDL_Renderer* ren);

/**
 * Séléctionne le bon afficheur de map en fonction du type de map
 * @param map La map à afficher
 * @param tils Le tableau contenant les textures des différents tils
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void affiche_map (Map *map, SDL_Texture* tils[11], SDL_Renderer* ren);

/**
 * Libère la mémoire disposée pour la map
 * @param map La map à afficher
 */
void freeMap (Map *map);

/**
 * Ajout des gums, big_gums et fruits sur la map dessinée
 * @param i La position en x de la case actuelle
 * @param j La position en y de la case actuelle
 * @param map La map à afficher
 * @param tils Le tableau contenant les textures des différents tils
 * @param ren Un pointeur sur une structure contenant l'état du rendu
 */
void ajout_gum_dessin (int i, int j, Map *map, SDL_Texture* tils[11], SDL_Renderer* ren);

/**
 * Un vrai opérateur modulo. Pas juste le remainder de '%'
 * @param a Un entier naturel à moduler
 * @param b Un entier naturel diviseur 
 */
int mod (int a, int b);

/**
 * Compte de nombre de gum totaux à manger sur la map
 * @param map La map à afficher
 * @return Le nombre de gum actuellement sur la map
 */
int compte_nb_gum (Map* map);

#endif