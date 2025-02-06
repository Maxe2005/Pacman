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

int is_collision_pacman_ghost (SDL_Renderer* ren, Ghost* ghost, Pacman *pacman, Partie* partie, int* running, Musique* musique) {
    if (abs(ghost->position_px_x - pacman->position_px_x) < ghost->taille_px/2 && abs(ghost->position_px_x - pacman->position_px_x) < pacman->taille_px/2
            && abs(ghost->position_px_y - pacman->position_px_y) < ghost->taille_px/2 && abs(ghost->position_px_y - pacman->position_px_y) < pacman->taille_px/2) {
        if (ghost->etat == ETAT_FRIGHTENED){
            playSoundEffect(musique->eat_ghost);
            ghost->etat = ETAT_EATEN;
            partie->score += 200;
        } else { if (ghost->etat != ETAT_EATEN){
            partie->nb_vies--;
            *running = 0;
            if (partie->nb_vies == 0) {
                ecran_game_over(ren, partie, musique);
            } else {
                annimation_mort_pacman(ren, partie, musique);
                placament_pacman_et_ghost(partie);
                debut_jeu(ren, partie, musique);
            }
        }}
        return 1;
    }
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

void annimation_mort_pacman (SDL_Renderer* ren, Partie* partie, Musique* musique) {
    playSoundEffect(musique->pacman_death);
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

void nouvelle_partie (SDL_Renderer* ren, Musique* musique) {
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
    
    placament_pacman_et_ghost(partie);
    partie->nb_gums = compte_nb_gum(partie->map);
    debut_jeu (ren, partie, musique);
}

void placament_pacman_et_ghost (Partie* partie){
    premier_placement_pacman(partie->pacman, partie->map, 14, 23);
    
    int positions_ghost_depart[4][2] = {{13, 11}, {13, 14}, {11, 13}, {15, 13}};
    partie->nb_ghosts = 0;
    for (int i = 0; i < 4; i++) {
        premier_placement_ghost(partie->ghosts[i], partie->map, positions_ghost_depart[i][0], positions_ghost_depart[i][1]);
    }
}

void debut_jeu (SDL_Renderer* ren, Partie* partie, Musique* musique){
    stopMusic();
    playSoundEffect(musique->pacman_song);
    SDL_Color yellow = {255, 255, 0, 255};
    time_t start_time_song = time(NULL);
    int is_musique_commencee = 0;
    int temps_avant_debut_musique = 5;

    int nb_cases_ready = 7;
    int ready_x = ORIGINE_X + (13 - (nb_cases_ready - 2)/2) * partie->map->taille_case;
    int ready_y = ORIGINE_Y + (11 + 6) * partie->map->taille_case - (int)((partie->map->taille_perso - partie->map->taille_case)/2);
    int taille_ready_x = nb_cases_ready * partie->map->taille_case;
    int taille_ready_y = partie->map->taille_perso;

    for (int i = 0; i < 4; i++){
        partie->ghosts[i]->etat_prioritaire = ETAT_INSIDE_HOME;
        partie->ghosts[i]->etat = ETAT_INSIDE_HOME;
    }

    char dir;
    int running = 1;

    time_t current_time;
    while (running) {
        current_time = time(NULL);

        affiche_ecran_jeu(ren, partie);
        affiche_pacman(partie->pacman, ren);
        for (int i = 0; i < 4; i++) {
            affiche_ghost(partie->ghosts[i], ren);
        }
        printText(ready_x, ready_y, "READY!", taille_ready_x, taille_ready_y, partie->font[0], yellow, ren);
        updateDisplay(ren);

        if (is_musique_commencee == 0 && current_time - start_time_song >= temps_avant_debut_musique) {
            playMusic(musique->musique_jeu);
            is_musique_commencee = 1;
        }

        // Gestion des événements
        dir = processKeyboard(&running);
        if (dir == 'd' || dir == 'g' || dir == 'h' || dir == 'b'){
            partie->pacman->next_direction = dir;
            if (!Mix_PlayingMusic()){
                playMusic(musique->musique_jeu);
            }
            boucle_de_jeu(ren, partie, musique);
            running = 0;
        }
        if (dir == 'M'){
            free_partie(partie);
            ecran_acceuil (ren,musique); // retour à l'écran d'acceuil
            running = 0;
        }
    }
}

void boucle_de_jeu(SDL_Renderer* ren, Partie* partie, Musique* musique){
    char dir;
    int running = 1;
    int is_mode_frightened = 0; // Booleen pour savoir si le mode frightened est actif
    time_t start_time_frightened = time(NULL);

    int duree_mode_scatter[] = {7,7,5,5};
    int duree_mode_chase[] = {20,20,20};
    int num_mode_max = sizeof(duree_mode_scatter) / sizeof(duree_mode_scatter[0]);
    int num_mode = 0; // Le n ème duo de modes scatter et chase
    int mode = ETAT_SCATTER;
    int temps_mode = duree_mode_scatter[num_mode];

    // Blinky est déjà en dehors de la base des fantômes au début contrairement aux autres
    partie->ghosts[0]->etat = mode;
    partie->ghosts[0]->etat_prioritaire = mode;
    changement_etat(partie->ghosts[0], partie->map);
    partie->nb_ghosts = 1;
    master_choix_directions(partie->ghosts[0], partie->map, partie->pacman, partie->ghosts[0]);

    time_t start_time_sortie_ghosts = time(NULL);
    time_t start_time_switch_modes = time(NULL);
    time_t current_time = time(NULL);
    while (running){
        current_time = time(NULL);
        // Affichage
        affiche_ecran_jeu(ren, partie);
        affiche_pacman(partie->pacman, ren);
        for (int i = 0; i < 4; i++) {
            affiche_ghost(partie->ghosts[i], ren);
        }
        updateDisplay(ren);

        // Gestion des personnages (pacman et ghosts)
        avance_pacman(partie->pacman, partie->map);
        if (update_score(partie) == 1){
            // Début du mode frightened
            pauseMusic();
            playMusic(musique->musique_super_mode);
            is_mode_frightened = 1;
            for (int i = 0; i < 4; i++){
                partie->ghosts[i]->etat = ETAT_FRIGHTENED;
                partie->ghosts[i]->is_clignotement = 0;
            }
            start_time_frightened = time(NULL);
        }
        for (int i = 0; i < 4; i++) {
            if (partie->ghosts[i]->etat_prioritaire == ETAT_INSIDE_HOME){
                if (current_time - start_time_sortie_ghosts > partie->ghosts[i]->temps_avant_sortie_maison){
                    partie->ghosts[i]->etat_prioritaire = ETAT_GO_OUTSIDE_HOME;
                } else {
                    bouger_dans_maison(partie->ghosts[i], partie->map);
                }
            } else {
            if (partie->ghosts[i]->etat_prioritaire == ETAT_GO_OUTSIDE_HOME){
                if (go_outside_home(partie->ghosts[i], partie->map, 13, 11) == 0){ // TODO : target doit dépendre de la map !
                    // Le fantôme est maintenant sur le maze
                    if (partie->ghosts[i]->etat != ETAT_FRIGHTENED){
                        partie->ghosts[i]->etat = mode;
                    }
                    partie->ghosts[i]->etat_prioritaire = mode;
                    partie->ghosts[i]->position_x = 13;
                    partie->ghosts[i]->position_y = 11;
                    changement_etat(partie->ghosts[i], partie->map);
                    partie->nb_ghosts++;
                    master_choix_directions(partie->ghosts[i], partie->map, partie->pacman, partie->ghosts[0]);
                } 
            } else {
                avance_ghost(partie->ghosts[i], partie->map, partie->pacman, partie->ghosts[0]);
                is_collision_pacman_ghost(ren, partie->ghosts[i], partie->pacman, partie, &running, musique);
            }
            }
        }

        // Gagné ?
        if (partie->nb_gums <= 0){
            running = 0;
            ecran_victoire(ren, partie, musique);
        }

        // Gestion des mode/etat des fantômes (chase, scatter, frightened et eaten)
        if (num_mode < num_mode_max && current_time - start_time_switch_modes >= temps_mode){ // Si contition rempli : il est temps de changer de mode !
            if (mode == ETAT_SCATTER){
                mode = ETAT_CHASE; // Nouveau mode
                if (num_mode == num_mode_max-1){
                    num_mode++;
                } else {
                    temps_mode = duree_mode_chase[num_mode];
                }
                for (int i = 0; i < partie->nb_ghosts; i++){
                    if (partie->ghosts[i]->etat == ETAT_SCATTER){ // Le ghost change de mode en forçant seulement si il est à l'état scatter, sinom il le fera tout seul quand son autre état se désactivera. 
                        partie->ghosts[i]->etat = ETAT_CHASE;
                    }
                }
            } else {
            if (mode == ETAT_CHASE){
                mode = ETAT_SCATTER; // Nouveau mode
                temps_mode = duree_mode_chase[++num_mode];
                for (int i = 0; i < partie->nb_ghosts; i++){
                    if (partie->ghosts[i]->etat == ETAT_CHASE){ // Le ghost change de mode en forçant seulement si il est à l'état chase, sinom il le fera tout seul quand son autre état se désactivera. 
                        partie->ghosts[i]->etat = ETAT_SCATTER;
                    }
                }
            }
            }
            start_time_switch_modes = current_time;
        }
        if (is_mode_frightened == 1){
            if (current_time - start_time_frightened > TEMPS_MODE_FRIGHTENED){
                // Fin du mode frightened
                playMusic(musique->musique_jeu);
                is_mode_frightened = 0;
                for (int i = 0; i < partie->nb_ghosts; i++){
                    if (partie->ghosts[i]->etat == ETAT_FRIGHTENED){
                        partie->ghosts[i]->etat = mode;
                        partie->ghosts[i]->is_clignotement = 0;
                    }
                }
            } else {
            if (current_time - start_time_frightened >= TEMPS_MODE_FRIGHTENED - TEMPS_MODE_FRIGHTENED * POURCENTAGE_FIN_FRIGHTENED/100){
                // Clignotemment d'avertissement de fin de mode frightened
                for (int i = 0; i < partie->nb_ghosts; i++){
                    if (partie->ghosts[i]->etat == ETAT_FRIGHTENED){
                        partie->ghosts[i]->is_clignotement = 1;
                    }
                }
            }
            }
        }
        for (int i = 0; i < partie->nb_ghosts; i++){
            if (partie->ghosts[i]->etat == ETAT_EATEN && partie->ghosts[i]->position_x == partie->ghosts[i]->target_x && partie->ghosts[i]->position_y == partie->ghosts[i]->target_y){
                partie->ghosts[i]->etat = mode;
            }
        }

        // Gestion des événements
        dir = processKeyboard(&running);
        if (dir == 'd' || dir == 'g' || dir == 'h' || dir == 'b'){
            partie->pacman->next_direction = dir;
        }
        if (dir == 'M'){
            free_partie(partie);
            ecran_acceuil (ren,musique); // retour à l'écran d'acceuil
            running = 0;
        }
    }
}

int update_score (Partie* partie){
    if (partie->map->contenu[partie->pacman->position_y][partie->pacman->position_x] == 4){
        partie->score += 10;
        partie->nb_gums--;
        partie->map->contenu[partie->pacman->position_y][partie->pacman->position_x] = 0; //Vider la case car le <Gum> à été consommé
    } else {
    if (partie->map->contenu[partie->pacman->position_y][partie->pacman->position_x] == 6){
        partie->score += 100;
        partie->map->contenu[partie->pacman->position_y][partie->pacman->position_x] = 0; //Vider la case car le <Cherry> à été consommé
    } else {
    if (partie->map->contenu[partie->pacman->position_y][partie->pacman->position_x] == 5){ // <Big_Gum> consommé
        partie->map->contenu[partie->pacman->position_y][partie->pacman->position_x] = 0;
        // Ici démare le mode <frightened>
        return 1;
    }}}
    return 0;
}

void affiche_logo (SDL_Renderer* ren, SDL_Texture* logo) {
    renderTexture(logo, ren,(int)(FEN_X /4),(int)(FEN_Y/8),(int)(FEN_X/2),(int)(FEN_Y/4));
}

void ecran_acceuil (SDL_Renderer* ren, Musique* musique){
    playMusic(musique->musique_accueil);

    SDL_Texture* logo = loadTexture("ressources/pac-man-logo.bmp", ren);
    TTF_Font * font = createFont("ressources/DejaVuSans-Bold.ttf", 20);

    clock_t current_time;
    clock_t start_time = clock();
    const double temps_clignotement_bouton_start = 125.0 / 1000.0 * CLOCKS_PER_SEC; //temps_clignotement_bouton_start convertion de milisecondes à clocks
    
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    affiche_logo(ren, logo);
    affiche_bouton_start(ren, font);

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
                affiche_bouton_start(ren, font);
                is_bouton_start_visible = 1;
            }
            start_time = current_time;
        }
        
        lancement = processKeyboard(&running);
        if (lancement == 'L'){
            playSoundEffect(musique->select);
            nouvelle_partie(ren,musique);
            running = 0;
        }
        if (lancement == 'm'){
            playSoundEffect(musique->select);
            ecran_musique(ren, musique);
            running = 0;
        }
    }
}

