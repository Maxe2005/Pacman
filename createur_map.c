#include "createur_map.h"

SelectionType_createur_map selection_en_cours_createur_map = SELECTION_NULL;


void init_buttons_createur_map (Session_modif_map* session){
    // Allouer de la mémoire pour les boutons de sélection de remplissage
    
    for (int k = 0; k < NB_BUTTONS; k++) {
        session->buttons[k] = malloc(sizeof(Button));
    }

    // Allouer de la mémoire pour les autres boutons
    session->button_modif_taille_map = malloc(sizeof(Button));
    session->button_grille = malloc(sizeof(Button));
    session->button_enregistrer = malloc(sizeof(Button));
    session->button_zoom_plus = malloc(sizeof(Button));
    session->button_zoom_moins = malloc(sizeof(Button));
    session->button_symetrie_verticale = malloc(sizeof(Button));
    session->button_symetrie_horizontale = malloc(sizeof(Button));

    // Les boutons de selection de mode de remplissage :
    int button_margin_y = (3*(FEN_Y - HEADER_HEIGHT)/4 - NB_BUTTONS_SELECTION_REMPLISSAGE * session->button_height)/NB_BUTTONS_SELECTION_REMPLISSAGE;
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        session->buttons_selection_remplissage[i] = malloc(sizeof(SelectionButton_createur_map));
        session->buttons_selection_remplissage[i]->button_base.rect.x = FEN_X - TAILLE_BARRE_MENU_X + (TAILLE_BARRE_MENU_X/2 - session->button_width)/2;
        session->buttons_selection_remplissage[i]->button_base.rect.y = HEADER_HEIGHT + button_margin_y/2 + i * (session->button_height + button_margin_y);
        session->buttons_selection_remplissage[i]->button_base.rect.w = session->button_width;
        session->buttons_selection_remplissage[i]->button_base.rect.h = session->button_height;
        session->buttons_selection_remplissage[i]->button_base.hovered = 0;
        session->buttons[i] = &(session->buttons_selection_remplissage[i]->button_base);
    }
    session->buttons_selection_remplissage[0]->type = SELECTION_VIDE_INTERNE;
    session->buttons_selection_remplissage[0]->button_base.label = "Vide Interne";
    session->buttons_selection_remplissage[1]->type = SELECTION_VIDE_EXTERNE;
    session->buttons_selection_remplissage[1]->button_base.label = "Vide Externe";
    session->buttons_selection_remplissage[2]->type = SELECTION_MUR;
    session->buttons_selection_remplissage[2]->button_base.label = "Mur";
    session->buttons_selection_remplissage[3]->type = SELECTION_GUM;
    session->buttons_selection_remplissage[3]->button_base.label = "Gum";
    session->buttons_selection_remplissage[4]->type = SELECTION_BIG_GUM;
    session->buttons_selection_remplissage[4]->button_base.label = "Big Gum";

    // Le bouton enregistrer :
    session->button_enregistrer->rect.x = FEN_X - TAILLE_BARRE_MENU_X + (TAILLE_BARRE_MENU_X/2 - session->button_width)/2;
    session->button_enregistrer->rect.y = FEN_Y - 2*session->button_height;
    session->button_enregistrer->rect.w = session->button_width;
    session->button_enregistrer->rect.h = session->button_height;
    session->button_enregistrer->hovered = 0;
    session->button_enregistrer->label = "Enregistrer";
    session->buttons[NB_BUTTONS_SELECTION_REMPLISSAGE] = session->button_enregistrer;

    // Les autres boutons :
    button_margin_y = ((FEN_Y - HEADER_HEIGHT) - (NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE - 1) * session->button_height)/(NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE - 1);
    Button* but[] = {session->button_modif_taille_map, session->button_grille, session->button_zoom_plus, session->button_zoom_moins, session->button_symetrie_verticale, session->button_symetrie_horizontale};
    char* noms[] = {"Modif taille", "Grille", "Zoom +", "Zoom -", "Sym. verti.", "Sym. horiz."};
    for (int j = 0; j < NB_BUTTONS - NB_BUTTONS_SELECTION_REMPLISSAGE - 1; j++){
        but[j]->rect.x = FEN_X - TAILLE_BARRE_MENU_X/2 + (TAILLE_BARRE_MENU_X/2 - session->button_width)/2;
        but[j]->rect.y = HEADER_HEIGHT + button_margin_y/2 + j * (session->button_height + button_margin_y);
        but[j]->rect.w = session->button_width;
        but[j]->rect.h = session->button_height;
        but[j]->hovered = 0;
        but[j]->label = noms[j];
        session->buttons[NB_BUTTONS_SELECTION_REMPLISSAGE + 1 + j] = but[j];
    }
}

void affiche_boutons_createur_map (SDL_Renderer* ren, SelectionButton_createur_map* boutons_selection[NB_BUTTONS_SELECTION_REMPLISSAGE], Button* boutons[NB_BUTTONS], Session_modif_map* session){
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        if (selection_en_cours_createur_map == boutons_selection[i]->type) {
            renderButton(ren, &(boutons_selection[i]->button_base), session->color->bt_texte, session->color->bt_selected, session->color->bt_touch);
        } else {
            renderButton(ren, &(boutons_selection[i]->button_base), session->color->bt_texte, session->color->bt_base, session->color->bt_touch);
        }
    }
    for (int j = NB_BUTTONS_SELECTION_REMPLISSAGE; j < NB_BUTTONS-2; j++){
        renderButton(ren, boutons[j], session->color->bt_texte, session->color->bt_base, session->color->bt_touch);
    }
    // Bouton symétrie verticale
    if (session->is_symetrie_verticale) {
        renderButton(ren, boutons[NB_BUTTONS-2], session->color->bt_texte, session->color->bt_selected, session->color->bt_touch);
    } else {
        renderButton(ren, boutons[NB_BUTTONS-2], session->color->bt_texte, session->color->bt_base, session->color->bt_touch);
    }
    // Bouton symétrie horizontale
    if (session->is_symetrie_horizontale) {
        renderButton(ren, boutons[NB_BUTTONS-1], session->color->bt_texte, session->color->bt_selected, session->color->bt_touch);
    } else {
        renderButton(ren, boutons[NB_BUTTONS-1], session->color->bt_texte, session->color->bt_base, session->color->bt_touch);
    }
}

