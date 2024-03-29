#include "effects.h"
#include "psg.h"
#include "TYPES.H"

#define WAKA_VOLUME 12
#define WAKA_NOISE 14

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
void play_kill_ghost_sound(){

	/*long old_ssp = Super(0);*/

	write_psg(4,255);
	write_psg(5,1);
	write_psg(6,0x0F);
	enable_channel(CHANNEL_C, TONE_OFF, NOISE_ON);

    set_volume(CHANNEL_A, 3);   /* set channel A */
    set_volume(CHANNEL_B, 4);   /* set channel B */
	set_volume(CHANNEL_C, 15);   /* set channel C */
	set_envelope(0,0x0700);

	/*Super(old_ssp);*/
}