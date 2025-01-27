#include "ghost.h"


void init_textures_ghost (Ghost *ghost, SDL_Renderer* ren){
    ghost->skin[0] = loadTexture("ressources/ghost1_0.bmp", ren);
    ghost->skin[1] = loadTexture("ressources/ghost1_1.bmp", ren);
    ghost->skin[2] = loadTexture("ressources/ghost1_2.bmp", ren);
    ghost->skin[3] = loadTexture("ressources/ghost1_3.bmp", ren);
}

void premier_placement_ghost (Ghost *ghost, int map[MAP_Y][MAP_X], const int x, const int y){
    ghost->position_x = x;
    ghost->position_y = y;
    if (map[ghost->position_y][ghost->position_x] == 1){
        printf("Erreur dans le premier placement de ghost sur la map");
    }
    map[ghost->position_y][ghost->position_x] = 0;
    ghost->position_px_x = ORIGINE_X + ghost->position_x*TAILLE_CASE;
    ghost->position_px_y = ORIGINE_Y + ghost->position_y*TAILLE_CASE;
    ghost->direction_g = ' ';
}

void affiche_ghost (Ghost *ghost, SDL_Renderer* ren) {
    SDL_Texture* tex;
    if (ghost->direction_g == 'd'){
        tex = ghost->skin[0];
    } else {
    if (ghost->direction_g == 'g'){
        tex = ghost->skin[2];
    } else {
    if (ghost->direction_g == 'h'){
        tex = ghost->skin[1];
    } else {
    if (ghost->direction_g == 'b'){
        tex = ghost->skin[3];
    } else {
        tex = ghost->skin[1]; //Par défaut le ghost regarde à droite
    }}}}
    renderTexture(tex, ren, ghost->position_px_x, ghost->position_px_y, TAILLE_CASE, TAILLE_CASE);
}

void aller_a_droite_g (Ghost *ghost){
    ghost->direction_g = 'd';
    ghost->position_px_x += VITESSE_GHOST;
}

void aller_a_gauche_g (Ghost *ghost){
    ghost->direction_g = 'g';
    ghost->position_px_x -= VITESSE_GHOST;
}

void aller_en_haut_g (Ghost *ghost){
    ghost->direction_g = 'h';
    ghost->position_px_y -= VITESSE_GHOST;
}

void aller_en_bas_g (Ghost *ghost){
    ghost->direction_g = 'b';
    ghost->position_px_y += VITESSE_GHOST;
}

//génére un nombre aléatoire
int nb_alea(int min, int max){
    return min + rand() % (max-min +1);
}

int avance_ghost (Ghost *ghost, int map[MAP_Y][MAP_X]){
    if (((ghost->position_px_x - ORIGINE_X) % TAILLE_CASE == 0) && ((ghost->position_px_y - ORIGINE_Y) % TAILLE_CASE == 0)){ // <=> ghost au milieu d'une case (et pas en transition entre 2)
        ghost->position_x = (ghost->position_px_x - ORIGINE_X) / TAILLE_CASE;
        ghost->position_y = (ghost->position_px_y - ORIGINE_Y) / TAILLE_CASE;
        // Initialisation de la liste des choix valides et du compteur
        int nb_choix = 0; // Compte le nombre de directions valides
        char choix_valides[4]; // Tableau pour stocker les directions possibles
        // Vérification des directions valides
        if (map[ghost->position_y][ghost->position_x + 1] != 1 && ghost->direction_g != 'g') {
            choix_valides[nb_choix++] = 'd'; // Droite
        }
        if (map[ghost->position_y][ghost->position_x - 1] != 1 && ghost->direction_g != 'd') {
            choix_valides[nb_choix++] = 'g'; // Gauche
        }
        if (map[ghost->position_y - 1][ghost->position_x] != 1 && ghost->direction_g != 'b') {
            choix_valides[nb_choix++] = 'h'; // Haut
        }
        if (map[ghost->position_y + 1][ghost->position_x] != 1 && ghost->direction_g != 'h') {
            choix_valides[nb_choix++] = 'b'; // Bas
        }
        
        // Choisir une direction valide aléatoire si des options existent
        if (nb_choix > 0) {
            ghost->direction_g = choix_valides[nb_alea(0, nb_choix - 1)];
        } else {
        // Pas de direction valide (ghost bloqué)
            printf("Le ghost est bloqué"); //si jamais une erreur est généré, on saura d'où il s'agit
            return 1;
        }
        // Si impossible -> continuation du mouvement :
        if (ghost->direction_g == 'd' && map[ghost->position_y][ghost->position_x + 1] != 1){
            aller_a_droite_g(ghost);
            return 0;
        }
        if (ghost->direction_g == 'g' && map[ghost->position_y][ghost->position_x - 1] != 1){
            aller_a_gauche_g(ghost);
            return 0;
        }
        if (ghost->direction_g == 'h' && map[ghost->position_y - 1][ghost->position_x] != 1){
            aller_en_haut_g(ghost);
            return 0;
        }
        if (ghost->direction_g == 'b' && map[ghost->position_y + 1][ghost->position_x] != 1){
            aller_en_bas_g(ghost);
            return 0;
        }
        // Si toujours pas possible alors c'est qu'on a touché un mur. Donc on ne fait rien.

    } else { // <=> Le ghost est en transition entre 2 cases. Les seuls mouvements possibles sont alors le demi-tour demandé ou bien le déplacement continue.
        if (((ghost->position_px_x - ORIGINE_X) % TAILLE_CASE != 0) && ((ghost->position_px_y - ORIGINE_Y) % TAILLE_CASE != 0)){
            printf("Erreur : Ghost ne peut pas se trouver sur la diagonale entre 2 cases !!\n");
            return 1;
        }
        if (ghost->direction_g == 'd'){
                aller_a_droite_g(ghost);
            return 0;
        }
        if (ghost->direction_g == 'g'){
                aller_a_gauche_g(ghost);
            return 0;
        }
        if (ghost->direction_g == 'h'){
                aller_en_haut_g(ghost);
            return 0;
        }
        if (ghost->direction_g == 'b'){
                aller_en_bas_g(ghost);
            return 0;
        }
    }
}




