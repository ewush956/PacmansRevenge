
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
/*bool is_waka_playing = FALSE; /* */

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

   
   if ( seconds > 7 && request_to_render == TRUE)
   {
       if (cell_map[entity.pacman->move->y_cell_index][entity.pacman->move->x_cell_index - 1].has_pellet == TRUE ||
            cell_map[entity.pacman->move->y_cell_index][entity.pacman->move->x_cell_index + 1].has_pellet == TRUE ||
            cell_map[entity.pacman->move->y_cell_index - 1][entity.pacman->move->x_cell_index].has_pellet == TRUE ||
            cell_map[entity.pacman->move->y_cell_index + 1][entity.pacman->move->x_cell_index].has_pellet == TRUE)
       {
            play_waka_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState); 
            play_waka_sound(CHANNEL_B, waka_noise_cycle, WAKA_CYCLE_LENGTH, &wakaNoise);
        
        } 
        else{
            stop_sound();
        }
       
           
        update_movement(&entity, ticks);
        update_current_frame(&entity, ticks);
        
   }

    if (ticks == 70){
        seconds++;
        ticks = 0;
    }

    time_now++;

    request_to_render = TRUE; 


}