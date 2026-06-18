#include "menus.h"

SelectionType selection_en_cours = SELECTION_AUCUNE;

void ecran_acceuil (SDL_Renderer* ren, Musique* musique){
    playMusic(musique->musique_accueil);

    SDL_Texture* logo = loadTexture("ressources/pac-man-logo.bmp", ren);
    TTF_Font * font = createFont("ressources/DejaVuSans-Bold.ttf", 20);

    clock_t current_time;
    clock_t start_time = clock();
    const double temps_clignotement_bouton_start = 125.0 / 1000.0 * CLOCKS_PER_SEC; //temps_clignotement_bouton_start convertion de milisecondes à clocks

    // Initialisation des boutons
    Button button_musique, button_niveaux, button_remerciements, button_createur_map;
    Button* buttons[NB_BOUTONS_ACCUEIL];
    init_buttons_accueil(buttons, &button_musique, &button_niveaux, &button_remerciements, &button_createur_map);

    int is_bouton_start_visible = 1; // Booleen qui permet de faire clignoter le bouton start
    int running = 1;

    while (running) {
        current_time = clock();
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        affiche_logo(ren, logo);
        affiche_boutons_accueil(ren, buttons, 4);
        if (is_bouton_start_visible) {
            affiche_bouton_start(ren, font);
        }
        updateDisplay(ren);

        if ((double)(current_time - start_time) >= temps_clignotement_bouton_start) {
            is_bouton_start_visible = !is_bouton_start_visible;
            start_time = current_time;
        }

        handle_events_accueil(buttons, musique, ren, &running);
    }
}

void init_buttons_accueil(Button* buttons[], Button* button_musique, Button* button_niveaux, Button* button_remerciements, Button* button_createur_map) {
    int button_height = 50;
    int button_width = 300;
    int button_margin_x = 20;
    
    Button* but[] = {button_musique, button_niveaux, button_remerciements, button_createur_map};
    char* noms[] = {"Musique", "Niveaux", "Remerciements", "Createur de Map"};
    int origine_x = FEN_X/2 - (NB_BOUTONS_ACCUEIL * button_width + (NB_BOUTONS_ACCUEIL - 1) * button_margin_x)/2;
    for (int j = 0; j < NB_BOUTONS_ACCUEIL; j++){
        but[j]->rect.x = origine_x + j * (button_width + button_margin_x);
        but[j]->rect.y = (FEN_Y - button_height)/2;
        but[j]->rect.w = button_width;
        but[j]->rect.h = button_height;
        but[j]->hovered = 0;
        but[j]->label = noms[j];
        buttons[j] = but[j];
    }
}

