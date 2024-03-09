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
const Note pacman_intro_treble[34] = {
    
    {B4, SIXTEENTH_NOTE, 15},
    {B5, SIXTEENTH_NOTE, 15},
    {F5_SHARP, SIXTEENTH_NOTE, 15},
    {D5_SHARP, SIXTEENTH_NOTE, 15},
    {B5, THIRTY_SECOND_NOTE, 15},

    /*Dotted 16th note*/
    {F5_SHARP, SIXTEENTH_NOTE, 15},
    {F5_SHARP, THIRTY_SECOND_NOTE, 15},

    {D5_SHARP, EIGHTH_NOTE, 15},

    {C4, SIXTEENTH_NOTE, 15},
    {C5, SIXTEENTH_NOTE, 15},
    {G5, SIXTEENTH_NOTE, 15},
    {E5, SIXTEENTH_NOTE, 15},
    {C5, THIRTY_SECOND_NOTE, 15},

    /*Dotted 16th note*/
    {G5, SIXTEENTH_NOTE, 15},
    {G5, THIRTY_SECOND_NOTE, 15},

    {E5, EIGHTH_NOTE, 15},

    {B4, SIXTEENTH_NOTE, 15},
    {B5, SIXTEENTH_NOTE, 15},
    {F4_SHARP, SIXTEENTH_NOTE, 15},
    {D5_SHARP, SIXTEENTH_NOTE, 15},
    {B5, THIRTY_SECOND_NOTE, 15},

    /*Dotted 16th note*/
    {F4_SHARP, SIXTEENTH_NOTE, 15},
    {F4_SHARP, THIRTY_SECOND_NOTE, 15},

    {D5_SHARP, EIGHTH_NOTE, 15},

    {D5_SHARP, THIRTY_SECOND_NOTE, 15},
    {E5, THIRTY_SECOND_NOTE, 15},
    {F5, SIXTEENTH_NOTE, 15},

    {F5, THIRTY_SECOND_NOTE, 15},
    {F5_SHARP, THIRTY_SECOND_NOTE, 15},
    {G5, SIXTEENTH_NOTE, 15},

    {G5, THIRTY_SECOND_NOTE, 15},
    {G5_SHARP, THIRTY_SECOND_NOTE, 15},
    {A5, SIXTEENTH_NOTE, 15},

    {B5, EIGHTH_NOTE, 15}
};
const Note pacman_intro_bass[100] = {
    {B5, EIGHTH_NOTE, 15}
};
/**
 * Plays a note on a specified channel with given tuning and volume.
 * 
 * @param channel The sound channel to play the note on. Valid channels depend on the hardware, typically 0, 1, or 2.
 * @param tuning The frequency tuning value of the note. This value should be compatible with the `set_tone` function.
 * @param volume The volume at which to play the note. Expected to be a value that `set_volume` can accept.
 */
void play_note(int channel, int tuning, unsigned char volume) {

    set_tone(channel, tuning);
    set_volume(channel, volume);
    enable_channel(channel, TONE_ON, NOISE_OFF);
}

int generate_frequency(int base_note, UCHAR8 target_octave) {
    return (base_note >> target_octave);
}
void start_music() {
    
}
void update_music(int channel, const Note song[], int song_length) {
    static int current_note_index = 0; 
    static int note_time_left = 0; 

    if (note_time_left == 0) {
        if (current_note_index < song_length) {
            note_time_left = song[current_note_index].duration; 
            play_note(channel, song[current_note_index].frequency, song[current_note_index].volume);
        } else {
            stop_sound(); 
            return;
        }
    }
    note_time_left -= 1; 

    if (note_time_left <= 0) {
        current_note_index++;
        if (current_note_index < song_length) {
            note_time_left = song[current_note_index].duration;
            play_note(channel, song[current_note_index].frequency, song[current_note_index].volume);
        } else {
            stop_sound();
            current_note_index = 0;
        }
    }
}
void play_intro() {
    /*mom pick me up i'm scared :( */
}
void play_jaws_theme() {

}
void stop_music() {
    
}