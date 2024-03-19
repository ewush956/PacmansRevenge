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

#include <osbind.h>
#include <stdio.h>
#include <linea.h>

/*ULONG32 combined_address;*/
volatile UCHAR8* ptr_to_highbyte = VIDEO_ADDR_HIGH;
volatile UCHAR8* ptr_to_lowbyte = VIDEO_ADDR_MID;


/************************* KNOWN BUGS ***************************
 * 1. Sometimes 3-4 pixels will plot right around a single pellet
 *    currently cause is unknown, might be due to bounds checking 
 *    on raster function 
 * 
 * 2. Occasionally ghost movement causes half of a pellet sprite
 *    to render on either the back or the front buffer causing flickering
 * 
 * 3. Pacman cannot initially move up(very first frame only), only left or right.
 *    This is because of the input detection.
 * 
 * 4. There is still a little bit of flickering when freeing the ghosts initially
 *    The double buffering appears to be solid in the main game loop, but it
 *    is not applied correctly in the initialize_game function.
 * 
 * 5. The screen occasionaly flashes, not sure if it's an issue with steem or not,
 *    seems to occur randomly.
 * 
 * 6. The cyclops ghost's eye is not properly centered in some of it's alternate frames
 *    causing the movement to look jittery. This is an issue with it's bitmap.
 * 
 ************************* STILL INCOMPLETE ***************************

 * 1. Games win / loose condition. Proximity checking has been added,
 *    we just need to implement the loosing / wining event
 * 
 * 2. Ghosts running from pacman
 * 
 * 3. Sound for eating a ghost / no sound when not eating a pellet.
 *    (currently waka waka sound is not event triggered, 
 *    it's just played in the main loop)
 * 
 *********************************************************************/

/**************************************************************************
* Declaration: Pacman pacman
* Purpose: Initializes the player character, Pacman, with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement pacman_movement = {
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,        
        0,0,        /*Initial Displacement*/
        UP,
        21,19,          /*Cell index -> y, x*/
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,
        FALSE
};
Pacman pacman = {
    0,
    UP,
    PACMAN,
    &pacman_movement
};
/*************************************************************
* Declaration: Ghost crying_ghost
* Purpose: Initializes the 'crying' ghost entity with its starting
*          position, movement displacement, state, direction, 
*          and cell index on the game map.
*************************************************************/
Movement crying_ghost_movement = {
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,     
        0,0,
        RIGHT,
        10, 17,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost crying_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CRYING,
    FALSE,
    &crying_ghost_movement
};

/*************************************************************
* Declaration: Ghost cyclops_ghost
* Purpose: Initializes the 'cyclops' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement cyclops_ghost_movement = {
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        12, 17,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost cyclops_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CYCLOPS,
    FALSE,
    &cyclops_ghost_movement
};
/*************************************************************
* Declaration: Ghost moustache_ghost
* Purpose: Initializes the 'moustache' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement moustache_ghost_movement = {
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        10, 21,
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost moustache_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_MOUSTACHE,
    FALSE,
    &moustache_ghost_movement
};

/*************************************************************
* Declaration: Ghost awkward_ghost
* Purpose: Initializes the 'awkward' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement awkward_ghost_movement = {
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        12, 21,
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET, 
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost awkward_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_AWKWARD,
    FALSE,
    &awkward_ghost_movement
};
/*************************************************************
* Declaration: Timer timer
* Purpose: Initializes the game timer with starting values
*          and thresholds for various game events.
*************************************************************/

Timer timer = {
    0,0,
    20, 28, 44, 52
};

UCHAR8 background[BUFFER_SIZE_BYTES];
UCHAR8 screen_buffer[BUFFER_SIZE_BYTES];

