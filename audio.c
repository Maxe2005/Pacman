#include "audio.h"
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

// Initialisation de SDL_mixer
int init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur Mix_OpenAudio : %s\n", Mix_GetError());
        return 0;
    }

    return 1; // Succès
}

// Jouer un fichier audio
void jouer_son(const char *fichier) {
    Mix_Chunk *son = Mix_LoadWAV(fichier);
    if (!son) {
        printf("Erreur Mix_LoadWAV : %s\n", Mix_GetError());
        return;
    }

    Mix_PlayChannel(-1, son, 0);
    SDL_Delay(10000);  // Attendre 3 secondes pour entendre le son
    Mix_CloseAudio();
    SDL_Delay(5000);
    Mix_FreeChunk(son);
}

// Nettoyage mémoire
void cleanup_audio() {
    Mix_CloseAudio();
    SDL_Quit();
}