void ecran_game_over (SDL_Renderer* ren, Partie* partie, Musique* musique){
    stopMusic();
    playSoundEffect(musique->game_over);
    time_t start_time_song = time(NULL);
    int is_musique_commencee = 0;
    int temps_avant_debut_musique = 7;

    
    clock_t start_time = clock();
    const double temps_clignotement_bouton_start = 125.0 / 1000.0 * CLOCKS_PER_SEC; //temps_clignotement_bouton_start convertion de milisecondes à clocks
    
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    affiche_titre_et_score(ren, partie, "Game Over", "red");

    char lancement;
    int is_bouton_start_visible = 1; // Booleen qui permet de faire clignoter le bouton start
    int running = 1;

    clock_t current_time;
    time_t current_time_bis;
    while (running) {
        current_time = clock();
        current_time_bis = time(NULL);
        updateDisplay(ren);

        if ((double)(current_time - start_time) >= temps_clignotement_bouton_start) {
            if (is_bouton_start_visible == 1){
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                SDL_RenderClear(ren);
                affiche_titre_et_score(ren, partie, "Game Over", "red");
                is_bouton_start_visible = 0;
            } else {
                affiche_bouton_start(ren, partie->font[0]);
                is_bouton_start_visible = 1;
            }
            start_time = current_time;
        }

        if (is_musique_commencee == 0 && current_time_bis - start_time_song >= temps_avant_debut_musique) {
            playMusic(musique->musique_accueil);
            is_musique_commencee = 1;
        }
        
        lancement = processKeyboard(&running);
        if (lancement == 'L'){
            playSoundEffect(musique->select);
            ecran_acceuil(ren, musique);
            running = 0;
        }
    }
}

