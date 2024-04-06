#include "pacman.h"
#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"
#include "events.h"
#include "music.h"
#include "effects.h"
#include "input.h"

#include "globals.h" 
#include "isr.h"

#include "splash.h"
#include "win_scr.h"
#include "lose_scr.h"

#include <osbind.h>
#include <stdio.h>
#include <linea.h>

/************************* KNOWN BUGS ***************************
 * 
 * 1. Occasionally ghost movement causes half of a pellet sprite
 *    to render on either the back or the front buffer causing flickering
 *    
 *    This has been PARTIALLY fixed, the fix we came up with at re renders the pellet
 *    but you can still see some flickering behind the ghost. 
 * 
 * 2. Ghosts frames are not being updated properly, like an issue with ticks or seconds in ISR.C
 * 
 * 3. The cyclops ghost's eye is not properly centered in some of it's alternate frames
 *    causing the movement to look jittery. This is an issue with it's bitmap.
 * 
 * 4. When killing a ghost, the event triggered "kill ghost" sound plays while pacman
 *    is in the vasinity of the tombstone, once pacman leaves the sound stops.
 *    it's supposed to only play once. I like how it sounds though :)
 * 
 * 5. Ghosts don't clear properly when being eaten, and occasionally "jump" leaving a flickering 
 *    trail, this is not an issue with double buffering, it's most an error in the game logic.
 * 
 ************************* TO DO **********************************
 *
 * 1. Games loose condition. Proximity checking has been added,
 *    we just need to implement the loosing event. (timer)
 *  
 * 
 * 2. Add a timer to the game.
 * 
 *********************************************************************/

UCHAR8  background[BUFFER_SIZE_BYTES];
UCHAR8  screen_buffer[BUFFER_SIZE_BYTES];
GAME_STATE state = MENU; /**/
        
/*******************************************************************
 * Function: initialize_game
 * Purpose: Initializes the game, manually moves the ghosts out of the center
 *          and plays intro music
 ******************************************************************/
int main () 
{

    menu();

    return 0;
}


void initialize_game(ULONG32* base32, ULONG32* back_buffer_ptr, Entities* entity) 
{
    SoundState  trebleState = {0, 0};
    SoundState  bassState   = {0, 0};
    UCHAR8*     base8       = (UCHAR8*)base32;
    UCHAR8*     back8       = (UCHAR8*)back_buffer_ptr;
    ULONG32     song_now, song_then, time_elapsed; 
    long old_ssp; 
    int  treble_song_length = PACMAN_INTRO_TREBLE_LENGTH;
    int  bass_song_length   = PACMAN_INTRO_BASS_LENGTH;
    int  initial_moves[5]   = {0,1,2,3,4};
    int  moves_index        = 0;
    int  intro_duration     = 0;
    int  first_frames       = 0;
    int* intro_duration_ptr = &intro_duration;
    int* indx_ptr           = &moves_index;
    bool song_finished      = FALSE;
    bool stop_ghosts        = FALSE;
    bool enable             = TRUE;
    int orig_ipl;
    int orig_ssp;

    init_map_cells(cell_map, tile_map);    
    clear_and_render_maps(base32, back_buffer_ptr);
    render_map(back_buffer_ptr, tile_map);
    clear_and_render_entities(base32, back_buffer_ptr, entity);
    set_first_movements(base32, base8, entity);
    initialize_sound(&old_ssp, &trebleState, &bassState);
    
    while (!song_finished) {
        song_finished = update_sound(&old_ssp, &song_then, &trebleState, &bassState, 
                                     treble_song_length, bass_song_length, intro_duration_ptr
                                     );
        if (*intro_duration_ptr > START_MUSIC_THRESHOLD) {
            
            if (first_frames > FIRST_STOP - 1) {
                stop_ghosts = execute_movements_and_render_frame(base32, base8, back8, entity, indx_ptr, initial_moves);
                first_frames = 0;
            }
            if (stop_ghosts == FALSE && request_to_render == TRUE) {
                manually_move_ghost(back_buffer_ptr, entity, 1, stop_ghosts);
                swap_buffers(&base32, &back_buffer_ptr);

                old_ssp = Super(0);
                set_video_base(base32);  
                Super(old_ssp);
                request_to_render = FALSE; 
                first_frames++;
            }
        }
    }
    state = PLAY;
}

