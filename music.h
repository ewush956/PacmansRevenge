#include "TYPES.H"

typedef struct {
    const char* name;
    int frequency;
} Note;

#define NUM_NOTES 12
#define FIRST_OCTAVE 0
#define SECOND_OCTAVE 1
#define THIRD_OCTAVE 2
#define FOURTH_OCTAVE 3
#define FIFTH_OCTAVE 4
#define SIXTH_OCTAVE 5
#define SEVENTH_OCTAVE 6
#define EIGHTH_OCTAVE 7

#define NOTE_C 0xD5D
#define NOTE_C_SHARP 0xC9C
#define NOTE_D 0xBE7
#define NOTE_D_SHARP 0xB3C
#define NOTE_E 0xA9B
#define NOTE_F 0xA02
#define NOTE_F_SHARP 0x973
#define NOTE_G 0x8EB
#define NOTE_G_SHARP 0x86B
#define NOTE_A 0x7F2
#define NOTE_A_SHARP 0x780
#define NOTE_B 0x714

extern const Note notes[12];

int generate_frequency(int base_note, UCHAR8 target_octave);
void play_note(int channel, int base_note, UCHAR8 octave, int duration);