void ecran_victoire (SDL_Renderer* ren, Partie* partie, Musique* musique){
    playMusic(musique->musique_accueil);
    clock_t current_time;
    clock_t start_time = clock();
    const double temps_clignotement_bouton_start = 125.0 / 1000.0 * CLOCKS_PER_SEC; //temps_clignotement_bouton_start convertion de milisecondes à clocks
    
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    affiche_titre_et_score(ren, partie, "You Win", "green");

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
                affiche_titre_et_score(ren, partie, "You Win", "green");
                is_bouton_start_visible = 0;
            } else {
                affiche_bouton_start(ren, partie->font[0]);
                is_bouton_start_visible = 1;
            }
            start_time = current_time;
        }
        
        lancement = processKeyboard(&running);
        if (lancement == 'L'){
            playSoundEffect(musique->select);
            ecran_acceuil(ren, musique);
            running = 0;
        }
    }
}

void ecran_musique (SDL_Renderer* ren, Musique* musique){
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    updateDisplay(ren);

    int running = 1;
    char touche_pressee;
    while (running) {
        touche_pressee = processKeyboard(&running);
        if (touche_pressee == 'L' || touche_pressee == 'M'){
            playSoundEffect(musique->select);
            ecran_acceuil(ren,musique);
            running = 0;
        }
        if (touche_pressee == '1'){
            musique->musique_accueil = musique->musiques_src[0];
        }
        if (touche_pressee == '2'){
            musique->musique_accueil = musique->musiques_src[1];
        }
        if (touche_pressee == '3'){
            musique->musique_accueil = musique->musiques_src[2];
        }
        if (touche_pressee == '4'){
            musique->musique_jeu = musique->musiques_src[0];
        }
        if (touche_pressee == '5'){
            musique->musique_jeu = musique->musiques_src[1];
        }
        if (touche_pressee == '6'){
            musique->musique_jeu = musique->musiques_src[2];
        }

    }
}