void menu()
{
    UCHAR8 input;
    long old_ssp;
    int orig_ssp;
    int orig_ipl;
    int  buffer_offset        = 256 - ((long)(screen_buffer) % 256); 
    ULONG32* back_buffer_ptr  = (ULONG32*)(&screen_buffer[buffer_offset]);
    ULONG32* original         = get_video_base();
    ULONG32* base32           = get_video_base();
    UINT16* base16            = (UINT16*)base32;

    plot_screen(base32, splash);
    install_custom_vectors(); 
    initialize_mouse(); 
    render_mouse(base16);
    
    while (state == MENU)
    {
        
        if (fill_level > 0)
        {
            orig_ssp = Super(0);                     
            orig_ipl = set_ipl(7);
            Super(orig_ssp);

            input = dequeue();
            
            orig_ssp = Super(0);
            set_ipl(orig_ipl);
            Super(orig_ssp); 

            process_keyboard_input(input);
        }
        if (left_button_pressed == TRUE)    /*the in bounds logic is checked within the update_mouse*/
        {     
            clear_screen_q(base32);
            game_loop();
        }
        if (request_to_render == TRUE)
        {  
            update_mouse();
            restore_mouse_background(base32,splash,old_mouse_x,old_mouse_y); 
            render_mouse(base16);
            request_to_render = FALSE;
        } 
     
    }
  
    if (state == WIN){
        plot_screen(original, win_splash);
        game_over_flag = TRUE;
    }
    
    if (state == QUIT){
        clear_screen_q(base32);
    }

    remove_custom_vectors();

   
}
/*******************************************************************
 * Function: game_loop
 * Purpose: executes main game loop
 ******************************************************************/
void game_loop() 
{
    int  i;
	UCHAR8 input;
    int  waka_repetitions    = 10; 
    int  buffer_offset       = 256 - ((long)(screen_buffer) % 256); 
    int  background_offset   = 256 - ((long)(background) % 256);
    long old_ssp; 
    int orig_ipl;
    int orig_ssp;
    ULONG32* base32          = (ULONG32*)get_video_base();
    ULONG32* original        = get_video_base();
    ULONG32* back_buffer_ptr = (ULONG32*)(&screen_buffer[buffer_offset]); 

    initialize_game(base32, back_buffer_ptr, &entity);

    while (state != QUIT && state != WIN) 
    {
        if (fill_level > 0){
            orig_ssp = Super(0);                        /* mask all intrpts before enQing */
            orig_ipl = set_ipl(7);
            Super(orig_ssp);

            input = dequeue();
            process_keyboard_input(input);

            orig_ssp = Super(0);
            set_ipl(orig_ipl);
            Super(orig_ssp);
        }

        if (request_to_render == TRUE){  
            render_frame(back_buffer_ptr, &entity);
            swap_buffers(&base32, &back_buffer_ptr);

            old_ssp = Super(0); 
            set_video_base(base32);
            Super(old_ssp);
            request_to_render = FALSE; 
        }  
        state = update_game_state(state, input, &entity);
    }
    
    old_ssp = Super(0);
    stop_sound();
    set_video_base(original);
    Super(old_ssp);	
}
/******************************************************************
* Function: update_entities
* Purpose: Updates the position of the ghosts and pacman
*******************************************************************/
void update_entities() {

    move_pacman(&pacman);
    move_ghost(&moustache_ghost);
    move_ghost(&crying_ghost);
    move_ghost(&cyclops_ghost);
    move_ghost(&awkward_ghost);
    
}
/*******************************************************************
 * Function: update_movement
 * Purpose: Super call to all movement functions
 * 
 * Parameters: entity, input, ticks
 ******************************************************************/
void update_movement(Entities* entity) {

    handle_collisions(entity);   
    update_entities();
    update_cells(entity);
    eat_pellet(entity->pacman->move);
    check_proximity(entity);   
} 
void page_flip(ULONG32* base32, ULONG32* back_buffer_ptr)
{
    long old_ssp;

    render_frame(back_buffer_ptr, &entity);
    swap_buffers(&base32, &back_buffer_ptr);

    old_ssp = Super(0); 
    set_video_base(base32);
    Super(old_ssp);


}
/*******************************************************************
 * Function: update_game_state
 * Purpose: Updates the game state
 * Parameters: new_state, input
 * Returns: GAME_STATE
 ******************************************************************/
GAME_STATE update_game_state(GAME_STATE new_state, UCHAR8 input, Entities* all) {

    GAME_STATE state;
    if (input == ESC_BREAK)
    {
        state = QUIT;
        return state;
    }
    if (all->awkward_ghost->state == DEAD && 
        all->crying_ghost->state == DEAD &&
        all->moustache_ghost->state == DEAD &&
        all->cyclops_ghost->state == DEAD) {
        return WIN; 
    }
    return new_state;
}

/*******************************************************************
 * Function: swap_buffers
 * Purpose: Swaps the adress of the front and back buffers
 * Parameters: base32, back_buffer_ptr
 ******************************************************************/
void swap_buffers (ULONG32** base32, ULONG32** back_buffer_ptr)
{
    ULONG32* temp = *base32;
    *base32 = *back_buffer_ptr;
    *back_buffer_ptr = temp;
}
/*******************************************************************
 * Function: manually_move_ghost
 * Purpose: Manually moves the ghost
 * Parameters: base, entity, frame_index
 *******************************************************************/
