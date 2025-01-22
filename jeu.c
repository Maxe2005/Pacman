#include "jeu.h"

TTF_Font* init_font () {
    TTF_Font* font[1];
    TTF_Font* font_titres = createFont("ressources/DejaVuSans-Bold.ttf", 25);
    return *font;
}