void clic_souris (int x, int y, SelectionButton_createur_map* selections[NB_BUTTONS_SELECTION_REMPLISSAGE], Musique* musique){
    // Vérifier si un bouton de sélection de catégorie est cliqué
    for (int i = 0; i < NB_BUTTONS_SELECTION_REMPLISSAGE; i++) {
        if (x >= selections[i]->button_base.rect.x && x <= selections[i]->button_base.rect.x + selections[i]->button_base.rect.w &&
            y >= selections[i]->button_base.rect.y && y <= selections[i]->button_base.rect.y + selections[i]->button_base.rect.h) {
                
                playSoundEffect(musique->select);
                if (selection_en_cours_createur_map == selections[i]->type) {
                    selection_en_cours_createur_map = SELECTION_NULL;
                } else {
                    selection_en_cours_createur_map = selections[i]->type;
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

void init_boutons_enregistrer (Sous_menu_enregistrement* sous_menu_enregistrement){
    int button_height = 50;
    int button_width = 210;

    sous_menu_enregistrement->entree_text = malloc(sizeof(Button));
    sous_menu_enregistrement->consigne = malloc(sizeof(Button));
    sous_menu_enregistrement->annuler = malloc(sizeof(Button));
    sous_menu_enregistrement->valider = malloc(sizeof(Button));

    sous_menu_enregistrement->entree_text->rect.w = 400;
    sous_menu_enregistrement->entree_text->rect.h = 200;
    sous_menu_enregistrement->entree_text->rect.x = (FEN_X - sous_menu_enregistrement->entree_text->rect.w)/2;
    sous_menu_enregistrement->entree_text->rect.y = (FEN_Y - sous_menu_enregistrement->entree_text->rect.h)/2;
    sous_menu_enregistrement->entree_text->hovered = 1;

    sous_menu_enregistrement->consigne->rect.w = 500;
    sous_menu_enregistrement->consigne->rect.h = 75;
    sous_menu_enregistrement->consigne->rect.x = (FEN_X - sous_menu_enregistrement->consigne->rect.w)/2;
    sous_menu_enregistrement->consigne->rect.y = sous_menu_enregistrement->entree_text->rect.y - sous_menu_enregistrement->consigne->rect.h - 50;
    sous_menu_enregistrement->consigne->hovered = 0;
    sous_menu_enregistrement->consigne->label = "Entrez le nom de la map :";

    sous_menu_enregistrement->annuler->rect.x = FEN_X/2 - 20 - button_width;
    sous_menu_enregistrement->annuler->rect.y = sous_menu_enregistrement->entree_text->rect.y + sous_menu_enregistrement->entree_text->rect.h + 50;
    sous_menu_enregistrement->annuler->rect.w = button_width;
    sous_menu_enregistrement->annuler->rect.h = button_height;
    sous_menu_enregistrement->annuler->hovered = 0;
    sous_menu_enregistrement->annuler->label = "Annuler";

    sous_menu_enregistrement->valider->rect.x = FEN_X/2 + 20;
    sous_menu_enregistrement->valider->rect.y = sous_menu_enregistrement-> entree_text->rect.y + sous_menu_enregistrement->entree_text->rect.h + 50;
    sous_menu_enregistrement->valider->rect.w = button_width;
    sous_menu_enregistrement->valider->rect.h = button_height;
    sous_menu_enregistrement->valider->hovered = 0;
    sous_menu_enregistrement->valider->label = "Valider";
}

void init_boutons_modif_taille_map (Sous_menu_modif_taille_map* sous_menu_modif_taille_map){
    int button_height = 50;
    int button_width = 210;
    int taille_saisie_x = 200;
    int taille_saisie_y = 50;
    int taille_text_x = 350;
    int taille_text_y = 100;
    int ecart_entre_saisies = 120;
    int ecart_entre_bt_valider_et_annuler = 50;
    int ecart_entre_saisies_et_bts = 200;
    int ecart_entre_saisies_et_def = 80;

    sous_menu_modif_taille_map->entree_width = malloc(sizeof(Button));
    sous_menu_modif_taille_map->entree_height = malloc(sizeof(Button));
    sous_menu_modif_taille_map->text_entree_width = malloc(sizeof(Button));
    sous_menu_modif_taille_map->text_entree_height = malloc(sizeof(Button));
    sous_menu_modif_taille_map->consigne = malloc(sizeof(Button));
    sous_menu_modif_taille_map->annuler = malloc(sizeof(Button));
    sous_menu_modif_taille_map->valider = malloc(sizeof(Button));

    // Position des champs de saisie
    sous_menu_modif_taille_map->entree_width->rect.w = taille_saisie_x;
    sous_menu_modif_taille_map->entree_width->rect.h = taille_saisie_y;
    sous_menu_modif_taille_map->entree_width->rect.x = (FEN_X + ecart_entre_saisies_et_def)/2;
    sous_menu_modif_taille_map->entree_width->rect.y = (FEN_Y - sous_menu_modif_taille_map->entree_width->rect.h - ecart_entre_saisies)/2;
    sous_menu_modif_taille_map->entree_width->hovered = 0;

    sous_menu_modif_taille_map->entree_height->rect.w = taille_saisie_x;
    sous_menu_modif_taille_map->entree_height->rect.h = taille_saisie_y;
    sous_menu_modif_taille_map->entree_height->rect.x = (FEN_X + ecart_entre_saisies_et_def)/2;
    sous_menu_modif_taille_map->entree_height->rect.y = (FEN_Y + ecart_entre_saisies - sous_menu_modif_taille_map->entree_width->rect.h)/2;
    sous_menu_modif_taille_map->entree_height->hovered = 0;

    // Position des textes de définition des champs de saisie
    sous_menu_modif_taille_map->text_entree_width->rect.w = taille_text_x;
    sous_menu_modif_taille_map->text_entree_width->rect.h = taille_text_y;
    sous_menu_modif_taille_map->text_entree_width->rect.x = FEN_X/2 - sous_menu_modif_taille_map->text_entree_width->rect.w - ecart_entre_saisies_et_def/2;
    sous_menu_modif_taille_map->text_entree_width->rect.y = (FEN_Y - sous_menu_modif_taille_map->text_entree_width->rect.h - ecart_entre_saisies)/2;
    sous_menu_modif_taille_map->text_entree_width->hovered = 0;
    sous_menu_modif_taille_map->text_entree_width->label = "Nombre de colones :";

    sous_menu_modif_taille_map->text_entree_height->rect.w = taille_text_x;
    sous_menu_modif_taille_map->text_entree_height->rect.h = taille_text_y;
    sous_menu_modif_taille_map->text_entree_height->rect.x = FEN_X/2 - sous_menu_modif_taille_map->text_entree_height->rect.w - ecart_entre_saisies_et_def/2;
    sous_menu_modif_taille_map->text_entree_height->rect.y = (FEN_Y + ecart_entre_saisies - sous_menu_modif_taille_map->text_entree_height->rect.h)/2;
    sous_menu_modif_taille_map->text_entree_height->hovered = 0;
    sous_menu_modif_taille_map->text_entree_height->label = "Nombre de lignes :";

    // Texte de consigne
    sous_menu_modif_taille_map->consigne->rect.w = 800;
    sous_menu_modif_taille_map->consigne->rect.h = 75;
    sous_menu_modif_taille_map->consigne->rect.x = (FEN_X - sous_menu_modif_taille_map->consigne->rect.w)/2;
    sous_menu_modif_taille_map->consigne->rect.y = sous_menu_modif_taille_map->entree_width->rect.y - sous_menu_modif_taille_map->consigne->rect.h - 50;
    sous_menu_modif_taille_map->consigne->hovered = 0;
    sous_menu_modif_taille_map->consigne->label = "Entrez les nouvelles dimentions de la map :";

    // Boutons valider et annuler
    sous_menu_modif_taille_map->valider->rect.w = button_width;
    sous_menu_modif_taille_map->valider->rect.h = button_height;
    sous_menu_modif_taille_map->valider->rect.x = FEN_X/2 - button_width - ecart_entre_bt_valider_et_annuler/2;
    sous_menu_modif_taille_map->valider->rect.y = sous_menu_modif_taille_map->entree_height->rect.y + (sous_menu_modif_taille_map->entree_height->rect.h + ecart_entre_saisies_et_bts - sous_menu_modif_taille_map->valider->rect.h)/2;
    sous_menu_modif_taille_map->valider->label = "Valider";
    sous_menu_modif_taille_map->valider->hovered = 0;

    sous_menu_modif_taille_map->annuler->rect.w = button_width;
    sous_menu_modif_taille_map->annuler->rect.h = button_height;
    sous_menu_modif_taille_map->annuler->rect.x = FEN_X/2 + ecart_entre_bt_valider_et_annuler/2;
    sous_menu_modif_taille_map->annuler->rect.y = sous_menu_modif_taille_map->entree_height->rect.y + (sous_menu_modif_taille_map->entree_height->rect.h + ecart_entre_saisies_et_bts - sous_menu_modif_taille_map->annuler->rect.h)/2;
    sous_menu_modif_taille_map->annuler->label = "Annuler";
    sous_menu_modif_taille_map->annuler->hovered = 0;
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

void init_couleurs_session (Session_modif_map* session){
    SDL_Color text = {255, 255, 255, 255};
    SDL_Color bg_text_descriptif = {50, 50, 50, 200};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color light_green = {0, 255, 0, 100};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color light_red = {255, 0, 0, 100};
    SDL_Color bt_texte = {255, 255, 255, 255};
    SDL_Color bt_base = {100, 100, 255, 255};
    SDL_Color bt_selected = {200, 100, 255, 255};
    SDL_Color bt_touch = {100, 200, 255, 255};
    SDL_Color bande_laterale_1 = {50, 100, 50, 255};
    SDL_Color bande_laterale_2 = {50, 50, 50, 255};

    session->color->text = text;
    session->color->bg_text_descriptif = bg_text_descriptif;
    session->color->green = green;
    session->color->light_green = light_green;
    session->color->red = red;
    session->color->light_red = light_red;
    session->color->bt_texte = bt_texte;
    session->color->bt_base = bt_base;
    session->color->bt_selected = bt_selected;
    session->color->bt_touch = bt_touch;
    session->color->bande_laterale_1 = bande_laterale_1;
    session->color->bande_laterale_2 = bande_laterale_2;
}

void affiche_interface_createur_map(SDL_Renderer* ren, Session_modif_map* session, time_t current_time) {
    int pos_x, pos_y; //variables de calcul intermédiaire non important
    
    SDL_Rect bande_laterale_gauche_1 = {FEN_X - TAILLE_BARRE_MENU_X, HEADER_HEIGHT, FEN_X - TAILLE_BARRE_MENU_X/2, FEN_Y};
    SDL_Rect bande_laterale_gauche_2 = {FEN_X - TAILLE_BARRE_MENU_X/2, HEADER_HEIGHT, FEN_X, FEN_Y};

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    renderHeader(ren, "Créateur de Map");
    affiche_map(session->map, session->tils, ren);
    if (session->is_enregistrement || session->is_modif_taille_map){
        session->color->bande_laterale_1.a = 100;
        session->color->bt_base.a = 100;
        session->color->bt_selected.a = 200;
    } else {
        session->color->bande_laterale_1.a = 255;
        session->color->bt_base.a = 255;
        session->color->bt_selected.a = 255;
    }
    SDL_SetRenderDrawColor(ren, session->color->bande_laterale_1.r, session->color->bande_laterale_1.g, session->color->bande_laterale_1.b, session->color->bande_laterale_1.a);
    SDL_RenderFillRect(ren, &bande_laterale_gauche_1);
    SDL_SetRenderDrawColor(ren, session->color->bande_laterale_2.r, session->color->bande_laterale_2.g, session->color->bande_laterale_2.b, session->color->bande_laterale_2.a);
    SDL_RenderFillRect(ren, &bande_laterale_gauche_2);
    affiche_boutons_createur_map(ren, session->buttons_selection_remplissage, session->buttons, session);
    if (session->is_enregistrement){
        if (SDL_GetTicks() - session->sous_menu_enregistrement->lastCursorToggle >= CURSOR_BLINK_TIME) {
            session->sous_menu_enregistrement->cursorVisible = !session->sous_menu_enregistrement->cursorVisible;
            session->sous_menu_enregistrement->lastCursorToggle = SDL_GetTicks();
        }
        snprintf(session->sous_menu_enregistrement->displayText, sizeof(session->sous_menu_enregistrement->displayText), "%s%s", session->sous_menu_enregistrement->text, session->sous_menu_enregistrement->cursorVisible ? "|" : " ");
        session->sous_menu_enregistrement->entree_text->label = session->sous_menu_enregistrement->displayText;
        renderButton(ren, session->sous_menu_enregistrement->consigne, session->color->text, session->color->bg_text_descriptif, session->color->bg_text_descriptif);
        renderButton(ren, session->sous_menu_enregistrement->entree_text, session->color->text, session->color->bg_text_descriptif, session->color->bg_text_descriptif);
        renderButton(ren, session->sous_menu_enregistrement->valider, session->color->text, session->color->green, session->color->light_green);
        renderButton(ren, session->sous_menu_enregistrement->annuler, session->color->text, session->color->red, session->color->light_red);
    } else {
    if (session->is_modif_taille_map){
        if (SDL_GetTicks() - session->sous_menu_modif_taille_map->lastCursorToggle >= CURSOR_BLINK_TIME) {
            session->sous_menu_modif_taille_map->cursorVisible = !session->sous_menu_modif_taille_map->cursorVisible;
            session->sous_menu_modif_taille_map->lastCursorToggle = SDL_GetTicks();
        }
        // Texte affiché (ajoute un curseur clignotant)
        snprintf(session->sous_menu_modif_taille_map->displayWidth, sizeof(session->sous_menu_modif_taille_map->displayWidth), "%s%s", session->sous_menu_modif_taille_map->width_text, (session->sous_menu_modif_taille_map->is_typing_width && session->sous_menu_modif_taille_map->cursorVisible) ? "|" : " ");
        snprintf(session->sous_menu_modif_taille_map->displayHeight, sizeof(session->sous_menu_modif_taille_map->displayHeight), "%s%s", session->sous_menu_modif_taille_map->height_text, (!session->sous_menu_modif_taille_map->is_typing_width && session->sous_menu_modif_taille_map->cursorVisible) ? "|" : " ");
        // Afficher les champs de texte
        session->sous_menu_modif_taille_map->entree_width->label = session->sous_menu_modif_taille_map->displayWidth;
        session->sous_menu_modif_taille_map->entree_height->label = session->sous_menu_modif_taille_map->displayHeight;
        renderButton(ren, session->sous_menu_modif_taille_map->entree_width, session->color->text, session->color->bg_text_descriptif, session->color->bg_text_descriptif);
        renderButton(ren, session->sous_menu_modif_taille_map->entree_height, session->color->text, session->color->bg_text_descriptif, session->color->bg_text_descriptif);
        // Afficher les boutons
        renderButton(ren, session->sous_menu_modif_taille_map->valider, session->color->text, session->color->green, session->color->light_green);
        renderButton(ren, session->sous_menu_modif_taille_map->annuler, session->color->text, session->color->red, session->color->light_red);
        // Afficher les textes
        renderButton(ren, session->sous_menu_modif_taille_map->consigne, session->color->text, session->color->bg_text_descriptif, session->color->bg_text_descriptif);
        renderButton(ren, session->sous_menu_modif_taille_map->text_entree_height, session->color->text, session->color->bg_text_descriptif, session->color->bg_text_descriptif);
        renderButton(ren, session->sous_menu_modif_taille_map->text_entree_width, session->color->text, session->color->bg_text_descriptif, session->color->bg_text_descriptif);

    } else {
        if (session->is_grille_on) {
            affiche_quadrillage(ren, session->map);
        }
        if (session->is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
            if (session->cercle_pointe_erreur_x == session->x_souris_cases && session->cercle_pointe_erreur_y == session->y_souris_cases){
                session->cercle_pointe_erreur_x = -1;
                session->cercle_pointe_erreur_y = -1;
            }
            // Affichage du (ou des) carrées rouge(s) de placement/sélection de la souris
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            SDL_Rect rectangle_selection_map = {ORIGINE_X + session->x_souris_cases * session->map->taille_case, ORIGINE_Y + session->y_souris_cases * session->map->taille_case, session->map->taille_case, session->map->taille_case};
            SDL_RenderDrawRect(ren, &rectangle_selection_map);
            pos_x = session->map_totale->x - 1 - session->x_souris_cases - 2*session->position_zoom_x;
            pos_y = session->map_totale->y - 1 - session->y_souris_cases - 2*session->position_zoom_y;
            if (session->is_symetrie_verticale && pos_x < session->map->x && pos_x >= 0){
                SDL_Rect rectangle_selection_map_2 = {ORIGINE_X + pos_x * session->map->taille_case, ORIGINE_Y + session->y_souris_cases * session->map->taille_case, session->map->taille_case, session->map->taille_case};
                SDL_RenderDrawRect(ren, &rectangle_selection_map_2);
            }
            if (session->is_symetrie_horizontale && pos_y < session->map->y && pos_y >= 0){
                SDL_Rect rectangle_selection_map_3 = {ORIGINE_X + session->x_souris_cases * session->map->taille_case, ORIGINE_Y + pos_y * session->map->taille_case, session->map->taille_case, session->map->taille_case};
                SDL_RenderDrawRect(ren, &rectangle_selection_map_3);
            }
            if (session->is_symetrie_horizontale && pos_y < session->map->y && pos_y >= 0 && 
                session->is_symetrie_verticale && pos_x < session->map->x && pos_x >= 0){
                SDL_Rect rectangle_selection_map_4 = {ORIGINE_X + pos_x * session->map->taille_case, ORIGINE_Y + pos_y * session->map->taille_case, session->map->taille_case, session->map->taille_case};
                SDL_RenderDrawRect(ren, &rectangle_selection_map_4);
            }
        }
        if (session->cercle_pointe_erreur_x >= 0 && session->cercle_pointe_erreur_y >= 0){
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            drawArc(ren, ORIGINE_X + session->cercle_pointe_erreur_x * session->map->taille_case + (int)(session->map->taille_case/2), ORIGINE_Y + session->cercle_pointe_erreur_y * session->map->taille_case + (int)(session->map->taille_case/2), session->map->taille_case, 0, 2*PI, 4, 100);
    }}}
    if (session->message->is_visible){
        if (current_time - session->message->start_time > session->message->temps_affichage){
            session->message->is_visible = 0;
        } else {
            renderButton(ren, &session->message->button_base, session->message->couleur_message, session->message->couleur_fond, session->message->couleur_fond);
        }
    }
}

void handle_events_createur_map(SDL_Event event, Session_modif_map* session, int* running, Musique* musique, SDL_Renderer* ren) {
    if (event.type == SDL_MOUSEMOTION) {
        session->x_souris_px = event.motion.x;
        session->y_souris_px = event.motion.y;

        // Souris sur un bouton ?
        for (int i = 0; i < NB_BUTTONS; i++) {
            if (is_souris_sur_button(*session->buttons[i], session->x_souris_px, session->y_souris_px)) {
                session->buttons[i]->hovered = 1;
            } else {
                session->buttons[i]->hovered = 0;
            }
        }
        
        // Souris sur la map ?
        if (session->x_souris_px >= ORIGINE_X && session->x_souris_px <= ORIGINE_X + session->map->x * session->map->taille_case &&
            session->y_souris_px >= ORIGINE_Y && session->y_souris_px <= ORIGINE_Y + session->map->y * session->map->taille_case) {
                session->x_souris_cases = (session->x_souris_px - ORIGINE_X)/session->map->taille_case;
                session->y_souris_cases = (session->y_souris_px - ORIGINE_Y)/session->map->taille_case;
                // Souris pas dans la maison des fantômes
                if (session->x_souris_cases >= session->position_maison_ghosts[0] - session->position_zoom_x && session->x_souris_cases <= session->position_maison_ghosts[2] - session->position_zoom_x &&
                    session->y_souris_cases >= session->position_maison_ghosts[1] - session->position_zoom_y && session->y_souris_cases <= session->position_maison_ghosts[3] - session->position_zoom_y){
                        session->is_souris_sur_map = 0;
                        session->is_en_cours_de_modif = 0; // Arrête la modification à la chaine
                }
                else {
                    session->is_souris_sur_map = 1;
                }
        }
        else {
            session->is_souris_sur_map = 0;
        }

        // Map en cours de modif ? <=> souris pressée sur une case <=> modification à la chaine
        if (session->is_en_cours_de_modif){
            modif_case(session->map, session->map_totale, session->x_souris_cases, session->y_souris_cases, session->zoom, session->position_zoom_x, session->position_zoom_y, session->is_symetrie_horizontale, session->is_symetrie_verticale);
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        clic_souris(session->x_souris_px, session->y_souris_px, session->buttons_selection_remplissage, musique);
        session->is_en_cours_de_modif = 0; // Arrête la modification à la chaine

        if (is_souris_sur_button(*session->button_grille, session->x_souris_px, session->y_souris_px)) {
            playSoundEffect(musique->select);
            if (session->is_grille_on) {
                session->is_grille_on = 0;
            } else {
                session->is_grille_on = 1;
            }
        }

        if (is_souris_sur_button(*session->button_zoom_plus, session->x_souris_px, session->y_souris_px)) {
            playSoundEffect(musique->select);
            session->zoom += VITESSE_ZOOM;
            if (session->zoom > session->map_totale->x - ZOOM_MAX || session->zoom > session->map_totale->y - ZOOM_MAX){
                session->zoom -= VITESSE_ZOOM;
            } else {
                nouveau_zoom(session->map, session->map_totale, session->zoom, session->position_zoom_x, session->position_zoom_y);
            }
        }
        if (is_souris_sur_button(*session->button_zoom_moins, session->x_souris_px, session->y_souris_px)) {
            playSoundEffect(musique->select);
            session->zoom -= VITESSE_ZOOM;
            if (session->zoom < 0){
                session->zoom = 0;
            } else {
                if (session->position_zoom_x > session->zoom){
                    session->position_zoom_x = session->zoom;
                }
                if (session->position_zoom_y > session->zoom){
                    session->position_zoom_y = session->zoom;
                }
                nouveau_zoom(session->map, session->map_totale, session->zoom, session->position_zoom_x, session->position_zoom_y);
            }
        }

        if (is_souris_sur_button(*session->button_enregistrer, session->x_souris_px, session->y_souris_px)) {
            int is_ok = is_map_conforme(session->map_totale, &session->cercle_pointe_erreur_x, &session->cercle_pointe_erreur_y);
            if (is_ok){
                playSoundEffect(musique->select);
                session->is_enregistrement = 1;
                session->sous_menu_enregistrement->text[0] = '\0';
                SDL_StartTextInput();
            } else {
                session->message->button_base.label = "La map ne doit pas contenir de 'cul de sac' !";
                session->message->couleur_message = (SDL_Color){0, 0, 0, 255};
                session->message->couleur_fond = (SDL_Color){255, 100, 0, 200};
                session->message->temps_affichage = 3;
                session->message->is_visible = 1;
                session->message->start_time = time(NULL);
            }
        }

        if (is_souris_sur_button(*session->button_modif_taille_map, session->x_souris_px, session->y_souris_px)){
            playSoundEffect(musique->select);
            session->is_modif_taille_map = 1;
            SDL_StartTextInput();
        }
        
        if (is_souris_sur_button(*session->button_symetrie_horizontale, session->x_souris_px, session->y_souris_px)){
            session->is_symetrie_horizontale = !session->is_symetrie_horizontale;
        }
        if (is_souris_sur_button(*session->button_symetrie_verticale, session->x_souris_px, session->y_souris_px)){
            session->is_symetrie_verticale = !session->is_symetrie_verticale;
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (session->is_souris_sur_map && selection_en_cours_createur_map != SELECTION_NULL){
            session->is_en_cours_de_modif = 1;
            modif_case(session->map, session->map_totale, session->x_souris_cases, session->y_souris_cases, session->zoom, session->position_zoom_x, session->position_zoom_y, session->is_symetrie_horizontale, session->is_symetrie_verticale);
        }
    }

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT){
            session->position_zoom_x -= VITESSE_MOVE_ZOOM;
            if (session->position_zoom_x < 0){
                session->position_zoom_x = 0;
            } else {
                nouveau_zoom(session->map, session->map_totale, session->zoom, session->position_zoom_x, session->position_zoom_y);
            }
        }
        if (event.key.keysym.sym == SDLK_RIGHT){
            session->position_zoom_x += VITESSE_MOVE_ZOOM;
            if (session->position_zoom_x + session->map->x > session->map_totale->x){
                session->position_zoom_x = session->map_totale->x - session->map->x;
            } else {
                nouveau_zoom(session->map, session->map_totale, session->zoom, session->position_zoom_x, session->position_zoom_y);
            }
        }
        if (event.key.keysym.sym == SDLK_UP){
            session->position_zoom_y -= VITESSE_MOVE_ZOOM;
            if (session->position_zoom_y < 0){
                session->position_zoom_y = 0;
            } else {
                nouveau_zoom(session->map, session->map_totale, session->zoom, session->position_zoom_x, session->position_zoom_y);
            }
        }
        if (event.key.keysym.sym == SDLK_DOWN){
            session->position_zoom_y += VITESSE_MOVE_ZOOM;
            if (session->position_zoom_y + session->map->y > session->map_totale->y){
                session->position_zoom_y = session->map_totale->y - session->map->y;
            } else {
                nouveau_zoom(session->map, session->map_totale, session->zoom, session->position_zoom_x, session->position_zoom_y);
            }
        }
    }

    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_BACKSPACE){
            playSoundEffect(musique->select);
            SDL_StopTextInput();
            ecran_acceuil(ren, musique);
            *running = 0;
        }
    }

}

void handle_events_enregistrement(SDL_Event event, Session_modif_map* session, Musique* musique) {
    if (event.type == SDL_TEXTINPUT) {
        if (strlen(session->sous_menu_enregistrement->text) < MAX_TEXT_LENGTH) {
            strcat(session->sous_menu_enregistrement->text, event.text.text);
        }
    }

    if (event.type == SDL_MOUSEMOTION) {
        session->x_souris_px = event.motion.x;
        session->y_souris_px = event.motion.y;

        // Souris sur un bouton ?
        if (is_souris_sur_button(*session->sous_menu_enregistrement->annuler, session->x_souris_px, session->y_souris_px)) {
            session->sous_menu_enregistrement->annuler->hovered = 1;
        } else {
            session->sous_menu_enregistrement->annuler->hovered = 0;
        }
        if (is_souris_sur_button(*session->sous_menu_enregistrement->valider, session->x_souris_px, session->y_souris_px)) {
            session->sous_menu_enregistrement->valider->hovered = 1;
        } else {
            session->sous_menu_enregistrement->valider->hovered = 0;
        }

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (is_souris_sur_button(*session->button_grille, session->x_souris_px, session->y_souris_px)) {
            playSoundEffect(musique->select);
            if (session->is_grille_on) {
                session->is_grille_on = 0;
            } else {
                session->is_grille_on = 1;
            }
        }
    }
}

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(session->sous_menu_enregistrement->text) > 0) {
            session->sous_menu_enregistrement->text[strlen(session->sous_menu_enregistrement->text) - 1] = '\0';
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (is_souris_sur_button(*session->sous_menu_enregistrement->annuler, session->x_souris_px, session->y_souris_px)) {
            playSoundEffect(musique->select);
            session->is_enregistrement = 0;
            SDL_StopTextInput();
        }
        if (is_souris_sur_button(*session->sous_menu_enregistrement->valider, session->x_souris_px, session->y_souris_px)) {
            if (strlen(session->sous_menu_enregistrement->text) <= 2) {
                session->message->button_base.label = "Le nom de la map doit contenir plus de 2 caractères";
                session->message->couleur_message = (SDL_Color){0, 0, 0, 255};
                session->message->couleur_fond = (SDL_Color){255, 50, 0, 200};
            } else {
                int is_espace = 0;
                for (int i = 0; i < strlen(session->sous_menu_enregistrement->text); i++){
                    if (session->sous_menu_enregistrement->text[i] == ' '){
                        is_espace = 1;
                    }
                }
                if (is_espace) {
                    session->message->button_base.label = "Le nom de la map ne doit pas contenir d'espaces !";
                    session->message->couleur_message = (SDL_Color){0, 0, 0, 255};
                    session->message->couleur_fond = (SDL_Color){255, 50, 0, 200};
                } else {
                    playSoundEffect(musique->select);
                    session->is_enregistrement = 0;
                    SDL_StopTextInput();
                    save_map_text(session->sous_menu_enregistrement->text, session->map_totale);
                    //save_map_binary(text, &map_totale);
                    char texte[50];
                    snprintf(texte, sizeof(texte), "La map '%s' à bien été enregistrée", session->sous_menu_enregistrement->text);
                    session->message->button_base.label = texte;
                    session->message->couleur_message = (SDL_Color){255, 255, 255, 255};
                    session->message->couleur_fond = (SDL_Color){0, 255, 0, 150};
                }
            }
            session->message->temps_affichage = 3;
            session->message->is_visible = 1;
            session->message->start_time = time(NULL);
        }
    }
}

void handle_events_modif_taille_map(SDL_Event event, Session_modif_map* session, Musique* musique) {
    if (event.type == SDL_MOUSEMOTION) {
        session->x_souris_px = event.motion.x;
        session->y_souris_px = event.motion.y;

        // Souris sur un bouton ?
        if (is_souris_sur_button(*session->sous_menu_modif_taille_map->annuler, session->x_souris_px, session->y_souris_px)) {
            session->sous_menu_modif_taille_map->annuler->hovered = 1;
        } else {
            session->sous_menu_modif_taille_map->annuler->hovered = 0;
        }
        if (is_souris_sur_button(*session->sous_menu_modif_taille_map->valider, session->x_souris_px, session->y_souris_px)) {
            session->sous_menu_modif_taille_map->valider->hovered = 1;
        } else {
            session->sous_menu_modif_taille_map->valider->hovered = 0;
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        // Vérifier si on clique sur un champ
        if (is_souris_sur_button(*session->sous_menu_modif_taille_map->entree_width, session->x_souris_px, session->y_souris_px)) {
            session->sous_menu_modif_taille_map->is_typing_width = 1;
        }
        if (is_souris_sur_button(*session->sous_menu_modif_taille_map->entree_height, session->x_souris_px, session->y_souris_px)) {
            session->sous_menu_modif_taille_map->is_typing_width = 0;
        }

        // Vérifier si on clique sur "Valider"
        if (is_souris_sur_button(*session->sous_menu_modif_taille_map->valider, session->x_souris_px, session->y_souris_px)) {
            int width = atoi(session->sous_menu_modif_taille_map->width_text);
            int height = atoi(session->sous_menu_modif_taille_map->height_text);
            if (width >= TAILLE_MIN_MAP && width <= TAILLE_MAX_MAP && height >= TAILLE_MIN_MAP && height <= TAILLE_MAX_MAP) {
                playSoundEffect(musique->select);
                *session->map_totale = modif_taille_map(session->map_totale, width, height);
                if (session->zoom > session->map_totale->x - ZOOM_MAX) {
                    session->zoom = session->map_totale->x - ZOOM_MAX;
                }
                if (session->zoom > session->map_totale->y - ZOOM_MAX) {
                    session->zoom = session->map_totale->y - ZOOM_MAX;
                }
                if (session->position_zoom_x + session->map->x > session->map_totale->x){
                    session->position_zoom_x = session->map_totale->x - session->map->x;
                    if (session->position_zoom_x < 0){
                        session->position_zoom_x = 0;
                    }
                }
                if (session->position_zoom_y + session->map->y > session->map_totale->y){
                    session->position_zoom_y = session->map_totale->y - session->map->y;
                    if (session->position_zoom_y < 0){
                        session->position_zoom_y = 0;
                    }
                }
                nouveau_zoom(session->map, session->map_totale, session->zoom, session->position_zoom_x, session->position_zoom_y);
                session->message->button_base.label = "La map à bien été redimentionnée";
                session->message->couleur_message = (SDL_Color){255, 255, 255, 255};
                session->message->couleur_fond = (SDL_Color){0, 255, 0, 150};
                session->is_modif_taille_map = 0;
                SDL_StopTextInput();
            } else {
                char texte[100];
                snprintf(texte, sizeof(texte), "Les dimentions doivent être entre %d et %d !", TAILLE_MIN_MAP, TAILLE_MAX_MAP);
                session->message->button_base.label = texte;
                session->message->couleur_message = (SDL_Color){0, 0, 0, 255};
                session->message->couleur_fond = (SDL_Color){255, 50, 0, 200};
            }
            session->message->temps_affichage = 3;
            session->message->is_visible = 1;
            session->message->start_time = time(NULL);
        }

        // Vérifier si on clique sur "Annuler"
        if (is_souris_sur_button(*session->sous_menu_modif_taille_map->annuler, session->x_souris_px, session->y_souris_px)) {
            playSoundEffect(musique->select);
            session->is_modif_taille_map = 0;
            SDL_StopTextInput();
        }
    }

    if (event.type == SDL_TEXTINPUT) {
        char *target = session->sous_menu_modif_taille_map->is_typing_width ? session->sous_menu_modif_taille_map->width_text : session->sous_menu_modif_taille_map->height_text;
        if (strlen(target) < MAX_NB_LENGTH && isdigit(event.text.text[0])) {
            strcat(target, event.text.text);
        }
    }

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            char *target = session->sous_menu_modif_taille_map->is_typing_width ? session->sous_menu_modif_taille_map->width_text : session->sous_menu_modif_taille_map->height_text;
            if (strlen(target) > 0) {
                target[strlen(target) - 1] = '\0';
            }
        }
    }
}

