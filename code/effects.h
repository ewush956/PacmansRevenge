#ifndef EFFECTS_H
#define EFFECTS_H

#include "TYPES.H"
#include "psg.h"

#define WAKA_CYCLE_LENGTH 14
#define GHOST_KILL_CYCLE_LENGTH 9

#define WAKA_VOLUME 12
#define WAKA_NOISE 14
#define KILL_GHOST_VOLUME 15

extern const SoundCycle waka_sound_cycle[WAKA_CYCLE_LENGTH];
extern const SoundCycle waka_noise_cycle[WAKA_CYCLE_LENGTH];
extern const SoundCycle ghost_kill_sound_cycle[GHOST_KILL_CYCLE_LENGTH];

bool play_waka_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state);
void play_kill_ghost_sound();
#endif