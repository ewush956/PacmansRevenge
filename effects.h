#include "TYPES.H"
#include "psg.h"

#define WAKA_CYCLE_LENGTH 12

typedef struct {
    int frequency;
    int volume;
    int duration;
}SoundCycle;

typedef struct {
    int current_sound_index;
    int sound_time_left;
}SoundState;

extern const SoundCycle waka_sound_cycle[WAKA_CYCLE_LENGTH];
extern const SoundCycle waka_noise_cycle[WAKA_CYCLE_LENGTH];

bool play_waka_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state);