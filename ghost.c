#include "ghost.h"

void init_ghost(Ghost* ghost, SDL_Renderer* ren, int num_ghost) {
    if (num_ghost == 0) {
        init_textures_Blinky(ghost, ren);
        strcpy(ghost->nom, "Blinky");
    } else if (num_ghost == 1) {
        init_textures_Pinky(ghost, ren);
        strcpy(ghost->nom, "Pinky");
    } else if (num_ghost == 2) {
        init_textures_Inky(ghost, ren);
        strcpy(ghost->nom, "Inky");
    } else if (num_ghost == 3) {
        init_textures_Clyde(ghost, ren);
        strcpy(ghost->nom, "Clyde");
    }

    // Initialiser les textures spécifiques aux états
    init_textures_frightened(ghost, ren);
    init_textures_eaten(ghost, ren);

    // Initialisation des autres membres
    ghost->is_affiche = 0;
    ghost->is_clignotement = 0;
    ghost->frame = 0;
    ghost->vitesse = VITESSE_GHOST;
    ghost->direction = ' ';
    ghost->etat = 0;
    ghost->etat_precedent = 0;
    ghost->etat_prioritaire = 0;
}


void init_textures_frightened(Ghost* ghost, SDL_Renderer* ren) {
    ghost->skin_frightened[0] = loadTexture("ressources/ghost/ghost_effraye1.bmp", ren);
    ghost->skin_frightened[1] = loadTexture("ressources/ghost/ghost_effraye2.bmp", ren);
    ghost->skin_frightened[2] = loadTexture("ressources/ghost/ghost_effraye3.bmp", ren);
    ghost->skin_frightened[3] = loadTexture("ressources/ghost/ghost_effraye4.bmp", ren);
}

void init_textures_eaten(Ghost* ghost, SDL_Renderer* ren) {
    ghost->skin_eaten[0] = loadTexture("ressources/ghost/ghost_yeux0.bmp", ren);
    ghost->skin_eaten[1] = loadTexture("ressources/ghost/ghost_yeux1.bmp", ren);
    ghost->skin_eaten[2] = loadTexture("ressources/ghost/ghost_yeux2.bmp", ren);
    ghost->skin_eaten[3] = loadTexture("ressources/ghost/ghost_yeux3.bmp", ren);
}

void init_textures_Blinky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost_red7.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost_red1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost_red5.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost_red3.bmp", ren);
    ghost->skin_normal[4] = loadTexture("ressources/ghost/ghost_red8.bmp", ren);
    ghost->skin_normal[5] = loadTexture("ressources/ghost/ghost_red2.bmp", ren);
    ghost->skin_normal[6] = loadTexture("ressources/ghost/ghost_red6.bmp", ren);
    ghost->skin_normal[7] = loadTexture("ressources/ghost/ghost_red4.bmp", ren);
}

void init_textures_Pinky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost_pink7.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost_pink1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost_pink5.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost_pink3.bmp", ren);
    ghost->skin_normal[4] = loadTexture("ressources/ghost/ghost_pink8.bmp", ren);
    ghost->skin_normal[5] = loadTexture("ressources/ghost/ghost_pink2.bmp", ren);
    ghost->skin_normal[6] = loadTexture("ressources/ghost/ghost_pink6.bmp", ren);
    ghost->skin_normal[7] = loadTexture("ressources/ghost/ghost_pink4.bmp", ren);
    ghost->temps_avant_sortie_maison = 1;
}

void init_textures_Inky (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost_lb7.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost_lb1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost_lb5.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost_lb3.bmp", ren);
    ghost->skin_normal[4] = loadTexture("ressources/ghost/ghost_lb8.bmp", ren);
    ghost->skin_normal[5] = loadTexture("ressources/ghost/ghost_lb2.bmp", ren);
    ghost->skin_normal[6] = loadTexture("ressources/ghost/ghost_lb6.bmp", ren);
    ghost->skin_normal[7] = loadTexture("ressources/ghost/ghost_lb4.bmp", ren);
    ghost->temps_avant_sortie_maison = 4;
}

