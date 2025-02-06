#include "menus.h"

SelectionType selection_en_cours = SELECTION_AUCUNE;

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
            nouvelle_partie(ren,musique,1);
            running = 0;
        }
        if (lancement == 'm'){
            playSoundEffect(musique->select);
            ecran_musique(ren, musique);
            running = 0;
        }
        if (lancement == 'n'){
            playSoundEffect(musique->select);
            ecran_niveaux(ren, musique);
            running = 0;
        }
    }
}

void ecran_musique (SDL_Renderer* ren, Musique* musique){
    Mix_HaltMusic();
    int button_height = 50;
    int button_margin_y = 20;
    int button_music_width = 200; 
    int button_select_width = 300; 

    // Boutons de musique
    MusicButton musicButtons[NB_MUSIQUES];
    for (int i = 0; i < NB_MUSIQUES; i++) {
        musicButtons[i].button_base.rect.x = (int)(FEN_X*3/4 - BUTTON_WIDTH/2);
        musicButtons[i].button_base.rect.y = HEADER_HEIGHT + 100 + i * (button_height + button_margin_y);
        musicButtons[i].button_base.rect.w = button_music_width;
        musicButtons[i].button_base.rect.h = button_height;
        musicButtons[i].button_base.hovered = 0;
        musicButtons[i].music = musique->musiques_src[i];
        musicButtons[i].label = malloc(20 * sizeof(char));  // Allouer de la mémoire
        if (musicButtons[i].label == NULL) {printf("Erreur d'allocation mémoire\n"); exit(1);}
        sprintf(musicButtons[i].label, "Musique %d", i + 1);
    }

    // Boutons de sélection de catégorie
    SelectionButton selectionButtons[NB_CATEGORIES];
    for (int i = 0; i < NB_CATEGORIES; i++) {
        selectionButtons[i].button_base.rect.x = (int)(FEN_X/4 - BUTTON_WIDTH/2);;
        selectionButtons[i].button_base.rect.y = HEADER_HEIGHT + 100 + i * (button_height + button_margin_y);
        selectionButtons[i].button_base.rect.w = button_select_width;
        selectionButtons[i].button_base.rect.h = button_height;
        selectionButtons[i].button_base.hovered = 0;
    }
    selectionButtons[0].type = SELECTION_ACCUEIL;
    selectionButtons[0].label = "Musique Accueil";
    selectionButtons[1].type = SELECTION_JEU;
    selectionButtons[1].label = "Musique Jeu";

    int running = 1;
    SDL_Event e;
    char touche_pressee;
    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Musiques et sons");
        draw_buttons(ren, musicButtons, selectionButtons);
        updateDisplay(ren);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                handle_events(&e, musicButtons, selectionButtons, musique);
            }
            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_BACKSPACE){
                    playSoundEffect(musique->select);
                    ecran_acceuil(ren,musique);
                    running = 0;
                }
            }
        }
    }
}

