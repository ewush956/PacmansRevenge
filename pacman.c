
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

/* NOTE: the frame buffer is just an arbitrary region of RAM and 
*  on the Atari and RAM starts at address $0x00000 up to $3FFFFF 
*/
#define BUFFER_SIZE_BYTES 32256                   /*added extra 256*/ 
#define BUFFER_SIZE_WORDS 16000             
#define BACK_BUFFER_START 0x000000
#define BACK_BUFFER_END 0x007E00            /* $7E00 is 32,256 in decimal */

#define FRONT_BUFFER_START 0x00FC0000         /* starts at 64,512 (+ 32,256 bytes more than the back_buffer) */
#define FRONT_BUFFER_END 0x017A0000           /* 32,256 more than the start of front_buffer*/

/* the purpose is to simulate the Physbase() call as now we know the start address of the Buffers*/


/*************************************************************
* Declaration: Pacman pacman
* Purpose: Initializes the player character, Pacman, with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement pacman_movement = {
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,        /*Initial position, won't actually be 0,0*/
        0,0,        /*Initial Displacement*/
        UP,
        21,19          /*Cell index -> y, x*/
};
Pacman pacman = {
    0,
    UP,
    PACMAN,
    &pacman_movement
};

Movement crying_ghost_movement = {
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
        0,0,
        LEFT,
        10, 17
};
Ghost crying_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CRYING,
    FALSE,
    &crying_ghost_movement
};

Movement cyclops_ghost_movement = {
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
        0,0,
        RIGHT,
        12, 17
};
Ghost cyclops_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CYCLOPS,
    FALSE,
    &cyclops_ghost_movement
};

Movement moustache_ghost_movement = {
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
        0,0,
        LEFT,
        10, 21
};
Ghost moustache_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_MOUSTACHE,
    FALSE,
    &moustache_ghost_movement
};

Movement awkward_ghost_movement = {
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
        0,0,
        LEFT,
        12, 21
};
Ghost awkward_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_AWKWARD,
    FALSE,
    &awkward_ghost_movement
};

Timer timer = {
    0,0,
    20, 28, 44, 52
};

/*************************************************************
* Declaration: Ghost crying_ghost
* Purpose: Initializes the 'crying' ghost entity with its starting
*          position, movement displacement, state, direction, 
*          and cell index on the game map.
*************************************************************/

/*************************************************************
* Declaration: Ghost cyclops_ghost
* Purpose: Initializes the 'cyclops' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/

/*************************************************************
* Declaration: Ghost moustache_ghost
* Purpose: Initializes the 'moustache' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/

/*************************************************************
* Declaration: Ghost awkward_ghost
* Purpose: Initializes the 'awkward' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/

/*************************************************************
* Declaration: Timer timer
* Purpose: Initializes the game timer with starting values
*          and thresholds for various game events.
*************************************************************/

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
	int i,j,counter;
    UINT16 ticks = 0;
	UCHAR8 collision_type = 0;
	ULONG32* base32 = Physbase();
    UINT16* base16 = Physbase();
    UCHAR8* base8 = Physbase();


    UCHAR8 front_buffer[BUFFER_SIZE_BYTES];                 /* frame buffer allocation */
    UCHAR8* front_buff_ptr = (UCHAR8*)FRONT_BUFFER_START;

    UCHAR8* test_base8 = front_buffer;                       /* points to the start of the front_buffer */
    UINT16* test_base16 = front_buff_ptr;

	ULONG32 time_then, time_now, time_elapsed;
    GAME_STATE state = PLAY;

    Xor xor = {123457};

	init_map_cells(cell_map,tile_map);				
    clear_screen_q(base32); 
    render_map(test_base16, tile_map);
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
                
            clear_entities(base32, &entity);
            set_input(&pacman,input);

            check_proximity(&entity);
            handle_collisions(&entity, ticks);       /*Checks and handles collisions*/

            update_pacman();
            update_ghosts();
            update_current_frame(&entity, ticks);

            render_frame(base32, &entity);
            update_cells(&entity);

            debug_cells_pac(test_base8, &pacman);
            /*
            ticks++;
            if (ticks > 64) {
                ticks = 0;
            }
            */
            ticks = (++ticks & 63);
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
void update_pacman(){
    move_pacman(&pacman);
}
void update_ghosts(){
    move_ghost(&moustache_ghost);
    move_ghost(&crying_ghost);
    move_ghost(&cyclops_ghost);
    move_ghost(&awkward_ghost);
    /*update current frame of ghosties here*/
}
void free_ghosts(ULONG32* base32, UCHAR8* base8, Entities* entity) {
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

	manually_move_ghost(base32, base8, entity, 16);

    moustache_ghost.move->delta_x = 1;
    moustache_ghost.move->delta_y = 0;
    moustache_ghost.move->direction = RIGHT;

    cyclops_ghost.move->delta_x = -1;
    cyclops_ghost.move->delta_y = 0;
    cyclops_ghost.move->direction = LEFT;

	manually_move_ghost(base32, base8, entity, 16);

    crying_ghost.move->delta_x = 0;
    crying_ghost.move->delta_y = -1;
    crying_ghost.move->direction = UP;

    awkward_ghost.move->delta_x = 0;
    awkward_ghost.move->delta_y = 1;
    awkward_ghost.move->direction = DOWN;
    manually_move_ghost(base32, base8, entity, 32);
}
void manually_move_ghost(ULONG32* base, UCHAR8* base8, Entities* entity, int stop){
    int i;

	for (i=0; i < stop; i++) {
		clear_bitmap_32(base, entity->crying_ghost->move->x, entity->crying_ghost->move->y, SPRITE_HEIGHT);
        clear_bitmap_32(base, entity->moustache_ghost->move->x, entity->moustache_ghost->move->y, SPRITE_HEIGHT);
        clear_bitmap_32(base, entity->awkward_ghost->move->x, entity->awkward_ghost->move->y, SPRITE_HEIGHT);
        clear_bitmap_32(base, entity->cyclops_ghost->move->x, entity->cyclops_ghost->move->y, SPRITE_HEIGHT); 

        move_ghost(entity->crying_ghost);
        move_ghost(entity->awkward_ghost);
        move_ghost(entity->moustache_ghost);
        move_ghost(entity->cyclops_ghost);
        update_current_frame(entity, i);


		update_cells(entity);

		render_frame(base, entity);
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
    debug_print(base, 4*LETTER_WIDTH, 0, pacman->move->x_cell_index);
    plot_string(base, 8*LETTER_WIDTH, 0, font, stry);
    debug_print(base, 12*LETTER_WIDTH, 0, pacman->move->y_cell_index);
}

/*TODO:
1) Initialize cell map
NOTES: init_map_cells could do without tile_map since it's included in bitmaps.h (globally accessable in renderer)

2) initialize first frame (render map)
3) make main game loop
NOTES: need a QUIT sentenel, i'm thinking we make it -1 or something that isn't easily mixed up with our other typedefs.
        while (state != QUIT) ...
*/