void ecran_musique (SDL_Renderer* ren, Musique* musique){
    Mix_HaltMusic();
    int button_height = 50;
    int button_margin_y = 20;
    int button_music_width = 200; 
    int button_select_width = 300; 

    // Boutons de musique
    char text[NB_MUSIQUES][20];
    MusicButton musicButtons[NB_MUSIQUES];
    for (int i = 0; i < NB_MUSIQUES; i++) {
        musicButtons[i].button_base.rect.x = (int)(FEN_X*3/4 - BUTTON_WIDTH/2);
        musicButtons[i].button_base.rect.y = HEADER_HEIGHT + 100 + i * (button_height + button_margin_y);
        musicButtons[i].button_base.rect.w = button_music_width;
        musicButtons[i].button_base.rect.h = button_height;
        musicButtons[i].button_base.hovered = 0;
        musicButtons[i].music = musique->musiques_src[i];
        snprintf(text[i], sizeof(text), "Musique %d", i + 1);
        musicButtons[i].button_base.label = text[i];
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
    selectionButtons[0].button_base.label = "Musique Accueil";
    selectionButtons[1].type = SELECTION_JEU;
    selectionButtons[1].button_base.label = "Musique Jeu";

    int running = 1;
    SDL_Event e;
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
                handle_events(musicButtons, selectionButtons, musique);
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
    char text[LEVEL_COUNT][10];
    Button_niveau buttons[LEVEL_COUNT];
    for (int i = 0; i < LEVEL_COUNT; i++) {
        buttons[i].button_base.rect.x = (FEN_X - BUTTON_WIDTH) / 2;
        buttons[i].button_base.rect.y = HEADER_HEIGHT + BUTTON_MARGIN + i * (BUTTON_HEIGHT + BUTTON_MARGIN);
        buttons[i].button_base.rect.w = BUTTON_WIDTH;
        buttons[i].button_base.rect.h = BUTTON_HEIGHT;
        buttons[i].level = i + 1;
        buttons[i].button_base.hovered = 0;
        snprintf(text[i], sizeof(text), "Level %d", buttons[i].level);
        buttons[i].button_base.label = text[i];
    }

    int scroll_offset = 0; // Décalage vertical du scrolling
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Niveaux");
        for (int i = 0; i < LEVEL_COUNT; i++) {
            SDL_Rect original_rect = buttons[i].button_base.rect;
            buttons[i].button_base.rect.y -= scroll_offset; // Appliquer le scroll
            renderButton(ren, &(buttons[i].button_base), (SDL_Color){255, 255, 255, 255}, (SDL_Color){0, 0, 255, 255}, (SDL_Color){255, 0, 0, 255});
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

void ecran_remerciements (SDL_Renderer* ren, Musique* musique){
    // Texte des remerciements
    int space_entre_lignes = 20;
    int taille_ligne_y = 30;
    int margin_x = 10;
    const char* creditsText[] = {"Merci à tous ceux qui ont contribué ...",
                                " ",
                                " ",
                                "Initiative du projet : M. José Mennesson",
                                " ",
                                " ",
                                "Développeurs :",
                                " ",
                                "Maxence CHOISEL",
                                "Arthur COPIN",
                                "Mohammed DAIB",
                                " ",
                                " ",
                                "Chef de projet : Maxence CHOISEL",
                                " ",
                                "Game Design : d'après le jeu original Pac-Man",
                                " ",
                                "Développeur moteur du jeu : Maxence CHOISEL",
                                " ",
                                "Développeur IA des fantômes : Maxence CHOISEL",
                                " ",
                                "Développeur interface utilisateur  : Arthur COPIN",
                                " ",
                                "Développeur gestion du son  : Arthur COPIN",
                                " ",
                                "Développeur système d’animation  : Mohammed DAIB",
                                " ",
                                "Développeur physique du jeu : Maxence CHOISEL",
                                " ",
                                "Développeur des cartes (level design) : ","Maxence CHOISEL",
                                " ",
                                " ",
                                "Designer graphique  : Mohammed DAIB",
                                " ",
                                "Animateur 2D  : Mohammed DAIB",
                                " ",
                                "Créateur d’effets visuels (VFX)  : Mohammed DAIB",
                                " ",
                                " ",
                                "Testeur Quality Assurance : Maxence CHOISEL",
                                " ",
                                "Développeur optimisation des performances :","Maxence CHOISEL",
                                " ",
                                "..."};

    int nb_lignes = sizeof(creditsText)/sizeof(const char*);
    Button lignes[nb_lignes];
    for (int i = 0; i < nb_lignes; i++) {
        lignes[i].rect.x = margin_x;
        lignes[i].rect.y = HEADER_HEIGHT + 40 + space_entre_lignes + i * (taille_ligne_y + space_entre_lignes);
        lignes[i].rect.w = FEN_X - 2*margin_x;
        lignes[i].rect.h = taille_ligne_y;
        lignes[i].label = creditsText[i];
        lignes[i].hovered = 0;
    }
    // TTF_Font * font = createFont("ressources/Chewy-Regular.ttf", 30);

    int scroll_offset = 0; // Décalage vertical du scrolling
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Remerciements");
        // Affichage du texte en tenant compte du scrolling
        for (int i = 0; i < nb_lignes; i++) {
            SDL_Rect original_rect = lignes[i].rect;
            lignes[i].rect.y -= scroll_offset; // Appliquer le scroll
            renderButton(ren, &(lignes[i]), (SDL_Color){255, 255, 255, 255}, (SDL_Color){0, 0, 0, 255}, (SDL_Color){0, 0, 0, 255});
            lignes[i].rect = original_rect; // Rétablir la position originale
        }
        updateDisplay(ren);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_MOUSEWHEEL) {
                scroll_offset -= event.wheel.y * SCROLL_SPEED;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_DOWN) scroll_offset += SCROLL_SPEED;
                if (event.key.keysym.sym == SDLK_UP) scroll_offset -= SCROLL_SPEED;
            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_BACKSPACE){
                    playSoundEffect(musique->select);
                    ecran_acceuil(ren,musique);
                    running = 0;
                }
            }
        if (scroll_offset < 0) scroll_offset = 0;
        if (scroll_offset > (nb_lignes * (taille_ligne_y + space_entre_lignes)) - (FEN_Y/2 - HEADER_HEIGHT))
            scroll_offset = (nb_lignes * (taille_ligne_y + space_entre_lignes)) - (FEN_Y/2 - HEADER_HEIGHT);
        }
    }
}

