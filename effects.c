#include "effects.h"
#include "psg.h"
#include "globals.h"
#include "TYPES.H"

const SoundCycle waka_sound_cycle[WAKA_CYCLE_LENGTH] = {
    {E4,        THIRTY_SECOND_NOTE, WAKA_VOLUME - 1},
    {G4_SHARP,  THIRTY_SECOND_NOTE, WAKA_VOLUME    },
    {C5,        THIRTY_SECOND_NOTE, WAKA_VOLUME    },
    {D5_SHARP,  THIRTY_SECOND_NOTE, WAKA_VOLUME    },
    {F5_SHARP,  THIRTY_SECOND_NOTE, WAKA_VOLUME    },
    {A5_SHARP,  THIRTY_SECOND_NOTE, WAKA_VOLUME    },

    {E1,        SIXTEENTH_NOTE,     1               },

    {B5,        THIRTY_SECOND_NOTE, WAKA_VOLUME     },
    {G5,        THIRTY_SECOND_NOTE, WAKA_VOLUME     },
    {E5,        THIRTY_SECOND_NOTE, WAKA_VOLUME     },
    {C5_SHARP,  THIRTY_SECOND_NOTE, WAKA_VOLUME     },
    {A4,        THIRTY_SECOND_NOTE, WAKA_VOLUME     },
    {F4,        THIRTY_SECOND_NOTE, WAKA_VOLUME     },
    {E1,        SIXTEENTH_NOTE,     0               }
};
const SoundCycle waka_noise_cycle[WAKA_CYCLE_LENGTH] = {
    {E3,        THIRTY_SECOND_NOTE, WAKA_NOISE - 1  },
    {G3_SHARP,  THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {C4,        THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {D4_SHARP,  THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {F4_SHARP,  THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {A4_SHARP,  THIRTY_SECOND_NOTE, WAKA_NOISE      },

    {E1,        SIXTEENTH_NOTE,     1               },

    {B4,        THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {G4,        THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {E4,        THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {C4_SHARP,  THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {A3,        THIRTY_SECOND_NOTE, WAKA_NOISE      },
    {F3,        THIRTY_SECOND_NOTE, WAKA_NOISE      },

    {E1,        SIXTEENTH_NOTE,     0               }
};

const int ghost_kill_volume = 15; 

const SoundCycle ghost_kill_sound_cycle[GHOST_KILL_CYCLE_LENGTH] = {
    {G4,        THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {A4,        THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {B4,        THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {C5,        THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {D5,        THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {E5,        THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {F5_SHARP,  THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {G5,        THIRTY_SECOND_NOTE, KILL_GHOST_VOLUME},
    {E5,        THIRTY_SECOND_NOTE, 0                }
};
/*
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
*/
void play_kill_ghost_sound(){

    kill_ghost_flag = TRUE;
}