#include "createur_map.h"

SelectionType_createur_map selection_en_cours_createur_map = SELECTION_NULL;

void init_buttons_createur_map (SelectionButton_createur_map selectionButtons[NB_BUTTONS_CREATEUR_MAP], int button_height, int button_margin_y, int button_width){
    for (int i = 0; i < NB_BUTTONS_CREATEUR_MAP; i++) {
        selectionButtons[i].button_base.rect.x = FEN_X - TAILLE_BARRE_MENU_X + (TAILLE_BARRE_MENU_X - button_width)/2;
        selectionButtons[i].button_base.rect.y = HEADER_HEIGHT + 100 + i * (button_height + button_margin_y);
        selectionButtons[i].button_base.rect.w = button_width;
        selectionButtons[i].button_base.rect.h = button_height;
        selectionButtons[i].button_base.hovered = 0;
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


}

void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map boutons[NB_BUTTONS_CREATEUR_MAP]){
    SDL_Color color_texte = {255, 255, 255, 255};
    SDL_Color color_base = {100, 100, 255, 255};
    SDL_Color color_selected = {200, 100, 255, 255};
    SDL_Color color_touch = {100, 200, 255, 255};
    SDL_Color color;
    for (int i = 0; i < NB_BUTTONS_CREATEUR_MAP; i++) {
        if (selection_en_cours_createur_map == boutons[i].type) {
            color.r = color_selected.r;
            color.g = color_selected.g;
            color.b = color_selected.b;
        } else {
            color.r = color_base.r;
            color.g = color_base.g;
            color.b = color_base.b;
        }
        renderButton(ren, &(boutons[i].button_base), color_texte, color, color_touch);
    }
}

void clic_souris (int x, int y, SelectionButton_createur_map selections[NB_BUTTONS_CREATEUR_MAP], Musique* musique){
    // Vérifier si un bouton de sélection de catégorie est cliqué
    for (int i = 0; i < NB_BUTTONS_CREATEUR_MAP; i++) {
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

void modif_case (Map* map, int x_souris_cases, int y_souris_cases){
    switch (selection_en_cours_createur_map) {
        case SELECTION_VIDE_INTERNE:
            map->contenu[y_souris_cases][x_souris_cases] = 0;
            break;
        case SELECTION_VIDE_EXTERNE:
            map->contenu[y_souris_cases][x_souris_cases] = 2;
            break;
        case SELECTION_MUR:
            map->contenu[y_souris_cases][x_souris_cases] = 1;
            break;
        case SELECTION_GUM:
            map->contenu[y_souris_cases][x_souris_cases] = 4;
            break;
        case SELECTION_BIG_GUM:
            map->contenu[y_souris_cases][x_souris_cases] = 5;
            break;
        default:
            break;
    }
}

void main_loop_createur_map (SDL_Renderer* ren, Musique* musique){
    int button_height = 50;
    int button_margin_y = 50;
    int button_width = 210; 

    SelectionButton_createur_map buttons[NB_BUTTONS_CREATEUR_MAP];
    init_buttons_createur_map(buttons, button_height, button_margin_y, button_width);

    SDL_Texture** tils = malloc(sizeof(SDL_Texture*) * 4);
    init_tils(tils, ren);

    Map map = init_map_dessin();
    if ((FEN_Y-HEADER_HEIGHT)/map.y < (FEN_X-TAILLE_BARRE_MENU_X)/map.x){
        map.taille_case = (FEN_Y-HEADER_HEIGHT)/(map.y + 2);
    } else {
        map.taille_case = (FEN_X-TAILLE_BARRE_MENU_X)/(map.x + 2);
    }
    ORIGINE_X = map.taille_case;
    ORIGINE_Y = HEADER_HEIGHT + map.taille_case;

    int position_maison_ghosts[] = {map.position_maison_ghosts_x - 4,
                                    map.position_maison_ghosts_y,
                                    map.position_maison_ghosts_x + 5,
                                    map.position_maison_ghosts_y + 6};

    int x_souris_px, y_souris_px, x_souris_cases, y_souris_cases;
    int is_en_cours_de_modif = 0;
    int is_souris_sur_map = 0;
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Créateur de Map");
        affiche_boutons_createur_map(ren, buttons);
        affiche_map(&map, tils, ren);
        affiche_quadrillage(ren, &map);
        if (is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            SDL_Rect rectangle_selection_map = {ORIGINE_X + x_souris_cases * map.taille_case, ORIGINE_Y + y_souris_cases * map.taille_case, map.taille_case, map.taille_case};
            SDL_RenderDrawRect(ren, &rectangle_selection_map);
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_MOUSEMOTION) {
                x_souris_px = event.motion.x;
                y_souris_px = event.motion.y;

                // Souris sur un bouton ?
                for (int i = 0; i < NB_BUTTONS_CREATEUR_MAP; i++) {
                    if (x_souris_px >= buttons[i].button_base.rect.x && x_souris_px <= buttons[i].button_base.rect.x + button_width &&
                        y_souris_px >= buttons[i].button_base.rect.y && y_souris_px <= buttons[i].button_base.rect.y + button_height) {
                            buttons[i].button_base.hovered = 1;
                    } else {
                        buttons[i].button_base.hovered = 0;
                    }
                }
                
                // Souris sur la map ?
                if (x_souris_px >= ORIGINE_X && x_souris_px <= ORIGINE_X + map.x * map.taille_case &&
                    y_souris_px >= ORIGINE_Y && y_souris_px <= ORIGINE_Y + map.y * map.taille_case) {
                        x_souris_cases = (x_souris_px - ORIGINE_X)/map.taille_case;
                        y_souris_cases = (y_souris_px - ORIGINE_Y)/map.taille_case;
                        // Souris pas dans la maison des fantômes
                        if (x_souris_cases >= position_maison_ghosts[0] && x_souris_cases <= position_maison_ghosts[2] &&
                            y_souris_cases >= position_maison_ghosts[1] && y_souris_cases <= position_maison_ghosts[3]){
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
                    modif_case(&map, x_souris_cases, y_souris_cases);
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                int x = event.button.x, y = event.button.y;
                clic_souris(x, y, buttons, musique);
                is_en_cours_de_modif = 0; // Arrête la modification à la chaine
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
                    is_en_cours_de_modif = 1;
                    modif_case(&map, x_souris_cases, y_souris_cases);
                }
            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_BACKSPACE){
                    playSoundEffect(musique->select);
                    ecran_acceuil(ren,musique);
                    running = 0;
                }
            }
        }
        updateDisplay(ren);
    }
}