
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
volatile UCHAR8 * const IKBD_control = 0xFFFC00;
volatile const UCHAR8 *const IKBD_status = 0xFFFC00;
volatile const SCANCODE * const IKBD_RDR = 0xFFFC02;            /* receive data register */
volatile UCHAR8  *const in_service_register_b = 0xFFFA11;       /* clear bit #6 of this*/ 
volatile UCHAR8 *const interrupt_enable_b = 0xFFFA09;           /* disable interrupts for MIDI*/
bool left_button_pressed = FALSE;
bool right_button_pressed = FALSE;
Vector orig_vector28;
Vector orig_vector70;

typedef enum {

    KEYBOARD_INPUT,
    MOUSE_HEADER,
    MOUSE_DELTA_X,
    MOUSE_DELTA_Y
}IKBDState;
IKBDState ikbd_state = KEYBOARD_INPUT;              


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

    if (seconds > START_DELAY && request_to_render == TRUE)
    {
        if (game_over_flag == TRUE) {
            stop_sound();
            /*return; */
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

void do_IKBD_isr()
{   
    SCANCODE code = *IKBD_RDR;

    switch(ikbd_state)
    {
        case KEYBOARD_INPUT:
            if ((code & 0x80) != 0x80 || code == ESC_BREAK) {       /* not enqueuing break codes as we dont want to HOLD w a s or d to move*/   
                enqueue(code);
            }
            else if (code >= 0xF8){
                ikbd_state = MOUSE_HEADER;
            }
                break;

        case MOUSE_HEADER:
            if (code & 0x02){
                left_button_pressed = TRUE;
            }
            else if (code & 0x01) {
                right_button_pressed = TRUE;
            }
            ikbd_state = MOUSE_DELTA_X;
            break;
        
        case MOUSE_DELTA_X:
            if (code & 0x80){
                global_mouse_x -= (int)(code & 0x7F);           /* clearing high bit with 0x7F*/
            }
            else{
                global_mouse_x += (int)(code & 0x7F);
            }

            if (global_mouse_x < 0){
                global_mouse_x = 0;
            }
            else if (global_mouse_x >= 640) {
                global_mouse_x = 639;
            }

            ikbd_state = MOUSE_DELTA_Y;
            break;
        
        case MOUSE_DELTA_Y:
            global_mouse_y += (int)(code & 0x7F);
            
            if (global_mouse_y < 0)
            {
                global_mouse_y = 0;
            }
            else if(global_mouse_y >= 399)
            {
                global_mouse_y = 399;
            }

            left_button_pressed = FALSE;
            right_button_pressed = FALSE;
            ikbd_state = KEYBOARD_INPUT;
            break;

        default:
            break;
    }

   *in_service_register_b &= CLEAR_BIT_6; 
}



void enqueue(SCANCODE code)
{
    tail = (tail + 1) % 256;
    keyboard_buffer[tail] = code;
    fill_level++;

}
UCHAR8 dequeue()
{
    UCHAR8 input;
    input = keyboard_buffer[head];
    head = (head + 1) % 256;
    fill_level--;

    return input;

}
void install_custom_vectors()
{
    disable_MIDI_interrupts();
    orig_vector28 = install_vector(TRAP_28, trap28_isr);
    orig_vector70 = install_vector(TRAP_70, trap70_isr);  
    enable_MIDI_interrupts();
}

void remove_custom_vectors()
{
    disable_MIDI_interrupts();
    install_vector(TRAP_28, orig_vector28);
    install_vector(TRAP_70, orig_vector70);
    enable_MIDI_interrupts();
}

void disable_MIDI_interrupts()
{
    long old_ssp = Super(0);
    *interrupt_enable_b &= DISABLE; 
    Super(old_ssp);
}
void enable_MIDI_interrupts()
{
    long old_ssp = Super(0);
    *interrupt_enable_b |= ENABLE; 
    Super(old_ssp);
}