void init_textures_Clyde (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin_normal[0] = loadTexture("ressources/ghost/ghost_yellow7.bmp", ren);
    ghost->skin_normal[1] = loadTexture("ressources/ghost/ghost_yellow1.bmp", ren);
    ghost->skin_normal[2] = loadTexture("ressources/ghost/ghost_yellow5.bmp", ren);
    ghost->skin_normal[3] = loadTexture("ressources/ghost/ghost_yellow3.bmp", ren);
    ghost->skin_normal[4] = loadTexture("ressources/ghost/ghost_yellow8.bmp", ren);
    ghost->skin_normal[5] = loadTexture("ressources/ghost/ghost_yellow2.bmp", ren);
    ghost->skin_normal[6] = loadTexture("ressources/ghost/ghost_yellow6.bmp", ren);
    ghost->skin_normal[7] = loadTexture("ressources/ghost/ghost_yellow4.bmp", ren);
    ghost->temps_avant_sortie_maison = 8;
}

int conversion_case_pixel_en_x_g (Ghost *ghost, Map *map, float difference){
    return ORIGINE_X + (int)((ghost->position_x + difference) * map->taille_case) - (int)((ghost->taille_px - map->taille_case)/2);
}

int conversion_case_pixel_en_y_g (Ghost *ghost, Map *map, float difference){
    return ORIGINE_Y + (int)((ghost->position_y + difference) * map->taille_case) - (int)((ghost->taille_px - map->taille_case)/2);
}

void premier_placement_ghost (Ghost *ghost, Map *map, const int x, const int y){
    ghost->position_x = x;
    ghost->position_y = y;
    if (map->contenu[ghost->position_y][ghost->position_x] == 1){
        printf("Erreur dans le premier placement de ghost sur la map");
    }
    ghost->taille_px = map->taille_perso;
    if (map->type == MAP_TYPE_DESSIN){
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, 0.5);
        if (strcmp(ghost->nom,"Blinky") == 0) {
            ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, 0.);
        } else {
            ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, 0.5);
        }
    } else {
    if (map->type == MAP_TYPE_TILS){
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, 0.);
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, 0.);
    }}
    ghost->direction = ' ';
    ghost->is_affiche = 1;
}


void affiche_ghost(Ghost* ghost, SDL_Renderer* ren) {
    if (ghost->is_affiche == 1) {
        // Incrémenter le compteur de temps
        ghost->frame_delay++;

        // Si un certain nombre de cycles est passé, on passe à la frame suivante
        if (ghost->frame_delay >= 10) { // Ajuster cette valeur selon la vitesse désirée
            ghost->frame++; // Incrémenter la frame
            ghost->frame_delay = 0; // Réinitialiser le compteur de temps
        }

        SDL_Texture* tex;

        // Si le fantôme est effrayé
        if (ghost->etat == ETAT_FRIGHTENED) {
            if (ghost->is_clignotement) {
                // Clignotement : alterne entre les 2 skins bleus et les 2 skins blancs
                if (ghost->frame % (FREQUENCE_CLIGNOTEMMENT * 2) < FREQUENCE_CLIGNOTEMMENT) {
                    tex = (ghost->frame % 2 == 0) ? ghost->skin_frightened[0] : ghost->skin_frightened[1]; // Bleu
                } else {
                    tex = (ghost->frame % 2 == 0) ? ghost->skin_frightened[2] : ghost->skin_frightened[3]; // Blanc
                }
            } else {
                // Mode frightened normal (bleu uniquement)
                tex = (ghost->frame % 2 == 0) ? ghost->skin_frightened[0] : ghost->skin_frightened[1]; 
            }
        }
        // Si le fantôme est mangé
        else if (ghost->etat == ETAT_EATEN) {
            if (ghost->direction == 'd') {
                tex = ghost->skin_eaten[0]; // Droite
            } else if (ghost->direction == 'h') {
                tex = ghost->skin_eaten[1]; // Haut
            } else if (ghost->direction == 'g') {
                tex = ghost->skin_eaten[2]; // Gauche
            } else if (ghost->direction == 'b') {
                tex = ghost->skin_eaten[3]; // Bas
            } else {
                tex = ghost->skin_eaten[0]; // Par défaut droite
            }
        }
        // Si le fantôme est en état normal
        else {
            if (ghost->direction == 'd') {
                tex = (ghost->frame % 2 == 0) ? ghost->skin_normal[0] : ghost->skin_normal[4]; // Droite
            } else if (ghost->direction == 'g') {
                tex = (ghost->frame % 2 == 0) ? ghost->skin_normal[2] : ghost->skin_normal[6]; // Gauche
            } else if (ghost->direction == 'h') {
                tex = (ghost->frame % 2 == 0) ? ghost->skin_normal[1] : ghost->skin_normal[5]; // Haut
            } else if (ghost->direction == 'b') {
                tex = (ghost->frame % 2 == 0) ? ghost->skin_normal[3] : ghost->skin_normal[7]; // Bas
            } else {
                tex = ghost->skin_normal[0]; // Par défaut droite
            }
        }

        renderTexture(tex, ren, ghost->position_px_x, ghost->position_px_y, ghost->taille_px, ghost->taille_px);
    }
}