void manually_move_ghost(ULONG32* base, Entities* entity, int frame_index, bool enable) {
    Movement* moustache_ghost = entity->moustache_ghost->move;
    Movement* awkward_ghost = entity->awkward_ghost->move;
    Movement* crying_ghost = entity->crying_ghost->move;
    Movement* cyclops_ghost = entity->cyclops_ghost->move;

    if (enable != TRUE) {
        update_cell(awkward_ghost, entity->awkward_ghost->state);
        update_cell(moustache_ghost, entity->moustache_ghost->state);
        update_cell(crying_ghost, entity->crying_ghost->state);
        update_cell(cyclops_ghost, entity->cyclops_ghost->state);

        move_ghost(entity->crying_ghost);
        move_ghost(entity->awkward_ghost);
        move_ghost(entity->moustache_ghost);
        move_ghost(entity->cyclops_ghost);

        update_current_frame(entity, frame_index);
	    render_frame(base, entity);
    }

}  
/*******************************************************************
 * Function: clear_and_render_maps
 * Purpose: Clears and renders the map
 ******************************************************************/
void clear_and_render_maps(ULONG32* base32, ULONG32* back_buffer_ptr) {
    clear_screen_q(base32);
    render_map(base32, tile_map);
    render_map(back_buffer_ptr, tile_map);
}
/*******************************************************************
 * Function: clear_and_render_entities
 * Purpose: Clears and renders the entities
 ******************************************************************/
void clear_and_render_entities(ULONG32* base32, ULONG32* back_buffer_ptr, Entities* entity) {
    clear_entities(base32, pacman.move, crying_ghost.move, moustache_ghost.move, awkward_ghost.move, cyclops_ghost.move);

    render_frame(base32, entity);
    render_frame(back_buffer_ptr, entity);
}
/*******************************************************************
 * Function: execute_movements_and_render_frame
 * Purpose: Executes the predetermined initial movements and renders the frame.
 *          Updates moves_index by refference.
 ******************************************************************/
bool execute_movements_and_render_frame(ULONG32* base32, UCHAR8* base8, UCHAR8* back8, Entities* entity, int* moves_index, int initial_moves[5]) {
    bool stop_ghosts = FALSE;
    switch (initial_moves[*moves_index])
    {
    case 0:
        set_second_movements(base32, base8, entity);
        (*moves_index)++;
        break;

    case 1:
        set_third_movements(base32, base8, entity);
        (*moves_index)++;
        break;

    case 2:
        set_third_movements(base32, base8, entity);
        (*moves_index)++;
        break;

    case 3:
        (*moves_index)++;
        break;

    case 4:
        stop_ghosts = TRUE;
        break;
    return stop_ghosts;
    }
}
/******************************************************************
 * Function: initialize_sound
 * Purpose: Enables channels A and B for sound
******************************************************************/
void initialize_sound(long* old_ssp, SoundState* trebleState, SoundState* bassState) {
    *old_ssp = Super(0);
    enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    Super(*old_ssp);
}
/*******************************************************************
 * Function: update_sound
 * Purpose: Updates the the state of a song (note structure) 
 *          returns TRUE if the song has finished.
 *****************************************************************/
bool update_sound(long* old_ssp, ULONG32* time_then, SoundState* trebleState, SoundState* bassState, int treble_song_length, int bass_song_length, int* intro_duration) {

    ULONG32 time_elapsed = time_now - *time_then;
    bool song_finished;
    int tempo = 5;

    if (time_elapsed >= tempo) {
        *time_then = time_now;

        *old_ssp = Super(0);
        play_sound(CHANNEL_A, pacman_intro_treble, treble_song_length, trebleState);
        song_finished = play_sound(CHANNEL_B, pacman_intro_bass, bass_song_length, bassState);
        Super(*old_ssp);
        (*intro_duration)++;
        return song_finished;
    }
    return FALSE;
}
/******************************************************************
 * Function: set_first_movements
 * Purpose: Sets the first movements of the ghosts
 * Parameters: base32, base8, entity
 * Returns: void
 ******************************************************************/
void set_first_movements(ULONG32* base32, UCHAR8* base8, Entities* entity){
    crying_ghost.move->delta_x = 1;
	crying_ghost.move->delta_y = 0;
    crying_ghost.move->direction = RIGHT;

    awkward_ghost.move->delta_x = -1;
    awkward_ghost.move->delta_y = 0;
    awkward_ghost.move->direction = LEFT;

    cyclops_ghost.move->delta_x = 0;
    cyclops_ghost.move->delta_y = -1;
    cyclops_ghost.move->direction = UP;

    moustache_ghost.move->delta_x = 0;
    moustache_ghost.move->delta_y = 1;
    moustache_ghost.move->direction = DOWN;
}
void set_second_movements(ULONG32* base32, UCHAR8* base8, Entities* entity){

    moustache_ghost.move->delta_x = 1;
    moustache_ghost.move->delta_y = 0;
    moustache_ghost.move->direction = RIGHT;

    cyclops_ghost.move->delta_x = -1;
    cyclops_ghost.move->delta_y = 0;
    cyclops_ghost.move->direction = LEFT;
}
void set_third_movements(ULONG32* base32, UCHAR8* base8, Entities* entity){
    crying_ghost.move->delta_x = 0;
    crying_ghost.move->delta_y = -1;
    crying_ghost.move->direction = UP;

    awkward_ghost.move->delta_x = 0;
    awkward_ghost.move->delta_y = 1;
    awkward_ghost.move->direction = DOWN;
}
