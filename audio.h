#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Fonction d'initialisation du son
int init_audio();

// Fonction pour jouer un son
void jouer_son(const char *fichier);

// Fonction pour nettoyer la mémoire
void cleanup_audio();

#endif