void aller_a_droite_g (Ghost *ghost, Map *map){
    ghost->direction = 'd';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((ghost->position_px_x + ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case > ghost->position_x && (ghost->position_px_x + ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) % map->taille_case > 0) {
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, 1.);
    } else {
        ghost->position_px_x += ghost->vitesse;
    }
}

void aller_a_gauche_g (Ghost *ghost, Map *map){
    ghost->direction = 'g';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers la droite (donc plus de valeurs négatives)
    if ((ghost->position_px_x - ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) / map->taille_case < ghost->position_x + 1 && (ghost->position_px_x - ghost->vitesse - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) % map->taille_case > 0) {
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, -1.);
    } else {
        ghost->position_px_x -= ghost->vitesse;
    }
}

void aller_en_haut_g (Ghost *ghost, Map *map){
    ghost->direction = 'h';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    // Si, avec la map torrique, la position est négative, les calculs de bases ne marchent plus... Pour corriger cela je teste en décalant de 2 cases vers le bas (donc plus de valeurs négatives)
    if ((ghost->position_px_y - ghost->vitesse - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) / map->taille_case < ghost->position_y + 1 && (ghost->position_px_y - ghost->vitesse - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2) + (2*map->taille_case)) % map->taille_case > 0) {
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, -1.);
    } else {
        ghost->position_px_y -= ghost->vitesse;
    }
}