void ecran_niveaux (SDL_Renderer* ren, Musique* musique){
    Button_niveau buttons[LEVEL_COUNT];
    for (int i = 0; i < LEVEL_COUNT; i++) {
        buttons[i].button_base.rect.x = (FEN_X - BUTTON_WIDTH) / 2;
        buttons[i].button_base.rect.y = HEADER_HEIGHT + BUTTON_MARGIN + i * (BUTTON_HEIGHT + BUTTON_MARGIN);
        buttons[i].button_base.rect.w = BUTTON_WIDTH;
        buttons[i].button_base.rect.h = BUTTON_HEIGHT;
        buttons[i].level = i + 1;
        buttons[i].button_base.hovered = 0;
    }

    int scroll_offset = 0; // Décalage vertical du scrolling
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Niveaux");
        char text[10];
        for (int i = 0; i < LEVEL_COUNT; i++) {
            SDL_Rect original_rect = buttons[i].button_base.rect;
            buttons[i].button_base.rect.y -= scroll_offset; // Appliquer le scroll
            sprintf(text, "Level %d", buttons[i].level); // Affichage du numéro du niveau
            renderButton(ren, &(buttons[i].button_base), text, (SDL_Color){255, 255, 255, 255}, (SDL_Color){255, 0, 0, 255}, (SDL_Color){0, 0, 255, 255});
            buttons[i].button_base.rect = original_rect; // Rétablir la position originale
        }
        updateDisplay(ren);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_MOUSEMOTION) {
                int x = event.motion.x, y = event.motion.y;
                for (int i = 0; i < LEVEL_COUNT; i++) {
                    if (x >= buttons[i].button_base.rect.x && x <= buttons[i].button_base.rect.x + BUTTON_WIDTH &&
                        y >= buttons[i].button_base.rect.y - scroll_offset && y <= buttons[i].button_base.rect.y + BUTTON_HEIGHT - scroll_offset) {
                        buttons[i].button_base.hovered = 1;
                    } else {
                        buttons[i].button_base.hovered = 0;
                    }
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                int x = event.button.x, y = event.button.y;
                for (int i = 0; i < LEVEL_COUNT; i++) {
                    if (x >= buttons[i].button_base.rect.x && x <= buttons[i].button_base.rect.x + BUTTON_WIDTH &&
                        y >= buttons[i].button_base.rect.y - scroll_offset && y <= buttons[i].button_base.rect.y + BUTTON_HEIGHT - scroll_offset) {
                        playSoundEffect(musique->select);
                        nouvelle_partie(ren, musique, buttons[i].level);
                        running = 0;
                    }
                }
            }

            if (event.type == SDL_MOUSEWHEEL) {
                scroll_offset -= event.wheel.y * SCROLL_SPEED;
                
                // Empêcher le défilement infini
                if (scroll_offset < SCROLL_OFFSET_MIN) scroll_offset = SCROLL_OFFSET_MIN;
                if (scroll_offset > (LEVEL_COUNT * (BUTTON_HEIGHT + BUTTON_MARGIN)) - (FEN_Y/2 - HEADER_HEIGHT)) {
                    scroll_offset = (LEVEL_COUNT * (BUTTON_HEIGHT + BUTTON_MARGIN)) - (FEN_Y/2 - HEADER_HEIGHT);
                }
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_DOWN) scroll_offset += (BUTTON_HEIGHT + BUTTON_MARGIN);
                if (event.key.keysym.sym == SDLK_UP) scroll_offset -= (BUTTON_HEIGHT + BUTTON_MARGIN);

                // Vérifier les limites
                if (scroll_offset < 0) scroll_offset = 0;
                if (scroll_offset > (LEVEL_COUNT * (BUTTON_HEIGHT + BUTTON_MARGIN)) - (FEN_Y/2 - HEADER_HEIGHT))
                    scroll_offset = (LEVEL_COUNT * (BUTTON_HEIGHT + BUTTON_MARGIN)) - (FEN_Y/2 - HEADER_HEIGHT);
            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_BACKSPACE){
                    playSoundEffect(musique->select);
                    ecran_acceuil(ren,musique);
                    running = 0;
                }
            }
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

