#include "music.h"
#include "TYPES.H"
#include "psg.h"

/***********************************************
 * Function Name: generate_note
 * Purpose: Shifts the octave of a note by a specified amount.
 *          Returns the hex frequency of the new note.
 * Parameters:
 *     - @param note (UCHAR8): The base note to shift.
 *     - @param octave (UCHAR8): The target octave.
 * *********************************************/
int bass_volume = 15;
int treble_volume = 15;
/*
const Note pacman_intro_treble[38] = {
   */
const SoundCycle pacman_intro_treble[PACMAN_INTRO_TREBLE_LENGTH] = {
    {B4,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {B5,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {F5_SHARP,  SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {D5_SHARP,  SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {B5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {F5_SHARP,  SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {F5_SHARP,  THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {D5_SHARP,  EIGHTH_NOTE,        TREBLE_VOLUME},

    {C5,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {C6,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {G5,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {E5,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {C6,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {G5,        SIXTEENTH_NOTE,     15},
    {G5,        THIRTY_SECOND_NOTE, 15},
    
    {E5,        EIGHTH_NOTE,        TREBLE_VOLUME},

    {B4,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {B5,        SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {F5_SHARP,  SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {D5_SHARP,  SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {B5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {F5_SHARP,  SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {F5_SHARP,  THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    
    {D5_SHARP,  SIXTEENTH_NOTE,     TREBLE_VOLUME},
    {D5_SHARP,  THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {D5_SHARP,  THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {E5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F4,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {F5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F5_SHARP,  THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G4,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {G5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G5_SHARP,  THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {A5,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {A4,        THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    {B5,        EIGHTH_NOTE,        TREBLE_VOLUME}
};
const SoundCycle pacman_intro_bass[PACMAN_INTRO_BASS_LENGTH] = {
    
    {B2,        EIGHTH_NOTE,        BASS_VOLUME},
    {B2,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {B3,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {B2,        EIGHTH_NOTE,        BASS_VOLUME},
    {B2,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {B3,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {C3,        EIGHTH_NOTE,        BASS_VOLUME},
    {C3,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {C4,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {C3,        EIGHTH_NOTE,        BASS_VOLUME},
    {C3,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {C4,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {B2,        EIGHTH_NOTE,        BASS_VOLUME},
    {B2,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {B3,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {B2,        EIGHTH_NOTE,        BASS_VOLUME},
    {B2,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {B3,        SIXTEENTH_NOTE,     BASS_VOLUME},

    {F2_SHARP,  EIGHTH_NOTE,        BASS_VOLUME},
    {G2_SHARP,  EIGHTH_NOTE,        BASS_VOLUME},
    {A2_SHARP,  EIGHTH_NOTE,        BASS_VOLUME},
    {B2,        EIGHTH_NOTE,        BASS_VOLUME}

};
int generate_frequency(int base_note, UCHAR8 target_octave) {
    return (base_note >> target_octave);
}
void start_music() {
    
}
/*Returns true when the song is finished*/
/*
bool update_music(int channel, const Note song[], int song_length, MusicState *state) {
    int index = state->current_note_index;
    int* time_left = &state->note_time_left;

    if (state->note_time_left == 0) {
        if (index < song_length) {
            state->note_time_left = song[index].duration; 
            play_note(channel, song[index].frequency, song[index].volume);
            state->current_note_index++;
        } else {
            stop_sound(); 
            state->current_note_index = 0;
            return TRUE;
        }
    }
    state->note_time_left -= 1; 
    return FALSE;
}
*/
/***********************************
bool play_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state) {
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
*/

void play_intro() {
    /*mom pick me up i'm scared :( */
}
void play_jaws_theme() {

}
void stop_music() {
    
}