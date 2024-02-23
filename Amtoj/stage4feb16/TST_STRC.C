#include <osbind.h>
#include <stdio.h> /* for printf remove later */
#include <linea.h>

#include "struct.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"

#include "model.h"
#include "events.h"
#include "input.h"
#include "renderer.h"

#define LETTERS_PER_BLOCK 6


void next_test(ULONG32* base);
void display_all_ascii(UCHAR8* base, int x0, int y0);
void test_arbitrary_letter(UCHAR8* base);

void set_input(Pacman *pacman,char input);

void move_pacman_test(Pacman *pacman);

void move_ghost_test(Ghost *ghost);

ULONG32 get_time();

Pacman pacman_obj = {
    PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE,       /*Initial state*/
    FALSE,
    1,1,         /*Cell index -> y, x*/
	PACMAN
};

Ghost c_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
    1,1,
    0,
    UP,
    DEFAULT,
    10,25,
	&cell_map[25][10],
	GHOST_TYPE_CRYING
               /*Or whatever cell it starts in*/
 
};
Ghost m_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    1,1,
    0,
    UP,
    DEFAULT,
    10, 21,
	&cell_map[21][10],
	GHOST_TYPE_MOUSTACHE
};
Ghost cy_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    1,1,
    0,
    UP,
    DEFAULT,
    1, 3,
	&cell_map[3][1  ],
	GHOST_TYPE_CRYING					/*(x,y)*/
};
Ghost a_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    LEFT,
    DEFAULT,
    12, 21,
	&cell_map[21][12],
	GHOST_TYPE_AWKWARD
};


int main()
{
	char input;
	int i,j,counter;
	UCHAR8 collision_type = 0;
	ULONG32* base = Physbase();
	ULONG32 time_then, time_now;

	Entities all_objs = {

		&pacman_obj,
		&c_ghost,
		&a_ghost,
		&m_ghost,
		&cy_ghost
	};



	Entities *ptr = &all_objs;

	init_map_cells(cell_map,tile_map);				/* i added the paramters for the init_cell map function*/

	
	if (Cconis())
	{
		input = (char)Cnecin();
	}

	while(input != 'Q')
	{

		if (Cconis())
		{
			input = (char)Cnecin();
		 	set_input(&pacman_obj,input);
			
			collision_type = check_collision(ptr, ptr->pacman->y_cell_index, 
											ptr->pacman->x_cell_index, 
											ptr->pacman->delta_y, 
											ptr->pacman->delta_x,
											ptr->pacman->type);

			if (collision_type == NO_COLLISION)
				move_pacman_test(&pacman_obj);
			else
				handle_pacman_collision(collision_type,&pacman_obj);
		
			collision_type = check_collision(ptr, ptr->awkward_ghost->y_cell_index, 
											ptr->awkward_ghost->x_cell_index, 
											ptr->awkward_ghost->delta_y, 
											ptr->awkward_ghost->delta_x,
											ptr->awkward_ghost->type);


			printf("awkward ghosts's direction BEFORE IF : %u\n", a_ghost.direction);

			if (collision_type == NO_COLLISION)
			{
				move_ghost_test(&a_ghost);
				printf("No ghost collision\n");
			}
			else
			{
				printf("yes there is a collision\n");
				handle_ghost_collision(collision_type, &a_ghost, cell_map, &xor);
				move_ghost_test(&a_ghost);
			}
						


			printf("a_ghost position now: (%u, %u)\n\n", a_ghost.y_cell_index, a_ghost.x_cell_index);


			collision_type = check_collision(ptr, ptr->moustache_ghost->y_cell_index, 
											ptr->moustache_ghost->x_cell_index, 
											ptr->moustache_ghost->delta_y, 
											ptr->moustache_ghost->delta_x,
											ptr->moustache_ghost->type);
			if (collision_type == NO_COLLISION)
			{
				move_ghost_test(&m_ghost);
				printf("No ghost collision\n");
			}
			else{
				printf("yes there is a collision\n");

				handle_ghost_collision(collision_type, &m_ghost, cell_map, &xor);
				move_ghost_test(&m_ghost);
						
			}
			printf("moustche_ghost position now: (%u, %u)\n\n", m_ghost.y_cell_index, m_ghost.x_cell_index);
		}	
	}
	

	return 0;
}


/*waits for input then calls clear_screen();*/
void next_test(ULONG32* base) {

	while(!Cconis()){

	}
	Cnecin();
	clear_screen_q(base);
}



void set_input(Pacman *pacman, char input)
{

	pacman -> move -> delta_y = 0;
    pacman -> move -> delta_x = 0;              /* make this better? how to reset it everytime?*/
    /*pacman -> move -> direction = 0;*/

	switch(input)
	{
		case W_KEY: 
			pacman -> move -> delta_y = -1;   		/* UP 1*/
            pacman -> move -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> move -> delta_x = -1;			/*Left 3*/
            pacman -> move -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> move -> delta_y = 1;			/*Down 2*/
            pacman -> move -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> move -> delta_x = 1;			/* Right 4*/
            pacman -> move -> direction = RIGHT;
			break;

		default:
			printf("Invalid input\n");
            pacman-> delta_x = 0;
            pacman -> move -> delta_y = 0;
			/*pacman -> move -> direction = 0;*/
			break;
	}

}

void move_pacman_test(Pacman *pacman)
{

	pacman -> move -> x_cell_index += pacman->delta_x;
	pacman -> move -> y_cell_index += pacman->delta_y;

}

void move_ghost_test(Ghost *ghost)
{

	UCHAR8 direction = ghost -> direction;

	ghost -> delta_x = 0;
	ghost -> delta_y = 0;
	
	if (ghost -> x_cell_index > 0 && ghost -> x_cell_index < MAP_TILE_LENGTH
		&& ghost -> y_cell_index > 0 && ghost -> y_cell_index < MAP_TILE_HEIGHT) 
	
	{
		switch(direction)
		{
			case UP:
				ghost -> y_cell_index -= 1;
				ghost -> delta_y = -1;
				ghost -> delta_x = 0;
				break;
			
			case DOWN:
				ghost -> y_cell_index += 1;
				ghost -> delta_y = 1;
				ghost -> delta_x = 0;
				break;
			
			case RIGHT:
				ghost -> x_cell_index += 1;
				ghost -> delta_x = 1;
				ghost -> delta_y = 0;
				break;
			
			case LEFT:
				ghost -> x_cell_index -= 1;
				ghost -> delta_x = -1;
				ghost -> delta_y = 0;
				break;
		}
	}

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