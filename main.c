#include "ressources.h"
#include "pacman.h"
#include "ghost.h"
#include "jeu.h"
#include "plateau.h"
#include "audio.h"

int main (int argc, char *argv[]){
    srand(time(NULL));
    // Initialisation globale fenêtre
    initSDL();
    initTTF();
    SDL_Window* window = createWindow("Pacman C²HAMD", FEN_X, FEN_Y);
    SDL_Renderer* ren = createRenderer(window);
    
    if (!init_audio()) {
        return 1; // Erreur d'initialisation
    }

    printf("Lecture du son...\n");
    jouer_son("son.wav");

    cleanup_audio();


    ecran_acceuil(ren);
    

    QuitSDL;
    return 0;
}