int main()
{
    Entities entity = {
        &pacman,
        &crying_ghost,
        &awkward_ghost,
        &moustache_ghost,
        &cyclops_ghost,
    };
    int i;
	char input;
    int waka_repetitions = 10; 
    int buffer_offset = 256 - ((long)(screen_buffer) % 256); 
    long old_ssp; 

	UCHAR8 collision_type = 0;
    UINT16 ticks = 0;
	ULONG32 time_then, time_now, time_elapsed;

    UCHAR8* base8 = (UCHAR8*)get_video_base();
    ULONG32* base32 = (ULONG32*)get_video_base();
    ULONG32* original = get_video_base();

    ULONG32* back_buffer_ptr = (ULONG32*)(&screen_buffer[buffer_offset]); 
    ULONG32* background_ptr = (ULONG32*)(&background[0]); /*Not using at the moment*/
  
    GAME_STATE state = PLAY;

    SoundState wakaState = {0, 0};
    SoundState wakaNoise = {0, 0};

    plot_screen(base32, splash);
    while (!Cconis());

    initialize_game(base32, back_buffer_ptr, &entity);
	if (Cconis())
	{
		input = (char)Cnecin();
	}
    
    while (state != QUIT) {

        time_now = get_time();
        time_elapsed = time_now - time_then;
        ticks = 0;

        if (Cconis())
        {
            input = (char)Cnecin();
        }
        if (time_elapsed > 0) {
/*
            old_ssp = Super(0);
            play_waka_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState); 
            play_waka_sound(CHANNEL_B, waka_noise_cycle, WAKA_CYCLE_LENGTH, &wakaNoise); 
            Super(old_ssp);
*/
            update_movement(&entity, input, ticks);
            if ((ticks & 7) == 0) {
                update_current_frame(&entity, ticks);   
            }
            render_frame(back_buffer_ptr, &entity);
            /*debug_pacman_movement(base32, &pacman);*/

            swap_buffers(&base32, &back_buffer_ptr);
            Setscreen(-1,base32,-1);  

            time_then = get_time();
            ticks = (++ticks & 63);
        }
        state = update_game_state(state, input);
    }
    old_ssp = Super(0);
    stop_sound();
    Super(old_ssp);
    Setscreen(-1,original,-1);
    clear_screen_q(original);

	return 0;
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
void update_movement(Entities* entity, char input, UINT16 ticks) {

    set_input(entity->pacman,input);
    handle_collisions(entity, ticks);   
    update_entities();
    eat_pellet(entity->pacman->move);
    update_cells(entity);
    check_proximity(entity);
    

} 
/*******************************************************************
 * Function: update_game_state
 * Purpose: Updates the game state
 * Parameters: new_state, input
 * Returns: GAME_STATE
 ******************************************************************/
GAME_STATE update_game_state(GAME_STATE new_state, char input) {

    /*Do something that updates the gamestate*/
    GAME_STATE state;
    if (input == '\033')
    {
        state = QUIT;
        return state;
    }

    state = new_state;

   return state;

}
/*******************************************************************
 * Function: get_time
 * Purpose: Gets the current time
 * Parameters: none
 * Returns: time
 * Note: time is in 70HZ
 ******************************************************************/
ULONG32 get_time()
{

	ULONG32 *timer = (ULONG32 *)0x462; 		
	ULONG32 timeNow;
	ULONG32 old_ssp;
	old_ssp = Super(0); 				
	timeNow = *timer;
	Super(old_ssp); 			

	return timeNow;

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
 * Function: initialize_game
 * Purpose: Initializes the game, manually moves the ghosts out of the center
 *          and plays intro music
 ******************************************************************/
void initialize_game(ULONG32* base32, ULONG32* back_buffer_ptr, Entities* entity) {
    MusicState trebleState = {0, 0};
    MusicState bassState = {0, 0};
    UCHAR8* base8 = (UCHAR8*)base32;
    UCHAR8* back8 = (UCHAR8*)back_buffer_ptr;

    ULONG32 time_then = get_time(), song_now, song_then, time_elapsed;
    long old_ssp; 
    int treble_song_length = sizeof(pacman_intro_treble) / sizeof(Note);
    int bass_song_length = sizeof(pacman_intro_bass) / sizeof(Note);
    int initial_moves[5] = {0,1,2,3,4};
    int moves_index = 0;
    int* indx_ptr = &moves_index;
    bool song_finished = FALSE;
    bool stop_ghosts = FALSE;
    int intro_duration = 0;
    int* intro_duration_ptr = &intro_duration;
    int first_frames = 0;
    bool enable = TRUE;

    int time_now = get_time();

    init_map_cells(cell_map, tile_map);    
    clear_and_render_maps(base32, back_buffer_ptr);
    clear_and_render_entities(base32, back_buffer_ptr, entity);
    set_first_movements(base32, base8, entity);
    initialize_sound(&old_ssp, &trebleState, &bassState);

    while (!song_finished) {
        song_finished = update_sound(&old_ssp, &song_then, &trebleState, &bassState, treble_song_length, bass_song_length, intro_duration_ptr);
        if (*intro_duration_ptr > 43) {
            time_now = get_time();
            time_elapsed = time_now - time_then;
            if (first_frames > FIRST_STOP - 1) {
                stop_ghosts = execute_movements_and_render_frame(base32, base8, back8, entity, indx_ptr, initial_moves);
                first_frames = 0;
            }
            if (stop_ghosts == FALSE && time_elapsed > 0) {
                manually_move_ghost(back_buffer_ptr, entity, 1, stop_ghosts);
                swap_buffers(&base32, &back_buffer_ptr);
                Setscreen(-1,base32,-1);  
                /*time_now = get_time();*/
                time_then = get_time();
            }
            first_frames++;
        }
    }
    clear_and_render_entities(base32, back_buffer_ptr, entity);
}
/*******************************************************************
 * Function: manually_move_ghost
 * Purpose: Manually moves the ghost
 * Parameters: base, entity, frame_index
 *******************************************************************/
void manually_move_ghost(ULONG32* base, Entities* entity, int frame_index, bool enable) {

    if (enable != TRUE) {
        move_ghost(entity->crying_ghost);
        move_ghost(entity->awkward_ghost);
        move_ghost(entity->moustache_ghost);
        move_ghost(entity->cyclops_ghost);
	    update_cells(entity);
    }
        update_current_frame(entity, frame_index);
	    render_frame(base, entity);

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
void initialize_sound(long* old_ssp, MusicState* trebleState, MusicState* bassState) {
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
bool update_sound(long* old_ssp, ULONG32* time_then, MusicState* trebleState, MusicState* bassState, int treble_song_length, int bass_song_length, int* intro_duration) {
    ULONG32 time_now = get_time();
    ULONG32 time_elapsed = time_now - *time_then;
    bool song_finished;
    int tempo = 5;

    if (time_elapsed >= tempo) {
        *time_then = time_now;

        *old_ssp = Super(0);
        update_music(CHANNEL_A, pacman_intro_treble, treble_song_length, trebleState);
        song_finished = update_music(CHANNEL_B, pacman_intro_bass, bass_song_length, bassState);
        Super(*old_ssp);
        (*intro_duration)++;
        return song_finished;
    }
    return FALSE;
}
/*******************************************************************
 * Function: debug_pacman_movement
 * Purpose: Prints out Pacman's movement coordinates for debugging
 ******************************************************************/
void debug_pacman_movement(ULONG32* base32, Pacman* pacman) 
{
    UCHAR8* base;
    const char labels[6][5] = {"X: ", "Y: ", "LX: ", "LY: ", "LLX: ", "LLY: "};
    UINT16 values[6];
    UINT16 x_offset, y_offset;
    UINT16 tens, ones, hundreds;
    int i, j;

    base = (UCHAR8*)base32;
    
    values[0] = pacman->move->x;
    values[1] = pacman->move->y;
    values[2] = pacman->move->last_x;
    values[3] = pacman->move->last_y;
    values[4] = pacman->move->last_last_x;
    values[5] = pacman->move->last_last_y;

    x_offset = 0;
    y_offset = LETTER_HEIGHT * 2; 

    for (i = 0; i < 6; ++i) {
        for (j = 0; j < 10; ++j) { 
            clear_letter(base, x_offset + j*LETTER_WIDTH, y_offset);
        }

        plot_string(base, x_offset, y_offset, font, labels[i]);
        x_offset += 4*LETTER_WIDTH; 

        if (values[i] >= 100) {
            hundreds = values[i] / 100;
            tens = (values[i] / 10) % 10;
            ones = values[i] % 10;
            debug_print(base, x_offset, y_offset, hundreds);
            x_offset += 2*LETTER_WIDTH; 
            debug_print(base, x_offset, y_offset, tens * 10 + ones);
        } else {
            tens = values[i] / 10;
            ones = values[i] % 10;
            debug_print(base, x_offset, y_offset, tens * 10 + ones);
        }

        x_offset += 4*LETTER_WIDTH; 

        if (x_offset + 8*LETTER_WIDTH > SCREEN_WIDTH) {
            x_offset = 0;
            /*y_offset += LETTER_HEIGHT; */
        }
    }
}
/*******************************************************************
 * Function: debug_print
 * Purpose: Prints out an integer value using plot letter
 *****************************************************************/
void debug_print(UCHAR8* base, UINT16 x, UINT16 y, UINT16 value){
    UINT16 tens = value / 10;
    UINT16 ones = value % 10;

    unsigned int tens_char = tens + '0';
    unsigned int ones_char = ones + '0';

	clear_letter(base, x, y);
	clear_letter(base, x+LETTER_WIDTH, y);
    plot_letter(base, x , y, font, tens_char);
    plot_letter(base, x + LETTER_WIDTH, y, font, ones_char);
}
/*******************************************************************
 * Function: debug_cells
 * Purpose: Prints out pacmans current cell indeces
 ******************************************************************/
void debug_cells_pac(UCHAR8* base, Pacman* pacman) {
    int j;

    const char strx[] = "X: ";
	const char stry[] = "Y: ";	

    for (j = 0; j < 14; j++) {
    	clear_letter(base, j*LETTER_WIDTH, 0);
	}

    plot_string(base, 0, 0, font, strx);
    debug_print(base, 4*LETTER_WIDTH, 0, pacman->move->x_cell_index);
    plot_string(base, 8*LETTER_WIDTH, 0, font, stry);
    debug_print(base, 12*LETTER_WIDTH, 0, pacman->move->y_cell_index);
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

ULONG32* get_video_base()
{
	ULONG32 old_ssp;
    ULONG32 combined_address;
   /* UINT16* video_base_ptr;*/

    UCHAR8 high_byte; 
    UCHAR8 low_byte ;

	old_ssp = Super(0); 				
    high_byte = *ptr_to_highbyte;
    low_byte = *ptr_to_lowbyte;
    Super(old_ssp); 		
    
   /*combined_address = ((ULONG32)high_byte << 16) | ((ULONG32)low_byte << 8);*/
   combined_address = ((ULONG32)high_byte << 16) | ((ULONG32)low_byte  << 8);
   
    return (ULONG32*)combined_address;

}
