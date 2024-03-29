
#include <osbind.h>

#include "isr.h"    
#include "TYPES.H"
#include "globals.h"
#include "music.h"
#include "effects.h"
#include "model.h"
#include "pacman.h"
#include "input.h"

int seconds = 0;
SoundState wakaState = {0, 0};
SoundState wakaNoise = {0, 0};
SoundState killState = {0, 0};

Vector install_vector(int num, Vector vector)
{
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);

    return orig;
}


void do_vbl()
{
    char input;
    ticks++;

    if ( seconds > 8 && request_to_render == TRUE)
    {
        if (game_over_flag == TRUE) {
            stop_sound();
            return;
        }
        update_movement(&entity);
        update_current_frame(&entity, ticks);
        if (kill_ghost_flag == TRUE) {
            if (play_sound(CHANNEL_C, ghost_kill_sound_cycle, GHOST_KILL_CYCLE_LENGTH, &killState) == TRUE)
                kill_ghost_flag = FALSE;
        }
        if (single_waka_playing == TRUE) {
            if (play_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState) == TRUE) 
                single_waka_playing = FALSE;
        }

        else if (waka_playing == TRUE) {
            play_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState); 
            if (play_sound(CHANNEL_B, waka_noise_cycle, WAKA_CYCLE_LENGTH, &wakaNoise) == TRUE) 
                waka_playing = FALSE;
        }
        else {
            if ( cell_map[entity.pacman->move->y_cell_index][entity.pacman->move->x_cell_index - 1].has_pellet == TRUE ||
                 cell_map[entity.pacman->move->y_cell_index][entity.pacman->move->x_cell_index + 1].has_pellet == TRUE ||
                 cell_map[entity.pacman->move->y_cell_index - 1][entity.pacman->move->x_cell_index].has_pellet == TRUE ||
                 cell_map[entity.pacman->move->y_cell_index + 1][entity.pacman->move->x_cell_index].has_pellet == TRUE)
            {
                waka_playing = TRUE;
                play_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState);
                play_sound(CHANNEL_B, waka_noise_cycle, WAKA_CYCLE_LENGTH, &wakaNoise);
            }  
            else {
                single_waka_playing = TRUE;
                play_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState);
            }
        }        
   }

    if (ticks == 70){
        seconds++;
        ticks = 0;
    }
    time_now++;
    request_to_render = TRUE; 
}