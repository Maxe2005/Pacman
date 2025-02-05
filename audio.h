#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define NB_MUSIQUES 3
#define NB_SONS 2

typedef struct {
    Mix_Music* musiques_src[NB_MUSIQUES];
    Mix_Chunk* sons_src[NB_SONS];
    Mix_Music* musique_accueil;
    Mix_Music* musique_jeu;
    Mix_Music* musique_super_mode;
    Mix_Chunk* eat_ghost;
} Musique ;

/**
 * Initialise le module SDL_mixer
 */
int init_audio();


/**
 * Initialise les différentes paths des musiques et sons disponibles
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void init_musiques_et_sons (Musique* musique);

/**
 * Libère la mémoire des paths des musiques et sons
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void liberer_musiques_et_sons(Musique* musique);

/**
 * Initialise les musiques et les sons du jeu par défault
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void musiques_et_sons_default (Musique* musique);

/**
 * Fonction pour charger une musique
 * @param filename Le path vers le fichier mp3 à jouer
 */
Mix_Music* loadMusic(const char *filename);

/**
 * Fonction pour jouer une musique
 * @param music La musique déjà chargée à jouer
 */
void playMusic(Mix_Music *music);

/**
 * Fonction pour mettre en pause la musique
 */
void pauseMusic();

/**
 * Fonction pour reprendre une musique
 */
void reprendreMusic();

/**
 * Fonction pour arrêter complètement une musique si elle est jouée
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
void playSoundEffect(Mix_Chunk *soundEffect);

/**
 * Fonction pour libérer l'espace mémoire de l'effet sonore
 * @param soundEffect L'effet sonore à ne plus utiliser
 */
void freeSoundEffect(Mix_Chunk *soundEffect);

/**
 * Nettoie tout l'espace de musique
 * @param musique La structure contenant toutes les infos pour les musiques
 */
void clear_musique (Musique* musique);

#endif
