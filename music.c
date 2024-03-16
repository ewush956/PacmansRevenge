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
const Note pacman_intro_treble[38] = {
    
    {B4, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {B5, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {F5_SHARP, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {D5_SHARP, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {B5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    /*Dotted 16th note */
    {F5_SHARP, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {F5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    /*
    {F5_SHARP, THIRTY_SECOND_NOTE, 15},
    {F4_SHARP, THIRTY_SECOND_NOTE, 15},
    {F5_SHARP, THIRTY_SECOND_NOTE, 15}, */




    {D5_SHARP, EIGHTH_NOTE, TREBLE_VOLUME},

    {C5, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {C6, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {G5, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {E5, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {C6, THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    /*Dotted 16th note */
    {G5, SIXTEENTH_NOTE, 15},
    {G5, THIRTY_SECOND_NOTE, 15},
    /*
    {G5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G4, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
*/

    {E5, EIGHTH_NOTE, TREBLE_VOLUME},

    {B4, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {B5, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {F5_SHARP, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {D5_SHARP, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {B5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    /*Dotted 16th note */
    {F5_SHARP, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {F5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    
    {D5_SHARP, SIXTEENTH_NOTE, TREBLE_VOLUME},
    {D5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},

    

/*
    {D5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {E5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F5, SIXTEENTH_NOTE, TREBLE_VOLUME},
*/
    {D5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {E5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F4, THIRTY_SECOND_NOTE, TREBLE_VOLUME},

/*
    {F5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G5, SIXTEENTH_NOTE, TREBLE_VOLUME},
    */
    {F5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {F5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G4, THIRTY_SECOND_NOTE, TREBLE_VOLUME},

/*
    {G5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {A5, SIXTEENTH_NOTE, TREBLE_VOLUME},
*/
    {G5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {G5_SHARP, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {A5, THIRTY_SECOND_NOTE, TREBLE_VOLUME},
    {A4, THIRTY_SECOND_NOTE, TREBLE_VOLUME},


    {B5, EIGHTH_NOTE, TREBLE_VOLUME}
};
const Note pacman_intro_bass[22] = {
    {B2, EIGHTH_NOTE, BASS_VOLUME},
    {B2, SIXTEENTH_NOTE, BASS_VOLUME},

    {B3, SIXTEENTH_NOTE, BASS_VOLUME},

    {B2, EIGHTH_NOTE, BASS_VOLUME},
    {B2, SIXTEENTH_NOTE, BASS_VOLUME},

    {B3, SIXTEENTH_NOTE, BASS_VOLUME},

    {C3, EIGHTH_NOTE, BASS_VOLUME},
    {C3, SIXTEENTH_NOTE, BASS_VOLUME},

    {C4, SIXTEENTH_NOTE, BASS_VOLUME},

    {C3, EIGHTH_NOTE, BASS_VOLUME},
    {C3, SIXTEENTH_NOTE, BASS_VOLUME},

    {C4, SIXTEENTH_NOTE, BASS_VOLUME},

    {B2, EIGHTH_NOTE, BASS_VOLUME},
    {B2, SIXTEENTH_NOTE, BASS_VOLUME},

    {B3, SIXTEENTH_NOTE, BASS_VOLUME},

    {B2, EIGHTH_NOTE, BASS_VOLUME},
    {B2, SIXTEENTH_NOTE, BASS_VOLUME},

    {B3, SIXTEENTH_NOTE, BASS_VOLUME},

    {F2_SHARP, EIGHTH_NOTE, BASS_VOLUME},
    {G2_SHARP, EIGHTH_NOTE, BASS_VOLUME},
    {A2_SHARP, EIGHTH_NOTE, BASS_VOLUME},
    {B2, EIGHTH_NOTE, BASS_VOLUME}

};
int generate_frequency(int base_note, UCHAR8 target_octave) {
    return (base_note >> target_octave);
}
void start_music() {
    
}
/*Returns true when the song is finished*/
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
void update_song(int treble_channel, const Note treble_song[], int treble_song_length,
                 int bass_channel, const Note bass_song[], int bass_song_length,
                 int elapsed_time) { /* Add elapsed_time parameter */
    static int treble_note_index = 0, bass_note_index = 0;
    static int treble_note_time_left = 0, bass_note_time_left = 0;

    /* Update treble part */
    if (treble_note_time_left <= elapsed_time) { /* Adjust based on actual elapsed time */
        elapsed_time -= treble_note_time_left; /* Use residual time for the start of the next note */
        if (treble_note_index < treble_song_length) {
            play_note(treble_channel, treble_song[treble_note_index].frequency, treble_song[treble_note_index].volume);
            treble_note_time_left = treble_song[treble_note_index].duration - elapsed_time; /* Start next note accounting for residual time */
            treble_note_index++;
        } else {
            treble_note_index = 0; /* Loop or handle end of song */
        }
    } else {
        treble_note_time_left -= elapsed_time;
    }

    /* Update bass part in a similar manner to treble */
    if (bass_note_time_left <= elapsed_time) {
        elapsed_time -= bass_note_time_left;
        if (bass_note_index < bass_song_length) {
            play_note(bass_channel, bass_song[bass_note_index].frequency, bass_song[bass_note_index].volume);
            bass_note_time_left = bass_song[bass_note_index].duration - elapsed_time;
            bass_note_index++;
        } else {
            bass_note_index = 0;
        }
    } else {
        bass_note_time_left -= elapsed_time;
    }

    /* Check if both treble and bass parts have reached the end */
    if (treble_note_index >= treble_song_length && bass_note_index >= bass_song_length) {
        stop_sound();
        treble_note_index = 0; /* Reset for looping or finishing */
        bass_note_index = 0;
    }
}

void play_intro() {
    /*mom pick me up i'm scared :( */
}
void play_jaws_theme() {

}
void stop_music() {
    
}