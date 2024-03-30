#include <osbind.h>
#include <stdio.h> /* for printf remove later */
#include <linea.h>

#include "raster.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"

#include "model.h"
#include "events.h"
#include "input.h"

#include "globals.h"

#define LETTERS_PER_BLOCK 6


void next_test(ULONG32* base);
void display_all_ascii(UCHAR8* base, int x0, int y0);
void test_arbitrary_letter(UCHAR8* base);

void set_input(Pacman *pacman,char input);

void move_pacman_test(Pacman *pacman);

void move_ghost_test(Ghost *ghost);

int main()
{
/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- - */
/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- -*/
/* - - - - -  for testing the individual objects (ghosts or pac or both) - - - - */

/**/
	char input;
	int i,j,counter;
	UCHAR8 collision_type; 
	ULONG32* base = Physbase();
	/*
	Entities all_objs = {

		&pacman_obj,
		&c_ghost,
		&a_ghost,
		&m_ghost,
		&cy_ghost
	};
	*/
		Entities all_objs = {
		&pacman,
		&crying_ghost,
		&moustache_ghost,
		&awkward_ghost,
		&cyclops_ghost
	};

	Entities *ptr = &all_objs;
	Pacman* pacman_obj = &pacman;


	Xor xor = {1234567};					/* inits a random value to be used for the rand num generator*/

	init_map_cells(cell_map,tile_map);				/* i added the paramters for the init_cell map function*/
	
	/* first loop used for testing if pacman collised with any objects */
		printf("Press enter key to go to next next\n\n\n");
		counter = 0;
		for (i = 0; i < MAP_TILE_HEIGHT; i++){
			for(j =0; j < MAP_TILE_LENGTH; j++){
				printf("---------Case number %d---------\n\n\n",counter);

				collision_type = check_collision(ptr, ptr->pacman->y_cell_index, 
												ptr->pacman->x_cell_index, 
												ptr->pacman->delta_y, 
												ptr->pacman->delta_x);
				if (collision_type == NO_COLLISION)
        			move_pacman_test(pacman_obj);
    			else
        			handle_pacman_collision(collision_type, pacman_obj);
				 
				printf("pacman position now: (%d, %d)\n\n", pacman_obj->y_cell_index, pacman_obj->x_cell_index);
				/*printf("pacman's direction: %u\n", pacman_obj.direction);*/
	
				if (j % 3 == 0)
					next_test(base);

				ptr->pacman->move->x_cell_index += 1;
				counter++;
			}
			ptr->pacman -> move -> y_cell_index += 1;
			ptr->pacman -> move -> x_cell_index =0; 
		}


	printf("pacman position final: (%d, %d)\n", pacman_obj->y_cell_index, pacman_obj->x_cell_index);


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
    pacman -> move -> delta_x = 0;             

	switch(input)
	{
		case W_KEY: 
			pacman -> move -> delta_y = -1;   		
            pacman -> move -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> move -> delta_x = -1;			
            pacman -> move -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> move -> delta_y = 1;			
            pacman -> move -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> move -> delta_x = 1;			
            pacman -> move -> direction = RIGHT;
			break;

		default:
            pacman-> delta_x = 0;
            pacman -> move -> delta_y = 0;
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

	switch(direction)
	{
		case UP:
			ghost -> y_cell_index -= 1;
		
		case DOWN:
			ghost -> y_cell_index += 1;
		
		case RIGHT:
			ghost -> x_cell_index += 1;
		
		case LEFT:
			ghost -> x_cell_index -= 1;
	}

}
/*
				***************   CURRENTLY NOT FUNCTIONAL ***************
				collision_type = check_collision(ptr, ptr->crying_ghost->y_cell_index, 
												ptr->crying_ghost->x_cell_index, 
												ptr->crying_ghost->delta_y, 
												ptr->crying_ghost->delta_x);
																			

				collision_type = check_collision(ptr, ptr->moustache_ghost->y_cell_index, 
												ptr->moustache_ghost->x_cell_index, 
												ptr->moustache_ghost->delta_y, 
												ptr->moustache_ghost->delta_x);

				collision_type = check_collision(ptr, ptr->awkward_ghost->y_cell_index, 
												ptr->awkward_ghost->x_cell_index, 
												ptr->awkward_ghost->delta_y, 
												ptr->awkward_ghost->delta_x);

				if (collision_type == NO_COLLISION)
				{
					move_ghost_test(&c_ghost);
					printf("No ghost collision\n");
				}
				else{
					handle_ghost_collision(collision_type, &c_ghost, cell_map, &xor);
					printf("yes there is a collision\n");
				}
				*/
