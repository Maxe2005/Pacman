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

    Audio* audio = malloc(sizeof(Audio));

    init_audios_et_sons (audio);
    audios_et_sons_default(audio);

    ecran_acceuil(ren, audio);

    clear_audio(audio);
    QuitSDL(window,ren);
    return 0;
}

