
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
bool is_waka_playing = FALSE;

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

    /*
    if (seconds > 8 && cell_map[entity.pacman->move->y_cell_index][entity.pacman->move->x_cell_index].has_pellet)
    {
        if (is_waka_playing == FALSE)
        {   
            /* (mask interrupts before this plays and unmask them after the end of the sound)
            play_waka_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState); 
            play_waka_sound(CHANNEL_B, waka_noise_cycle, WAKA_CYCLE_LENGTH, &wakaNoise);
            is_waka_playing = TRUE;
        } 
        else   
        {
            is_waka_playing = FALSE;
        }
    }
    */  
    /*
    input = get_input();
    */

   if (request_to_render == TRUE)
   {
        /*
        update_movement(&entity, ticks);
        update_current_frame(&entity, ticks);
        */
   }

    if (ticks == 70){
        seconds++;
        ticks = 0;
    }

    time_now++;

    request_to_render = TRUE; 


}