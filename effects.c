#include "effects.h"
#include "psg.h"
#include "TYPES.H"
#define waka_volume 13

const SoundCycle waka_sound_cycle[WAKA_CYCLE_LENGTH] = {
    {E4, waka_volume, THIRTY_SECOND_NOTE},
    {G4_SHARP, waka_volume, THIRTY_SECOND_NOTE},
    {C5, waka_volume, THIRTY_SECOND_NOTE},
    {D5_SHARP, waka_volume, THIRTY_SECOND_NOTE},
    {F5_SHARP, waka_volume, THIRTY_SECOND_NOTE},
    {A5_SHARP, waka_volume, THIRTY_SECOND_NOTE},
    {B5, waka_volume, THIRTY_SECOND_NOTE},
    {G5, waka_volume, THIRTY_SECOND_NOTE},
    {E5, waka_volume, THIRTY_SECOND_NOTE},
    {C5_SHARP, waka_volume, THIRTY_SECOND_NOTE},
    {A4, waka_volume, THIRTY_SECOND_NOTE},
    {F4, waka_volume, THIRTY_SECOND_NOTE}
};
const SoundCycle waka_noise_cycle[WAKA_CYCLE_LENGTH] = {
    {E3, 15, THIRTY_SECOND_NOTE},
    {G3_SHARP, 15, THIRTY_SECOND_NOTE},
    {C4, 15, THIRTY_SECOND_NOTE},
    {D4_SHARP, 15, THIRTY_SECOND_NOTE},
    {F4_SHARP, 15, THIRTY_SECOND_NOTE},
    {A4_SHARP, 15, THIRTY_SECOND_NOTE},
    {B4, 15, THIRTY_SECOND_NOTE},
    {G4, 15, THIRTY_SECOND_NOTE},
    {E4, 15, THIRTY_SECOND_NOTE},
    {C4_SHARP, 15, THIRTY_SECOND_NOTE},
    {A3, 15, THIRTY_SECOND_NOTE},
    {F3, 15, THIRTY_SECOND_NOTE}
};

bool play_waka_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state) {
    int index = state->current_sound_index;
    int* time_left = &state->sound_time_left;

    if (*time_left == 0) {
        if (index < cycle_length) {
            *time_left = sound_cycle[index].duration;
            play_note(channel, sound_cycle[index].frequency, sound_cycle[index].volume);
            state->current_sound_index++;
        } else {
            stop_sound();
            state->current_sound_index = 0; 
            return TRUE;
        }
    }
    (*time_left)--;
    return FALSE; 
}
