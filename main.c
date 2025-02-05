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
    init_audio();

    SDL_Window* window = createWindow("Pacman C²HAMD", FEN_X, FEN_Y);
    SDL_Renderer* ren = createRenderer(window);

    Musique* musique = malloc(sizeof(Musique));

    init_musiques_et_sons (musique);
    musiques_et_sons_default(musique);

    ecran_acceuil(ren, musique);

    clear_musique(musique);
    QuitSDL(window,ren);
    return 0;
}

