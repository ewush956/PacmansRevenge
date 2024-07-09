#ifndef MUSIC_H
#define MUSIC_H

#include "TYPES.H"
#include "psg.h"

#define BASS_VOLUME 15
#define TREBLE_VOLUME 14

#define PACMAN_INTRO_TREBLE_LENGTH 38
#define PACMAN_INTRO_BASS_LENGTH 22

extern const SoundCycle pacman_intro_treble[PACMAN_INTRO_TREBLE_LENGTH];
extern const SoundCycle pacman_intro_bass[PACMAN_INTRO_BASS_LENGTH];

int generate_frequency(int base_note, UCHAR8 target_octave);
void play_intro();
void stop_music();

#endif