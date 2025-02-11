#include "createur_map.h"

SelectionType_createur_map selection_en_cours_createur_map = SELECTION_NULL;

void init_buttons_createur_map (Button* buttons[NB_BUTTONS], int button_height, int button_width, SelectionButton_createur_map selectionButtons[NB_BUTTONS_SELECTION_REMPLISSAGE], 
                                Button* button_grille, Button* button_enregistrer, Button* button_zoom_plus, Button* button_zoom_moins){
    // Les boutons de selection de mode de remplissage :
    int button_margin_y = ((FEN_Y - HEADER_HEIGHT)/2 - NB_BUTTONS_SELECTION_REMPLISSAGE * button_height)/NB_BUTTONS_SELECTION_REMPLISSAGE;
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        selectionButtons[i].button_base.rect.x = FEN_X - TAILLE_BARRE_MENU_X + (TAILLE_BARRE_MENU_X - button_width)/2;
        selectionButtons[i].button_base.rect.y = HEADER_HEIGHT + button_margin_y/2 + i * (button_height + button_margin_y);
        selectionButtons[i].button_base.rect.w = button_width;
        selectionButtons[i].button_base.rect.h = button_height;
        selectionButtons[i].button_base.hovered = 0;
        buttons[i] = &(selectionButtons[i].button_base);
    }
    selectionButtons[0].type = SELECTION_VIDE_INTERNE;
    selectionButtons[0].button_base.label = "Vide Interne";
    selectionButtons[1].type = SELECTION_VIDE_EXTERNE;
    selectionButtons[1].button_base.label = "Vide Externe";
    selectionButtons[2].type = SELECTION_MUR;
    selectionButtons[2].button_base.label = "Mur";
    selectionButtons[3].type = SELECTION_GUM;
    selectionButtons[3].button_base.label = "Gum";
    selectionButtons[4].type = SELECTION_BIG_GUM;
    selectionButtons[4].button_base.label = "Big Gum";

    // Les autres boutons :
    button_margin_y = ((FEN_Y - HEADER_HEIGHT)/2 - (NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE) * button_height)/(NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE);
    Button* but[] = {button_grille, button_zoom_plus, button_zoom_moins, button_enregistrer};
    char* noms[] = {"Grille", "Zoom +", "Zoom -", "Enregistrer"};
    for (int j = 0; j < NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE; j++){
        but[j]->rect.x = FEN_X - TAILLE_BARRE_MENU_X + (TAILLE_BARRE_MENU_X - button_width)/2;
        but[j]->rect.y = (FEN_Y + HEADER_HEIGHT)/2 + button_margin_y/2 + j * (button_height + button_margin_y);
        but[j]->rect.w = button_width;
        but[j]->rect.h = button_height;
        but[j]->hovered = 0;
        but[j]->label = noms[j];
        buttons[NB_BUTTONS_SELECTION_REMPLISSAGE + j] = but[j];
    }
}

void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map boutons_selection[NB_BUTTONS_SELECTION_REMPLISSAGE], Button* boutons[NB_BUTTONS]){
    SDL_Color color_texte = {255, 255, 255, 255};
    SDL_Color color_base = {100, 100, 255, 255};
    SDL_Color color_selected = {200, 100, 255, 255};
    SDL_Color color_touch = {100, 200, 255, 255};
    SDL_Color color;
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        if (selection_en_cours_createur_map == boutons_selection[i].type) {
            color.r = color_selected.r;
            color.g = color_selected.g;
            color.b = color_selected.b;
        } else {
            color.r = color_base.r;
            color.g = color_base.g;
            color.b = color_base.b;
        }
        renderButton(ren, &(boutons_selection[i].button_base), color_texte, color, color_touch);
    }
    for (int j = NB_BUTTONS_SELECTION_REMPLISSAGE; j < NB_BUTTONS; j++){
        renderButton(ren, boutons[j], color_texte, color_base, color_touch);
    }
}

void clic_souris (int x, int y, SelectionButton_createur_map selections[NB_BUTTONS_SELECTION_REMPLISSAGE], Musique* musique){
    // Vérifier si un bouton de sélection de catégorie est cliqué
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        if (x >= selections[i].button_base.rect.x && x <= selections[i].button_base.rect.x + selections[i].button_base.rect.w &&
            y >= selections[i].button_base.rect.y && y <= selections[i].button_base.rect.y + selections[i].button_base.rect.h) {
                
                playSoundEffect(musique->select);
                if (selection_en_cours_createur_map == selections[i].type) {
                    selection_en_cours_createur_map = SELECTION_NULL;
                } else {
                    selection_en_cours_createur_map = selections[i].type;
                }
            return;
        }
    }
}

