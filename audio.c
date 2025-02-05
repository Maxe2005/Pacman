#include "audio.h"

int init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur Mix_OpenAudio : %s\n", Mix_GetError());
        return 1;
    }
    return 0; // Succès
}

void init_musiques_et_sons(Musique* musique) {
    musique->musiques_src[0] = loadMusic("ressources/musiques/Pacman-Remix.mp3");
    musique->musiques_src[1] = loadMusic("ressources/musiques/PacMan.mp3");
    musique->musiques_src[2] = loadMusic("ressources/musiques/SuperMode.mp3");

    musique->sons_src[0] = loadSoundEffect("ressources/sons/rattle.wav"); 
    musique->sons_src[1] = loadSoundEffect("ressources/sons/son.wav"); 
}

void liberer_musiques_et_sons(Musique* musique) {
    for (int i = 0; i < NB_MUSIQUES; i++) {
        Mix_FreeMusic(musique->musiques_src[i]);
    }
    for (int i = 0; i < NB_SONS; i++) {
        freeSoundEffect(musique->sons_src[i]);
    }
}

void musiques_et_sons_default (Musique* musique){
    musique->musique_accueil = musique->musiques_src[0];
    musique->musique_jeu = musique->musiques_src[1];
    musique->musique_super_mode = musique->musiques_src[2];

    musique->eat_ghost = musique->sons_src[0];
}


Mix_Music* loadMusic(const char *filename) {
    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music) {
        printf("Erreur chargement musique (%s): %s\n", filename, Mix_GetError());
    }
    return music;
}

void playMusic(Mix_Music *music) {
    if (music) {
        Mix_PlayMusic(music, -1); // -1 = boucle infinie
    }
}

void pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void reprendreMusic() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void stopMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

Mix_Chunk * loadSoundEffect(const char *filename) {
    Mix_Chunk *soundEffect = Mix_LoadWAV(filename);
    if (!soundEffect) {
        printf("Erreur chargement son (%s): %s\n", filename, Mix_GetError());
    }
    return soundEffect;
}

void playSoundEffect(Mix_Chunk *soundEffect) {
    if (soundEffect) {
        Mix_PlayChannel(-1, soundEffect, 0);
    }
}

void freeSoundEffect(Mix_Chunk *soundEffect) {
    if (soundEffect) {
        Mix_FreeChunk(soundEffect);
    }
}

void clear_musique (Musique* musique){
    stopMusic();
    liberer_musiques_et_sons(musique);
    Mix_CloseAudio();
}
