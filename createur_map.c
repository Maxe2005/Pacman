#include "createur_map.h"

SelectionType_createur_map selection_en_cours_createur_map = SELECTION_NULL;

void init_buttons_createur_map (Button* buttons[NB_BUTTONS], int button_height, int button_width, SelectionButton_createur_map selectionButtons[NB_BUTTONS_SELECTION_REMPLISSAGE], 
                                Button* button_modif_taille_map, Button* button_grille, Button* button_enregistrer, Button* button_zoom_plus, Button* button_zoom_moins, Button* button_symetrie_verticale, Button* button_symetrie_horizontale){
    // Les boutons de selection de mode de remplissage :
    int button_margin_y = (3*(FEN_Y - HEADER_HEIGHT)/4 - NB_BUTTONS_SELECTION_REMPLISSAGE * button_height)/NB_BUTTONS_SELECTION_REMPLISSAGE;
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        selectionButtons[i].button_base.rect.x = FEN_X - TAILLE_BARRE_MENU_X + (TAILLE_BARRE_MENU_X/2 - button_width)/2;
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

    // Le bouton enregistrer :
    button_enregistrer->rect.x = FEN_X - TAILLE_BARRE_MENU_X + (TAILLE_BARRE_MENU_X/2 - button_width)/2;
    button_enregistrer->rect.y = FEN_Y - 2*button_height;
    button_enregistrer->rect.w = button_width;
    button_enregistrer->rect.h = button_height;
    button_enregistrer->hovered = 0;
    button_enregistrer->label = "Enregistrer";
    buttons[NB_BUTTONS_SELECTION_REMPLISSAGE] = button_enregistrer;

    // Les autres boutons :
    button_margin_y = ((FEN_Y - HEADER_HEIGHT) - (NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE - 1) * button_height)/(NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE - 1);
    Button* but[] = {button_modif_taille_map, button_grille, button_zoom_plus, button_zoom_moins, button_symetrie_verticale, button_symetrie_horizontale};
    char* noms[] = {"Modif taille", "Grille", "Zoom +", "Zoom -", "Sym. verti.", "Sym. horiz."};
    for (int j = 0; j < NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE - 1; j++){
        but[j]->rect.x = FEN_X - TAILLE_BARRE_MENU_X/2 + (TAILLE_BARRE_MENU_X/2 - button_width)/2;
        but[j]->rect.y = HEADER_HEIGHT + button_margin_y/2 + j * (button_height + button_margin_y);
        but[j]->rect.w = button_width;
        but[j]->rect.h = button_height;
        but[j]->hovered = 0;
        but[j]->label = noms[j];
        buttons[NB_BUTTONS_SELECTION_REMPLISSAGE + 1 + j] = but[j];
    }
}