void affiche_quadrillage (SDL_Renderer* ren, Map* map){
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    for (int i = 0; i<=map->x; i++) {
        SDL_RenderDrawLine(ren, ORIGINE_X + map->taille_case*i, ORIGINE_Y, ORIGINE_X + map->taille_case*i, ORIGINE_Y + map->taille_case*map->y);
    }
    for (int i = 0; i<=map->y; i++) {
        SDL_RenderDrawLine(ren, ORIGINE_X, ORIGINE_Y + map->taille_case*i, ORIGINE_X + map->taille_case*map->x, ORIGINE_Y + map->taille_case*i);
    }
}

void modif_case (Map* map, Map* map_totale, int x_souris_cases, int y_souris_cases, int position_zoom_x, int position_zoom_y){
    switch (selection_en_cours_createur_map) {
        case SELECTION_VIDE_INTERNE:
            map->contenu[y_souris_cases][x_souris_cases] = 0;
            map_totale->contenu[y_souris_cases + position_zoom_y][x_souris_cases + position_zoom_x] = 0;
            break;
        case SELECTION_VIDE_EXTERNE:
            map->contenu[y_souris_cases][x_souris_cases] = 2;
            map_totale->contenu[y_souris_cases + position_zoom_y][x_souris_cases + position_zoom_x] = 2;
            break;
        case SELECTION_MUR:
            map->contenu[y_souris_cases][x_souris_cases] = 1;
            map_totale->contenu[y_souris_cases + position_zoom_y][x_souris_cases + position_zoom_x] = 1;
            break;
        case SELECTION_GUM:
            map->contenu[y_souris_cases][x_souris_cases] = 4;
            map_totale->contenu[y_souris_cases + position_zoom_y][x_souris_cases + position_zoom_x] = 4;
            break;
        case SELECTION_BIG_GUM:
            map->contenu[y_souris_cases][x_souris_cases] = 5;
            map_totale->contenu[y_souris_cases + position_zoom_y][x_souris_cases + position_zoom_x] = 5;
            break;
        default:
            break;
    }
}

int is_souris_sur_button (Button button, int x_souris_px, int y_souris_px){
    return x_souris_px >= button.rect.x && x_souris_px <= button.rect.x + button.rect.w &&
                    y_souris_px >= button.rect.y && y_souris_px <= button.rect.y + button.rect.h;
}

void nouveau_zoom (Map* map, Map* map_totale, int zoom, int position_zoom_x, int position_zoom_y){
    freeMap(map);
    map->x = map_totale->x - zoom;
    map->y = map_totale->y - zoom;
    map->contenu = malloc(map->y * sizeof(int *));
    for (int i = 0; i < map->y; i++) {
        map->contenu[i] = malloc(map->x * sizeof(int));
        for (int j = 0; j < map->x; j++) {
            map->contenu[i][j] = map_totale->contenu[position_zoom_y + i][position_zoom_x + j];
        }
    }
    if ((FEN_Y-HEADER_HEIGHT)/map->y < (FEN_X-TAILLE_BARRE_MENU_X)/map->x){
        map->taille_case = (FEN_Y-HEADER_HEIGHT)/(map->y + 2);
    } else {
        map->taille_case = (FEN_X-TAILLE_BARRE_MENU_X)/(map->x + 2);
    }
    ORIGINE_X = (FEN_X-TAILLE_BARRE_MENU_X - map->x * map->taille_case)/2;
    ORIGINE_Y = HEADER_HEIGHT + (FEN_Y-HEADER_HEIGHT - map->y * map->taille_case)/2;
}

Map copyMap(const Map *src) {
    Map dest;
    dest.x = src->x;
    dest.y = src->y;
    dest.taille_case = src->taille_case;
    dest.type = src->type;
    dest.taille_perso = src->taille_perso;
    dest.position_maison_ghosts_x = src->position_maison_ghosts_x;
    dest.position_maison_ghosts_y = src->position_maison_ghosts_y;
    dest.position_pacman_start_x = src->position_pacman_start_x;
    dest.position_pacman_start_y = src->position_pacman_start_y;
    
    // Allocation et copie du contenu
    dest.contenu = malloc(dest.y * sizeof(int *));
    for (int i = 0; i < dest.y; i++) {
        dest.contenu[i] = malloc(dest.x * sizeof(int));
        for (int j = 0; j < dest.x; j++) {
            dest.contenu[i][j] = src->contenu[i][j];
        }
    }
    
    return dest;
}