void affiche_logo (SDL_Renderer* ren, SDL_Texture* logo) {
    renderTexture(logo, ren,(int)(FEN_X /4),(int)(FEN_Y/8),(int)(FEN_X/2),(int)(FEN_Y/4));
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

void renderButton(SDL_Renderer *renderer, Button *button, SDL_Color color_text, SDL_Color colorh0, SDL_Color colorh1) {
    if (button->rect.y > HEADER_HEIGHT + BUTTON_MARGIN/2 && button->rect.y + button->rect.h/2 < FEN_Y) {
        TTF_Font * font;
        SDL_Color color = button->hovered ? colorh1 : colorh0;
        SDL_Rect tmp_rect;
        if (button->hovered) {
            int taille_bonus_x = 20;
            int taille_bonus_y = 20;
            tmp_rect.w = button->rect.w + taille_bonus_x;
            tmp_rect.h = button->rect.h + taille_bonus_y;
            tmp_rect.x = button->rect.x - taille_bonus_x/2;
            tmp_rect.y = button->rect.y - taille_bonus_y/2;
            font = fonts[2];
        } else {
            tmp_rect.w = button->rect.w;
            tmp_rect.h = button->rect.h;
            tmp_rect.x = button->rect.x;
            tmp_rect.y = button->rect.y;
            font = fonts[1];
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &tmp_rect);

        SDL_Surface *surface =  TTF_RenderUTF8_Solid(font, button->label, color_text);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {tmp_rect.x + tmp_rect.w/2 - surface->w/2, tmp_rect.y + tmp_rect.h/2 - surface->h/2, surface->w, surface->h};

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
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, titre, (SDL_Color){255, 255, 255, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = {FEN_X / 2 - surface->w / 2, HEADER_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};
    
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void handle_events(MusicButton musics[], SelectionButton selections[], Musique* musique) {
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
        renderButton(renderer, &(musics[i].button_base), color_texte, color_base_musics, color_touch_musics);
    }

    // Dessiner les boutons de sélection de catégorie
    for (int i = 0; i < NB_CATEGORIES; i++) {
        if (selection_en_cours == selections[i].type) {
            selections[i].button_base.hovered = 1;
        } else {
            selections[i].button_base.hovered = 0;
        }
        renderButton(renderer, &(selections[i].button_base), color_texte, color_base_select, color_touch_select);
    }
}

void affiche_boutons_accueil(SDL_Renderer* ren, Button* buttons[], int nb_buttons) {
    SDL_Color color_texte = {255, 255, 255, 255};
    SDL_Color color_base = {0, 0, 255, 255};
    SDL_Color color_touch = {255, 0, 0, 255};

    for (int i = 0; i < nb_buttons; i++) {
        renderButton(ren, buttons[i], color_texte, color_base, color_touch);
    }
}

void handle_events_accueil(Button* buttons[], Musique* musique, SDL_Renderer* ren, int *running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            *running = 0;
        }
        if (e.type == SDL_MOUSEMOTION) {
            int x = e.motion.x, y = e.motion.y;
            for (int i = 0; i < 4; i++) {
                if (x >= buttons[i]->rect.x && x <= buttons[i]->rect.x + buttons[i]->rect.w &&
                    y >= buttons[i]->rect.y && y <= buttons[i]->rect.y + buttons[i]->rect.h) {
                    buttons[i]->hovered = 1;
                } else {
                    buttons[i]->hovered = 0;
                }
            }
        }
        if (e.type == SDL_MOUSEBUTTONUP) {
            int x = e.button.x, y = e.button.y;
            for (int i = 0; i < 4; i++) {
                if (x >= buttons[i]->rect.x && x <= buttons[i]->rect.x + buttons[i]->rect.w &&
                    y >= buttons[i]->rect.y && y <= buttons[i]->rect.y + buttons[i]->rect.h) {
                    playSoundEffect(musique->select);
                    switch (i) {
                        case 0:
                            ecran_musique(ren, musique);
                            break;
                        case 1:
                            ecran_niveaux(ren, musique);
                            break;
                        case 2:
                            ecran_remerciements(ren, musique);
                            break;
                        case 3:
                            main_loop_createur_map(ren, musique);
                            break;
                    }
                    *running = 0;
                    return;
                }
            }
        }
        if (e.type == SDL_KEYUP) {
            char lancement = e.key.keysym.sym;
            switch (lancement) {
                case SDLK_SPACE:
                    playSoundEffect(musique->select);
                    nouvelle_partie(ren, musique, 1);
                    *running = 0;
                    break;
                case SDLK_m:
                    playSoundEffect(musique->select);
                    ecran_musique(ren, musique);
                    *running = 0;
                    break;
                case SDLK_n:
                    playSoundEffect(musique->select);
                    ecran_niveaux(ren, musique);
                    *running = 0;
                    break;
                case SDLK_r:
                    playSoundEffect(musique->select);
                    ecran_remerciements(ren, musique);
                    *running = 0;
                    break;
                case SDLK_c:
                    playSoundEffect(musique->select);
                    main_loop_createur_map(ren, musique);
                    *running = 0;
                    break;
                default:
                    break;
            }
        }
    }
}

