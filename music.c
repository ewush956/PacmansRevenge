#include "music.h"
#include "TYPES.H"
#include "psg.h"

/*Might not be needed*/
const Note notes[] = {
    {"C1", NOTE_C},    
    {"C1_sharp", 0xC9C},
    {"D1", 0xBE7},    
    {"D1_sharp", 0xB3C},
    {"E1", 0xA9B},    
    {"F1", 0xA02},    
    {"F1_sharp", 0x973},
    {"G1", 0x8EB},    
    {"G1_sharp", 0x86B}, 
    {"A1", 0x7F2},    
    {"A1_sharp", 0x780}, 
    {"B1", 0x714}     
};

/***********************************************
 * Function Name: generate_note
 * Purpose: Shifts the octave of a note by a specified amount.
 *          Returns the hex frequency of the new note.
 * Parameters:
 *     - @param note (UCHAR8): The base note to shift.
 *     - @param octave (UCHAR8): The target octave.
 * *********************************************/
int generate_frequency(int base_note, UCHAR8 target_octave) {
    return (base_note >> target_octave);
}
void start_music() {
    
}
void update_music(ULONG32 time_elapsed) {
    
}
void play_intro() {
    /*mom pick me up i'm scared :( */
}
void play_jaws_theme() {

}
void stop_music() {
    
}