void main_loop_createur_map (SDL_Renderer* ren, Musique* musique){
    int button_height = 50;
    int button_width = 210; 

    Button* buttons[NB_BUTTONS];
    SelectionButton_createur_map buttons_selection_remplissage [NB_BUTTONS_SELECTION_REMPLISSAGE];
    Button button_grille;
    Button button_enregistrer;
    Button button_zoom_plus;
    Button button_zoom_moins;
    init_buttons_createur_map(buttons, button_height, button_width, buttons_selection_remplissage, &button_grille, &button_enregistrer, &button_zoom_plus, &button_zoom_moins);

    SDL_Texture** tils = malloc(sizeof(SDL_Texture*) * 4);
    init_tils(tils, ren);

    Map map = init_map_dessin();
    if ((FEN_Y-HEADER_HEIGHT)/map.y < (FEN_X-TAILLE_BARRE_MENU_X)/map.x){
        map.taille_case = (FEN_Y-HEADER_HEIGHT)/(map.y + 2);
    } else {
        map.taille_case = (FEN_X-TAILLE_BARRE_MENU_X)/(map.x + 2);
    }
    ORIGINE_X = (FEN_X-TAILLE_BARRE_MENU_X - map.x * map.taille_case)/2;
    ORIGINE_Y = HEADER_HEIGHT + (FEN_Y-HEADER_HEIGHT - map.y * map.taille_case)/2;
    Map map_totale = copyMap(&map);

    int position_maison_ghosts[] = {map.position_maison_ghosts_x - 4,
                                    map.position_maison_ghosts_y,
                                    map.position_maison_ghosts_x + 5,
                                    map.position_maison_ghosts_y + 6};

    int x_souris_px, y_souris_px, x_souris_cases, y_souris_cases;
    int is_en_cours_de_modif = 0;
    int is_souris_sur_map = 0;
    int is_grille_on = 1;
    int zoom = 0;
    int position_zoom_x = 0;
    int position_zoom_y = 0;

    char text[MAX_TEXT_LENGTH + 1] = "";
    SDL_Color color = {255, 255, 255, 255};
    int cursorVisible = 1;
    Uint32 lastCursorToggle = SDL_GetTicks();
    char displayText[MAX_TEXT_LENGTH + 2];
    Button entree_text;
    entree_text.rect.x = FEN_X/2-200;
    entree_text.rect.y = FEN_Y/2-50;
    entree_text.rect.w = 400;
    entree_text.rect.h = 200;
    entree_text.hovered = 1;
    Button annuler_enregistrement;
    annuler_enregistrement.rect.x = FEN_X/2 - 20 - button_width;
    annuler_enregistrement.rect.y = 3*FEN_Y/4 - button_height/2;
    annuler_enregistrement.rect.w = button_width;
    annuler_enregistrement.rect.h = button_height;
    annuler_enregistrement.hovered = 0;
    annuler_enregistrement.label = "Annuler";
    Button valider_enregistrement;
    valider_enregistrement.rect.x = FEN_X/2 + 20;
    valider_enregistrement.rect.y = 3*FEN_Y/4 - button_height/2;
    valider_enregistrement.rect.w = button_width;
    valider_enregistrement.rect.h = button_height;
    valider_enregistrement.hovered = 0;
    valider_enregistrement.label = "Valider";

    int is_enregistrement = 0;
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Créateur de Map");
        affiche_map(&map, tils, ren);
        if (!is_enregistrement){
            SDL_SetRenderDrawColor(ren, 50, 100, 50, 255);
            SDL_Rect bande_laterale_haut = {FEN_X - TAILLE_BARRE_MENU_X, HEADER_HEIGHT, FEN_X, (int)((FEN_Y + HEADER_HEIGHT)/2)};
            SDL_RenderFillRect(ren, &bande_laterale_haut);
            SDL_SetRenderDrawColor(ren, 50, 50, 50, 255);
            SDL_Rect bande_laterale_bas = {FEN_X - TAILLE_BARRE_MENU_X, (int)((FEN_Y + HEADER_HEIGHT)/2), FEN_X, FEN_Y};
            SDL_RenderFillRect(ren, &bande_laterale_bas);
            affiche_boutons_createur_map(ren, buttons_selection_remplissage, buttons);
            if (is_grille_on) {
                affiche_quadrillage(ren, &map);
            }
            if (is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
                SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                SDL_Rect rectangle_selection_map = {ORIGINE_X + x_souris_cases * map.taille_case, ORIGINE_Y + y_souris_cases * map.taille_case, map.taille_case, map.taille_case};
                SDL_RenderDrawRect(ren, &rectangle_selection_map);
            }
        } else {
            if (SDL_GetTicks() - lastCursorToggle >= CURSOR_BLINK_TIME) {
                cursorVisible = !cursorVisible;
                lastCursorToggle = SDL_GetTicks();
            }
            snprintf(displayText, sizeof(displayText), "%s%s", text, cursorVisible ? "|" : " ");
            entree_text.label = displayText;
            renderButton(ren, &entree_text, color, (SDL_Color){50, 50, 50, 100}, (SDL_Color){50, 50, 50, 100});
            renderButton(ren, &valider_enregistrement, color, (SDL_Color){0, 255, 0, 255}, (SDL_Color){0, 255, 0, 100});
            renderButton(ren, &annuler_enregistrement, color, (SDL_Color){255, 0, 0, 255}, (SDL_Color){255, 0, 0, 100});
        } 

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (!is_enregistrement) {
                if (event.type == SDL_MOUSEMOTION) {
                    x_souris_px = event.motion.x;
                    y_souris_px = event.motion.y;

                    // Souris sur un bouton ?
                    for (int i = 0; i < NB_BUTTONS; i++) {
                        if (x_souris_px >= buttons[i]->rect.x && x_souris_px <= buttons[i]->rect.x + button_width &&
                            y_souris_px >= buttons[i]->rect.y && y_souris_px <= buttons[i]->rect.y + button_height) {
                                buttons[i]->hovered = 1;
                        } else {
                            buttons[i]->hovered = 0;
                        }
                    }
                    
                    // Souris sur la map ?
                    if (x_souris_px >= ORIGINE_X && x_souris_px <= ORIGINE_X + map.x * map.taille_case &&
                        y_souris_px >= ORIGINE_Y && y_souris_px <= ORIGINE_Y + map.y * map.taille_case) {
                            x_souris_cases = (x_souris_px - ORIGINE_X)/map.taille_case;
                            y_souris_cases = (y_souris_px - ORIGINE_Y)/map.taille_case;
                            // Souris pas dans la maison des fantômes
                            if (x_souris_cases >= position_maison_ghosts[0] - position_zoom_x && x_souris_cases <= position_maison_ghosts[2] - position_zoom_x &&
                                y_souris_cases >= position_maison_ghosts[1] - position_zoom_y && y_souris_cases <= position_maison_ghosts[3] - position_zoom_y){
                                    is_souris_sur_map = 0;
                                    is_en_cours_de_modif = 0; // Arrête la modification à la chaine
                            }
                            else {
                                is_souris_sur_map = 1;
                            }
                    }
                    else {
                        is_souris_sur_map = 0;
                    }

                    // Map en cours de modif ? <=> souris pressée sur une case <=> modification à la chaine
                    if (is_en_cours_de_modif){
                        modif_case(&map, &map_totale, x_souris_cases, y_souris_cases, position_zoom_x, position_zoom_y);
                    }
                }

                if (event.type == SDL_MOUSEBUTTONUP) {
                    clic_souris(x_souris_px, y_souris_px, buttons_selection_remplissage, musique);
                    is_en_cours_de_modif = 0; // Arrête la modification à la chaine

                    if (is_souris_sur_button(button_grille, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        if (is_grille_on) {
                            is_grille_on = 0;
                        } else {
                            is_grille_on = 1;
                        }
                    }

                    if (is_souris_sur_button(button_zoom_plus, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        zoom += VITESSE_ZOOM;
                        if (zoom > map.x - ZOOM_MAX || zoom > map.y - ZOOM_MAX ){
                            zoom -= VITESSE_ZOOM;
                        } else {
                            nouveau_zoom(&map, &map_totale, zoom, position_zoom_x, position_zoom_y);
                        }
                    }
                    if (is_souris_sur_button(button_zoom_moins, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        zoom -= VITESSE_ZOOM;
                        if (zoom < 0){
                            zoom = 0;
                        } else {
                            if (position_zoom_x > zoom){
                                position_zoom_x = zoom;
                            }
                            if (position_zoom_y > zoom){
                                position_zoom_y = zoom;
                            }
                            nouveau_zoom(&map, &map_totale, zoom, position_zoom_x, position_zoom_y);
                        }
                    }

                    if (is_souris_sur_button(button_enregistrer, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        is_enregistrement = 1;
                        SDL_StartTextInput();
                    }
                }

                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
                        is_en_cours_de_modif = 1;
                        modif_case(&map, &map_totale, x_souris_cases, y_souris_cases, position_zoom_x, position_zoom_y);
                    }
                }

                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_LEFT){
                        position_zoom_x -= VITESSE_MOVE_ZOOM;
                        if (position_zoom_x < 0){
                            position_zoom_x = 0;
                        } else {
                            nouveau_zoom(&map, &map_totale, zoom, position_zoom_x, position_zoom_y);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT){
                        position_zoom_x += VITESSE_MOVE_ZOOM;
                        if (position_zoom_x + map.x > map_totale.x){
                            position_zoom_x = map_totale.x - map.x;
                        } else {
                            nouveau_zoom(&map, &map_totale, zoom, position_zoom_x, position_zoom_y);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_UP){
                        position_zoom_y -= VITESSE_MOVE_ZOOM;
                        if (position_zoom_y < 0){
                            position_zoom_y = 0;
                        } else {
                            nouveau_zoom(&map, &map_totale, zoom, position_zoom_x, position_zoom_y);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_DOWN){
                        position_zoom_y += VITESSE_MOVE_ZOOM;
                        if (position_zoom_y + map.y > map_totale.y){
                            position_zoom_y = map_totale.y - map.y;
                        } else {
                            nouveau_zoom(&map, &map_totale, zoom, position_zoom_x, position_zoom_y);
                        }
                    }
                }

                if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == SDLK_BACKSPACE){
                        playSoundEffect(musique->select);
                        SDL_StopTextInput();
                        ecran_acceuil(ren,musique);
                        running = 0;
                    }
                }
            } else {
                if (event.type == SDL_TEXTINPUT) {
                    if (strlen(text) < MAX_TEXT_LENGTH) {
                        strcat(text, event.text.text);
                    }
                }

                if (event.type == SDL_MOUSEMOTION) {
                    x_souris_px = event.motion.x;
                    y_souris_px = event.motion.y;

                    // Souris sur un bouton ?
                    if (x_souris_px >= annuler_enregistrement.rect.x && x_souris_px <= annuler_enregistrement.rect.x + button_width &&
                        y_souris_px >= annuler_enregistrement.rect.y && y_souris_px <= annuler_enregistrement.rect.y + button_height) {
                            annuler_enregistrement.hovered = 1;
                    } else {
                        annuler_enregistrement.hovered = 0;
                    }
                    if (x_souris_px >= valider_enregistrement.rect.x && x_souris_px <= valider_enregistrement.rect.x + button_width &&
                        y_souris_px >= valider_enregistrement.rect.y && y_souris_px <= valider_enregistrement.rect.y + button_height) {
                            valider_enregistrement.hovered = 1;
                    } else {
                        valider_enregistrement.hovered = 0;
                    }

                if (event.type == SDL_MOUSEBUTTONUP) {
                    if (is_souris_sur_button(button_grille, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        if (is_grille_on) {
                            is_grille_on = 0;
                        } else {
                            is_grille_on = 1;
                        }
                    }
                }
            }
            
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0) {
                        text[strlen(text) - 1] = '\0';
                    } else if (event.key.keysym.sym == SDLK_c && (event.key.keysym.mod & KMOD_CTRL)) {
                        color.r = rand() % 256;
                        color.g = rand() % 256;
                        color.b = rand() % 256;
                    }
                }
            
                if (event.type == SDL_MOUSEBUTTONUP) {
                    if (is_souris_sur_button(annuler_enregistrement, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        is_enregistrement = 0;
                        SDL_StopTextInput();
                    }
                    if (is_souris_sur_button(valider_enregistrement, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        is_enregistrement = 0;
                        SDL_StopTextInput();
                        save_map_text(text, &map_totale);
                        //save_map_binary(text, &map_totale);
                    }
                }
            }
        }
        updateDisplay(ren);
    }
}