void aller_en_bas_g (Ghost *ghost, Map *map){
    ghost->direction = 'b';
    // Test si le ghost ne vas pas trop vite donc qu'il ne loupe pas le centre des cases car c'est une position obligatoire qui sert pour la de prise de décisions
    if ((ghost->position_px_y + ghost->vitesse - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case > ghost->position_y && (ghost->position_px_y + ghost->vitesse - ORIGINE_Y) % map->taille_case > 0) {
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, 1.);
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
    if (ghost->etat == ETAT_FRIGHTENED) {
        choix_direction_aleatoire(ghost, choix_valides, nb_choix);
    } else {
        if (ghost->etat == ETAT_CHASE) {
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

void scatter_target_Pinky (Ghost *ghost) {
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
    if (ghost->etat == ETAT_SCATTER){
        ghost->vitesse = VITESSE_GHOST;
        if (strcmp(ghost->nom,"Blinky") == 0) {
            scatter_target_Blinky(ghost, map);
        } else {
        if (strcmp(ghost->nom,"Pinky") == 0) {
            scatter_target_Pinky(ghost);
        } else {
        if (strcmp(ghost->nom,"Inky") == 0) {
            scatter_target_Inky(ghost, map);
        } else {
        if (strcmp(ghost->nom,"Clyde") == 0){
            scatter_target_Clyde(ghost, map);
        }}}}
    } else {
    if (ghost->etat == ETAT_EATEN){
        ghost->vitesse = VITESSE_GHOST_EATEN;
        // Target au dessus de la base des fantômes
        ghost->target_x = map->position_maison_ghosts_x;
        ghost->target_y = map->position_maison_ghosts_y;
    } else {
    if (ghost->etat == ETAT_FRIGHTENED){
        ghost->vitesse = VITESSE_GHOST_FRIGHTENED;
    } else {
    if (ghost->etat == ETAT_CHASE){
        ghost->vitesse = VITESSE_GHOST;
    }}}}
    ghost->etat_precedent = ghost->etat;
}

void gestion_map_torique_g (Ghost *ghost, Map *map) {
    if (ghost->position_x == map->x) {
        ghost->position_x = 0;
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, -1.);
    }
    if (ghost->position_y == map->y) {
        ghost->position_y = 0;
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, -1.);
    }
    if (ghost->position_x == -1) {
        ghost->position_x = map->x - 1;
        ghost->position_px_x = conversion_case_pixel_en_x_g(ghost, map, 1.);
    }
    if (ghost->position_y == -1) {
        ghost->position_y = map->y - 1;
        ghost->position_px_y = conversion_case_pixel_en_y_g(ghost, map, +1.);
    }
}

int avance_ghost (Ghost *ghost, Map *map, Pacman* pacman, Ghost* Blinky){
    if (ghost->is_affiche == 1) {
        if (ghost->etat != ghost->etat_precedent && ghost->etat_precedent != ETAT_FRIGHTENED) {
            // Dans ce cas faire demi tour (La seule exception pour laquelle le fantôme peut faire demi tour):
            changement_etat(ghost, map);
            faire_demi_tour(ghost, map);
        } else {
            if (ghost->etat != ghost->etat_precedent) {
                changement_etat(ghost, map);
            }
            if (((ghost->position_px_x - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) % map->taille_case == 0) && ((ghost->position_px_y - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2)) % map->taille_case == 0)){ // <=> ghost au milieu d'une case (et pas en transition entre 2)
                ghost->position_x = (ghost->position_px_x - ORIGINE_X + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case;
                ghost->position_y = (ghost->position_px_y - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2)) / map->taille_case;
                gestion_map_torique_g(ghost, map);
                master_choix_directions(ghost, map, pacman, Blinky);
            }  // <=> Le ghost est en transition entre 2 cases. Le seul mouvement possible est alors de continuer le mouvement.
            suivre_direction(ghost, map);
        }
    }
    return 0;
}

void master_choix_directions (Ghost *ghost, Map *map, Pacman* pacman, Ghost* Blinky){
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

void bouger_dans_maison (Ghost *ghost, Map *map){
    if ((ghost->position_px_y - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2) - (int)(map->taille_case/2)) % map->taille_case == 0){ // <=> ghost au milieu d'une case (et pas en transition entre 2)
        ghost->position_y = (ghost->position_px_y - ORIGINE_Y + (int)((ghost->taille_px - map->taille_case)/2) - (int)(map->taille_case/2)) / map->taille_case;
        if (map->contenu[ghost->position_y + 2][ghost->position_x] == 1){
            ghost->direction = 'h';
        } else {
        if (map->contenu[ghost->position_y - 1][ghost->position_x] == 1 || map->contenu[ghost->position_y - 1][ghost->position_x] == 3){
            ghost->direction = 'b';
        }}
    }
    if (ghost->direction == 'h'){
        ghost->position_px_y--;
    } else {
    if (ghost->direction == 'b'){
        ghost->position_px_y++;
    }}
}

int go_outside_home (Ghost *ghost, Map *map){
    int target_x_px = ORIGINE_X + map->position_maison_ghosts_x * map->taille_case - (int)((ghost->taille_px - map->taille_case)/2) + (int)(map->taille_case/2);
    int target_y_px = ORIGINE_Y + map->position_maison_ghosts_y * map->taille_case - (int)((ghost->taille_px - map->taille_case)/2);
    if (ghost->position_px_x == target_x_px){
        if (ghost->position_px_y == target_y_px){
            return 0;
        } else {
            ghost->position_px_y--;
            return 1;
        }
    } else {
        if (ghost->position_px_x < target_x_px){
            ghost->position_px_x++;
        } else {
            ghost->position_px_x--;
        }
        return 1;
    }
}

int go_inside_home (Ghost *ghost, Map *map){
    int target_x_px = ORIGINE_X + map->position_maison_ghosts_x * map->taille_case - (int)((ghost->taille_px - map->taille_case)/2) + (int)(map->taille_case/2);
    int target_y_px = ORIGINE_Y + (map->position_maison_ghosts_y + 2) * map->taille_case - (int)((ghost->taille_px - map->taille_case)/2);
    if (ghost->position_px_x == target_x_px){
        if (ghost->position_px_y == target_y_px){
            return 0;
        } else {
            ghost->position_px_y++;
            return 1;
        }
    } else {
        if (ghost->position_px_x < target_x_px){
            ghost->position_px_x++;
        } else {
            ghost->position_px_x--;
        }
        return 1;
    }
}
