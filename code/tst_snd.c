#include "psg.h"
#include "TYPES.H"
#include "music.h"
#include "effects.h"
#include "globals.h"
#include <stdio.h>
#include <osbind.h>

#define QUIT ((UCHAR8)0)
#define PLAYING ((UCHAR8)1)

ULONG32 get_time();
GAME_STATE update_game_state(GAME_STATE new_state, char input);

int main() {
    long old_ssp; 
    char input;
    GAME_STATE state = PLAYING;
    ULONG32 time_then = get_time(), time_now;
    ULONG32 time_elapsed;
    int treble_song_length = PACMAN_INTRO_TREBLE_LENGTH;
    int bass_song_length = PACMAN_INTRO_BASS_LENGTH;
    bool song_finished = FALSE;

    int waka_repetitions = 5; 
    int current_index = 0;
    int time_left = 0;

    SoundState trebleState = {0, 0};
    SoundState bassState = {0, 0};
    SoundState wakaState = {0, 0};
    SoundState wakaNoise = {0, 0};
    printf("Press anykey to continue\n");
    old_ssp = Super(0);
    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
    play_note(CHANNEL_C, C3_SHARP, 10);
    play_note(CHANNEL_A, C4_SHARP, 12);
    play_note(CHANNEL_B, A3, 15);
    while (!Cconis()){
    }
    
    Super(old_ssp);
/* ~~~~~~~~~~~~~~~~~~~~~~~ PLAY PACMAN INTRO ~~~~~~~~~~~~~~~~~~~~~~ */

    old_ssp = Super(0);
    enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    enable_channel(CHANNEL_C, TONE_OFF, NOISE_OFF);
    Super(old_ssp);

    while (song_finished == FALSE) {
        time_now = get_time();
        time_elapsed = time_now - time_then; 

        if (time_elapsed >= 5) { 
            time_then = time_now;
            if (Cconis()) {
                input = (char)Cnecin();
            }

            old_ssp = Super(0);
            play_sound(CHANNEL_A, pacman_intro_treble, treble_song_length, &trebleState);
            song_finished = play_sound(CHANNEL_B, pacman_intro_bass, bass_song_length, &bassState); 
            Super(old_ssp);
        }
    }
    /* ~~~~~~~~~~~~~~~~~~~~~~~ RANDOM CHORD ~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~~~~~~~~~~~~~~~~~~~~~~ DONE TESTS ~~~~~~~~~~~~~~~~~~~~~~ */
    old_ssp = Super(0);
    set_master_volume(0);
    Super(old_ssp);
    printf("Done :)\n");
    return 0;
}
ULONG32 get_time()
{

	ULONG32 *timer = (ULONG32 *)0x462; 		/* address of longword auto-inc’ed 70 x per second */
	ULONG32 timeNow;
	ULONG32 old_ssp;
	old_ssp = Super(0); 				/* enter privileged mode */
	timeNow = *timer;
	Super(old_ssp); 					/* exit privileged mode as soon as possible */

	return timeNow;

}
GAME_STATE update_game_state(GAME_STATE new_state, char input) {

    /*Do something that updates the gamestate*/
    GAME_STATE state;
    if (input == '\033')
        state = QUIT;
    
    state = new_state;
    return state;


}