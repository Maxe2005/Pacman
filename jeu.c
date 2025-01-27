#include "jeu.h"

void init_font (TTF_Font* font[1]) {
    font[0] = createFont("ressources/DejaVuSans-Bold.ttf", 20); //Font de titres

}


void debut_jeu (SDL_Renderer* ren,int map[MAP_Y][MAP_X],SDL_Texture** tils,Pacman* pacman,TTF_Font *font[1]) {
    unsigned int score = 0;
    char text_score[15];
    int running = 1;
    
    ecran_acceuil (ren,map,tils,pacman,text_score,score,font,&running);


    

}  

void ecran_acceuil (SDL_Renderer* ren,int map[MAP_Y][MAP_X],SDL_Texture** tils,Pacman* pacman,char text_score[15],unsigned int score,TTF_Font *font[1],int* running){
    char lancement;
    SDL_Texture* logo =loadTexture("ressources/pac-man-logo.bmp", ren);
    SDL_Texture* bouton_start =loadTexture("ressources/bouton_start_pacman.bmp", ren);
    int verification; // permet de ne pas charger trop d'image plus bas
    clock_t start_time = clock();
    const double temps_reaction_pacman = 2000.0 / 1000.0 * CLOCKS_PER_SEC; //temps_reaction_pacman convertion de milisecondes à clocks
    verification = 0;
    renderTexture(logo, ren,(int)(FEN_X /4),(int)(FEN_Y/8),(int)(FEN_X/2),(int)(FEN_Y/4));
    while (*running) {
        clock_t current_time = clock();
        updateDisplay(ren);
        if ((double)(current_time - start_time) >= (temps_reaction_pacman / 2) && verification==0) {
            renderTexture(bouton_start, ren,(int)(FEN_X /4),(int)(FEN_Y/2),(int)(FEN_X/2),(int)(FEN_Y/4));
            verification=1;
        }
         if ((double)(current_time - start_time) >= temps_reaction_pacman && verification==1) {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);
            renderTexture(logo, ren,(int)(FEN_X /4),(int)(FEN_Y/8),(int)(FEN_X/2),(int)(FEN_Y/4));
            verification=0;
            start_time = current_time;
        }
        
        
        lancement = processKeyboard(running);
        if (lancement == 'L'){
            boucle_de_jeu(ren,map,tils,pacman,text_score,score,font,running);
}
}
}






void boucle_de_jeu(SDL_Renderer* ren,int map[MAP_Y][MAP_X],SDL_Texture** tils,Pacman* pacman,char text_score[15],unsigned int score,TTF_Font *font[1],int* running){
    char dir;
    SDL_Color white = {255, 255, 255, 255} ;
    while (*running){
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        affiche_map(map, tils, ren);
        affiche_pacman(pacman, ren);
        sprintf(text_score, "Score : %d",score);
        printText(10, 20, text_score, 300, 60, font[0], white, ren);
        updateDisplay(ren);

        dir = processKeyboard(running);
        if (dir != ' '){
            pacman->next_direction = dir;
        }
        avance_pacman(pacman, map, &score);
    }
    
        
}



//void set_affichage_global (SDL_Renderer *ren, int map[MAP_Y][MAP_X]) {}