void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map boutons_selection[NB_BUTTONS_SELECTION_REMPLISSAGE], Button* boutons[NB_BUTTONS], int is_symetrie_horizontale, int is_symetrie_verticale, SDL_Color color_texte, SDL_Color color_touch, SDL_Color color_base, SDL_Color color_selected){
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        if (selection_en_cours_createur_map == boutons_selection[i].type) {
            renderButton(ren, &(boutons_selection[i].button_base), color_texte, color_selected, color_touch);
        } else {
            renderButton(ren, &(boutons_selection[i].button_base), color_texte, color_base, color_touch);
        }
    }
    for (int j = NB_BUTTONS_SELECTION_REMPLISSAGE; j < NB_BUTTONS-2; j++){
        renderButton(ren, boutons[j], color_texte, color_base, color_touch);
    }
    // Bouton symétrie verticale
    if (is_symetrie_verticale) {
        renderButton(ren, boutons[NB_BUTTONS-2], color_texte, color_selected, color_touch);
    } else {
        renderButton(ren, boutons[NB_BUTTONS-2], color_texte, color_base, color_touch);
    }
    // Bouton symétrie horizontale
    if (is_symetrie_horizontale) {
        renderButton(ren, boutons[NB_BUTTONS-1], color_texte, color_selected, color_touch);
    } else {
        renderButton(ren, boutons[NB_BUTTONS-1], color_texte, color_base, color_touch);
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

void modif_case (Map* map, Map* map_totale, int x_souris_cases, int y_souris_cases, int zoom, int position_zoom_x, int position_zoom_y, int is_symetrie_horizontale, int is_symetrie_verticale){
    int num_a_changer;
    switch (selection_en_cours_createur_map) {
        case SELECTION_VIDE_INTERNE:
            num_a_changer = 0;
            break;
        case SELECTION_VIDE_EXTERNE:
            num_a_changer = 2;
            break;
        case SELECTION_MUR:
            num_a_changer = 1;
            break;
        case SELECTION_GUM:
            num_a_changer = 4;
            break;
        case SELECTION_BIG_GUM:
            num_a_changer = 5;
            break;
        default:
            break;
    }
    map->contenu[y_souris_cases][x_souris_cases] = num_a_changer;
    map_totale->contenu[y_souris_cases + position_zoom_y][x_souris_cases + position_zoom_x] = num_a_changer;
    if (is_symetrie_verticale){
        map_totale->contenu[y_souris_cases + position_zoom_y][map_totale->x - 1 - (x_souris_cases + position_zoom_x)] = num_a_changer;
    }
    if (is_symetrie_horizontale){
        map_totale->contenu[map_totale->y - 1 - (y_souris_cases + position_zoom_y)][x_souris_cases + position_zoom_x] = num_a_changer;
    }
    if (is_symetrie_horizontale && is_symetrie_verticale){
        map_totale->contenu[map_totale->y - 1 - (y_souris_cases + position_zoom_y)][map_totale->x - 1 - (x_souris_cases + position_zoom_x)] = num_a_changer;
    }
    if (is_symetrie_horizontale || is_symetrie_verticale){
        // Pour actualiser les modifications potentiellement apparantes sur la map zoomée
        nouveau_zoom(map, map_totale, zoom, position_zoom_x, position_zoom_y);
    }
}

int is_souris_sur_button (Button button, int x_souris_px, int y_souris_px){
    return x_souris_px >= button.rect.x && x_souris_px <= button.rect.x + button.rect.w &&
                    y_souris_px >= button.rect.y && y_souris_px <= button.rect.y + button.rect.h;
}

void nouveau_zoom (Map* map, Map* map_totale, int zoom, int position_zoom_x, int position_zoom_y){
    freeMap(map); // libère la mémoire de son contenu pour pouvoir le remplacer
    map->x = map_totale->x - zoom;
    map->y = map_totale->y - zoom;
    map->contenu = malloc(map->y * sizeof(int *));
    for (int i = 0; i < map->y; i++) {
        map->contenu[i] = malloc(map->x * sizeof(int));
        for (int j = 0; j < map->x; j++) {
            map->contenu[i][j] = map_totale->contenu[position_zoom_y + i][position_zoom_x + j];
        }
    }
    init_taille_case_et_origine(map);
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

int is_map_conforme (Map* map, int* x, int* y){
    int nb_murs;
    for (int j = 1; j < map->y-1; j++){
        for (int i = 1; i < map->x-1; i++){
            if (map->contenu[j][i] == 0 || map->contenu[j][i] >= 4){
                nb_murs = 0;
                if (map->contenu[j][i+1] == 1) nb_murs++;
                if (map->contenu[j][i-1] == 1) nb_murs++;
                if (map->contenu[j+1][i] == 1) nb_murs++;
                if (map->contenu[j-1][i] == 1) nb_murs++;
                if (nb_murs == 3){
                    *x = i;
                    *y = j;
                    return 0;
                }
            }
        }
    }
    return 1;
}

void init_boutons_enregistrer (int button_width, int button_height, Button* entree_text, Button* consigne_enregistrement, Button* annuler_enregistrement, Button* valider_enregistrement){
    entree_text->rect.w = 400;
    entree_text->rect.h = 200;
    entree_text->rect.x = (FEN_X - entree_text->rect.w)/2;
    entree_text->rect.y = (FEN_Y - entree_text->rect.h)/2;
    entree_text->hovered = 1;

    consigne_enregistrement->rect.w = 500;
    consigne_enregistrement->rect.h = 75;
    consigne_enregistrement->rect.x = (FEN_X - consigne_enregistrement->rect.w)/2;
    consigne_enregistrement->rect.y = entree_text->rect.y - consigne_enregistrement->rect.h - 50;
    consigne_enregistrement->hovered = 0;
    consigne_enregistrement->label = "Entrez le nom de la map :";

    annuler_enregistrement->rect.x = FEN_X/2 - 20 - button_width;
    annuler_enregistrement->rect.y = entree_text->rect.y + entree_text->rect.h + 50;
    annuler_enregistrement->rect.w = button_width;
    annuler_enregistrement->rect.h = button_height;
    annuler_enregistrement->hovered = 0;
    annuler_enregistrement->label = "Annuler";

    valider_enregistrement->rect.x = FEN_X/2 + 20;
    valider_enregistrement->rect.y = entree_text->rect.y + entree_text->rect.h + 50;
    valider_enregistrement->rect.w = button_width;
    valider_enregistrement->rect.h = button_height;
    valider_enregistrement->hovered = 0;
    valider_enregistrement->label = "Valider";
}

void init_boutons_modif_taille_map (int button_width, int button_height, Button* entree_width, Button* entree_height, Button* valider_taille_map, Button* annuler_taille_map, Button* consigne_modif_taille_map, Button* text_entree_width, Button* text_entree_height){
    int taille_saisie_x = 200;
    int taille_saisie_y = 50;
    int taille_text_x = 350;
    int taille_text_y = 100;
    int ecart_entre_saisies = 120;
    int ecart_entre_bt_valider_et_annuler = 50;
    int ecart_entre_saisies_et_bts = 200;
    int ecart_entre_saisies_et_def = 80;

    // Position des champs de saisie
    entree_width->rect.w = taille_saisie_x;
    entree_width->rect.h = taille_saisie_y;
    entree_width->rect.x = (FEN_X + ecart_entre_saisies_et_def)/2;
    entree_width->rect.y = (FEN_Y - entree_width->rect.h - ecart_entre_saisies)/2;
    entree_width->hovered = 0;

    entree_height->rect.w = taille_saisie_x;
    entree_height->rect.h = taille_saisie_y;
    entree_height->rect.x = (FEN_X + ecart_entre_saisies_et_def)/2;
    entree_height->rect.y = (FEN_Y + ecart_entre_saisies - entree_width->rect.h)/2;
    entree_height->hovered = 0;

    // Position des textes de définition des champs de saisie
    text_entree_width->rect.w = taille_text_x;
    text_entree_width->rect.h = taille_text_y;
    text_entree_width->rect.x = FEN_X/2 - text_entree_width->rect.w - ecart_entre_saisies_et_def/2;
    text_entree_width->rect.y = (FEN_Y - text_entree_width->rect.h - ecart_entre_saisies)/2;
    text_entree_width->hovered = 0;
    text_entree_width->label = "Nombre de colones :";

    text_entree_height->rect.w = taille_text_x;
    text_entree_height->rect.h = taille_text_y;
    text_entree_height->rect.x = FEN_X/2 - text_entree_height->rect.w - ecart_entre_saisies_et_def/2;
    text_entree_height->rect.y = (FEN_Y + ecart_entre_saisies - text_entree_height->rect.h)/2;
    text_entree_height->hovered = 0;
    text_entree_height->label = "Nombre de lignes :";

    // Texte de consigne
    consigne_modif_taille_map->rect.w = 800;
    consigne_modif_taille_map->rect.h = 75;
    consigne_modif_taille_map->rect.x = (FEN_X - consigne_modif_taille_map->rect.w)/2;
    consigne_modif_taille_map->rect.y = entree_width->rect.y - consigne_modif_taille_map->rect.h - 50;
    consigne_modif_taille_map->hovered = 0;
    consigne_modif_taille_map->label = "Entrez les nouvelles dimentions de la map :";

    // Boutons valider et annuler
    valider_taille_map->rect.w = button_width;
    valider_taille_map->rect.h = button_height;
    valider_taille_map->rect.x = FEN_X/2 - button_width - ecart_entre_bt_valider_et_annuler/2;
    valider_taille_map->rect.y = entree_height->rect.y + (entree_height->rect.h + ecart_entre_saisies_et_bts - valider_taille_map->rect.h)/2;
    valider_taille_map->label = "Valider";
    valider_taille_map->hovered = 0;

    annuler_taille_map->rect.w = button_width;
    annuler_taille_map->rect.h = button_height;
    annuler_taille_map->rect.x = FEN_X/2 + ecart_entre_bt_valider_et_annuler/2;
    annuler_taille_map->rect.y = entree_height->rect.y + (entree_height->rect.h + ecart_entre_saisies_et_bts - annuler_taille_map->rect.h)/2;
    annuler_taille_map->label = "Annuler";
    annuler_taille_map->hovered = 0;
}

Map modif_taille_map (Map* map, int x, int y){
    Map dest;
    dest.x = x;
    dest.y = y;
    init_taille_case_et_origine(&dest);
    dest.type = map->type;
    dest.taille_perso = map->taille_perso;
    dest.position_maison_ghosts_x = map->position_maison_ghosts_x;
    dest.position_maison_ghosts_y = map->position_maison_ghosts_y;
    dest.position_pacman_start_x = map->position_pacman_start_x;
    dest.position_pacman_start_y = map->position_pacman_start_y;
    
    // Allocation et copie du contenu
    dest.contenu = malloc(dest.y * sizeof(int *));
    for (int i = 0; i < dest.y; i++) {
        dest.contenu[i] = malloc(dest.x * sizeof(int));
        for (int j = 0; j < dest.x; j++) {
            if (i < map->y && j < map->x){
                dest.contenu[i][j] = map->contenu[i][j];
            } else {
                dest.contenu[i][j] = 0;
            }
        }
    }
    return dest;
}

void init_taille_case_et_origine (Map* map){
    if ((FEN_Y-HEADER_HEIGHT)/map->y < (FEN_X-TAILLE_BARRE_MENU_X)/map->x){
        map->taille_case = (FEN_Y-HEADER_HEIGHT)/(map->y + 2);
    } else {
        map->taille_case = (FEN_X-TAILLE_BARRE_MENU_X)/(map->x + 2);
    }
    ORIGINE_X = (FEN_X-TAILLE_BARRE_MENU_X - map->x * map->taille_case)/2;
    ORIGINE_Y = HEADER_HEIGHT + (FEN_Y-HEADER_HEIGHT - map->y * map->taille_case)/2;
}

void free_tils(SDL_Texture** tils, int nb_tils) {
    for (int i = 0; i < nb_tils; i++) {
        SDL_DestroyTexture(tils[i]); // Libérer les textures
    }
    free(tils);
}

void main_loop_createur_map (SDL_Renderer* ren, Musique* musique){
    int button_height = 50;
    int button_width = 210; 

    Button* buttons[NB_BUTTONS];
    SelectionButton_createur_map buttons_selection_remplissage [NB_BUTTONS_SELECTION_REMPLISSAGE];
    Button button_modif_taille_map, button_grille, button_enregistrer, button_zoom_plus, button_zoom_moins, button_symetrie_verticale, button_symetrie_horizontale;
    init_buttons_createur_map(buttons, button_height, button_width, buttons_selection_remplissage, &button_modif_taille_map, &button_grille, &button_enregistrer, &button_zoom_plus, &button_zoom_moins, &button_symetrie_verticale, &button_symetrie_horizontale);

    SDL_Texture** tils = malloc(sizeof(SDL_Texture*) * 4);
    init_tils(tils, ren);

    // Un message à afficher (soit une erreur, une alerte ou bien une confirmation que tout c'est bien passé)
    Message message;
    message.button_base.rect = (SDL_Rect){FEN_X/2-400, FEN_Y/2-50, 800, 200};
    message.button_base.hovered = 0;
    message.is_visible = 0;
    time_t start_time_message = time(NULL);

    // Init pour le sous-menu enregistrer
    char text[MAX_TEXT_LENGTH + 1] = "";
    char displayText[MAX_TEXT_LENGTH + 2];
    Button entree_text, consigne_enregistrement, annuler_enregistrement, valider_enregistrement;
    init_boutons_enregistrer(button_width, button_height, &entree_text, &consigne_enregistrement, &annuler_enregistrement, &valider_enregistrement);
    

    // Init pour le sous-menu de modification de la taille de la map
    char width_text[MAX_NB_LENGTH + 1] = "";  // Stocke la largeur saisie
    char height_text[MAX_NB_LENGTH + 1] = ""; // Stocke la hauteur saisie
    char displayWidth[MAX_NB_LENGTH + 2];
    char displayHeight[MAX_NB_LENGTH + 2];
    int is_typing_width = 1; // 1 = saisie largeur en cours, 0 = saisie hauteur
    Button entree_width, entree_height, valider_taille_map, annuler_taille_map, consigne_modif_taille_map, text_entree_width, text_entree_height;
    init_boutons_modif_taille_map(button_width, button_height, &entree_width, &entree_height, &valider_taille_map, &annuler_taille_map, &consigne_modif_taille_map, &text_entree_width, &text_entree_height);

    // Init des maps
    Map map = init_map_dessin();
    init_taille_case_et_origine(&map);
    Map map_totale = copyMap(&map);

    int position_maison_ghosts[] = {map.position_maison_ghosts_x - 4,
                                    map.position_maison_ghosts_y,
                                    map.position_maison_ghosts_x + 5,
                                    map.position_maison_ghosts_y + 6};

    SDL_Color color_text = {255, 255, 255, 255};
    SDL_Color bgColor_text_descriptif = {50, 50, 50, 200};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color bt_color_texte = {255, 255, 255, 255};
    SDL_Color bt_color_base = {100, 100, 255, 255};
    SDL_Color bt_color_selected = {200, 100, 255, 255};
    SDL_Color bt_color_touch = {100, 200, 255, 255};
    SDL_Color color_bande_laterale_1 = {50, 100, 50, 255};
    SDL_Color color_bande_laterale_2 = {50, 50, 50, 255};
    SDL_Rect bande_laterale_gauche_1 = {FEN_X - TAILLE_BARRE_MENU_X, HEADER_HEIGHT, FEN_X - TAILLE_BARRE_MENU_X/2, FEN_Y};
    SDL_Rect bande_laterale_gauche_2 = {FEN_X - TAILLE_BARRE_MENU_X/2, HEADER_HEIGHT, FEN_X, FEN_Y};
    int cursorVisible = 1;
    Uint32 lastCursorToggle = SDL_GetTicks();
    int x_souris_px, y_souris_px, x_souris_cases, y_souris_cases;
    int is_en_cours_de_modif = 0;
    int is_souris_sur_map = 0;
    int is_grille_on = 1;
    int zoom = 0;
    int position_zoom_x = 0;
    int position_zoom_y = 0;
    int cercle_pointe_erreur_x = -1;
    int cercle_pointe_erreur_y = -1;
    int is_symetrie_verticale = 0;
    int is_symetrie_horizontale = 0;
    int pos_x, pos_y; //variables de calcul intermédiaire non important
    int is_enregistrement = 0;
    int is_modif_taille_map = 0;
    int running = 1;
    SDL_Event event;
    time_t current_time;

    while (running) {
        current_time = time(NULL);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        renderHeader(ren, "Créateur de Map");
        affiche_map(&map, tils, ren);
        if (is_enregistrement || is_modif_taille_map){
            color_bande_laterale_1.a = 100;
            bt_color_base.a = 100;
            bt_color_selected.a = 200;
        } else {
            color_bande_laterale_1.a = 255;
            bt_color_base.a = 255;
            bt_color_selected.a = 255;
        }
        SDL_SetRenderDrawColor(ren, color_bande_laterale_1.r, color_bande_laterale_1.g, color_bande_laterale_1.b, color_bande_laterale_1.a);
        SDL_RenderFillRect(ren, &bande_laterale_gauche_1);
        SDL_SetRenderDrawColor(ren, color_bande_laterale_2.r, color_bande_laterale_2.g, color_bande_laterale_2.b, color_bande_laterale_2.a);
        SDL_RenderFillRect(ren, &bande_laterale_gauche_2);
        affiche_boutons_createur_map(ren, buttons_selection_remplissage, buttons, is_symetrie_horizontale, is_symetrie_verticale, bt_color_texte, bt_color_touch, bt_color_base, bt_color_selected);
        if (is_enregistrement){
            if (SDL_GetTicks() - lastCursorToggle >= CURSOR_BLINK_TIME) {
                cursorVisible = !cursorVisible;
                lastCursorToggle = SDL_GetTicks();
            }
            snprintf(displayText, sizeof(displayText), "%s%s", text, cursorVisible ? "|" : " ");
            entree_text.label = displayText;
            renderButton(ren, &consigne_enregistrement, color_text, bgColor_text_descriptif, bgColor_text_descriptif);
            renderButton(ren, &entree_text, color_text, (SDL_Color){50, 50, 50, 200}, (SDL_Color){50, 50, 50, 200});
            renderButton(ren, &valider_enregistrement, color_text, (SDL_Color){0, 255, 0, 255}, (SDL_Color){0, 255, 0, 100});
            renderButton(ren, &annuler_enregistrement, color_text, (SDL_Color){255, 0, 0, 255}, (SDL_Color){255, 0, 0, 100});
        } else {
        if (is_modif_taille_map){
            if (SDL_GetTicks() - lastCursorToggle >= CURSOR_BLINK_TIME) {
                cursorVisible = !cursorVisible;
                lastCursorToggle = SDL_GetTicks();
            }
            // Texte affiché (ajoute un curseur clignotant)
            snprintf(displayWidth, sizeof(displayWidth), "%s%s", width_text, (is_typing_width && cursorVisible) ? "|" : " ");
            snprintf(displayHeight, sizeof(displayHeight), "%s%s", height_text, (!is_typing_width && cursorVisible) ? "|" : " ");
            // Afficher les champs de texte
            entree_width.label = displayWidth;
            entree_height.label = displayHeight;
            renderButton(ren, &entree_width, color_text, bgColor_text_descriptif, bgColor_text_descriptif);
            renderButton(ren, &entree_height, color_text, bgColor_text_descriptif, bgColor_text_descriptif);
            // Afficher les boutons
            renderButton(ren, &valider_taille_map, color_text, green, green);
            renderButton(ren, &annuler_taille_map, color_text, red, red);
            // Afficher les textes
            renderButton(ren, &consigne_modif_taille_map, color_text, bgColor_text_descriptif, bgColor_text_descriptif);
            renderButton(ren, &text_entree_height, color_text, bgColor_text_descriptif, bgColor_text_descriptif);
            renderButton(ren, &text_entree_width, color_text, bgColor_text_descriptif, bgColor_text_descriptif);

        } else {
            if (is_grille_on) {
                affiche_quadrillage(ren, &map);
            }
            if (is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
                if (cercle_pointe_erreur_x == x_souris_cases && cercle_pointe_erreur_y == y_souris_cases){
                    cercle_pointe_erreur_x = -1;
                    cercle_pointe_erreur_y = -1;
                }
                // Affichage du (ou des) carrées rouge(s) de placement/sélection de la souris
                SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                SDL_Rect rectangle_selection_map = {ORIGINE_X + x_souris_cases * map.taille_case, ORIGINE_Y + y_souris_cases * map.taille_case, map.taille_case, map.taille_case};
                SDL_RenderDrawRect(ren, &rectangle_selection_map);
                pos_x = map_totale.x - 1 - x_souris_cases - 2*position_zoom_x;
                pos_y = map_totale.y - 1 - y_souris_cases - 2*position_zoom_y;
                if (is_symetrie_verticale && pos_x < map.x && pos_x >= 0){
                    SDL_Rect rectangle_selection_map_2 = {ORIGINE_X + pos_x * map.taille_case, ORIGINE_Y + y_souris_cases * map.taille_case, map.taille_case, map.taille_case};
                    SDL_RenderDrawRect(ren, &rectangle_selection_map_2);
                }
                if (is_symetrie_horizontale && pos_y < map.y && pos_y >= 0){
                    SDL_Rect rectangle_selection_map_3 = {ORIGINE_X + x_souris_cases * map.taille_case, ORIGINE_Y + pos_y * map.taille_case, map.taille_case, map.taille_case};
                    SDL_RenderDrawRect(ren, &rectangle_selection_map_3);
                }
                if (is_symetrie_horizontale && pos_y < map.y && pos_y >= 0 && 
                    is_symetrie_verticale && pos_x < map.x && pos_x >= 0){
                    SDL_Rect rectangle_selection_map_4 = {ORIGINE_X + pos_x * map.taille_case, ORIGINE_Y + pos_y * map.taille_case, map.taille_case, map.taille_case};
                    SDL_RenderDrawRect(ren, &rectangle_selection_map_4);
                }
            }
            if (cercle_pointe_erreur_x >= 0 && cercle_pointe_erreur_y >= 0){
                SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                drawArc(ren, ORIGINE_X + cercle_pointe_erreur_x * map.taille_case + (int)(map.taille_case/2), ORIGINE_Y + cercle_pointe_erreur_y * map.taille_case + (int)(map.taille_case/2), map.taille_case, 0, 2*PI, 4, 100);
        }}}
        if (message.is_visible){
            if (current_time - start_time_message > message.temps_affichage){
                message.is_visible = 0;
            } else {
                renderButton(ren, &message.button_base, message.couleur_message, message.couleur_fond, message.couleur_fond);
            }
        }
            
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (is_enregistrement) {
                if (event.type == SDL_TEXTINPUT) {
                    if (strlen(text) < MAX_TEXT_LENGTH) {
                        strcat(text, event.text.text);
                    }
                }

                if (event.type == SDL_MOUSEMOTION) {
                    x_souris_px = event.motion.x;
                    y_souris_px = event.motion.y;

                    // Souris sur un bouton ?
                    if (is_souris_sur_button(annuler_enregistrement, x_souris_px, y_souris_px)) {
                        annuler_enregistrement.hovered = 1;
                    } else {
                        annuler_enregistrement.hovered = 0;
                    }
                    if (is_souris_sur_button(valider_enregistrement, x_souris_px, y_souris_px)) {
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
                        color_text.r = rand() % 256;
                        color_text.g = rand() % 256;
                        color_text.b = rand() % 256;
                    }
                }
            
                if (event.type == SDL_MOUSEBUTTONUP) {
                    if (is_souris_sur_button(annuler_enregistrement, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        is_enregistrement = 0;
                        SDL_StopTextInput();
                    }
                    if (is_souris_sur_button(valider_enregistrement, x_souris_px, y_souris_px)) {
                        if (strlen(text) <= 2) {
                            message.button_base.label = "Le nom de la map doit contenir plus de 2 caractères";
                            message.couleur_message = (SDL_Color){0, 0, 0, 255};
                            message.couleur_fond = (SDL_Color){255, 50, 0, 200};
                        } else {
                            int is_espace = 0;
                            for (int i = 0; i < strlen(text); i++){
                                if (text[i] == ' '){
                                    is_espace = 1;
                                }
                            }
                            if (is_espace) {
                                message.button_base.label = "Le nom de la map ne doit pas contenir d'espaces !";
                                message.couleur_message = (SDL_Color){0, 0, 0, 255};
                                message.couleur_fond = (SDL_Color){255, 50, 0, 200};
                            } else {
                                playSoundEffect(musique->select);
                                is_enregistrement = 0;
                                SDL_StopTextInput();
                                save_map_text(text, &map_totale);
                                //save_map_binary(text, &map_totale);
                                char texte[50];
                                snprintf(texte, sizeof(texte), "La map '%s' à bien été enregistrée", text);
                                message.button_base.label = texte;
                                message.couleur_message = (SDL_Color){255, 255, 255, 255};
                                message.couleur_fond = (SDL_Color){0, 255, 0, 150};
                            }
                        }
                        message.temps_affichage = 3;
                        message.is_visible = 1;
                        start_time_message = time(NULL);
                    }
                }
            
            } else {
            if (is_modif_taille_map){
                if (event.type == SDL_MOUSEMOTION) {
                    x_souris_px = event.motion.x;
                    y_souris_px = event.motion.y;

                    // Souris sur un bouton ?
                    if (is_souris_sur_button(annuler_taille_map, x_souris_px, y_souris_px)) {
                        annuler_taille_map.hovered = 1;
                    } else {
                        annuler_taille_map.hovered = 0;
                    }
                    if (is_souris_sur_button(valider_taille_map, x_souris_px, y_souris_px)) {
                        valider_taille_map.hovered = 1;
                    } else {
                        valider_taille_map.hovered = 0;
                    }
                }

                if (event.type == SDL_MOUSEBUTTONUP) {
                    // Vérifier si on clique sur un champ
                    if (is_souris_sur_button(entree_width, x_souris_px, y_souris_px)) {
                        is_typing_width = 1;
                    }
                    if (is_souris_sur_button(entree_height, x_souris_px, y_souris_px)) {
                        is_typing_width = 0;
                    }
            
                    // Vérifier si on clique sur "Valider"
                    if (is_souris_sur_button(valider_taille_map, x_souris_px, y_souris_px)) {
                        int width = atoi(width_text);
                        int height = atoi(height_text);
                        if (width >= TAILLE_MIN_MAP && width <= TAILLE_MAX_MAP && height >= TAILLE_MIN_MAP && height <= TAILLE_MAX_MAP) {
                            playSoundEffect(musique->select);
                            map_totale = modif_taille_map(&map_totale, width, height);
                            if (zoom > map_totale.x - ZOOM_MAX) {
                                zoom = map_totale.x - ZOOM_MAX;
                            }
                            if (zoom > map_totale.y - ZOOM_MAX) {
                                zoom = map_totale.y - ZOOM_MAX;
                            }
                            if (position_zoom_x + map.x > map_totale.x){
                                position_zoom_x = map_totale.x - map.x;
                                if (position_zoom_x < 0){
                                    position_zoom_x = 0;
                                }
                            }
                            if (position_zoom_y + map.y > map_totale.y){
                                position_zoom_y = map_totale.y - map.y;
                                if (position_zoom_y < 0){
                                    position_zoom_y = 0;
                                }
                            }
                            nouveau_zoom(&map, &map_totale, zoom, position_zoom_x, position_zoom_y);
                            message.button_base.label = "La map à bien été redimentionnée";
                            message.couleur_message = (SDL_Color){255, 255, 255, 255};
                            message.couleur_fond = (SDL_Color){0, 255, 0, 150};
                            is_modif_taille_map = 0;
                            SDL_StopTextInput();
                        } else {
                            char texte[100];
                            snprintf(texte, sizeof(texte), "Les dimentions doivent être entre %d et %d !", TAILLE_MIN_MAP, TAILLE_MAX_MAP);
                            message.button_base.label = texte;
                            message.couleur_message = (SDL_Color){0, 0, 0, 255};
                            message.couleur_fond = (SDL_Color){255, 50, 0, 200};
                        }
                        message.temps_affichage = 3;
                        message.is_visible = 1;
                        start_time_message = time(NULL);
                    }
            
                    // Vérifier si on clique sur "Annuler"
                    if (is_souris_sur_button(annuler_taille_map, x_souris_px, y_souris_px)) {
                        playSoundEffect(musique->select);
                        is_modif_taille_map = 0;
                        SDL_StopTextInput();
                    }
                }
            
                if (event.type == SDL_TEXTINPUT) {
                    char *target = is_typing_width ? width_text : height_text;
                    if (strlen(target) < MAX_NB_LENGTH && isdigit(event.text.text[0])) {
                        strcat(target, event.text.text);
                    }
                }
            
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        char *target = is_typing_width ? width_text : height_text;
                        if (strlen(target) > 0) {
                            target[strlen(target) - 1] = '\0';
                        }
                    }
                }
            
            } else {
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
                        modif_case(&map, &map_totale, x_souris_cases, y_souris_cases, zoom, position_zoom_x, position_zoom_y, is_symetrie_horizontale, is_symetrie_verticale);
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
                        //printf("zoom : %d, min_x : %d, min_y : %d\n", zoom, map.x - ZOOM_MAX, map.y - ZOOM_MAX);
                        if (zoom > map_totale.x - ZOOM_MAX || zoom > map_totale.y - ZOOM_MAX){
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
                        int is_ok = is_map_conforme(&map_totale, &cercle_pointe_erreur_x, &cercle_pointe_erreur_y);
                        if (is_ok){
                            playSoundEffect(musique->select);
                            is_enregistrement = 1;
                            text[0] = '\0';
                            SDL_StartTextInput();
                        } else {
                            message.button_base.label = "La map ne doit pas contenir de 'cul de sac' !";
                            message.couleur_message = (SDL_Color){0, 0, 0, 255};
                            message.couleur_fond = (SDL_Color){255, 100, 0, 200};
                            message.temps_affichage = 3;
                            message.is_visible = 1;
                            start_time_message = time(NULL);
                        }
                    }

                    if (is_souris_sur_button(button_modif_taille_map, x_souris_px, y_souris_px)){
                        playSoundEffect(musique->select);
                        is_modif_taille_map = 1;
                        SDL_StartTextInput();
                    }
                    
                    if (is_souris_sur_button(button_symetrie_horizontale, x_souris_px, y_souris_px)){
                        is_symetrie_horizontale = !is_symetrie_horizontale;
                    }
                    if (is_souris_sur_button(button_symetrie_verticale, x_souris_px, y_souris_px)){
                        is_symetrie_verticale = !is_symetrie_verticale;
                    }
                }

                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
                        is_en_cours_de_modif = 1;
                        modif_case(&map, &map_totale, x_souris_cases, y_souris_cases, zoom, position_zoom_x, position_zoom_y, is_symetrie_horizontale, is_symetrie_verticale);
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

            }
        }}
        updateDisplay(ren);
    }
    freeMap(&map);
    freeMap(&map_totale);
    free_tils(tils, 4);
    SDL_StopTextInput();
}