void renderButton(SDL_Renderer *renderer, Button *button, const char* texte, SDL_Color color_text, SDL_Color color1, SDL_Color color2) {
    if (button->rect.y > HEADER_HEIGHT + BUTTON_MARGIN/2 && button->rect.y + button->rect.h/2 < FEN_Y) {
        TTF_Font * font = createFont("ressources/DejaVuSans-Bold.ttf", 25);
        SDL_Color color = button->hovered ? color1 : color2;
        int tmp_width;
        int tmp_height;
        int tmp_x;
        int tmp_y;
        if (button->hovered) {
            int taille_bonus_x = 10;
            int taille_bonus_y = 10;
            tmp_width = button->rect.w + taille_bonus_x;
            tmp_height = button->rect.h + taille_bonus_y;
            tmp_x = button->rect.x - taille_bonus_x/2;
            tmp_y = button->rect.y - taille_bonus_y/2;
        } else {
            tmp_width = button->rect.w;
            tmp_height = button->rect.h;
            tmp_x = button->rect.x;
            tmp_y = button->rect.y;
        }

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderFillRect(renderer, &button->rect);

        SDL_Surface *surface = TTF_RenderText_Solid(font, texte, color_text);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {tmp_x + tmp_width/2 - surface->w/2, tmp_y + tmp_height/2 - surface->h/2, surface->w, surface->h};

        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void renderHeader(SDL_Renderer *renderer, char *titre) {
    TTF_Font * font = createFont("ressources/DejaVuSans-Bold.ttf", 35);
    // Fond de l'en-tête
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_Rect header = {0, 0, FEN_X, HEADER_HEIGHT};
    SDL_RenderFillRect(renderer, &header);

    // Texte "Sélection du niveau"
    SDL_Surface *surface = TTF_RenderText_Solid(font, titre, (SDL_Color){255, 255, 255, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = {FEN_X / 2 - surface->w / 2, HEADER_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};
    
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void handle_events(SDL_Event* e, MusicButton musics[], SelectionButton selections[], Musique* musique) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Vérifier si un bouton de sélection de catégorie est cliqué
    for (int i = 0; i < NB_CATEGORIES; i++) {
        if (x >= selections[i].button_base.rect.x && x <= selections[i].button_base.rect.x + selections[i].button_base.rect.w &&
            y >= selections[i].button_base.rect.y && y <= selections[i].button_base.rect.y + selections[i].button_base.rect.h) {
            
            selection_en_cours = selections[i].type;
            return;
        }
    }

    // Vérifier si un bouton de musique est cliqué après avoir sélectionné une catégorie
    if (selection_en_cours != SELECTION_AUCUNE) {
        for (int i = 0; i < NB_MUSIQUES; i++) {
            if (x >= musics[i].button_base.rect.x && x <= musics[i].button_base.rect.x + musics[i].button_base.rect.w &&
                y >= musics[i].button_base.rect.y && y <= musics[i].button_base.rect.y + musics[i].button_base.rect.h) {
                
                Mix_HaltMusic();
                Mix_PlayMusic(musics[i].music, -1);

                // Associer la musique à la catégorie choisie
                switch (selection_en_cours) {
                    case SELECTION_ACCUEIL:
                        musique->musique_accueil = musics[i].music;
                        break;
                    case SELECTION_JEU:
                        musique->musique_jeu = musics[i].music;
                        break;
                    case SELECTION_SUPER_MODE:
                        musique->musique_super_mode = musics[i].music;
                        break;
                    default:
                        break;
                }
                //selection_en_cours = SELECTION_AUCUNE;  // Réinitialiser la sélection
                return;
            }
        }
    }
}

void draw_buttons(SDL_Renderer* renderer, MusicButton musics[], SelectionButton selections[]) {
    SDL_Color color_texte = {255, 255, 255, 255};
    SDL_Color color_base_musics = {0, 0, 255, 255};
    SDL_Color color_touch_musics = {255, 0, 0, 255};
    SDL_Color color_base_select = {100, 100, 255, 255};
    SDL_Color color_touch_select = {200, 100, 255, 255};

    // Dessiner les boutons de musique
    for (int i = 0; i < NB_MUSIQUES; i++) {
        renderButton(renderer, &(musics[i].button_base), musics[i].label, color_texte, color_touch_musics, color_base_musics);
    }

    // Dessiner les boutons de sélection de catégorie
    for (int i = 0; i < NB_CATEGORIES; i++) {
        if (selection_en_cours == selections[i].type) {
            selections[i].button_base.hovered = 1;
        } else {
            selections[i].button_base.hovered = 0;
        }
        renderButton(renderer, &(selections[i].button_base), selections[i].label, color_texte, color_touch_select, color_base_select);
    }
}

