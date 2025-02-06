#include "plateau.h"

void save_map_text(const char *filename, Map *map) {
    char path[100] = "ressources/maps/";
    strcat(path, filename);

    FILE *file = fopen(path, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Sauvegarde des données de map dans un format lisible
    fprintf(file, "%d %d\n", map->x, map->y);
    fprintf(file, "%d\n", map->type);
    fprintf(file, "%d %d\n", map->position_maison_ghosts_x, map->position_maison_ghosts_y);
    fprintf(file, "%d %d\n", map->position_pacman_start_x, map->position_pacman_start_y);

    // Sauvegarde des données de la map
    for (int i = 0; i < map->y; i++) {
        for (int j = 0; j < map->x; j++) {
            fprintf(file, "%d ", map->contenu[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

Map *load_map_text(const char *filename) {
    char path[100] = "ressources/maps/";
    strcat(path, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    Map *map = malloc(sizeof(Map));
    if (!map) {
        perror("Erreur d'allocation de la matrice");
        fclose(file);
        return NULL;
    }

    // Lecture des données de map
    fscanf(file, "%d %d", &map->x, &map->y);
    fscanf(file, "%d", &map->type);
    fscanf(file, "%d %d", &map->position_maison_ghosts_x, &map->position_maison_ghosts_y);
    fscanf(file, "%d %d", &map->position_pacman_start_x, &map->position_pacman_start_y);
    map->taille_case = (FEN_Y - TAILLE_BANDEAU_HAUT) / map->y;

    if (map->type == MAP_TYPE_DESSIN) {
        map->taille_perso = 1.8 * map->taille_case;
    } else if (map->type == MAP_TYPE_TILS) {
        map->taille_perso = map->taille_case;
    } else {
        perror("Type de map inconnu");
        fclose(file);
        return NULL;
    }

    // Allocation dynamique de la matrice
    map->contenu = malloc(map->y * sizeof(int *));
    for (int i = 0; i < map->y; i++) {
        map->contenu[i] = malloc(map->x * sizeof(int));
        for (int j = 0; j < map->x; j++) {
            fscanf(file, "%d", &map->contenu[i][j]);
        }
    }

    fclose(file);
    return map;
}

void save_map_binary (const char *filename, Map *map) {
    char path[100] = "ressources/maps/";
    strcat(path,filename);

    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Sauvegarde des dimensions
    fwrite(&map->x, sizeof(int), 1, file);
    fwrite(&map->y, sizeof(int), 1, file);
    fwrite(&map->type, sizeof(int), 1, file);
    fwrite(&map->position_maison_ghosts_x, sizeof(int), 1, file);
    fwrite(&map->position_maison_ghosts_y, sizeof(int), 1, file);
    fwrite(&map->position_pacman_start_x, sizeof(int), 1, file);
    fwrite(&map->position_pacman_start_y, sizeof(int), 1, file);

    // Sauvegarde des données de la map
    for (int i = 0; i < map->y; i++) {
        fwrite(map->contenu[i], sizeof(int), map->x, file);
    }

    fclose(file);
}

Map *load_map_binary (const char *filename) {
    char path[100] = "ressources/maps/";
    strcat(path,filename);

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    Map *map = malloc(sizeof(Map));
    if (!map) {
        perror("Erreur d'allocation de la matrice");
        fclose(file);
        return NULL;
    }

    // Lecture des dimensions
    fread(&map->x, sizeof(int), 1, file);
    fread(&map->y, sizeof(int), 1, file);
    fread(&map->type, sizeof(int), 1, file);
    fread(&map->position_maison_ghosts_x, sizeof(int), 1, file);
    fread(&map->position_maison_ghosts_y, sizeof(int), 1, file);
    fread(&map->position_pacman_start_x, sizeof(int), 1, file);
    fread(&map->position_pacman_start_y, sizeof(int), 1, file);
    map->taille_case = (FEN_Y-TAILLE_BANDEAU_HAUT)/map->y;

    if (map->type == MAP_TYPE_DESSIN) {
        map->taille_perso = 1.8 * map->taille_case;
    } else if (map->type == MAP_TYPE_TILS) {
        map->taille_perso = map->taille_case;
    } else {
        perror("Type de map inconnu");
        fclose(file);
        return NULL;
    }

    // Allocation dynamique de la matrice
    map->contenu = malloc(map->y * sizeof(int *));
    for (int i = 0; i < map->y; i++) {
        map->contenu[i] = malloc(map->x * sizeof(int));
        fread(map->contenu[i], sizeof(int), map->x, file);
    }

    fclose(file);
    return map;
}

Map init_map_dessin (){
    Map map;
    map.x = 28;
    map.y = 31;
    map.taille_case = (FEN_Y-TAILLE_BANDEAU_HAUT)/map.y;
    map.type = MAP_TYPE_DESSIN;
    map.taille_perso = 1.8*map.taille_case;
    map.position_maison_ghosts_x = 13;
    map.position_maison_ghosts_y = 11;
    map.position_pacman_start_x = 14;
    map.position_pacman_start_y = 23;

    int valeurs[31][28] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,1,1,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,1,1,1,1,4,1,1,1,1,1,4,1,1,4,1,1,1,1,1,4,1,1,1,1,4,1},
    {1,5,1,1,1,1,4,1,1,1,1,1,4,1,1,4,1,1,1,1,1,4,1,1,1,1,5,1},
    {1,4,1,1,1,1,4,1,1,1,1,1,4,1,1,4,1,1,1,1,1,4,1,1,1,1,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,1,1,1,1,4,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,1,1,1,4,1},
    {1,4,1,1,1,1,4,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,1,1,1,4,1},
    {1,4,4,4,4,4,4,1,1,4,4,4,4,1,1,4,4,4,4,1,1,4,4,4,4,4,4,1},
    {1,1,1,1,1,1,4,1,1,1,1,1,4,1,1,4,1,1,1,1,1,4,1,1,1,1,1,1},
    {2,2,2,2,2,1,4,1,1,1,1,1,4,1,1,4,1,1,1,1,1,4,1,2,2,2,2,2},
    {2,2,2,2,2,1,4,1,1,0,0,0,0,0,0,0,0,0,0,1,1,4,1,2,2,2,2,2},
    {2,2,2,2,2,1,4,1,1,0,1,1,1,3,3,1,1,1,0,1,1,4,1,2,2,2,2,2},
    {1,1,1,1,1,1,4,1,1,0,1,2,2,2,2,2,2,1,0,1,1,4,1,1,1,1,1,1},
    {0,0,0,0,0,0,4,4,4,0,1,2,2,2,2,2,2,1,0,4,4,4,0,0,0,0,0,0},
    {1,1,1,1,1,1,4,1,1,0,1,2,2,2,2,2,2,1,0,1,1,4,1,1,1,1,1,1},
    {2,2,2,2,2,1,4,1,1,0,1,1,1,1,1,1,1,1,0,1,1,4,1,2,2,2,2,2},
    {2,2,2,2,2,1,4,1,1,0,0,0,0,0,0,0,0,0,0,1,1,4,1,2,2,2,2,2},
    {2,2,2,2,2,1,4,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,2,2,2,2,2},
    {1,1,1,1,1,1,4,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,1,1,1,1,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,1,1,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,1,1,1,1,4,1,1,1,1,1,4,1,1,4,1,1,1,1,1,4,1,1,1,1,4,1},
    {1,4,1,1,1,1,4,1,1,1,1,1,4,1,1,4,1,1,1,1,1,4,1,1,1,1,4,1},
    {1,5,4,4,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1,1,4,4,5,1},
    {1,1,1,4,1,1,4,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,1,4,1,1,1},
    {1,1,1,4,1,1,4,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,1,4,1,1,1},
    {1,4,4,4,4,4,4,1,1,4,4,4,4,1,1,4,4,4,4,1,1,4,4,4,4,4,4,1},
    {1,4,1,1,1,1,1,1,1,1,1,1,4,1,1,4,1,1,1,1,1,1,1,1,1,1,4,1},
    {1,4,1,1,1,1,1,1,1,1,1,1,4,1,1,4,1,1,1,1,1,1,1,1,1,1,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
    
    // Allocation de la map 2D
    map.contenu = malloc(map.y * sizeof(int *));
    for (int i = 0; i < map.y; i++) {
        map.contenu[i] = malloc(map.x * sizeof(int));
        for (int j = 0; j < map.x; j++) {
            map.contenu[i][j] = valeurs[i][j];
        }
    }
    return map;
}

Map init_map_tils () {
    Map map;
    map.x = 19;
    map.y = 21;
    map.taille_case = (FEN_Y-TAILLE_BANDEAU_HAUT)/map.y;
    map.type = MAP_TYPE_TILS;
    map.taille_perso = map.taille_case;
    map.position_maison_ghosts_x = 9;
    map.position_maison_ghosts_y = 9;
    map.position_pacman_start_x = 9;
    map.position_pacman_start_y = 16;

    int valeurs[21][19] = {
    {1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1},
    {1,4,4,4,4,4,4,4,4,1,4,4,4,4,4,4,4,4,1},
    {1,4,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,4,1},
    {1,5,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,5,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,1,1,4,1,4,1,1,1,1,1,4,1,4,1,1,4,1},
    {1,4,4,4,4,1,5,4,4,1,4,4,5,1,4,4,4,4,1},
    {1,1,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,1,1},
    {1,1,1,1,4,1,0,0,0,0,0,0,0,1,4,1,1,1,1},
    {1,1,1,1,4,1,0,1,1,3,1,1,0,1,4,1,1,1,1},
    {0,0,0,0,4,4,0,1,0,0,0,1,0,4,4,0,0,0,0},
    {1,1,1,1,4,1,0,1,1,1,1,1,0,1,4,1,1,1,1},
    {1,1,1,1,4,1,0,0,0,0,0,0,0,1,4,1,1,1,1},
    {1,1,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,1,1},
    {1,4,4,4,4,1,5,4,4,1,4,4,5,1,4,4,4,4,1},
    {1,4,1,1,4,1,4,1,1,1,1,1,4,1,4,1,1,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,5,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,5,1},
    {1,4,1,1,4,1,1,1,4,1,4,1,1,1,4,1,1,4,1},
    {1,4,4,4,4,4,4,4,4,1,4,4,4,4,4,4,4,4,1},
    {1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1}};

    // Allocation de la map 2D
    map.contenu = malloc(map.y * sizeof(int *));
    for (int i = 0; i < map.y; i++) {
        map.contenu[i] = malloc(map.x * sizeof(int));
        for (int j = 0; j < map.x; j++) {
            map.contenu[i][j] = valeurs[i][j];
        }
    }
    return map;
}

void freeMap (Map *map) {
    for (int i = 0; i < map->y; i++) {
        free(map->contenu[i]);
    }
    free(map->contenu);
}


void init_tils (SDL_Texture* tils[4], SDL_Renderer* ren){
    tils[0] = loadTexture("ressources/wall.bmp", ren);
    tils[1] = loadTexture("ressources/gum.bmp", ren);
    tils[2] = loadTexture("ressources/bigGum.bmp", ren);
    tils[3] = loadTexture("ressources/cherry.bmp", ren);
}


void affiche_map (Map *map, SDL_Texture* tils[4], SDL_Renderer* ren){
    if (map->type == MAP_TYPE_TILS) {
        affiche_map_tils(map, tils, ren);
    } else {
    if (map->type == MAP_TYPE_DESSIN) {
        affiche_map_draw(map, tils, ren);
    }
    }
}

void affiche_map_tils (Map *map, SDL_Texture* tils[4], SDL_Renderer* ren){
    for (int j = 0; j<map->y; j++){
        for (int i = 0; i<map->x; i++){
            if (map->contenu[j][i] == 1){
                renderTexture(tils[0], ren, 
                    ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case,
                    map->taille_case, map->taille_case);
            }
            if (map->contenu[j][i] >= 4){
                renderTexture(tils[map->contenu[j][i] - 3], ren, 
                    ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case,
                    map->taille_case, map->taille_case);
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
        new_radius = (radius + e); // -(int)(thickness/2)
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

void affiche_map_draw (Map *map, SDL_Texture* tils[4], SDL_Renderer* ren){
    const int nb_pts = 12;
    const int thickness = 2;
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    for (int j = 0; j<map->y; j++){
        for (int i = 0; i<map->x; i++){
            if (map->contenu[j][i] == 1){
                if (i > 0 && j > 0 && i < map->x-1 && j < map->y - 1) { // On exclu les bords
                    if (map->contenu[j-1][i] == 1 && map->contenu[j+1][i] == 1 && ((map->contenu[j][i-1] == 1 && map->contenu[j][i+1] != 1) || (map->contenu[j][i+1] == 1 && map->contenu[j][i-1] != 1))) {
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j][i-1] == 1 && map->contenu[j][i+1] == 1 && ((map->contenu[j-1][i] == 1 && map->contenu[j+1][i] != 1) || (map->contenu[j+1][i] == 1 && map->contenu[j-1][i] != 1))) {
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                    } else { // Arcs externes :
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i-1] == 1 && map->contenu[j-1][i] != 1 && map->contenu[j][i+1] != 1) { // Arc haut droite 
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), 0, PI/2, thickness, nb_pts);
                    } else {
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j-1][i] != 1 && map->contenu[j][i-1] != 1) { // Arc haut gauche 
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), PI/2, PI, thickness, nb_pts);
                    } else {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j+1][i] != 1 && map->contenu[j][i-1] != 1) { // Arc bas gauche 
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), PI, 3*PI/2, thickness, nb_pts);
                    } else {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i-1] == 1 && map->contenu[j+1][i] != 1 && map->contenu[j][i+1] != 1) { // Arc bas droite 
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), 3*PI/2, 2*PI, thickness, nb_pts);
                    } else { // Arcs internes :
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i-1] == 1 && map->contenu[j+1][i-1] != 1){ // Arc bas gauche
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), 0, PI/2, thickness, nb_pts);
                    } else {
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j+1][i+1] != 1){ // Arc bas droite
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), PI/2, PI, thickness, nb_pts);
                    } else {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j-1][i+1] != 1){ // Arc haut droite
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), PI, 3*PI/2, thickness, nb_pts);
                    } else {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i-1] == 1 && map->contenu[j-1][i-1] != 1){ // Arc haut gauche
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), 3*PI/2, 2*PI, thickness, nb_pts);
                    } else { // Bordures externes enclavés
                    if (map->contenu[j+1][i] == 2 && map->contenu[j-1][i] != 1) { // Bordure haute de l'enclave
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j-1][i] == 2 && map->contenu[j+1][i] != 1) { // Bordure basse de l'enclave
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j][i-1] == 2 && map->contenu[j][i+1] != 1) { // Bordure droite de l'enclave
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j][i+1] == 2 && map->contenu[j][i-1] != 1) { // Bordure gauche de l'enclave
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                    }
                    }}}}}}}}}}}}}
                } else { 
                // ---------------------------------- Bord Haut -----------------------------------
                if (j == 0 && i > 0 && i < map->x-1) {
                    if (map->contenu[j][i-1] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j+1][i] != 1) {
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i-1] == 1 && map->contenu[j+1][i-1] != 1){ // Arc bas gauche
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), 0, PI/2, thickness, nb_pts);
                        if (map->contenu[j][i+1] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case, 0, PI/2, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        }
                    } else {
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j+1][i+1] != 1){ // Arc bas droite
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), PI/2, PI, thickness, nb_pts);
                        if (map->contenu[j][i-1] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case, PI/2, PI, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        }
                    } else { // Bordure haute sortie torrique
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i-1] == 2 && map->contenu[j][i+1] != 1){
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else { // Bordure basse sortie torrique
                    if (map->contenu[j+1][i] == 1 && map->contenu[j][i+1] == 2 && map->contenu[j][i-1] != 1){
                        drawLineVertical(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                    }}}}}
                } else { 
                // ------------------------------------- Bord Bas ------------------------------
                if (j == map->y-1 && i > 0 && i < map->x-1) {
                    if (map->contenu[j][i-1] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j-1][i] != 1) {
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i+1] == 1 && map->contenu[j-1][i+1] != 1){ // Arc haut droite
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), PI, 3*PI/2, thickness, nb_pts);
                        if (map->contenu[j][i-1] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case, PI, 3*PI/2, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case);
                        }
                    } else {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i-1] == 1 && map->contenu[j-1][i-1] != 1){ // Arc haut gauche
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), 3*PI/2, 2*PI, thickness, nb_pts);
                        if (map->contenu[j][i+1] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case, 3*PI/2, 2*PI, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case);
                        }
                    } else { // Bordure haute sortie torrique
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i-1] == 2 && map->contenu[j][i+1] != 1){
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else { // Bordure basse sortie torrique
                    if (map->contenu[j-1][i] == 1 && map->contenu[j][i+1] == 2 && map->contenu[j][i-1] != 1){
                        drawLineVertical(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                    }}}}}
                } else { 
                // ------------------------ Bord Gauche --------------------------------
                if (i == 0 && j > 0 && j < map->y-1) {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j+1][i] == 1 && map->contenu[j][i+1] != 1) { // Mur simple
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X, ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j][i+1] == 1 && map->contenu[j-1][i] == 1 && map->contenu[j-1][i+1] != 1){ // Arc haut droite
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), PI, 3*PI/2, thickness, nb_pts);
                        if (map->contenu[j+1][i] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case, PI, 3*PI/2, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineVertical(ren, ORIGINE_X, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        }
                    } else {
                    if (map->contenu[j][i+1] == 1 && map->contenu[j+1][i] == 1 && map->contenu[j+1][i+1] != 1){ // Arc bas droite
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), PI/2, PI, thickness, nb_pts);
                        if (map->contenu[j-1][i] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case, PI/2, PI, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineVertical(ren, ORIGINE_X, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        }
                    } else { // Bordure haute sortie torrique
                    if (map->contenu[j][i+1] == 1 && map->contenu[j-1][i] == 2 && map->contenu[j+1][i] != 1){
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                    } else { // Bordure basse sortie torrique
                    if (map->contenu[j][i+1] == 1 && map->contenu[j+1][i] == 2 && map->contenu[j-1][i] != 1){
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                    }}}}}
                } else { 
                // -------------------------------- Bord Droit ---------------------------------------
                if (i == map->x - 1 && j > 0 && j < map->y-1) {
                    if (map->contenu[j-1][i] == 1 && map->contenu[j+1][i] == 1 && map->contenu[j][i-1] != 1) {
                        drawLineVertical(ren, ORIGINE_X + i*map->taille_case + (int)(map->taille_case/2), ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineVertical(ren, ORIGINE_X + map->x * map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                    } else {
                    if (map->contenu[j][i-1] == 1 && map->contenu[j-1][i] == 1 && map->contenu[j-1][i-1] != 1){ // Arc haut gauche
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), 3*PI/2, 2*PI, thickness, nb_pts);
                        if (map->contenu[j+1][i] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case, 3*PI/2, 2*PI, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineVertical(ren, ORIGINE_X + map->x * map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        }
                    } else {
                    if (map->contenu[j][i-1] == 1 && map->contenu[j+1][i] == 1 && map->contenu[j+1][i-1] != 1){ // Arc bas gauche
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), 0, PI/2, thickness, nb_pts);
                        if (map->contenu[j-1][i] == 2) { // Départ de l'enclave
                            drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case, 0, PI/2, thickness, 2*nb_pts);
                        } else { // Départ d'un mur perpendiculaire
                            drawLineVertical(ren, ORIGINE_X + map->x * map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        }
                    } else { // Bordure haute sortie torrique
                    if (map->contenu[j][i-1] == 1 && map->contenu[j-1][i] == 2 && map->contenu[j+1][i] != 1){ 
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                    } else { // Bordure basse sortie torrique
                    if (map->contenu[j][i-1] == 1 && map->contenu[j+1][i] == 2 && map->contenu[j-1][i] != 1){
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case);
                        drawLineHorizontal(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case);
                    }}}}}
                } else {
                    if (i == 0 && j == 0 && map->contenu[j][i+1] == 1 && map->contenu[j+1][i] == 1){
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), PI/2, PI, thickness, nb_pts);
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case, PI/2, PI, thickness, 2*nb_pts);
                    } else {
                    if (i == map->x - 1 && j == 0 && map->contenu[j][i-1] == 1 && map->contenu[j+1][i] == 1){
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, (int)(map->taille_case/2), 0, PI/2, thickness, nb_pts);
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + (j+1)*map->taille_case, map->taille_case, 0, PI/2, thickness, 2*nb_pts);
                    } else {
                    if (i == 0 && j == map->y - 1 && map->contenu[j][i+1] == 1 && map->contenu[j-1][i] == 1){
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), PI, 3*PI/2, thickness, nb_pts);
                        drawArc(ren, ORIGINE_X + (i+1)*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case, PI, 3*PI/2, thickness, 2*nb_pts);
                    } else {
                    if (i == map->x - 1 && j == map->y - 1 && map->contenu[j][i-1] == 1 && map->contenu[j-1][i] == 1){
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, (int)(map->taille_case/2), 3*PI/2, 2*PI, thickness, nb_pts);
                        drawArc(ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case, 3*PI/2, 2*PI, thickness, 2*nb_pts);
                }}}}}}}}}
            } else {
                if (map->contenu[j][i] == 3){
                    SDL_SetRenderDrawColor(ren,255,192,203,255);
                    SDL_Rect rectangle = {ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case + (int)(map->taille_case/2), map->taille_case, (int)(map->taille_case/2)};
                    SDL_RenderFillRect(ren,&rectangle);
                    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
                } else {
                    if (map->contenu[j][i] >= 4) {
                    ajout_gum_dessin(i, j, map, tils, ren);
                }}
            }
        }
    }
}

void ajout_gum_dessin (int i, int j, Map *map, SDL_Texture* tils[4], SDL_Renderer* ren) {
    renderTexture(tils[map->contenu[j][i] - 3], ren, ORIGINE_X + i*map->taille_case, ORIGINE_Y + j*map->taille_case, map->taille_case, map->taille_case);
}

int mod (int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}

int compte_nb_gum (Map* map) {
    int nb_gum = 0;
    for (int j = 0; j<map->y; j++){
        for (int i = 0; i<map->x; i++){
            if (map->contenu[j][i] == 4){
                nb_gum++;
            }
        }
    }
    return nb_gum;
}
