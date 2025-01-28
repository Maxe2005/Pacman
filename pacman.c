#include "pacman.h"


void init_textures_pacman (Pacman *pacman, SDL_Renderer* ren){
    pacman->skin[0] = loadTexture("ressources/pakuman_0.bmp", ren);
    pacman->skin[1] = loadTexture("ressources/pakuman_1.bmp", ren);
    pacman->skin[2] = loadTexture("ressources/pakuman_2.bmp", ren);
    pacman->skin[3] = loadTexture("ressources/pakuman_3.bmp", ren);
}

void premier_placement_pacman (Pacman *pacman, int map[MAP_Y][MAP_X], const int x, const int y){
    pacman->position_x = x;
    pacman->position_y = y;
    if (map[pacman->position_y][pacman->position_x] == 1){
        printf("Erreur dans le premier placement de pacman sur la map");
    }
    map[pacman->position_y][pacman->position_x] = 0;
    pacman->position_px_x = ORIGINE_X + pacman->position_x*TAILLE_CASE;
    pacman->position_px_y = ORIGINE_Y + pacman->position_y*TAILLE_CASE;
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
    renderTexture(tex, ren, pacman->position_px_x, pacman->position_px_y, TAILLE_CASE, TAILLE_CASE);
}

void aller_a_droite (Pacman *pacman){
    pacman->direction = 'd';
    pacman->position_px_x += VITESSE_PACMAN;
}

void aller_a_gauche (Pacman *pacman){
    pacman->direction = 'g';
    pacman->position_px_x -= VITESSE_PACMAN;
}

void aller_en_haut (Pacman *pacman){
    pacman->direction = 'h';
    pacman->position_px_y -= VITESSE_PACMAN;
}

void aller_en_bas (Pacman *pacman){
    pacman->direction = 'b';
    pacman->position_px_y += VITESSE_PACMAN;
}

int avance_pacman (Pacman *pacman, int map[MAP_Y][MAP_X], int *score){
    if (((pacman->position_px_x - ORIGINE_X) % TAILLE_CASE == 0) && ((pacman->position_px_y - ORIGINE_Y) % TAILLE_CASE == 0)){ // <=> pacman au milieu d'une case (et pas en transition entre 2)
        pacman->position_x = (pacman->position_px_x - ORIGINE_X) / TAILLE_CASE;
        pacman->position_y = (pacman->position_px_y - ORIGINE_Y) / TAILLE_CASE;
        update_score(pacman, map, score);
        // Prise en compte de la nouvelle diretion :
        if (pacman->next_direction == 'd' && map[pacman->position_y][pacman->position_x + 1] != 1){
            aller_a_droite(pacman);
            return 0;
        }
        if (pacman->next_direction == 'g' && map[pacman->position_y][pacman->position_x - 1] != 1){
            aller_a_gauche(pacman);
            return 0;
        }
        if (pacman->next_direction == 'h' && map[pacman->position_y - 1][pacman->position_x] != 1){
            aller_en_haut(pacman);
            return 0;
        }
        if (pacman->next_direction == 'b' && map[pacman->position_y + 1][pacman->position_x] != 1){
            aller_en_bas(pacman);
            return 0;
        }

        // Si impossible -> continuation du mouvement :
        if (pacman->direction == 'd' && map[pacman->position_y][pacman->position_x + 1] != 1){
            aller_a_droite(pacman);
            return 0;
        }
        if (pacman->direction == 'g' && map[pacman->position_y][pacman->position_x - 1] != 1){
            aller_a_gauche(pacman);
            return 0;
        }
        if (pacman->direction == 'h' && map[pacman->position_y - 1][pacman->position_x] != 1){
            aller_en_haut(pacman);
            return 0;
        }
        if (pacman->direction == 'b' && map[pacman->position_y + 1][pacman->position_x] != 1){
            aller_en_bas(pacman);
            return 0;
        }
        // Si toujours pas possible alors c'est qu'on a touché un mur. Donc on ne fait rien.

    } else { // <=> Le pacman est en transition entre 2 cases. Les seuls mouvements possibles sont alors le demi-tour demandé ou bien le déplacement continue.
        if (((pacman->position_px_x - ORIGINE_X) % TAILLE_CASE != 0) && ((pacman->position_px_y - ORIGINE_Y) % TAILLE_CASE != 0)){
            printf("Erreur : Pacman ne peut pas se trouver sur la diagonale entre 2 cases !!\n");
            return 1;
        }
        if (pacman->direction == 'd'){
            if (pacman->next_direction == 'g'){
                aller_a_gauche(pacman);
            } else {
                aller_a_droite(pacman);
            }
            return 0;
        }
        if (pacman->direction == 'g'){
            if (pacman->next_direction == 'd'){
                aller_a_droite(pacman);
            } else {
                aller_a_gauche(pacman);
            }
            return 0;
        }
        if (pacman->direction == 'h'){
            if (pacman->next_direction == 'b'){
                aller_en_bas(pacman);
            } else {
                aller_en_haut(pacman);
            }
            return 0;
        }
        if (pacman->direction == 'b'){
            if (pacman->next_direction == 'h'){
                aller_en_haut(pacman);
            } else {
                aller_en_bas(pacman);
            }
            return 0;
        }
    }
}

void update_score (Pacman *pacman, int map[MAP_Y][MAP_X], int *score){
    if (map[pacman->position_y][pacman->position_x] == 2){
        *score += 10;
        map[pacman->position_y][pacman->position_x] = 0; //Vider la case car le <Gum> à été consommé
    } else {
    if (map[pacman->position_y][pacman->position_x] == 4){
        *score += 100;
        map[pacman->position_y][pacman->position_x] = 0; //Vider la case car le <Cherry> à été consommé
    } else {
    if (map[pacman->position_y][pacman->position_x] == 3){ // <Big_Gum> consommé
        map[pacman->position_y][pacman->position_x] = 0;
        // TODO : Ici démarer le mode <frightened>
    }
    }}
}
