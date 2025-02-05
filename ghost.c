#include "ghost.h"

void init_ghost (Ghost *ghost, SDL_Renderer* ren, int num_ghost){
    if (num_ghost == 0){
        init_textures_Blinky(ghost, ren);
        strcpy(ghost->nom, "Blinky");
    } else {
    if (num_ghost == 1){
        init_textures_Pinky(ghost, ren);
        strcpy(ghost->nom, "Pinky");
    } else {
    if (num_ghost == 2){
        init_textures_Inky(ghost, ren);
        strcpy(ghost->nom, "Inky");
    } else {
    if (num_ghost == 3){
        init_textures_Clyde(ghost, ren);
        strcpy(ghost->nom, "Clyde");
    }}}}
    ghost->skin_eaten[0] = loadTexture("ressources/pacman/pakuman_0.bmp", ren);
    ghost->skin_eaten[1] = loadTexture("ressources/pacman/pakuman_1.bmp", ren);
    ghost->skin_eaten[2] = loadTexture("ressources/pacman/pakuman_2.bmp", ren);
    ghost->skin_eaten[3] = loadTexture("ressources/pacman/pakuman_3.bmp", ren);
    ghost->skin_frightened[0] = loadTexture("ressources/cherry.bmp", ren);
    ghost->skin_frightened[1] = loadTexture("ressources/wall.bmp", ren);
    ghost->is_affiche = 0;
    ghost->is_clignotement = 0;
    ghost->frame = 0;
    ghost->vitesse = VITESSE_GHOST;
}

void init_textures_Blinky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost1_0.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost1_1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost1_2.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost1_3.bmp", ren);
}

void init_textures_Pinky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost2_0.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost2_1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost2_2.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost2_3.bmp", ren);
}

void init_textures_Inky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost3_0.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost3_1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost3_2.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost3_3.bmp", ren);
}

void init_textures_Clyde (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost4_0.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost4_1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost4_2.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost4_3.bmp", ren);
}

int conversion_case_pixel_en_x_g (Ghost *ghost, Map *map, int difference){
    return ORIGINE_X + (ghost->position_x + difference) * map->taille_case - (int)((ghost->taille_px - map->taille_case)/2);
}

int conversion_case_pixel_en_y_g (Ghost *ghost, Map *map, int difference){
    return ORIGINE_Y + (ghost->position_y + difference) * map->taille_case - (int)((ghost->taille_px - map->taille_case)/2);
}

void premier_placement_ghost (Ghost *ghost, Map *map, const int x, const int y){
    ghost->position_x = x;
    ghost->position_y = y;
    if (map->contenu[ghost->position_y][ghost->position_x] == 1){
        printf("Erreur dans le premier placement de ghost sur la map");
    }
    ghost->taille_px = map->taille_perso;
    ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, 0);
    ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, 0);
    ghost->direction = ' ';
    ghost->is_affiche = 1;
}

void affiche_ghost (Ghost *ghost, SDL_Renderer* ren) {
    if (ghost->is_affiche == 1) {
        SDL_Texture* tex;
        SDL_Texture** skin;
        if (strcmp(ghost->etat, "frightened") == 0){
            if (ghost->is_clignotement == 1 && (int)(ghost->frame/FREQUENCE_CLIGNOTEMMENT) % 2 == 1) {
                tex = ghost->skin_frightened[1];
            } else {
                tex = ghost->skin_frightened[0];
            }
        } else {
            if (strcmp(ghost->etat, "eaten") == 0){
                skin = ghost->skin_eaten;
            } else {
                skin = ghost->skin_normal;
            }
            if (ghost->direction == 'd'){
                tex = skin[0];
            } else {
            if (ghost->direction == 'g'){
                tex = skin[2];
            } else {
            if (ghost->direction == 'h'){
                tex = skin[1];
            } else {
            if (ghost->direction == 'b'){
                tex = skin[3];
            } else {
                tex = skin[0]; //Par défaut le ghost regarde a droite
            }}}}
        }
        ghost->frame++;
        renderTexture(tex, ren, ghost->position_px_x, ghost->position_px_y, ghost->taille_px, ghost->taille_px);
    }
}

