#include "ghost.h"


void init_textures_Blinky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin[0] = loadTexture("ressources/ghost1_0.bmp", ren);
    ghost->skin[1] = loadTexture("ressources/ghost1_1.bmp", ren);
    ghost->skin[2] = loadTexture("ressources/ghost1_2.bmp", ren);
    ghost->skin[3] = loadTexture("ressources/ghost1_3.bmp", ren);
    ghost->is_affiche = 0;
}

void init_textures_Pinky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin[0] = loadTexture("ressources/ghost2_0.bmp", ren);
    ghost->skin[1] = loadTexture("ressources/ghost2_1.bmp", ren);
    ghost->skin[2] = loadTexture("ressources/ghost2_2.bmp", ren);
    ghost->skin[3] = loadTexture("ressources/ghost2_3.bmp", ren);
    ghost->is_affiche = 0;
}

void init_textures_Inky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin[0] = loadTexture("ressources/ghost3_0.bmp", ren);
    ghost->skin[1] = loadTexture("ressources/ghost3_1.bmp", ren);
    ghost->skin[2] = loadTexture("ressources/ghost3_2.bmp", ren);
    ghost->skin[3] = loadTexture("ressources/ghost3_3.bmp", ren);
    ghost->is_affiche = 0;
}

void init_textures_Clyde (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin[0] = loadTexture("ressources/ghost4_0.bmp", ren);
    ghost->skin[1] = loadTexture("ressources/ghost4_1.bmp", ren);
    ghost->skin[2] = loadTexture("ressources/ghost4_2.bmp", ren);
    ghost->skin[3] = loadTexture("ressources/ghost4_3.bmp", ren);
    ghost->is_affiche = 0;
}

void premier_placement_ghost (Ghost *ghost, int map[MAP_Y][MAP_X], const int x, const int y){
    ghost->position_x = x;
    ghost->position_y = y;
    if (map[ghost->position_y][ghost->position_x] == 1){
        printf("Erreur dans le premier placement de ghost sur la map");
    }
    ghost->position_px_x = ORIGINE_X + ghost->position_x*TAILLE_CASE;
    ghost->position_px_y = ORIGINE_Y + ghost->position_y*TAILLE_CASE;
    ghost->direction = ' ';
    ghost->is_affiche = 1;
    ghost->taille_px = TAILLE_CASE;
}

void affiche_ghost (Ghost *ghost, SDL_Renderer* ren) {
    if (ghost->is_affiche == 1) {
        SDL_Texture* tex;
        if (ghost->direction == 'd'){
            tex = ghost->skin[0];
        } else {
        if (ghost->direction == 'g'){
            tex = ghost->skin[2];
        } else {
        if (ghost->direction == 'h'){
            tex = ghost->skin[1];
        } else {
        if (ghost->direction == 'b'){
            tex = ghost->skin[3];
        } else {
            tex = ghost->skin[1]; //Par défaut le ghost regarde en haut
        }}}}
        renderTexture(tex, ren, ghost->position_px_x, ghost->position_px_y, ghost->taille_px, ghost->taille_px);
    }
}

void aller_a_droite_g (Ghost *ghost){
    ghost->direction = 'd';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((ghost->position_px_x + VITESSE_GHOST - ORIGINE_X) / TAILLE_CASE > ghost->position_x && (ghost->position_px_x + VITESSE_GHOST - ORIGINE_X) % TAILLE_CASE > 0) {
        ghost->position_px_x = ORIGINE_X + (ghost->position_x + 1) * TAILLE_CASE;
    } else {
        ghost->position_px_x += VITESSE_GHOST;
    }
}

void aller_a_gauche_g (Ghost *ghost){
    ghost->direction = 'g';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers la droite (donc plus de valeurs négatives)
    if ((ghost->position_px_x - VITESSE_GHOST - ORIGINE_X + (2*TAILLE_CASE)) / TAILLE_CASE < ghost->position_x + 1 && (ghost->position_px_x - VITESSE_GHOST - ORIGINE_X + (2*TAILLE_CASE)) % TAILLE_CASE > 0) {
        ghost->position_px_x = ORIGINE_X + (ghost->position_x - 1) * TAILLE_CASE;
    } else {
        ghost->position_px_x -= VITESSE_GHOST;
    }
}

void aller_en_haut_g (Ghost *ghost){
    ghost->direction = 'h';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers le bas (donc plus de valeurs négatives)
    if ((ghost->position_px_y - VITESSE_GHOST - ORIGINE_Y + (2*TAILLE_CASE)) / TAILLE_CASE < ghost->position_y + 1 && (ghost->position_px_y - VITESSE_GHOST - ORIGINE_Y + (2*TAILLE_CASE)) % TAILLE_CASE > 0) {
        ghost->position_px_y = ORIGINE_Y + (ghost->position_y - 1) * TAILLE_CASE;
    } else {
        ghost->position_px_y -= VITESSE_GHOST;
    }
}