void init_session (SDL_Renderer* ren, Session_modif_map* session){
    session->button_height = 50;
    session->button_width = 210; 

    session->is_enregistrement = 0;
    session->is_modif_taille_map = 0;
    session->is_souris_sur_map = 0;
    session->is_en_cours_de_modif = 0;
    session->is_grille_on = 1;

    session->zoom = 0;
    session->position_zoom_x = 0;
    session->position_zoom_y = 0;

    session->cercle_pointe_erreur_x = -1;
    session->cercle_pointe_erreur_y = -1;

    session->is_symetrie_verticale = 0;
    session->is_symetrie_horizontale = 0;

    init_buttons_createur_map(session);

    session->tils = malloc(sizeof(SDL_Texture*) * 4);
    init_tils(session->tils, ren);

    // Initialisation des messages
    session->message = malloc(sizeof(Message));
    session->message->button_base.rect = (SDL_Rect){FEN_X/2-400, FEN_Y/2-50, 800, 200};
    session->message->button_base.hovered = 0;
    session->message->is_visible = 0;
    session->message->start_time = time(NULL);

    // Init pour le sous-menu enregistrer
    session->sous_menu_enregistrement = malloc(sizeof(Sous_menu_enregistrement));
    session->sous_menu_enregistrement->text[0] ='\0';
    session->sous_menu_enregistrement->cursorVisible = 1;
    session->sous_menu_enregistrement->lastCursorToggle = SDL_GetTicks();
    init_boutons_enregistrer(session->sous_menu_enregistrement);

    // Init pour le sous-menu de modification de la taille de la map
    session->sous_menu_modif_taille_map = malloc(sizeof(Sous_menu_modif_taille_map));
    session->sous_menu_modif_taille_map->width_text[0] = '\0';
    session->sous_menu_modif_taille_map->height_text[0] = '\0';
    session->sous_menu_modif_taille_map->cursorVisible = 1;
    session->sous_menu_modif_taille_map->lastCursorToggle = SDL_GetTicks();
    session->sous_menu_modif_taille_map->is_typing_width = 1;
    init_boutons_modif_taille_map(session->sous_menu_modif_taille_map);

    // Init des maps
    session->map = malloc(sizeof(Map));
    session->map_totale = malloc(sizeof(Map));
    *session->map = init_map_dessin();
    init_taille_case_et_origine(session->map);
    *session->map_totale = copyMap(session->map);

    session->position_maison_ghosts[0] = session->map->position_maison_ghosts_x - 4;
    session->position_maison_ghosts[1] = session->map->position_maison_ghosts_y;
    session->position_maison_ghosts[2] = session->map->position_maison_ghosts_x + 5;
    session->position_maison_ghosts[3] = session->map->position_maison_ghosts_y + 6;

    session->color = malloc(sizeof(Colors));
    init_couleurs_session(session);
}

