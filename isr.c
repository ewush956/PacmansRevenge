
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

volatile UCHAR8 * const IKBD_control = 0xFFFC00;
volatile const UCHAR8 *const IKBD_status = 0xFFFC00;
volatile const SCANCODE * const IKBD_RDR = 0xFFFC02;            /* receive data register */

volatile UCHAR8  *const in_service_register_b = 0xFFFA11;            /* clear bit #6 of this*/ 
volatile UCHAR8 *const interrupt_enable_b = 0xFFFA09;               /* disable interrupts for MIDI*/



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


void do_IKBD_isr()
{
    
    /*if ((*IKBD_status & 0x80) == 0) /**/

    SCANCODE code = *IKBD_RDR;

    if ((code & 0x80) != 0x80) {                /* not enqueuing break codes as we dont want to HOLD w a s or d to move*/   
        
        tail = (tail + 1) % 256;
        keyboard_buffer[tail] = code;
        fill_level++;
    }
    else if (code == ESC_BREAK)
    {
        tail = (tail + 1) % 256;
        keyboard_buffer[tail] = code;
        fill_level++;   
    }


    *in_service_register_b &= CLEAR_BIT_6; 



}
void disable_MIDI_interrupts()
{
    long old_ssp = Super(0);
    *interrupt_enable_b &= DISABLE; 
    /**interrupt_enable_b = DISABLE;*/
    Super(old_ssp);
}
void enable_MIDI_interrupts()
{
    long old_ssp = Super(0);
    *interrupt_enable_b |= ENABLE; 
    /**interrupt_enable_b = 0xFF; */
    Super(old_ssp);
}



/*****************
*   Purpose: Initializes the cirecular queue keyboard buffer struct
*
***************
void initialize_queue (Queue *queue)
{
    queue->head = 0;
    queue->tail = 0;
    queue->fill_level = 0;

}*/