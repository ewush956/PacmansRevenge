#include "music.h"
#include "TYPES.H"
#include "psg.h"

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