void affiche_bouton_start(SDL_Renderer* ren, TTF_Font * font){
    int division_x_titre = 4; // doit être >= 3
    int division_y_titre = 6; // doit être >= 3
    int titre_x = (int)(FEN_X/division_x_titre);
    int titre_y = (int)(FEN_Y/division_y_titre*4);
    int taille_titre_x = (int)(FEN_X/division_x_titre * (division_x_titre-2));
    int taille_titre_y = taille_titre_x/4 ;

    SDL_Color red = {255, 0, 0, 255};
    printText(titre_x, titre_y, "PRESS SPACE", taille_titre_x, taille_titre_y, font, red, ren);
}

void affiche_titre_et_score (SDL_Renderer* ren, Partie* partie, char *titre, char *color) {
    int division_x_titre = 5; // doit être >= 3
    int division_y_titre = 6; // doit être >= 3
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
    SDL_Color couleur = {255, 255, 255, 255};;
    if (strcmp(color, "red") == 0){
        couleur.r = 255;
        couleur.g = 0;
        couleur.b = 0;
    } else {
    if (strcmp(color, "green") == 0){
        couleur.r = 0;
        couleur.g = 255;
        couleur.b = 0;
    }
    }

    printText(titre_x, titre_y, titre, taille_titre_x, taille_titre_y, partie->font[0], couleur, ren);
    sprintf(text_score, "Score : %d",partie->score);
    printText(score_x, score_y, text_score, taille_score_x, taille_score_y, partie->font[0], white, ren);
}


