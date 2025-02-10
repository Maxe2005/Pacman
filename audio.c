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

void init_audios_et_sons(Audio* audio) {
    audio->musiques_src[0] = malloc(sizeof(Musique));
    audio->musiques_src[0]->musique = loadMusic("ressources/musiques/Ambiance.mp3");
    audio->musiques_src[0]->nom="Ambiance";

    audio->musiques_src[1] = malloc(sizeof(Musique));
    audio->musiques_src[1]->musique = loadMusic("ressources/musiques/Font_de_jeu.mp3");
    audio->musiques_src[1]->nom="Font_de_jeu";

    audio->musiques_src[2] = malloc(sizeof(Musique));
    audio->musiques_src[2]->musique = loadMusic("ressources/musiques/SuperMode.mp3");
    audio->musiques_src[2]->nom="SuperMode";

    audio->musiques_src[3] = malloc(sizeof(Musique));
    audio->musiques_src[3]->musique = loadMusic("ressources/musiques/THEME.mp3");
    audio->musiques_src[3]->nom="THEME";

    audio->musiques_src[4] = malloc(sizeof(Musique));
    audio->musiques_src[4]->musique = loadMusic("ressources/musiques/Turi.mp3");
    audio->musiques_src[4]->nom="Turi";

    audio->musiques_src[5] = malloc(sizeof(Musique));
    audio->musiques_src[5]->musique = loadMusic("ressources/musiques/Sans_musique.mp3");
    audio->musiques_src[5]->nom="Sans_musique";

    audio->musiques_src[6] = malloc(sizeof(Musique));
    audio->musiques_src[6]->musique = loadMusic("ressources/musiques/DAMSO.mp3");
    audio->musiques_src[6]->nom="DAMSO";

    audio->sons_src[0] = malloc(sizeof(Son));
    audio->sons_src[0]->son = loadSoundEffect("ressources/sons/rattle.wav");
    audio->sons_src[0]->nom="rattle";

    audio->sons_src[1] = malloc(sizeof(Son));
    audio->sons_src[1]->son = loadSoundEffect("ressources/sons/Game_Over.wav");
    audio->sons_src[1]->nom="Game_Over";

    audio->sons_src[2] = malloc(sizeof(Son));
    audio->sons_src[2]->son = loadSoundEffect("ressources/sons/pacman_death.wav");
    audio->sons_src[2]->nom="pacman_death";

    audio->sons_src[3] = malloc(sizeof(Son));
    audio->sons_src[3]->son = loadSoundEffect("ressources/sons/Pacman_song.wav");
    audio->sons_src[3]->nom="Pacman_song";

    audio->sons_src[4] = malloc(sizeof(Son));
    audio->sons_src[4]->son = loadSoundEffect("ressources/sons/Select.wav");
    audio->sons_src[4]->nom="Select";

    audio->sons_src[5] = malloc(sizeof(Son));
    audio->sons_src[5]->son = loadSoundEffect("ressources/sons/eatghost.wav");
    audio->sons_src[5]->nom="eatghost";

    
}

void liberer_audios_et_sons(Audio* audio) {
    for (int i = 0; i < NB_MUSIQUES; i++) {
        Mix_FreeMusic(audio->musiques_src[i]->musique);
    }
    for (int i = 0; i < NB_SONS; i++) {
        freeSoundEffect(audio->sons_src[i]->son);
    }
}

void audios_et_sons_default (Audio* audio){
    audio->musique_accueil = audio->musiques_src[3];
    audio->musique_jeu = audio->musiques_src[1];
    audio->musique_super_mode = audio->musiques_src[2];

    audio->game_over = audio->sons_src[1];
    audio->pacman_death = audio->sons_src[2];
    audio->pacman_song = audio->sons_src[3];
    audio->select = audio->sons_src[4];
    audio->eat_ghost = audio->sons_src[5];
}


Mix_Music* loadMusic(const char *filename) {
    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music) {
        printf("Erreur chargement audio (%s): %s\n", filename, Mix_GetError());
    }
    return music;
}

void playMusic(Musique *music) {
    if (music) {
        Mix_PlayMusic(music->musique, -1); // -1 = boucle infinie
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

void playSoundEffect(Son *soundEffect) {
    if (soundEffect->son) {
        Mix_PlayChannel(-1, soundEffect->son, 0);
    }
}

void freeSoundEffect(Mix_Chunk *soundEffect) {
    if (soundEffect) {
        Mix_FreeChunk(soundEffect);
    }
}

void clear_audio (Audio* audio){
    stopMusic();
    liberer_audios_et_sons(audio);
    Mix_CloseAudio();
}
