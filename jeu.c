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
            if (strcmp(ghosts[i]->etat,"frightened") == 0){
                strcpy(ghosts[i]->etat,"eaten");
                partie->score += 200;
            } else { if (strcmp(ghosts[i]->etat,"eaten") != 0){
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
            }}
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
    char text_score[100];
    SDL_Color white = {255, 255, 255, 255};
    sprintf(text_score, "Score : %d",partie->score);
    printText(MARGE_BANDEAU_HAUT, MARGE_BANDEAU_HAUT, text_score, MARGE_BANDEAU_HAUT + 500, TAILLE_BANDEAU_HAUT - 2*MARGE_BANDEAU_HAUT, partie->font[0], white, ren);
    
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
        partie->nb_ghosts++;
    }
}

void boucle_de_jeu(SDL_Renderer* ren, Partie* partie){
    char dir;
    int running = 1;
    int is_mode_frightened = 0; // Booleen pour savoir si le mode frightened est actif
    time_t start_time_frightened = time(NULL);

    int duree_mode_scatter[] = {7,7,5,5};
    int duree_mode_chase[] = {20,20,20};
    int num_mode_max = sizeof(duree_mode_scatter) / sizeof(duree_mode_scatter[0]);
    int num_mode = 0; // Le n ème duo de modes scatter et chase
    char mode[8] = "scatter";
    int temps_mode = duree_mode_scatter[num_mode];
    for (int i = 0; i < partie->nb_ghosts; i++){
        strcpy(partie->ghosts[i]->etat, "scatter");
        changement_etat(partie->ghosts[i], partie->map);
    }
    //printf("Passage au mode %s / n: %d\n",mode, num_mode);
    //clock_t start_time = clock();    
    time_t start_time = time(NULL);

    while (running){
        // Affichage
        affiche_ecran_jeu(ren, partie);
        affiche_pacman(partie->pacman, ren);
        for (int i = 0; i < 4; i++) {
            affiche_ghost(partie->ghosts[i], ren);
        }
        updateDisplay(ren);

        // Gestion des personnages (pacman et ghosts)
        avance_pacman(partie->pacman, partie->map);
        if (update_score(partie->pacman, partie->map, &(partie->score), partie->nb_ghosts, partie->ghosts) == 1){
            is_mode_frightened = 1;
            time_t start_time_frightened = time(NULL);
        }
        for (int i = 0; i < 4; i++) {
            avance_ghost(partie->ghosts[i], partie->map, partie->pacman, partie->ghosts[0]);
        }
        is_collision_pacman_ghost(ren, partie->ghosts, partie->pacman, partie, &running);

        // Gestion des mode/etat des fantômes (chase, scatter, frightened et eaten)
        time_t current_time = time(NULL);
        if (num_mode < num_mode_max && current_time - start_time >= temps_mode){ // Si contition rempli : il est temps de changer de mode !
            if (strcmp(mode,"scatter") == 0){
                strcpy(mode, "chase"); // Nouveau mode
                if (num_mode == num_mode_max-1){
                    num_mode++;
                } else {
                    temps_mode = duree_mode_chase[num_mode];
                }
                for (int i = 0; i < partie->nb_ghosts; i++){
                    if (strcmp(partie->ghosts[i]->etat, "scatter") == 0){ // Le ghost change de mode en forçant seulement si il est à l'état scatter, sinom il le fera tout seul quand son autre état se désactivera. 
                        strcpy(partie->ghosts[i]->etat, "chase");
                    }
                }
            } else {
            if (strcmp(mode,"chase") == 0){
                strcpy(mode, "scatter"); // Nouveau mode
                temps_mode = duree_mode_chase[++num_mode];
                for (int i = 0; i < partie->nb_ghosts; i++){
                    if (strcmp(partie->ghosts[i]->etat, "chase") == 0){ // Le ghost change de mode en forçant seulement si il est à l'état chase, sinom il le fera tout seul quand son autre état se désactivera. 
                        strcpy(partie->ghosts[i]->etat, "scatter");
                    }
                }
            }
            }
            start_time = current_time;
            printf("Passage au mode %s / n: %d\n",mode, num_mode);
        }
        if (is_mode_frightened == 1 && current_time - start_time >= TEMPS_MODE_FRIGHTENED){
            // Fin du mode frightened
            for (int i = 0; i < partie->nb_ghosts; i++){
                if (strcmp(partie->ghosts[i]->etat, "frightened") == 0){
                    strcpy(partie->ghosts[i]->etat, mode);
                }
            }
        }

        // Gestion des événements
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

int update_score (Pacman *pacman, Map *map, int *score, int nb_ghosts, Ghost** ghosts){
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
        // Ici démarer le mode <frightened>
        printf("Début mode frightened\n");
        for (int i = 0; i < nb_ghosts; i++){
            strcpy(ghosts[i]->etat, "frightened");
        }
        return 1;
    }
    }}
    return 0;
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