void aller_a_droite_g (Ghost *ghost, Map *map){
    ghost->direction = 'd';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((ghost->position_px_x + ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case > ghost->position_x && (ghost->position_px_x + ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) % map->taille_case > 0) {
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, 1);
    } else {
        ghost->position_px_x += ghost->vitesse;
    }
}

void aller_a_gauche_g (Ghost *ghost, Map *map){
    ghost->direction = 'g';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers la droite (donc plus de valeurs négatives)
    if ((ghost->position_px_x - ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) / map->taille_case < ghost->position_x + 1 && (ghost->position_px_x - ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) % map->taille_case > 0) {
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, -1);
    } else {
        ghost->position_px_x -= ghost->vitesse;
    }
}

void aller_en_haut_g (Ghost *ghost, Map *map){
    ghost->direction = 'h';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers le bas (donc plus de valeurs négatives)
    if ((ghost->position_px_y - ghost->vitesse - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) / map->taille_case < ghost->position_y + 1 && (ghost->position_px_y - ghost->vitesse - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) % map->taille_case > 0) {
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, -1);
    } else {
        ghost->position_px_y -= ghost->vitesse;
    }
}

void aller_en_bas_g (Ghost *ghost, Map *map){
    ghost->direction = 'b';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((ghost->position_px_y + ghost->vitesse - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case > ghost->position_y && (ghost->position_px_y + ghost->vitesse - ORIGINE_Y) % map->taille_case > 0) {
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, 1);
    } else {
        ghost->position_px_y += ghost->vitesse;
    }
}

int nb_alea(int min, int max){
    return min + rand() % (max-min +1);
}

void choix_direction_aleatoire (Ghost *ghost, char choix_valides[4], const int nb_choix) {
    ghost->direction = choix_valides[nb_alea(0, nb_choix - 1)];
}

void chase_target_Blinky (Ghost *ghost, Pacman* pacman){
    ghost->target_x = pacman->position_x;
    ghost->target_y = pacman->position_y;
}

void chase_target_Pinky (Ghost *ghost, Pacman* pacman){
    if (pacman->direction == 'd') {
        ghost->target_x = pacman->position_x + 4;
        ghost->target_y = pacman->position_y;
    } else {
    if (pacman->direction == 'g') {
        ghost->target_x = pacman->position_x - 4;
        ghost->target_y = pacman->position_y;
    } else {
    if (pacman->direction == 'b') {
        ghost->target_x = pacman->position_x;
        ghost->target_y = pacman->position_y + 4;
    } else {
    if (pacman->direction == 'h') {
        ghost->target_x = pacman->position_x - 4; // C'est bizare mais c'est comme ça dans l'original ! (cf : https://www.youtube-nocookie.com/embed/ataGotQ7ir8?playlist=ataGotQ7ir8&autoplay=1&iv_load_policy=3&loop=1&start=807)
        ghost->target_y = pacman->position_y - 4;
    }}}}
}

void chase_target_Inky (Ghost *ghost, Pacman* pacman, Ghost* Blinky){
    int target_x;
    int target_y;
    if (pacman->direction == 'd') {
        target_x = pacman->position_x + 2;
        target_y = pacman->position_y;
    } else {
    if (pacman->direction == 'g') {
        target_x = pacman->position_x - 2;
        target_y = pacman->position_y;
    } else {
    if (pacman->direction == 'b') {
        target_x = pacman->position_x;
        target_y = pacman->position_y + 2;
    } else {
    if (pacman->direction == 'h') {
        target_x = pacman->position_x - 2; // C'est bizare mais c'est comme ça dans l'original ! (cf : https://www.youtube-nocookie.com/embed/ataGotQ7ir8?playlist=ataGotQ7ir8&autoplay=1&iv_load_policy=3&loop=1&start=807)
        target_y = pacman->position_y - 2;
    }
    }}}
    // Le target est le symétrique de la position de Blinky par rapport au target intermédiaire calculé juste avant.
    ghost->target_x = 2*target_x - Blinky->position_x;
    ghost->target_y = 2*target_y - Blinky->position_y;
}

void chase_target_Clyde (Ghost *ghost, Pacman* pacman, Map *map){
    if (abs(ghost->position_x - pacman->position_x) < 8 && abs(ghost->position_y - pacman->position_y) < 8){
        scatter_target_Clyde(ghost, map);
    } else {
        ghost->target_x = pacman->position_x;
        ghost->target_y = pacman->position_y;
    }
}

