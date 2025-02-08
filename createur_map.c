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
    SDL_Color color_selected = {100, 200, 255, 255};
    SDL_Color color_touch = {200, 100, 255, 255};
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

void main_loop_createur_map (SDL_Renderer* ren, Musique* musique){
    int button_height = 50;
    int button_margin_y = 50;
    int button_width = 200; 

    SelectionButton_createur_map buttons[NB_BUTTONS_CREATEUR_MAP];
    init_buttons_createur_map(buttons, button_height, button_margin_y, button_width);

    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Créateur de Map");
        affiche_boutons_createur_map(ren, buttons);
        updateDisplay(ren);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_MOUSEMOTION) {
                int x = event.motion.x, y = event.motion.y;
                for (int i = 0; i < NB_BUTTONS_CREATEUR_MAP; i++) {
                    if (x >= buttons[i].button_base.rect.x && x <= buttons[i].button_base.rect.x + button_width &&
                        y >= buttons[i].button_base.rect.y && y <= buttons[i].button_base.rect.y + button_height) {
                        buttons[i].button_base.hovered = 1;
                    } else {
                        buttons[i].button_base.hovered = 0;
                    }
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                int x = event.button.x, y = event.button.y;
                for (int i = 0; i < NB_BUTTONS_CREATEUR_MAP; i++) {
                    if (x >= buttons[i].button_base.rect.x && x <= buttons[i].button_base.rect.x + button_width &&
                        y >= buttons[i].button_base.rect.y && y <= buttons[i].button_base.rect.y + button_height) {
                        playSoundEffect(musique->select);
                        //todo
                    }
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
    }
}