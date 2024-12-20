
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
void advance_sound ();
SoundState wakaState = {0, 0};
SoundState wakaNoise = {0, 0};
SoundState killState = {0, 0};
volatile UCHAR8 * const IKBD_control = 0xFFFC00;
volatile const UCHAR8 *const IKBD_status = 0xFFFC00;
volatile const SCANCODE * const IKBD_RDR = 0xFFFC02;            /* receive data register */
volatile UCHAR8  *const in_service_register_b = 0xFFFA11;       /* clear bit #6 of this*/ 
volatile UCHAR8 *const interrupt_enable_b = 0xFFFA09;           /* disable interrupts for MIDI*/

Vector orig_vector28;
Vector orig_vector70;

UCHAR8 mouse_delta_x;
UCHAR8 mouse_delta_y;
UCHAR8 mouse_button = 0;

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
/*************************************************************
 * Function: do_vbl
 * Purpose:  Handles the VBL interrupt via trap #28
 *************************************************************/
void do_vbl()
{
    ticks++;
    time_now++;
    
    if (request_to_render == TRUE && state == PLAY) { advance_sound(); }
    if (ticks == 70) {
        seconds++;
        second_has_passed = TRUE;
        ticks = 0;
    }
    request_to_render = TRUE; 
}
void do_IKBD_isr()
{   
    SCANCODE code = *IKBD_RDR;

    switch(ikbd_state)
    {
        case KEYBOARD_INPUT:
            if ((code & 0x80) == 0x00 || code == ESC_BREAK) {    
                enqueue(code);
            }
            else if (code >= 0xF8){
                mouse_button = code;
                ikbd_state = MOUSE_DELTA_X;
            }
            break;

        case MOUSE_DELTA_X: 
            mouse_delta_x = code;
            ikbd_state = MOUSE_DELTA_Y;
            break;

        case MOUSE_DELTA_Y:
            mouse_delta_y = code;
            ikbd_state = KEYBOARD_INPUT;
            break;

        default:
            break;
    }

   *in_service_register_b &= CLEAR_BIT_6; 
}


void update_mouse()
{

    old_mouse_x = global_mouse_x;
    old_mouse_y = global_mouse_y;

    global_mouse_x += (int)((char)mouse_delta_x); 
    global_mouse_y += (int)((char)mouse_delta_y);

    if (global_mouse_x < 0){
        global_mouse_x = 0;
    }
    else if (global_mouse_x >= MAX_MOUSE_X_BOUND) {
        global_mouse_x = MAX_MOUSE_X_BOUND;
    }

    if (global_mouse_y < 0){ 
        global_mouse_y = 0;
    }

    else if(global_mouse_y >= MAX_MOUSE_Y_BOUND ){
        global_mouse_y = MAX_MOUSE_Y_BOUND;
    }

    if (mouse_button == LEFT_CLICK && is_mouse_in_bounds() ) {
        left_button_pressed = TRUE;
        mouse_button = 0;
    }
 
    mouse_delta_x = 0;
    mouse_delta_y = 0;
}


bool is_mouse_in_bounds()
{
    if (global_mouse_x > BOX_MIN_X && global_mouse_x < BOX_MAX_X)
    {   
        if (global_mouse_y > ONE_PLAYER_BOX_MIN_Y && global_mouse_y < ONE_PLAYER_BOX_MAX_Y)  
            return TRUE;

        else if ( global_mouse_y > EXIT_BOX_MIN_Y && global_mouse_y < EXIT_BOX_MAX_Y)
        {   
            state = QUIT;
            return TRUE;
        }
    }   
    return FALSE;
}




void enqueue(SCANCODE code)
{
    
   tail = (tail + 1) & BUFFER_SIZE_255_HEX;
    keyboard_buffer[tail] = code;
    fill_level++;

}
UCHAR8 dequeue()
{
    UCHAR8 input;
    input = keyboard_buffer[head];
    head = (head + 1) & BUFFER_SIZE_255_HEX;
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

void initialize_mouse()
{
    int global_mouse_x = MIDDLE_OF_SCREEN_X;
    int global_mouse_y = MIDDLE_OF_SCREEN_Y;
   
}
void advance_sound () {

        if (end_game_flag == TRUE) {
            stop_sound();
            return; 
        }
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