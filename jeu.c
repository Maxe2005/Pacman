#include "jeu.h"


void init_font (TTF_Font* font[1]) {
    font[0] = createFont("ressources/DejaVuSans-Bold.ttf", 20); //Font de titres
}

void affiche_les_vies (SDL_Renderer* ren, SDL_Texture * skin_vies, const int nb_vies) {
    const int taille = TAILLE_BANDEAU_HAUT - 2*MARGE_BANDEAU_HAUT;
    for (int i = 1; i <= nb_vies; i++) {
        renderTexture(skin_vies, ren, FEN_X - MARGE_BANDEAU_HAUT - i*taille, MARGE_BANDEAU_HAUT, taille, taille);
    }
}

int is_collision_pacman_ghost (SDL_Renderer* ren, Ghost** ghosts, Pacman *pacman, Partie* partie, int* running) {
    for (int i = 0; i < partie->nb_ghosts; i++){
        if (abs(ghosts[i]->position_px_x - pacman->position_px_x) < ghosts[i]->taille_px/2 && abs(ghosts[i]->position_px_x - pacman->position_px_x) < pacman->taille_px/2
                && abs(ghosts[i]->position_px_y - pacman->position_px_y) < ghosts[i]->taille_px/2 && abs(ghosts[i]->position_px_y - pacman->position_px_y) < pacman->taille_px/2) {
            partie->nb_vies--;
            *running = 0;
            if (partie->nb_vies == 0) {
                affiche_ecran_game_over(ren, partie);
                SDL_Delay(5000);
                ecran_acceuil(ren);
            } else {
                annimation_mort_pacman(ren, partie);
                placament_pacman_et_ghost(ren, partie);
                boucle_de_jeu(ren, partie);
            }
            return 1;
        }
    }
    return 0;
}

void affiche_ecran_game_over (SDL_Renderer* ren, Partie* partie) {
    int division_x_titre = 5; // doit être >= 3
    int division_y_titre = 4; // doit être >= 3
    int titre_x = (int)(FEN_X/division_x_titre);
    int titre_y = (int)(FEN_Y/division_y_titre);
    int taille_titre_x = (int)(FEN_X/division_x_titre * (division_x_titre-2));
    int taille_titre_y = taille_titre_x/3 ;

    int division_x_score = 5; // doit être >= 3
    int division_y_score = 5;
    int score_x = titre_x + (int)(taille_titre_x / division_x_score);
    int score_y = titre_y + taille_titre_y + (int)(taille_titre_y / division_y_score);
    int taille_score_x = (int)(taille_titre_x/division_x_score * (division_x_score-2));
    int taille_score_y = taille_score_x/5;

    char text_score[15];
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};

    // Effacer
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    printText(titre_x, titre_y, "Game Over", taille_titre_x, taille_titre_y, partie->font[0], red, ren);
    sprintf(text_score, "Score : %d",partie->score);
    printText(score_x, score_y, text_score, taille_score_x, taille_score_y, partie->font[0], white, ren);
    updateDisplay(ren);
}

void annimation_mort_pacman (SDL_Renderer* ren, Partie* partie) {
    char directions[4] = {'d', 'b', 'g', 'h'};
    unsigned int i = 0; 

    while ( i < 10 ){
        affiche_ecran_jeu(ren, partie);
        partie->pacman->direction = directions[i%4] ;
        affiche_pacman(partie->pacman, ren);
        updateDisplay(ren);
        SDL_Delay(100);
        i++;
    }
}

void affiche_ecran_jeu (SDL_Renderer* ren, Partie* partie) {
    // Effacer
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    // Score
    char text_score[15];
    SDL_Color white = {255, 255, 255, 255};
    sprintf(text_score, "Score : %d",partie->score);
    printText(MARGE_BANDEAU_HAUT, MARGE_BANDEAU_HAUT, text_score, MARGE_BANDEAU_HAUT + 250, TAILLE_BANDEAU_HAUT - 2*MARGE_BANDEAU_HAUT, partie->font[0], white, ren);
    
    affiche_les_vies(ren, partie->skin_vies, partie->nb_vies);
    affiche_map(partie->map, partie->tils, ren);
}

