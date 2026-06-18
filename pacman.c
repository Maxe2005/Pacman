#include "pacman.h"


void init_textures_pacman(Pacman *pacman, SDL_Renderer* ren) {
    pacman->skin[0] = loadTexture("ressources/pacman/pakumanD1.bmp", ren);  
    pacman->skin[1] = loadTexture("ressources/pacman/pakumanD2.bmp", ren);  
    pacman->skin[2] = loadTexture("ressources/pacman/pakumanH1.bmp", ren);  
    pacman->skin[3] = loadTexture("ressources/pacman/pakumanH2.bmp", ren);  
    pacman->skin[4] = loadTexture("ressources/pacman/pakumanG1.bmp", ren);  
    pacman->skin[5] = loadTexture("ressources/pacman/pakumanG2.bmp", ren);  
    pacman->skin[6] = loadTexture("ressources/pacman/pakumanB1.bmp", ren);  
    pacman->skin[7] = loadTexture("ressources/pacman/pakumanB2.bmp", ren);  
    pacman->skin[8] = loadTexture("ressources/pacman/pakumanGlobal.bmp", ren);
}

void init_textures_pacman_mort(Pacman *pacman, SDL_Renderer* ren) {
    pacman->skin_mort[0] = loadTexture("ressources/pacman/Game_Over/pacman_G_O1.bmp", ren);  
    pacman->skin_mort[1] = loadTexture("ressources/pacman/Game_Over/pacman_G_O2.bmp", ren);  
    pacman->skin_mort[2] = loadTexture("ressources/pacman/Game_Over/pacman_G_O3.bmp", ren);  
    pacman->skin_mort[3] = loadTexture("ressources/pacman/Game_Over/pacman_G_O4.bmp", ren);  
    pacman->skin_mort[4] = loadTexture("ressources/pacman/Game_Over/pacman_G_O5.bmp", ren);  
    pacman->skin_mort[5] = loadTexture("ressources/pacman/Game_Over/pacman_G_O6.bmp", ren);  
    pacman->skin_mort[6] = loadTexture("ressources/pacman/Game_Over/pacman_G_O7.bmp", ren);  
    pacman->skin_mort[7] = loadTexture("ressources/pacman/Game_Over/pacman_G_O8.bmp", ren);  
    pacman->skin_mort[8] = loadTexture("ressources/pacman/Game_Over/pacman_G_O9.bmp", ren);  
    pacman->skin_mort[9] = loadTexture("ressources/pacman/Game_Over/pacman_G_O10.bmp", ren);  
    pacman->skin_mort[10] = loadTexture("ressources/pacman/Game_Over/pacman_G_O11.bmp", ren); 
}

void free_textures_pacman(Pacman *pacman) {
    for (int i = 0; i < 9; i++) {
        SDL_DestroyTexture(pacman->skin[i]); // Libérer les textures de Pacman
    }
    for (int i = 0; i < 11; i++) {
        SDL_DestroyTexture(pacman->skin_mort[i]); // Libérer les textures de mort de Pacman
    }
}

int conversion_case_pixel_en_x (Pacman *pacman, Map *map, int difference){
    return ORIGINE_X + (pacman->position_x + difference) * map->taille_case - (int)((pacman->taille_px - map->taille_case)/2);
}

int conversion_case_pixel_en_y (Pacman *pacman, Map *map, int difference){
    return ORIGINE_Y + (pacman->position_y + difference) * map->taille_case - (int)((pacman->taille_px - map->taille_case)/2);
}

void premier_placement_pacman (Pacman *pacman, Map *map){
    pacman->position_x = map->position_pacman_start_x;
    pacman->position_y = map->position_pacman_start_y;
    if (map->contenu[pacman->position_y][pacman->position_x] == 1){
        printf("Erreur dans le premier placement de pacman sur la map");
    }
    map->contenu[pacman->position_y][pacman->position_x] = 0;
    pacman->taille_px = map->taille_perso;
    pacman->position_px_x = conversion_case_pixel_en_x(pacman, map, 0);
    pacman->position_px_y = conversion_case_pixel_en_y(pacman, map, 0);
    pacman->direction = ' ';
    pacman->next_direction = ' ';
    pacman->pacman_frame_delay = 0;
}


void affiche_pacman(Pacman *pacman, SDL_Renderer* ren) {
    // Incrémentation du compteur de frames
    pacman->pacman_frame_delay++;

    // Si un certain nombre de cycles est passé, on passe à la frame suivante
    if (pacman->pacman_frame_delay >= 5) { // 🔥 Ajuste cette valeur pour ralentir/accélérer
        pacman->pacman_frame++;
        pacman->pacman_frame_delay = 0;
        if (pacman->pacman_frame >= 4){
            pacman->pacman_frame = 0;
        }
    }

    SDL_Texture* tex;

    // Vérifier si c'est le moment d'afficher Pacman avec la bouche fermée
    if (pacman->pacman_frame == 3) {
        tex = pacman->skin[8];  // Bouche fermée (cercle jaune)
    } else {
        // Sélection de la texture en fonction de la direction
        if (pacman->direction == 'd') {
            tex = pacman->skin[0 + (pacman->pacman_frame % 2)];
        } else if (pacman->direction == 'h') {
            tex = pacman->skin[2 + (pacman->pacman_frame % 2)];
        } else if (pacman->direction == 'g') {
            tex = pacman->skin[4 + (pacman->pacman_frame % 2)];
        } else if (pacman->direction == 'b') {
            tex = pacman->skin[6 + (pacman->pacman_frame % 2)];
        } else {
            tex = pacman->skin[0]; // Par défaut, Pacman regarde à droite
        }
    }
    // Affichage de Pacman
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

int avance_pacman (Pacman *pacman, Map *map){
    if (((pacman->position_px_x - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case == 0) && ((pacman->position_px_y - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2)) % map->taille_case == 0)){ // <=> pacman au milieu d'une case (et pas en transition entre 2)
        pacman->position_x = (pacman->position_px_x - ORIGINE_X + (int)((pacman->taille_px - map->taille_case)/2)) / map->taille_case;
        pacman->position_y = (pacman->position_px_y - ORIGINE_Y + (int)((pacman->taille_px - map->taille_case)/2)) / map->taille_case;
        gestion_map_torique(pacman, map);

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
    return 0;
}

