
#include "pacman.h"
#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"
#include "events.h"

#include <osbind.h>
#include <stdio.h>
#include <linea.h>


/*************************************************************
* Declaration: Pacman pacman
* Purpose: Initializes the player character, Pacman, with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Pacman pacman = {
    PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,  
    0,0,           /*Initial Displacement*/
    0,             /*Initial state index*/
    UP,            /*Initial direction*/
    DEFAULT,       /*Initial state*/
    21,19,          /*Cell index -> y, x*/
    PACMAN
};
/*************************************************************
* Declaration: Ghost crying_ghost
* Purpose: Initializes the 'crying' ghost entity with its starting
*          position, movement displacement, state, direction, 
*          and cell index on the game map.
*************************************************************/
Ghost crying_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,     
    0,0,
    0,
    LEFT,
    DEFAULT,
    10, 17,
    GHOST_TYPE_CRYING
};
/*************************************************************
* Declaration: Ghost cyclops_ghost
* Purpose: Initializes the 'cyclops' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost cyclops_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    LEFT,
    DEFAULT,
    12, 17,
    GHOST_TYPE_CYCLOPS
};
/*************************************************************
* Declaration: Ghost moustache_ghost
* Purpose: Initializes the 'moustache' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost moustache_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    0,0,
    0,
    RIGHT,
    DEFAULT,
    10, 21,
    GHOST_TYPE_MOUSTACHE
};
/*************************************************************
* Declaration: Ghost awkward_ghost
* Purpose: Initializes the 'awkward' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost awkward_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    RIGHT,
    DEFAULT,
    12, 21,
    GHOST_TYPE_AWKWARD
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

Entities entity = {
    &pacman,
    &crying_ghost,
    &awkward_ghost,
    &moustache_ghost,
    &cyclops_ghost,
};

int main()
{
	char input;
	int i,j,counter;
    int ticks = 0;
	UCHAR8 collision_type = 0;
	ULONG32* base32 = Physbase();
    UINT16* base16 = Physbase();
    UCHAR8* base8 = Physbase();

	ULONG32 time_then, time_now, time_elapsed;
    GAME_STATE state = PLAY;

    Xor xor = {123457};

	init_map_cells(cell_map,tile_map);				/* i added the paramters for the init_cell map function*/
    clear_screen_q(base32); 
    render_map(base16, tile_map);
    render_frame(base32, &entity);
    render_initial_timer(base8);
    free_ghosts(base32, base8, &entity);
	
	if (Cconis())
	{
		input = (char)Cnecin();
	}

    while (state != QUIT) {

        time_now = get_time();
        time_elapsed = time_now - time_then;

        if (time_elapsed > 0) {

            if (Cconis())
            {
                input = (char)Cnecin();
            }
                /*
                if (ticks % 70 == 0) {
                    ticks = 0;
                }
                ticks++;
                */
                
                clear_entities(base32, &entity);
                set_input(&pacman,input);

                check_proximity(&entity);
                handle_collisions(&entity, &xor);       /*Checks and handles collisions*/

                update_pacman(ticks);
                update_ghosts();

                render_frame(base32, &entity);
                update_cells(&entity);

                debug_cells_pac(base8, &pacman);
            time_then = time_now;
        }
        update_game_state(state, input);
    }

	return 0;
}
/*******************************************************************
* Function: update_pacman
* Purpose: Updates the position of the pacman
*/
void update_pacman(int do_the_roar){
    move_pacman(&pacman);
    if (do_the_roar % 2 == 0) {
        if (pacman.state == DEFAULT) {
            pacman.current_frame = ((pacman.current_frame) + 1) % 8;
        }
        else {
        pacman.current_frame = ((pacman.current_frame) + 1) % 6;
        }
    }
}
void update_ghosts(){
                move_ghost(&moustache_ghost);
                move_ghost(&crying_ghost);
                move_ghost(&cyclops_ghost);
                move_ghost(&awkward_ghost);
                /*update current frame of ghosties here*/
}
void free_ghosts(ULONG32* base32, UCHAR8* base8, Entities* entity) {
    crying_ghost.delta_x = 1;
	crying_ghost.delta_y = 0;
	crying_ghost.direction = RIGHT;


    awkward_ghost.delta_x = -1;
    awkward_ghost.delta_y = 0;
    awkward_ghost.direction = LEFT;

	manually_move_ghost(base32, base8, entity, &crying_ghost, &awkward_ghost, 32);
    
	crying_ghost.delta_x = 0;
	crying_ghost.delta_y = -1;
	crying_ghost.direction = UP;

    awkward_ghost.delta_x = 0;
    awkward_ghost.delta_y = 1;
    awkward_ghost.direction = DOWN;

	manually_move_ghost(base32, base8, entity, &crying_ghost, &awkward_ghost, 32);


    awkward_ghost.delta_x = 0;
}
void manually_move_ghost(ULONG32* base, UCHAR8* base8, Entities* entity, Ghost* ghost1, Ghost* ghost2, int stop){
    int i;

	for (i=0; i < stop; i++) {
		clear_bitmap_32(base, ghost1->x, ghost1->y, SPRITE_HEIGHT); 
        clear_bitmap_32(base, ghost2->x, ghost2->y, SPRITE_HEIGHT);

        ghost1 -> x += (ghost1 -> delta_x);
        ghost1 -> y += (ghost1 -> delta_y);

        ghost2 -> x += (ghost2 -> delta_x);
        ghost2 -> y += (ghost2 -> delta_y);

		update_cells(entity);

		render_frame(base, entity);
		if (i % 8 == 0) {
			ghost1->current_frame = ((ghost1->current_frame) + 1) % 2;
            ghost2->current_frame = ((ghost2->current_frame) + 1) % 2;
		}
	}
}
GAME_STATE update_game_state(GAME_STATE new_state, char input) {
    /*Do something that updates the gamestate*/
    GAME_STATE state;
    if (input == '\033')
        state = QUIT;
    
    state = new_state;
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
void debug_cells_pac(UCHAR8* base, Pacman* pacman) {
    int j;

    const char strx[] = "X: ";
	const char stry[] = "Y: ";	

    for (j = 0; j < 14; j++) {
    	clear_letter(base, j*LETTER_WIDTH, 0);
	}

    plot_string(base, 0, 0, font, strx);
    debug_print(base, 4*LETTER_WIDTH, 0, pacman->x_cell_index);
    plot_string(base, 8*LETTER_WIDTH, 0, font, stry);
    debug_print(base, 12*LETTER_WIDTH, 0, pacman->y_cell_index);
}

/*TODO:
1) Initialize cell map
NOTES: init_map_cells could do without tile_map since it's included in bitmaps.h (globally accessable in renderer)

2) initialize first frame (render map)
3) make main game loop
NOTES: need a QUIT sentenel, i'm thinking we make it -1 or something that isn't easily mixed up with our other typedefs.
        while (state != QUIT) ...
*/

