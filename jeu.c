#include "jeu.h"
#include "plateau.h"
#include "pacman.h"
#include "ghost.h"



void init_font (TTF_Font* font[1]) {
    font[0] = createFont("ressources/DejaVuSans-Bold.ttf", 20); //Font de titres
}
void affiche_les_vies (SDL_Renderer* ren, SDL_Texture * skin_vies, const int nb_vies) {
    const int taille = TAILLE_BANDEAU_HAUT - 2*MARGE_BANDEAU_HAUT;
    for (int i = 1; i <= nb_vies; i++) {
        renderTexture(skin_vies, ren, FEN_X - MARGE_BANDEAU_HAUT - i*taille, MARGE_BANDEAU_HAUT, taille, taille);
    }
}

void collision_avec_ghost (Pacman *pacman) {
    pacman->nb_vies--;
    if (pacman->nb_vies == 0) {
        // TODO menu game over
    }
    // TODO stop la loop et reconmencer partie
}
void free_partie (Partie* partie) {
    free(partie->tils);
    free(partie->font);
    free(partie->pacman);
    free(partie);
}

void init_partie (SDL_Renderer* ren) {
    Partie* partie = malloc(sizeof(Partie));
    partie->score = 0;

    // Initialisation map, textures pour map et font pour titres
    int map[MAP_Y][MAP_X];
    init_map(map);

    partie->tils = malloc(sizeof(SDL_Texture*) * 4);
    init_tils(partie->tils, ren);

    partie->font = malloc(sizeof(TTF_Font*) * 1);
    init_font(partie->font);

    // Initialisation Pacman
    partie->pacman = malloc(sizeof(Pacman));
    init_textures_pacman(partie->pacman, ren);
    premier_placement_pacman(partie->pacman, map, 1, 1);

    boucle_de_jeu (ren, partie, map);
}

void boucle_de_jeu(SDL_Renderer* ren, Partie* partie, int map[MAP_Y][MAP_X]){
    char dir;
    SDL_Color white = {255, 255, 255, 255};
    char text_score[15];
    int running = 1;

    while (running){
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        affiche_map(map, partie->tils, ren);
        affiche_pacman(partie->pacman, ren);
        sprintf(text_score, "Score : %d",partie->score);
        printText(10, 20, text_score, 300, 60, partie->font[0], white, ren);
        updateDisplay(ren);

        avance_pacman(partie->pacman, map, &(partie->score));

        dir = processKeyboard(&running);
        if (dir != ' '){
            partie->pacman->next_direction = dir;
        }
        if (dir == 'M'){
            free_partie(partie);
            ecran_acceuil (ren); // retour à l'écran d'acceuil
            running = 0;
        }
    }
}


void affiche_logo (SDL_Renderer* ren, SDL_Texture* logo) {
    renderTexture(logo, ren,(int)(FEN_X /4),(int)(FEN_Y/8),(int)(FEN_X/2),(int)(FEN_Y/4));
}

void affiche_bouton_start (SDL_Renderer* ren, SDL_Texture* bouton_start) {
    renderTexture(bouton_start, ren,(int)(FEN_X /4),(int)(FEN_Y/2),(int)(FEN_X/2),(int)(FEN_Y/4));
}

void ecran_acceuil (SDL_Renderer* ren){
    SDL_Texture* logo = loadTexture("ressources/pac-man-logo.bmp", ren);
    SDL_Texture* bouton_start = loadTexture("ressources/bouton_start_pacman.bmp", ren);

    clock_t current_time;
    clock_t start_time = clock();
    const double temps_clignotement_bouton_start = 125.0 / 1000.0 * CLOCKS_PER_SEC; //temps_reaction_pacman convertion de milisecondes à clocks
    
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    affiche_logo(ren, logo);
    affiche_bouton_start(ren, bouton_start);

    char lancement;
    int is_bouton_start_visible = 1; // Booleen qui permet de faire clignoter le bouton start
    int running = 1;

    while (running) {
        current_time = clock();
        updateDisplay(ren);

        if ((double)(current_time - start_time) >= temps_clignotement_bouton_start) {
            if (is_bouton_start_visible == 1){
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                SDL_RenderClear(ren);
                affiche_logo(ren, logo);
                is_bouton_start_visible = 0;
            } else {
                affiche_bouton_start(ren, bouton_start);
                is_bouton_start_visible = 1;
            }
            start_time = current_time;
        }
        
        lancement = processKeyboard(&running);
        if (lancement == 'L'){
            init_partie(ren);
            running = 0;
        }
    }
}

