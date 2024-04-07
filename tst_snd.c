#include "psg.h"
#include "TYPES.H"
#include "music.h"
#include "effects.h"
#include <stdio.h>
#include <osbind.h>

typedef unsigned char GAME_STATE;

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
    int treble_song_length = sizeof(pacman_intro_treble) / sizeof(Note);
    int bass_song_length = sizeof(pacman_intro_bass) / sizeof(Note);
    bool song_finished = FALSE;

    int waka_repetitions = 10; 
    int current_index = 0;
    int time_left = 0;

    MusicState trebleState = {0, 0};
    MusicState bassState = {0, 0};
    SoundState wakaState = {0, 0};
    SoundState wakaNoise = {0, 0};

/* ~~~~~~~~~~~~~~~~~~~~~~~ PLAY PACMAN INTRO ~~~~~~~~~~~~~~~~~~~~~~ */

    old_ssp = Super(0);
    enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
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
            update_music(CHANNEL_A, pacman_intro_treble, treble_song_length, &trebleState);
            song_finished = update_music(CHANNEL_B, pacman_intro_bass, bass_song_length, &bassState); 
            Super(old_ssp);
        }
    }
    
/* ~~~~~~~~~~~~~~~~~~~~~~~~ PLAY WAKA WAKA SOUND ~~~~~~~~~~~~~~~~~~~~~*/
    old_ssp = Super(0);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_ON);
    enable_channel(CHANNEL_B, TONE_ON, NOISE_ON);
    Super(old_ssp);

    while (waka_repetitions > 0) {
        time_now = get_time();
        time_elapsed = time_now - time_then;

        if (time_elapsed >= 1) { 
            time_then = time_now;

            if (Cconis()) {
                input = (char)Cnecin();
            }

            old_ssp = Super(0);
            play_waka_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState); 
            play_waka_sound(CHANNEL_B, waka_noise_cycle, WAKA_CYCLE_LENGTH, &wakaNoise); 
            Super(old_ssp);

            if (time_left <= 0) {
                waka_repetitions--;

                current_index = 0;
                time_left = waka_sound_cycle[0].duration; 
            }
        }
    }
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
/* Implementations for setNoteFrequency, setVolume, and enableChannel would go here */
GAME_STATE update_game_state(GAME_STATE new_state, char input) {

    /*Do something that updates the gamestate*/
    GAME_STATE state;
    if (input == '\033')
        state = QUIT;
    
    state = new_state;
    return state;


}