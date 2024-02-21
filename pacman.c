
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
    PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 18 + Y_PIXEL_OFFSET,  
    0,0,           /*Initial Displacement*/
    0,             /*Initial state index*/
    UP,            /*Initial direction*/
    DEFAULT,       /*Initial state*/
    18,19,          /*Cell index -> y, x*/
    PACMAN
};
/*************************************************************
* Declaration: Ghost crying_ghost
* Purpose: Initializes the 'crying' ghost entity with its starting
*          position, movement displacement, state, direction, 
*          and cell index on the game map.
*************************************************************/
Ghost crying_ghost = {
    PIXELS_PER_CELL * 17 + 1, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,     
    1,0,
    0,
    STOP,
    DEFAULT,
    (UINT16)10, (UINT16)17,
    GHOST_TYPE_CRYING
};
/*************************************************************
* Declaration: Ghost cyclops_ghost
* Purpose: Initializes the 'cyclops' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost cyclops_ghost = {
    PIXELS_PER_CELL * 17 + 1, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    STOP,
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
    PIXELS_PER_CELL * 21 - 1, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    0,0,
    0,
    STOP,
    DEFAULT,
    (UINT16)10, (UINT16)21,
    GHOST_TYPE_MOUSTACHE
};
/*************************************************************
* Declaration: Ghost awkward_ghost
* Purpose: Initializes the 'awkward' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost awkward_ghost = {
    PIXELS_PER_CELL * 21 - 1, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    STOP,
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
    &moustache_ghost,
    &crying_ghost,
    &cyclops_ghost,
    &awkward_ghost
};

/*
Pacman *pac = entity.pacman;
Ghost *moustache = entity.moustache_ghost;
Ghost *crying = entity.crying_ghost;
Ghost *cyclops = entity.cyclops_ghost;
Ghost *awkward = entity.awkward_ghost;
*/

int main()
{
	char input;
	int i,j,counter;
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
	
	if (Cconis())
	{
		input = (char)Cnecin();
	}

    while (state != QUIT) {

        time_now = get_time();
        time_elapsed = time_now - time_then;

        if (time_elapsed > 1) {

            if (Cconis())
            {
                input = (char)Cnecin();
            }
                set_input(&pacman,input);
                handle_collisions(&entity, &xor);       /*Checks and handles collisions*/

                clear_bitmap_32(base32, pacman.x, pacman.y, SPRITE_HEIGHT); 
                clear_bitmap_32(base32, crying_ghost.x, crying_ghost.y, SPRITE_HEIGHT);
                clear_bitmap_32(base32, moustache_ghost.x, moustache_ghost.y, SPRITE_HEIGHT);
                clear_bitmap_32(base32, awkward_ghost.x, awkward_ghost.y, SPRITE_HEIGHT);
                clear_bitmap_32(base32, cyclops_ghost.x, cyclops_ghost.y, SPRITE_HEIGHT);

                move_pacman(&pacman);
                move_ghost(&moustache_ghost);
                move_ghost(&crying_ghost);
                move_ghost(&cyclops_ghost);
                move_ghost(&awkward_ghost);

                update_cells(&entity);

                debug_cells_pac(base8, &pacman);
                render_frame(base32, &entity);

            time_then = time_now;
        }
        update_game_state(state, input);
    }

	return 0;
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

