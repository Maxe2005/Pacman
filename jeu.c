#include "jeu.h"

void init_font (TTF_Font* font[1]) {
    font[0] = createFont("ressources/DejaVuSans-Bold.ttf", 20); //Font de titres
}

void affiche_les_vies (SDL_Renderer* ren, SDL_Texture * skin_vies, const int nb_vies) {
    const int taille = TAILLE_BANDEAU_HAUT - 2*MARGE_BANDEAU_HAUT;
    for (int i = 1; i <= nb_vies; i++) {
        renderTexture(skin_vies, ren, FEN_X - MARGE_BANDEAU_HAUT - i*taille, MARGE_BANDEAU_HAUT, taille, taille);
    }
}

void collision_avec_ghost (Pacman *pacman) {
    pacman->nb_vies--;
    if (pacman->nb_vies == 0) {
        // TODO menu game over
    }
    // TODO stop la loop et reconmencer partie
}

void affiche_les_vies (SDL_Renderer* ren, SDL_Texture * skin_vies, const int nb_vies) {
    const int taille = TAILLE_BANDEAU_HAUT - 2*MARGE_BANDEAU_HAUT;
    for (int i = 1; i <= nb_vies; i++) {
        renderTexture(skin_vies, ren, FEN_X - MARGE_BANDEAU_HAUT - i*taille, MARGE_BANDEAU_HAUT, taille, taille);
    }
}

void collision_avec_ghost (Pacman *pacman) {
    pacman->nb_vies--;
    if (pacman->nb_vies == 0) {
        // TODO menu game over
    }
    // TODO stop la loop et reconmencer partie
}

//void set_affichage_global (SDL_Renderer *ren, Map *map) {}
