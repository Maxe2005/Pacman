#include "ressources.h"
#include "pacman.h"
#include "ghost.h"
#include "jeu.h"
#include "plateau.h"


int main (int argc, char *argv[]){
    srand(time(NULL));
    // Initialisation globale fenêtre
    initSDL();
    initTTF();
    SDL_Window* window = createWindow("Pacman C²HAMD", FEN_X, FEN_Y);
    SDL_Renderer* ren = createRenderer(window);
    
    // Initialisation variables globales
    /*unsigned int score = 0;
    char text_score[15];
    SDL_Color white = {255, 255, 255, 255} ;
    char dir;
    int running = 1;

    clock_t start_time = clock();
    const double temps_reaction_pacman = 1000.0 / 1000.0 * CLOCKS_PER_SEC; //temps_reaction_pacman convertion de milisecondes à clocks
    */
    
    ecran_acceuil(ren);

    QuitSDL;
    return 0;
}

