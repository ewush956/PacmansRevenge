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
    const char* notes[] = {"C4", "E4", "G4"}; /* Note names for display */
    unsigned char volume; /* Volume for the current channel */

    /* Enter supervisor mode if necessary */
    old_ssp = Super(0);

    /* Test each channel sequentially with different notes and increasing volumes */
    for(channel = 0; channel < 3; channel++) {
        volume = 5 + channel * 5; /* Increasing volume: 5, 10, 15 */

        printf("Testing Channel %d with Note %s at Volume %d\n", channel, notes[channel], volume);

        /* Set the frequency for the current channel */
        set_note_frequency(channel, frequencies[channel]);

        /* Initially disable all channels to ensure a clean state */
        for(int i = 0; i < 3; i++) {
            enable_channel(i, 0, 0); /* Disable both tone and noise */
        }

        /* Enable the current channel with tone only */
        enable_channel(channel, 1, 0);

        /* Set the volume for the current channel */
        set_volume(channel, volume);

        /* Tone now playing, await key */
        while (!Cconis())
            ;
        
        set_master_volume(0);
        /* Optionally, add a brief message indicating the test is complete */
        printf("Test Complete for Channel %d. Press any key to continue...\n", channel);

        /* Await keypress to proceed */
        Cnecin();
    }

    /* Reset volumes to 0 to silence the PSG after testing */
    for(channel = 0; channel < 3; channel++) {
        setVolume(channel, 0);
    }

    /* Return to original processor state */
    Super(old_ssp);
    return 0;
}

/* Implementations for setNoteFrequency, setVolume, and enableChannel would go here */