void choix_direction (Ghost *ghost, char choix_valides[4], const int nb_choix, Pacman* pacman, Ghost* Blinky, Map *map){
    if (strcmp(ghost->etat,"frightened") == 0) {
        choix_direction_aleatoire(ghost, choix_valides, nb_choix);
    } else {
        if (strcmp(ghost->etat,"chase") == 0) {
            if (strcmp(ghost->nom,"Blinky") == 0) {
                chase_target_Blinky(ghost, pacman);
            } else {
            if (strcmp(ghost->nom,"Pinky") == 0) {
                chase_target_Pinky(ghost, pacman);
            } else {
            if (strcmp(ghost->nom,"Inky") == 0) {
                chase_target_Inky(ghost, pacman, Blinky);
            } else {
            if (strcmp(ghost->nom,"Clyde") == 0){
                chase_target_Clyde(ghost, pacman, map);
            }}}}
        }
        choix_direction_vers_target(ghost, choix_valides, nb_choix, map);
    }
}

int distance_entre_2_points (int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void choix_direction_vers_target (Ghost *ghost, char choix_valides[4], const int nb_choix, Map *map){
    int num_dir_min = 0;
    if (nb_choix > 1){
        int distance;
        int distance_min = map->x * map->x + map->y * map->y; // Initialisation avec un maximum
        for (int i = 0; i < nb_choix; i++){
            if (choix_valides[i] == 'd'){
                distance = distance_entre_2_points(ghost->position_x + 1, ghost->position_y, ghost->target_x, ghost->target_y);
            } else {
            if (choix_valides[i] == 'g'){
                distance = distance_entre_2_points(ghost->position_x - 1, ghost->position_y, ghost->target_x, ghost->target_y);
            } else {
            if (choix_valides[i] == 'h'){
                distance = distance_entre_2_points(ghost->position_x, ghost->position_y - 1, ghost->target_x, ghost->target_y);
            } else {}
            if (choix_valides[i] == 'b'){
                distance = distance_entre_2_points(ghost->position_x, ghost->position_y + 1, ghost->target_x, ghost->target_y);
            }}}
            if (distance < distance_min){
                distance_min = distance;
                num_dir_min = i;
            }
        }
    }
    ghost->direction = choix_valides[num_dir_min];
}

void scatter_target_Blinky (Ghost *ghost, Map *map) {
    ghost->target_x = map->x - 3;
    ghost->target_y = -4;
}

void scatter_target_Pinky (Ghost *ghost, Map *map) {
    ghost->target_x = 2;
    ghost->target_y = -4;
}

void scatter_target_Inky (Ghost *ghost, Map *map) {
    ghost->target_x = map->x - 1;
    ghost->target_y = map->y;
}

void scatter_target_Clyde (Ghost *ghost, Map *map) {
    ghost->target_x = 0;
    ghost->target_y = map->y;
}

void changement_etat (Ghost *ghost, Map *map) {
    if (strcmp(ghost->etat, "scatter") == 0){
        ghost->vitesse = VITESSE_GHOST;
        if (strcmp(ghost->nom,"Blinky") == 0) {
            scatter_target_Blinky(ghost, map);
        } else {
        if (strcmp(ghost->nom,"Pinky") == 0) {
            scatter_target_Pinky(ghost, map);
        } else {
        if (strcmp(ghost->nom,"Inky") == 0) {
            scatter_target_Inky(ghost, map);
        } else {
        if (strcmp(ghost->nom,"Clyde") == 0){
            scatter_target_Clyde(ghost, map);
        }}}}
    } else {
    if (strcmp(ghost->etat, "eaten") == 0){
        ghost->vitesse = VITESSE_GHOST_EATEN;
        // Target au dessus de la base des fantômes
        ghost->target_x = 13; // TODO target dépend de la map !
        ghost->target_y = 11;
    } else {
    if (strcmp(ghost->etat, "frightened") == 0){
        ghost->vitesse = VITESSE_GHOST_FRIGHTENED;
    } else {
    if (strcmp(ghost->etat, "chase") == 0){
        ghost->vitesse = VITESSE_GHOST;
    }}}}
    strcpy(ghost->etat_precedent, ghost->etat);
}

void gestion_map_torique_g (Ghost *ghost, Map *map) {
    if (ghost->position_x == map->x) {
        ghost->position_x = 0;
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, -1);
    }
    if (ghost->position_y == map->y) {
        ghost->position_y = 0;
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, -1);
    }
    if (ghost->position_x == -1) {
        ghost->position_x = map->x - 1;
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, 1);
    }
    if (ghost->position_y == -1) {
        ghost->position_y = map->y - 1;
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, +1);
    }
}

