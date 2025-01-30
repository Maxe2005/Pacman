#include "pacman.h"


void init_textures_pacman (Pacman *pacman, SDL_Renderer* ren){
    pacman->skin[0] = loadTexture("ressources/pacman/pakuman_0.bmp", ren);
    pacman->skin[1] = loadTexture("ressources/pacman/pakuman_1.bmp", ren);
    pacman->skin[2] = loadTexture("ressources/pacman/pakuman_2.bmp", ren);
    pacman->skin[3] = loadTexture("ressources/pacman/pakuman_3.bmp", ren);
}

int conversion_case_pixel_en_x (Pacman *pacman, Map *map, int difference){
    return ORIGINE_X + (pacman->position_x + difference) * map->taille_case - (int)((pacman->taille_px - map->taille_case)/2);
}

int conversion_case_pixel_en_y (Pacman *pacman, Map *map, int difference){
    return ORIGINE_Y + (pacman->position_y + difference) * map->taille_case - (int)((pacman->taille_px - map->taille_case)/2);
}

void premier_placement_pacman (Pacman *pacman, Map *map, const int x, const int y){
    pacman->position_x = x;
    pacman->position_y = y;
    if (map->contenu[pacman->position_y][pacman->position_x] == 1){
        printf("Erreur dans le premier placement de pacman sur la map");
    }
    map->contenu[pacman->position_y][pacman->position_x] = 0;
    pacman->taille_px = map->taille_perso;
    pacman->position_px_x = conversion_case_pixel_en_x(pacman, map, 0);
    pacman->position_px_y = conversion_case_pixel_en_y(pacman, map, 0);
    pacman->direction = ' ';
    pacman->next_direction = ' ';
}

void affiche_pacman (Pacman *pacman, SDL_Renderer* ren) {
    SDL_Texture* tex;
    if (pacman->direction == 'd'){
        tex = pacman->skin[0];
    } else {
    if (pacman->direction == 'g'){
        tex = pacman->skin[2];
    } else {
    if (pacman->direction == 'h'){
        tex = pacman->skin[1];
    } else {
    if (pacman->direction == 'b'){
        tex = pacman->skin[3];
    } else {
        tex = pacman->skin[0]; //Par défaut le pacman regarde à droite
    }}}}
    renderTexture(tex, ren, pacman->position_px_x, pacman->position_px_y, pacman->taille_px, pacman->taille_px);
}

void aller_a_droite (Pacman *pacman, Map *map){
    pacman->direction = 'd';
    // Test si le pacman ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((pacman->position_px_x + VITESSE_PACMAN - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2)) / map->taille_case > pacman->position_x && (pacman->position_px_x + VITESSE_PACMAN - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case > 0) {
        pacman->position_px_x = conversion_case_pixel_en_x(pacman, map, 1); // Correction de la position si centre loupé
    } else {
        pacman->position_px_x += VITESSE_PACMAN;
    }
}

void aller_a_gauche (Pacman *pacman, Map *map){
    pacman->direction = 'g';
    // Test si le pacman ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers la droite (donc plus de valeurs négatives)
    if ((pacman->position_px_x - VITESSE_PACMAN - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2) + (2*map->taille_case)) / map->taille_case < pacman->position_x + 1 && (pacman->position_px_x - VITESSE_PACMAN - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2) + (2*map->taille_case)) % map->taille_case > 0) {
        pacman->position_px_x = conversion_case_pixel_en_x(pacman, map, -1); // Correction de la position si centre loupé
    } else {
        pacman->position_px_x -= VITESSE_PACMAN;
    }
}

void aller_en_haut (Pacman *pacman, Map *map){
    pacman->direction = 'h';
    // Test si le pacman ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers le bas (donc plus de valeurs négatives)
    if ((pacman->position_px_y - VITESSE_PACMAN - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2) + (2*map->taille_case)) / map->taille_case < pacman->position_y + 1 && (pacman->position_px_y - VITESSE_PACMAN - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2) + (2*map->taille_case)) % map->taille_case > 0) {
        pacman->position_px_y = conversion_case_pixel_en_y(pacman, map, -1); // Correction de la position si centre loupé
    } else {
        pacman->position_px_y -= VITESSE_PACMAN;
    }
}

void aller_en_bas (Pacman *pacman, Map *map){
    pacman->direction = 'b';
    // Test si le pacman ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((pacman->position_px_y + VITESSE_PACMAN - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2)) / map->taille_case > pacman->position_y && (pacman->position_px_y + VITESSE_PACMAN - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case > 0) {
        pacman->position_px_y = conversion_case_pixel_en_y(pacman, map, 1); // Correction de la position si centre loupé
    } else {
        pacman->position_px_y += VITESSE_PACMAN;
    }
}