void free_partie (Partie* partie) {
    free(partie->tils);
    free(partie->font);
    free(partie->pacman);
    freeMap(partie->map);
    free(partie);
}

void init_partie (SDL_Renderer* ren) {
    Partie* partie = malloc(sizeof(Partie));

    partie->score = 0;

    // Initialisation map, textures pour map et font pour titres
    //Map mape = init_map_dessin();
    //Map mape = init_map_tils();
    //partie->map = &mape;
    const char *nom_map = "Map_originale.csv";
    //save_map_text(nom_map, &map);
    partie->map = load_map_text(nom_map);

    partie->tils = malloc(sizeof(SDL_Texture*) * 4);
    init_tils(partie->tils, ren);

    partie->font = malloc(sizeof(TTF_Font*) * 1);
    init_font(partie->font);

    // Initialisation Pacman
    partie->pacman = malloc(sizeof(Pacman));
    init_textures_pacman(partie->pacman, ren);
    // Initialisation des vies
    partie->skin_vies = loadTexture("ressources/pacman/pakuman_0.bmp", ren);
    partie->nb_vies = 3;

    // Initialisation ghosts
    partie->ghosts = malloc(sizeof(Ghost) * 4);
    for (int i = 0; i < 4; i++) {
        partie->ghosts[i] = malloc(sizeof(Ghost));
        init_ghost(partie->ghosts[i], ren, i);
    }
    
    placament_pacman_et_ghost(ren, partie);
    boucle_de_jeu (ren, partie);
}

void placament_pacman_et_ghost (SDL_Renderer* ren, Partie* partie){
    premier_placement_pacman(partie->pacman, partie->map, 14, 23);
    
    partie->nb_ghosts = 0;
    for (int i = 0; i < 4; i++) {
        premier_placement_ghost(partie->ghosts[i], partie->map, 12 + i, 11);
        strcpy(partie->ghosts[i]->etat, "chase");
        changement_etat(partie->ghosts[i], partie->map);
        partie->nb_ghosts++;
    }
    /*
    printf("target Blinky : (x,y) : (%d,%d)\n", partie->ghosts[0]->target_x, partie->ghosts[0]->target_y);
    printf("target Pinky : (x,y) : (%d,%d)\n", partie->ghosts[1]->target_x, partie->ghosts[1]->target_y);
    printf("target Inky : (x,y) : (%d,%d)\n", partie->ghosts[2]->target_x, partie->ghosts[2]->target_y);
    printf("target Clyde : (x,y) : (%d,%d)\n", partie->ghosts[3]->target_x, partie->ghosts[3]->target_y);*/
    /*
    partie->nb_ghosts = 1;
    premier_placement_ghost(partie->ghosts[3], partie->map, 12, 11);
    strcpy(partie->ghosts[3]->etat, "chase");
    changement_etat(partie->ghosts[3], partie->map);*/
}

void boucle_de_jeu(SDL_Renderer* ren, Partie* partie){
    char dir;
    int running = 1;

    clock_t current_time;
    clock_t start_time = clock();
    const double temps_clignotement_bouton_start = 100.0 / 1000.0 * CLOCKS_PER_SEC; //temps_reaction_pacman convertion de milisecondes à clocks
    

    while (running){
        affiche_ecran_jeu(ren, partie);
        affiche_pacman(partie->pacman, ren);
        for (int i = 0; i < 4; i++) {
            affiche_ghost(partie->ghosts[i], ren);
        }
        updateDisplay(ren);

        current_time = clock();
        //if ((double)(current_time - start_time) >= temps_clignotement_bouton_start) {
        avance_pacman(partie->pacman, partie->map, &(partie->score));
        for (int i = 0; i < 4; i++) {
            avance_ghost(partie->ghosts[i], partie->map, partie->pacman, partie->ghosts[0]);
        }
        is_collision_pacman_ghost(ren, partie->ghosts, partie->pacman, partie, &running);
        //start_time = current_time;
        //}

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
    const double temps_clignotement_bouton_start = 125.0 / 1000.0 * CLOCKS_PER_SEC; //temps_clignotement_bouton_start convertion de milisecondes à clocks
    
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

