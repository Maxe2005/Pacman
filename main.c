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
    
    
    ecran_acceuil(ren);
    
    QuitSDL(window, ren);
    return 0;
}

