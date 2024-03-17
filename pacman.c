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

/************************* KNOWN BUG ***************************
 * Currently, there is a bug that does not render the top left portion 
 * of the map from the back buffer. It appears to be in the correct memory 
 * location as there are no address bombs and the double buffering for the entities 
 * (pacman and ghosts) works. Pacman is also leaving behind pixel trails 
 * when moving around at random. We suspect that the clear last last (2 frames before) 
 * is not working for him only. The ghosts dont have this issue and render perfectly.
 * With no trailing pixels. 
 * 
 * The double buffering seems to work as intented aside from the effected regions.
 * 
 * Pacman currently does not eat the pellets.
 ***********************************************************/

/*************************************************************
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
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET
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
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
        0,0,
        RIGHT,
        10, 17,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET
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
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET  
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
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET   
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
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
        0,0,
        LEFT,
        12, 21,
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET, 
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET
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

	char input;
    int waka_repetitions = 10; 
    int buffer_offset = 256 - ((long)(screen_buffer) % 256); 
    long old_ssp; 

	UCHAR8 collision_type = 0;
    UCHAR8* base8 = Physbase();

    UINT16 ticks = 0;
    /*UINT16* base16 = Physbase();*/

	ULONG32* base32 = Physbase();
    ULONG32* original = Physbase();
    ULONG32* back_buffer_ptr = (ULONG32*)(&screen_buffer[buffer_offset]);
    
    ULONG32* background_ptr = (ULONG32*)(&background[0]); /*Not using at the moment*/
	ULONG32 time_then, time_now, time_elapsed;
  
    GAME_STATE state = PLAY;

    SoundState wakaState = {0, 0};
    SoundState wakaNoise = {0, 0};

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

            old_ssp = Super(0);
            play_waka_sound(CHANNEL_A, waka_sound_cycle, WAKA_CYCLE_LENGTH, &wakaState); 
            play_waka_sound(CHANNEL_B, waka_noise_cycle, WAKA_CYCLE_LENGTH, &wakaNoise); 
            Super(old_ssp);


            update_movement(&entity, input, ticks);
            update_current_frame(&entity, ticks);
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
/*******************************************************************
 * Function: manually_move_ghost
 * Purpose: Manually moves the ghost
 * Parameters: base, entity, frame_index
 *******************************************************************/
void manually_move_ghost(ULONG32* base, Entities* entity, int frame_index){

    move_ghost(entity->crying_ghost);
    move_ghost(entity->awkward_ghost);
    move_ghost(entity->moustache_ghost);
    move_ghost(entity->cyclops_ghost);
	update_cells(entity);

    update_current_frame(entity, frame_index);

	render_frame(base, entity);

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
 * Function: update_movement
 * Purpose: Super call to all movement functions
 * 
 * Parameters: entity, input, ticks
 ******************************************************************/
void update_movement(Entities* entity, char input, UINT16 ticks) {
    

    set_input(entity->pacman,input);
    
    handle_collisions(entity, ticks);   
    update_entities();

    update_cells(entity);
    check_proximity(entity);
    

}
void initialize_game(ULONG32* base32, ULONG32* back_buffer_ptr, Entities* entity) 
{

    MusicState trebleState = {0, 0};
    MusicState bassState = {0, 0};
    UCHAR8* base8 = (UCHAR8*)base32;
    UCHAR8* back8 = (UCHAR8*)back_buffer_ptr;

    ULONG32 time_then, time_now, time_elapsed;

    long old_ssp; 

    int initial_moves[5] = {0,1,2,3,4};
    int moves_index = 0;
    int intro_duration = 0;
    int treble_song_length = sizeof(pacman_intro_treble) / sizeof(Note);
    int bass_song_length = sizeof(pacman_intro_bass) / sizeof(Note);
    int first_frames = 0;
    int second_frames = 0;
    int third_frames = 0;

    bool song_finished = FALSE;
    bool stop_ghosts = FALSE;
    
    
    init_map_cells(cell_map,tile_map);	

    cell_map[10][17].has_pellet = FALSE;
    cell_map[10][18].has_pellet = FALSE;

    cell_map[10][20].has_pellet = FALSE;
    cell_map[10][21].has_pellet = FALSE;

    cell_map[12][17].has_pellet = FALSE;
    cell_map[12][18].has_pellet = FALSE;

    cell_map[12][20].has_pellet = FALSE;
    cell_map[12][21].has_pellet = FALSE;
    

    clear_screen_q(base32);
    render_map(base32, tile_map);

    render_map(back_buffer_ptr, tile_map);

    clear_bitmap_32(base32, entity->moustache_ghost->move->x, entity->moustache_ghost->move->y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, entity->awkward_ghost->move->x, entity->awkward_ghost->move->y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, entity->cyclops_ghost->move->x, entity->cyclops_ghost->move->y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, entity->crying_ghost->move->x, entity->crying_ghost->move->y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, entity->pacman->move->x, entity->pacman->move->y, SPRITE_HEIGHT);
    
    
    render_initial_timer(base8);
    render_initial_timer(back8);
    
    
    set_first_movements(base32, base8, entity);
    render_frame(base32, entity);

    old_ssp = Super(0);
    enable_channel(CHANNEL_B, TONE_ON, NOISE_OFF);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    Super(old_ssp);

    time_then = get_time();
    while (song_finished == FALSE) {
        time_now = get_time();
        time_elapsed = time_now - time_then; 

        if (time_elapsed >= 5) { 
            time_then = time_now;
            
            old_ssp = Super(0);
            update_music(CHANNEL_A, pacman_intro_treble, treble_song_length, &trebleState);
            song_finished = update_music(CHANNEL_B, pacman_intro_bass, bass_song_length, &bassState); 
            Super(old_ssp);
            intro_duration++;
        }
        if (intro_duration > 40) {
        if (first_frames > FIRST_STOP - 1) {
            switch (initial_moves[moves_index]) {
                case 0:
                    set_second_movements(base32, base8, entity);
                    moves_index++;
                    break;
                case 1:
                    set_third_movements(base32, base8, entity);
                    moves_index++;
                    break;
                case 2:
                    set_third_movements(base32, base8, entity);
                    moves_index++;
                    break;
                case 3:
                    moves_index++;
                    break;
                case 4:
                    stop_ghosts = TRUE;
                    break;
            }
            first_frames = 0;
            
        }
        if (stop_ghosts == FALSE) {
            manually_move_ghost(base32, entity, 1);
        }
        first_frames++;
        }
    }
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

