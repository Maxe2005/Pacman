#ifndef AUDIO_H
#define AUDIO_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define NB_MUSIQUES 7
#define NB_SONS 6

typedef struct {
    Mix_Music* musique;
    char* nom;
} Musique ;

typedef struct {
    Mix_Chunk* son;
    char* nom;
} Son ;

typedef struct {
    Musique* musiques_src[NB_MUSIQUES];
    Son* sons_src[NB_SONS];
    Musique* musique_accueil;
    Musique* musique_jeu;
    Musique* musique_super_mode;
    Son* eat_ghost;
    Son* pacman_song;
    Son* game_over;
    Son* pacman_death;
    Son* select;
} Audio ;






/**
 * Initialise le module SDL_mixer
 */
int init_audio();


/**
 * Initialise les différentes paths des audios et sons disponibles
 * @param audio La structure contenant toutes les infos pour les audios
 */
void init_audios_et_sons (Audio* audio);

/**
 * Libère la mémoire des paths des audios et sons
 * @param audio La structure contenant toutes les infos pour les audios
 */
void liberer_audios_et_sons(Audio* audio);

/**
 * Initialise les audios et les sons du jeu par défault
 * @param audio La structure contenant toutes les infos pour les audios
 */
void audios_et_sons_default (Audio* audio);

/**
 * Fonction pour charger une audio
 * @param filename Le path vers le fichier mp3 à jouer
 */
Mix_Music* loadMusic(const char *filename);

/**
 * Fonction pour jouer une audio
 * @param music La audio déjà chargée à jouer
 */
void playMusic(Musique *music);

/**
 * Fonction pour mettre en pause la audio
 */
void pauseMusic();

/**
 * Fonction pour reprendre une audio
 */
void reprendreMusic();

/**
 * Fonction pour arrêter complètement une audio si elle est jouée
 */
void stopMusic();

/**
 * Fonction pour charger un effet sonore
 * @param filename Le path vers le fichier mp3 ou wav à jouer
 */
Mix_Chunk * loadSoundEffect(const char *filename);

/**
 * Fonction pour jouer un effet sonore
 * @param soundEffect L'effet sonore déjà chargé
 */
void playSoundEffect(Son *soundEffect);

/**
 * Fonction pour libérer l'espace mémoire de l'effet sonore
 * @param soundEffect L'effet sonore à ne plus utiliser
 */
void freeSoundEffect(Mix_Chunk *soundEffect);

/**
 * Nettoie tout l'espace de audio
 * @param audio La structure contenant toutes les infos pour les audios
 */
void clear_audio (Audio* audio);

#endif