void free_session(Session_modif_map* session) {
    for (int i = 0; i < NB_BUTTONS; i++) {
        free(session->buttons[i]);
    }
    /* TODO : comprendre pourquoi ça plante
    for (int j = 0; j < NB_BUTTONS_SELECTION_REMPLISSAGE; j++) {
        free(session->buttons_selection_remplissage[j]);
    }
    free(session->button_modif_taille_map);
    free(session->button_grille);
    free(session->button_enregistrer);
    free(session->button_zoom_plus);
    free(session->button_zoom_moins);
    free(session->button_symetrie_verticale);
    free(session->button_symetrie_horizontale);
    */
    free(session->message);
    free(session->sous_menu_enregistrement->entree_text);
    free(session->sous_menu_enregistrement->consigne);
    free(session->sous_menu_enregistrement->annuler);
    free(session->sous_menu_enregistrement->valider);
    free(session->sous_menu_enregistrement);

    free(session->sous_menu_modif_taille_map->entree_width);
    free(session->sous_menu_modif_taille_map->entree_height);
    free(session->sous_menu_modif_taille_map->text_entree_width);
    free(session->sous_menu_modif_taille_map->text_entree_height);
    free(session->sous_menu_modif_taille_map->consigne);
    free(session->sous_menu_modif_taille_map->annuler);
    free(session->sous_menu_modif_taille_map->valider);
    free(session->sous_menu_modif_taille_map);

    free(session->color);
    freeMap(session->map);
    free(session->map);
    freeMap(session->map_totale);
    free(session->map_totale);
    free_tils(session->tils, 4);
    free(session);
}

void main_loop_createur_map (SDL_Renderer* ren, Musique* musique){
    Session_modif_map* session = malloc(sizeof(Session_modif_map));
    init_session(ren, session);

    int running = 1;
    SDL_Event event;
    time_t current_time;

    while (running) {
        current_time = time(NULL);
        
        affiche_interface_createur_map(ren, session, current_time);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (session->is_enregistrement) {
                handle_events_enregistrement(event, session, musique);
            } else if (session->is_modif_taille_map) {
                handle_events_modif_taille_map(event, session, musique);
            } else {
                handle_events_createur_map(event, session, &running, musique, ren);
            }
        }
        updateDisplay(ren);
    }
    free_session(session);
    SDL_StopTextInput();
}
