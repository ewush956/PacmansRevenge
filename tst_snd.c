#include "psg.h"
#include "TYPES.H"
#include "music.h"
#include "effects.h"
#include <stdio.h>
#include <osbind.h>

#include <osbind.h>
#include <stdio.h>

int main() {
    long old_ssp; /* Store the original superuser stack pointer */
    int channel; /* Channel iterator */
    float frequencies[] = {261.63, 329.63, 392.00}; /* Frequencies for the C major chord: C4, E4, G4 */
    int hex_frequencies[] = {0x1AC, 0x153, 0x11D};
    const char* notes[] = {"C4", "E4", "G4"}; /* Note names for display */
    unsigned char volume; /* Volume for the current channel */
    int i;

    /* Enter supervisor mode if necessary */
    old_ssp = Super(0);

    /* Test each channel sequentially with different notes and increasing volumes */
    for(channel = 0; channel < 3; channel++) {

        /*volume = 5 + (channel * 5); */
        volume = 15;
        printf("Testing Channel %d with Note %s at Volume %d\n", channel, notes[channel], volume);

        /* Set the frequency for the current channel */
        /*set_note_frequency(channel, frequencies[channel]); */
        set_tone(channel, hex_frequencies[channel]);

        /* Enable the current channel with tone only */
        set_volume(channel, volume);

        enable_channel(channel, TONE_ON, NOISE_OFF);

        /* Set the volume for the current channel */

        /* Tone now playing, await key */
        while (!Cconis())
            ;
        
        /* Optionally, add a brief message indicating the test is complete */
        printf("Test Complete for Channel %d. Press any key to continue...\n", channel);
        enable_channel(channel, TONE_OFF, NOISE_OFF);
        /* Await keypress to proceed */
        Cnecin();
    }
    set_master_volume(0);

    /* Reset volumes to 0 to silence the PSG after testing */
    /* Return to original processor state */
    Super(old_ssp);
    return 0;
}

/* Implementations for setNoteFrequency, setVolume, and enableChannel would go here */