void gestion_map_torique (Pacman *pacman, Map *map) {
    if (pacman->position_x == map->x) {
        pacman->position_x = 0;
        pacman->position_px_x = conversion_case_pixel_en_x(pacman, map, -1);
    }
    if (pacman->position_y == map->y) {
        pacman->position_y = 0;
        pacman->position_px_y = conversion_case_pixel_en_y(pacman, map, -1);
    }
    if (pacman->position_x == -1) {
        pacman->position_x = map->x - 1;
        pacman->position_px_x = conversion_case_pixel_en_x(pacman, map, 1);
    }
    if (pacman->position_y == -1) {
        pacman->position_y = map->y - 1;
        pacman->position_px_y = conversion_case_pixel_en_y(pacman, map, 1);
    }
}

int avance_pacman (Pacman *pacman, Map *map, int *score){
    if (((pacman->position_px_x - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case == 0) && ((pacman->position_px_y - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case == 0)){ // <=> pacman au milieu d'une case (et pas en transition entre 2)
        pacman->position_x = (pacman->position_px_x - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2)) / map->taille_case;
        pacman->position_y = (pacman->position_px_y - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2)) / map->taille_case;
        gestion_map_torique(pacman, map);
        update_score(pacman, map, score);

        // Prise en compte de la nouvelle diretion :
        if (pacman->next_direction == 'd' && map->contenu[pacman->position_y][mod(pacman->position_x + 1, map->x)] != 1){
            aller_a_droite(pacman, map);
            return 0;
        }
        if (pacman->next_direction == 'g' && map->contenu[pacman->position_y][mod(pacman->position_x - 1, map->x)] != 1){
            aller_a_gauche(pacman, map);
            return 0;
        }
        if (pacman->next_direction == 'h' && map->contenu[mod(pacman->position_y - 1, map->y)][pacman->position_x] != 1){
            aller_en_haut(pacman, map);
            return 0;
        }
        if (pacman->next_direction == 'b' && map->contenu[mod(pacman->position_y + 1, map->y)][pacman->position_x] != 1 && map->contenu[pacman->position_y + 1][pacman->position_x] != 3){
            aller_en_bas(pacman, map);
            return 0;
        }

        // Si impossible -> continuation du mouvement :
        if (pacman->direction == 'd' && map->contenu[pacman->position_y][mod(pacman->position_x + 1,map->x)] != 1){
            aller_a_droite(pacman, map);
            return 0;
        }
        if (pacman->direction == 'g' && map->contenu[pacman->position_y][mod(pacman->position_x - 1, map->x)] != 1){
            aller_a_gauche(pacman, map);
            return 0;
        }
        if (pacman->direction == 'h' && map->contenu[mod(pacman->position_y - 1, map->y)][pacman->position_x] != 1){
            aller_en_haut(pacman, map);
            return 0;
        }
        if (pacman->direction == 'b' && map->contenu[mod(pacman->position_y + 1, map->y)][pacman->position_x] != 1 && map->contenu[pacman->position_y + 1][pacman->position_x] != 3){
            aller_en_bas(pacman, map);
            return 0;
        }
        // Si toujours pas possible alors c'est qu'on a touché un mur. Donc on ne fait rien.

    } else { // <=> Le pacman est en transition entre 2 cases. Les seuls mouvements possibles sont alors le demi-tour demandé ou bien le déplacement continue.
        if (((pacman->position_px_x - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case != 0) && ((pacman->position_px_y - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case != 0)){
            printf("Erreur : Pacman ne peut pas se trouver sur la diagonale entre 2 cases !!\n");
            return 1;
        }
        if (pacman->direction == 'd'){
            if (pacman->next_direction == 'g'){
                aller_a_gauche(pacman, map);
            } else {
                aller_a_droite(pacman, map);
            }
            return 0;
        }
        if (pacman->direction == 'g'){
            if (pacman->next_direction == 'd'){
                aller_a_droite(pacman, map);
            } else {
                aller_a_gauche(pacman, map);
            }
            return 0;
        }
        if (pacman->direction == 'h'){
            if (pacman->next_direction == 'b'){
                aller_en_bas(pacman, map);
            } else {
                aller_en_haut(pacman, map);
            }
            return 0;
        }
        if (pacman->direction == 'b'){
            if (pacman->next_direction == 'h'){
                aller_en_haut(pacman, map);
            } else {
                aller_en_bas(pacman, map);
            }
            return 0;
        }
    }
}

void update_score (Pacman *pacman, Map *map, int *score){
    if (map->contenu[pacman->position_y][pacman->position_x] == 4){
        *score += 10;
        map->contenu[pacman->position_y][pacman->position_x] = 0; //Vider la case car le <Gum> à été consommé
    } else {
    if (map->contenu[pacman->position_y][pacman->position_x] == 6){
        *score += 100;
        map->contenu[pacman->position_y][pacman->position_x] = 0; //Vider la case car le <Cherry> à été consommé
    } else {
    if (map->contenu[pacman->position_y][pacman->position_x] == 5){ // <Big_Gum> consommé
        map->contenu[pacman->position_y][pacman->position_x] = 0;
        // TODO : Ici démarer le mode <frightened>
    }
    }}
}