void aller_en_bas_g (Ghost *ghost){
    ghost->direction = 'b';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((ghost->position_px_y + VITESSE_GHOST - ORIGINE_Y) / TAILLE_CASE > ghost->position_y && (ghost->position_px_y + VITESSE_GHOST - ORIGINE_Y) % TAILLE_CASE > 0) {
        ghost->position_px_y = ORIGINE_Y + (ghost->position_y + 1) * TAILLE_CASE;
    } else {
        ghost->position_px_y += VITESSE_GHOST;
    }
}

int nb_alea(int min, int max){
    return min + rand() % (max-min +1);
}

void choix_direction_aleatoire (Ghost *ghost, char choix_valides[4], const int nb_choix) {
    ghost->direction = choix_valides[nb_alea(0, nb_choix - 1)];
}

void is_colision_pacman (Ghost *ghost, Pacman *pacman) {
    if (ghost->position_px_x - pacman->position_px_x < ghost->taille_px && ghost->position_px_x - pacman->position_px_x < pacman->taille_px
        && ghost->position_px_y - pacman->position_px_y < ghost->taille_px && ghost->position_px_y - pacman->position_px_y < pacman->taille_px) {
            collision_avec_ghost(pacman);
        }
}

void gestion_map_torique_g (Ghost *ghost) {
    if (ghost->position_x == MAP_X) {
        ghost->position_x = 0;
        ghost->position_px_x = ORIGINE_X + -1 * TAILLE_CASE;
    }
    if (ghost->position_y == MAP_Y) {
        ghost->position_y = 0;
        ghost->position_px_y = ORIGINE_Y + -1 * TAILLE_CASE;
    }
    if (ghost->position_x == -1) {
        ghost->position_x = MAP_X - 1;
        ghost->position_px_x = ORIGINE_X + MAP_X * TAILLE_CASE;
    }
    if (ghost->position_y == -1) {
        ghost->position_y = MAP_Y - 1;
        ghost->position_px_y = ORIGINE_Y + MAP_Y * TAILLE_CASE;
    }
}

int avance_ghost (Ghost *ghost, int map[MAP_Y][MAP_X], Pacman *pacman){
    if (ghost->is_affiche == 1) {
        is_colision_pacman(ghost, pacman);
        if (((ghost->position_px_x - ORIGINE_X) % TAILLE_CASE == 0) && ((ghost->position_px_y - ORIGINE_Y) % TAILLE_CASE == 0)){ // <=> ghost au milieu d'une case (et pas en transition entre 2)
            ghost->position_x = (ghost->position_px_x - ORIGINE_X) / TAILLE_CASE;
            ghost->position_y = (ghost->position_px_y - ORIGINE_Y) / TAILLE_CASE;
            gestion_map_torique_g(ghost);
            // Initialisation de la liste des choix valides et du compteur
            int nb_choix = 0; // Compte le nombre de directions valides
            char choix_valides[4]; // Tableau pour stocker les directions possibles

            // Vérification des directions valides (impossibilié de faire demi-tour)
            if (map[ghost->position_y][mod(ghost->position_x + 1, MAP_X)] != 1 && ghost->direction != 'g') {
                choix_valides[nb_choix++] = 'd'; // Droite
            }
            if (map[ghost->position_y][mod(ghost->position_x - 1, MAP_X)] != 1 && ghost->direction != 'd') {
                choix_valides[nb_choix++] = 'g'; // Gauche
            }
            if (map[mod(ghost->position_y - 1, MAP_Y)][ghost->position_x] != 1 && ghost->direction != 'b') {
                choix_valides[nb_choix++] = 'h'; // Haut
            }
            if (map[mod(ghost->position_y + 1, MAP_Y)][ghost->position_x] != 1 && ghost->direction != 'h') {
                choix_valides[nb_choix++] = 'b'; // Bas
            }
            
            // Choisir une direction valide si des options existent
            if (nb_choix > 0) {
                choix_direction_aleatoire (ghost, choix_valides, nb_choix);
            } else { // Pas de direction valide (ghost bloqué)
                printf("Le ghost est bloqué\n"); //si jamais une erreur est généré, on saura d'où il s'agit
                return 1;
            }

        }  // <=> Le ghost est en transition entre 2 cases. Le seul mouvement possible est alors de continuer le mouvement.
        if (((ghost->position_px_x - ORIGINE_X) % TAILLE_CASE != 0) && ((ghost->position_px_y - ORIGINE_Y) % TAILLE_CASE != 0)){
            printf("Erreur : Ghost ne peut pas se trouver sur la diagonale entre 2 cases !!\n");
            return 1;
        }
        if (ghost->direction == 'd'){
                aller_a_droite_g(ghost);
            return 0;
        }
        if (ghost->direction == 'g'){
                aller_a_gauche_g(ghost);
            return 0;
        }
        if (ghost->direction == 'h'){
                aller_en_haut_g(ghost);
            return 0;
        }
        if (ghost->direction == 'b'){
                aller_en_bas_g(ghost);
            return 0;
        }
    }
}




