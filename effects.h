#ifndef EFFECTS_H
#define EFFECTS_H

#include "TYPES.H"
#include "psg.h"

#define WAKA_CYCLE_LENGTH 14
/*
typedef struct {
    int frequency;
    int volume;
    int duration;
}SoundCycle;

typedef struct {
    int current_sound_index;
    int sound_time_left;
}SoundState;
*/
extern const SoundCycle waka_sound_cycle[WAKA_CYCLE_LENGTH];
extern const SoundCycle waka_noise_cycle[WAKA_CYCLE_LENGTH];

bool play_waka_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state);
void play_kill_ghost_sound();
#endif