int avance_ghost (Ghost *ghost, Map *map, Pacman* pacman, Ghost* Blinky){
    if (ghost->is_affiche == 1) {
        if (strcmp(ghost->etat,ghost->etat_precedent) != 0 && strcmp(ghost->etat_precedent,"frightened") != 0) {
            // Dans ce cas faire demi tour (La seule exception pour laquelle le fantôme peut faire demi tour):
            changement_etat(ghost, map);
            faire_demi_tour(ghost, map);
        } else {
            if (strcmp(ghost->etat,ghost->etat_precedent) != 0) {
                changement_etat(ghost, map);
            }
            if (((ghost->position_px_x - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) % map->taille_case == 0) && ((ghost->position_px_y - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2)) % map->taille_case == 0)){ // <=> ghost au milieu d'une case (et pas en transition entre 2)
                ghost->position_x = (ghost->position_px_x - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case;
                ghost->position_y = (ghost->position_px_y - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case;
                gestion_map_torique_g(ghost, map);

                // Initialisation de la liste des choix valides et du compteur
                int nb_choix = 0; // Compte le nombre de directions valides
                char choix_valides[4]; // Tableau pour stocker les directions possibles

                // Vérification des directions valides (impossibilié de faire demi-tour)
                // ! Attention ! ordre des directions très important ! pour les priorités de déplacements : haut > gauche > bas > droite
                if (map->contenu[mod(ghost->position_y - 1, map->y)][ghost->position_x] != 1 && ghost->direction != 'b') { // TODO ajouter les bouts de map safe (pas possible d'aller en haut)
                    choix_valides[nb_choix++] = 'h'; // Haut
                }
                if (map->contenu[ghost->position_y][mod(ghost->position_x - 1, map->x)] != 1 && ghost->direction != 'd') {
                    choix_valides[nb_choix++] = 'g'; // Gauche
                }
                if (map->contenu[mod(ghost->position_y + 1, map->y)][ghost->position_x] != 1 && ghost->direction != 'h' && map->contenu[mod(ghost->position_y + 1, map->y)][ghost->position_x] != 3) {
                    choix_valides[nb_choix++] = 'b'; // Bas
                }
                if (map->contenu[ghost->position_y][mod(ghost->position_x + 1, map->x)] != 1 && ghost->direction != 'g') {
                    choix_valides[nb_choix++] = 'd'; // Droite
                }

                // Choisir une direction valide si des options existent
                if (nb_choix > 0) {
                    choix_direction (ghost, choix_valides, nb_choix, pacman, Blinky, map);
                } else { // Pas de direction valide (ghost bloqué)
                    printf("Le ghost est bloqué\n"); //si jamais une erreur est généré, on saura d'où il s'agit
                    return 1;
                }
            }  // <=> Le ghost est en transition entre 2 cases. Le seul mouvement possible est alors de continuer le mouvement.
            suivre_direction(ghost, map);
        }
    }
}

void suivre_direction (Ghost *ghost, Map *map){
    if (ghost->direction == 'd'){
        aller_a_droite_g(ghost, map);
    }
    if (ghost->direction == 'g'){
        aller_a_gauche_g(ghost, map);
    }
    if (ghost->direction == 'h'){
        aller_en_haut_g(ghost, map);
    }
    if (ghost->direction == 'b'){
        aller_en_bas_g(ghost, map);
    }
}

void faire_demi_tour (Ghost *ghost, Map *map){
    if (ghost->direction == 'd'){
        aller_a_gauche_g(ghost, map);
    }
    if (ghost->direction == 'g'){
        aller_a_droite_g(ghost, map);
    }
    if (ghost->direction == 'h'){
        aller_en_bas_g(ghost, map);
    }
    if (ghost->direction == 'b'){
        aller_en_haut_g(ghost, map);
    }
}


