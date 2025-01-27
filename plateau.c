#include "plateau.h"

void init_map (int map[MAP_Y][MAP_X]){
    int valeurs[MAP_Y][MAP_X] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,3,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,3,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
    {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,1,1,0,1,1,1,4,4,1,1,1,0,1,1,2,1,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,0,2,2,2,0,1,0,0,0,0,0,0,1,0,2,2,2,0,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,1},
    {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
    {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
    {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
            map[i][j] = valeurs[i][j];
        }
    }
}


void init_tils (SDL_Texture* tils[4], SDL_Renderer* ren){
    tils[0] = loadTexture("ressources/wall.bmp", ren);
    tils[1] = loadTexture("ressources/gum.bmp", ren);
    tils[2] = loadTexture("ressources/bigGum.bmp", ren);
    tils[3] = loadTexture("ressources/cherry.bmp", ren);
}


void affiche_map_tils (int map[MAP_Y][MAP_X], SDL_Texture* tils[4], SDL_Renderer* ren){
    for (int j = 0; j<MAP_Y; j++){
        for (int i = 0; i<MAP_X; i++){
            if (map[j][i] > 0){
                renderTexture(tils[map[j][i] - 1], ren, 
                    ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE,
                    TAILLE_CASE, TAILLE_CASE);
            }
        }
    }
}

void drawLineHorizontal (SDL_Renderer* renderer, const int x, const int y, const int length) {
    SDL_RenderDrawLine(renderer, x, y, x + length, y);
}

void drawLineVertical (SDL_Renderer* renderer, const int x, const int y, const int height) {
    SDL_RenderDrawLine(renderer, x, y, x, y + height);
}

void drawArc(SDL_Renderer* renderer, const int centerX, const int centerY, const int radius, const double startAngle, const double endAngle, const int thickness, const int nb_pts) {
    int new_radius;
    int new_nb_pts;
    for (int e = 0; e < thickness; e++){
        new_radius = (radius-(int)(thickness/2) + e);
        new_nb_pts = nb_pts * new_radius / radius;
        double angleStep = (endAngle - startAngle) / (new_nb_pts-1);
        for (int i = 0; i < new_nb_pts; ++i) {
            double angle = startAngle + i * angleStep;
            int x = centerX + (int)(new_radius * cos(angle));
            int y = centerY - (int)(new_radius * sin(angle)); // SDL a l'axe Y inversé
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void affiche_map_draw (int map[MAP_Y][MAP_X], SDL_Renderer* ren){
    const int nb_pts = 10;
    const int thickness = 2;
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    for (int j = 0; j<MAP_Y; j++){
        for (int i = 0; i<MAP_X; i++){
            if (map[j][i] == 1){
                if (i > 0 && j > 0 && i < MAP_X-1 && j < MAP_Y - 1) { // On exclu les bords
                    if (map[j-1][i] == 1 && map[j+1][i] == 1 && ((map[j][i-1] == 1 && map[j][i+1] != 1) || (map[j][i+1] == 1 && map[j][i-1] != 1))) {
                        drawLineVertical(ren, ORIGINE_X + i*TAILLE_CASE + (int)(TAILLE_CASE/2), ORIGINE_Y + j*TAILLE_CASE, TAILLE_CASE);
                    } else {
                    if (map[j][i-1] == 1 && map[j][i+1] == 1 && ((map[j-1][i] == 1 && map[j+1][i] != 1) || (map[j+1][i] == 1 && map[j-1][i] != 1))) {
                        drawLineHorizontal(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE + (int)(TAILLE_CASE/2), TAILLE_CASE);
                    } else { // Arcs externes :
                    if (map[j+1][i] == 1 && map[j][i-1] == 1 && map[j-1][i] != 1 && map[j][i+1] != 1) { // Arc haut droite 
                        drawArc(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + (j+1)*TAILLE_CASE, (int)(TAILLE_CASE/2), 0, PI/2, thickness, nb_pts);
                    } else {
                    if (map[j+1][i] == 1 && map[j][i+1] == 1 && map[j-1][i] != 1 && map[j][i-1] != 1) { // Arc haut gauche 
                        drawArc(ren, ORIGINE_X + (i+1)*TAILLE_CASE, ORIGINE_Y + (j+1)*TAILLE_CASE, (int)(TAILLE_CASE/2), PI/2, PI, thickness, nb_pts);
                    } else {
                    if (map[j-1][i] == 1 && map[j][i+1] == 1 && map[j+1][i] != 1 && map[j][i-1] != 1) { // Arc bas gauche 
                        drawArc(ren, ORIGINE_X + (i+1)*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE, (int)(TAILLE_CASE/2), PI, 3*PI/2, thickness, nb_pts);
                    } else {
                    if (map[j-1][i] == 1 && map[j][i-1] == 1 && map[j+1][i] != 1 && map[j][i+1] != 1) { // Arc bas droite 
                        drawArc(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE, (int)(TAILLE_CASE/2), 3*PI/2, 2*PI, thickness, nb_pts);
                    } else { // Arcs internes :
                    if (map[j+1][i] == 1 && map[j][i-1] == 1 && map[j+1][i-1] != 1){ // Arc bas gauche
                        drawArc(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + (j+1)*TAILLE_CASE, (int)(TAILLE_CASE/2), 0, PI/2, thickness, nb_pts);
                    } else {
                    if (map[j+1][i] == 1 && map[j][i+1] == 1 && map[j+1][i+1] != 1){ // Arc bas droite
                        drawArc(ren, ORIGINE_X + (i+1)*TAILLE_CASE, ORIGINE_Y + (j+1)*TAILLE_CASE, (int)(TAILLE_CASE/2), PI/2, PI, thickness, nb_pts);
                    } else {
                    if (map[j-1][i] == 1 && map[j][i+1] == 1 && map[j-1][i+1] != 1){ // Arc haut droite
                        drawArc(ren, ORIGINE_X + (i+1)*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE, (int)(TAILLE_CASE/2), PI, 3*PI/2, thickness, nb_pts);
                    } else {
                    if (map[j-1][i] == 1 && map[j][i-1] == 1 && map[j-1][i-1] != 1){ // Arc haut gauche
                        drawArc(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE, (int)(TAILLE_CASE/2), 3*PI/2, 2*PI, thickness, nb_pts);
                    }}}}}}}}}}
                } else { // Bord Haut :
                if (j == 0 && i > 0 && i < MAP_X-1) {
                    if (map[j][i-1] == 1 && map[j][i+1] == 1 && map[j+1][i] != 1) {
                        drawLineHorizontal(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE + (int)(TAILLE_CASE/2), TAILLE_CASE);
                    } else {
                    if (map[j+1][i] == 1 && map[j][i-1] == 1 && map[j+1][i-1] != 1){ // Arc bas gauche
                        drawArc(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + (j+1)*TAILLE_CASE, (int)(TAILLE_CASE/2), 0, PI/2, thickness, nb_pts);
                    } else {
                    if (map[j+1][i] == 1 && map[j][i+1] == 1 && map[j+1][i+1] != 1){ // Arc bas droite
                        drawArc(ren, ORIGINE_X + (i+1)*TAILLE_CASE, ORIGINE_Y + (j+1)*TAILLE_CASE, (int)(TAILLE_CASE/2), PI/2, PI, thickness, nb_pts);
                    }}}
                    drawLineHorizontal(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE, TAILLE_CASE);
                } else { // Bord Bas :
                if (j == MAP_Y-1 && i > 0 && i < MAP_X-1) {
                    if (map[j][i-1] == 1 && map[j][i+1] == 1 && map[j-1][i] != 1) {
                        drawLineHorizontal(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE + (int)(TAILLE_CASE/2), TAILLE_CASE);
                    } else {
                    if (map[j-1][i] == 1 && map[j][i+1] == 1 && map[j-1][i+1] != 1){ // Arc haut droite
                        drawArc(ren, ORIGINE_X + (i+1)*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE, (int)(TAILLE_CASE/2), PI, 3*PI/2, thickness, nb_pts);
                    } else {
                    if (map[j-1][i] == 1 && map[j][i-1] == 1 && map[j-1][i-1] != 1){ // Arc haut gauche
                        drawArc(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + j*TAILLE_CASE, (int)(TAILLE_CASE/2), 3*PI/2, 2*PI, thickness, nb_pts);
                    }}}
                    drawLineHorizontal(ren, ORIGINE_X + i*TAILLE_CASE, ORIGINE_Y + (j+1)*TAILLE_CASE, TAILLE_CASE);
                }}
                }
            } 
        }
    }
}
