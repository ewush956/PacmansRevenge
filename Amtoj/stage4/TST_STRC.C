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


void next_test(UINT32* base);
void display_all_ascii(UINT8* base, int x0, int y0);
void test_arbitrary_letter(UINT8* base);

void set_input(Pacman *pacman,char input);

void move_pacman_test(Pacman *pacman);

void move_ghost_test(Ghost *ghost);

Pacman pacman_obj = {
    PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE,       /*Initial state*/
    FALSE,
    0,0          /*Cell index -> y, x*/
};

Ghost c_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
    1,1,
    0,
    UP,
    DEFAULT,
    1,1 
               /*Or whatever cell it starts in*/
 
};
Ghost m_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    1,1,
    0,
    UP,
    DEFAULT,
    18, 1
};
Ghost cy_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    1,1,
    0,
    UP,
    DEFAULT,
    1, 3						/*(x,y)*/
};
Ghost a_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    1,1,
    0,
    UP,
    DEFAULT,
    12, 21
};



int main()
{
/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- - */
/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- -*/
/* - - - - -  for testing the individual objects (ghosts or pac or both) - - - - */

/**/
	char input;
	int i,j,counter;
	UINT8 collision_type; 
	UINT32* base = Physbase();

	Entities all_objs = {

		&pacman_obj,
		&c_ghost,
		&a_ghost,
		&m_ghost,
		&cy_ghost
	};



	Entities *ptr = &all_objs;

	Xor xor = {1234567};					/* inits a random value to be used for the rand num generator*/

	init_map_cells(cell_map,tile_map);				/* i added the paramters for the init_cell map function*/

	/*init_ghost_paths()*/
	/*
	printf("%u,%d:",ptr->pacman->x,ptr->pacman->has_collided);

	printf("pacman position old : (%d, %d)\n", pacman_obj.y_cell_index, pacman_obj.x_cell_index);
	
	printf("pacman direction before:(%u)\n\n", pacman_obj.direction);
	

	/*printf("%d,%d\n",ptr->pacman->y_cell_index,ptr->pacman->x_cell_index);
	/*
	for (i = 0; i < MAP_TILE_HEIGHT; i++)
	{
		for(j = 0; j < MAP_TILE_LENGTH; j++)
		{
			printf("%d",cell_map[i][j].open_path);
		}
		printf("\n");
		break;
	}
	*/
	
	
	/* use plot font to test (...?) */ 
	
	/* im trying to take keyboard input here and each time  w a s or d is pressed 
		i want to increment the position by 1 (we cna chnage this to whatever pixel amount)
		NOT taking input but works with hard-coded funtion calls */
	
		
/*
	while(!Cconis())
	{
		
		input = Cconin();

		 printf("RAND NUM::%u\n",random_number_generator(&xor));

		 set_input(&pacman_obj,input);
		
		
    	collision_type = check_collision(&ptr, ptr->pacman->y_cell_index, 
										ptr->pacman->x_cell_index, 
										ptr->pacman->delta_y, 
										ptr->pacman->delta_x);

    	if (collision_type == NO_COLLISION)
        	move_pacman_test(&pacman_obj);
    	else
        	handle_pacman_collision(collision_type,&pacman_obj);
		


		printf("pacman position now: (%d, %d)\n", pacman_obj.y_cell_index, pacman_obj.x_cell_index);
		printf("pacman's cuurent direction.:(%u)\n", pacman_obj.direction); 

	}

	/*Cnecin();*/
	
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
        			move_pacman_test(&pacman_obj);
    			else
        			handle_pacman_collision(collision_type,&pacman_obj);
				 
				
				/*
				collision_type = check_collision(ptr, ptr->crying_ghost->y_cell_index, 
												ptr->crying_ghost->x_cell_index, 
												ptr->crying_ghost->delta_y, 
												ptr->crying_ghost->delta_x);
																			

				collision_type = check_collision(ptr, ptr->moustache_ghost->y_cell_index, 
												ptr->moustache_ghost->x_cell_index, 
												ptr->moustache_ghost->delta_y, 
												ptr->moustache_ghost->delta_x);*/

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
					/*
					collision_type = check_collision(ptr, ptr->moustache_ghost_ghost->y_cell_index, 
													ptr->moustache_ghost->x_cell_index, 
													ptr->moustache_ghost_ghost->delta_y, 
													ptr->moustache_ghost_ghost->delta_x);*/

				/*
				if (collision_type == NO_COLLISION)
					move_ghost_test(&c_ghost);
				else
					handle_ghost_collision(collision_type, c_ghost, cell_map, xor);

				if (collision_type == NO_COLLISION)
					move_ghost_test(&c_ghost);
				else
					handle_ghost_collision(collision_type, c_ghost, cell_map, xor);

				if (collision_type == NO_COLLISION)
					move_ghost_test(&c_ghost);
				else
					handle_ghost_collision(collision_type, c_ghost, cell_map, xor);

				*/





				printf("pacman position now: (%d, %d)\n\n", pacman_obj.y_cell_index, pacman_obj.x_cell_index);
				/*printf("pacman's direction: %u\n", pacman_obj.direction);*/

				if (j % 3 == 0)
					next_test(base);

				ptr->pacman->x_cell_index += 1;
				counter++;
			}
			ptr->pacman -> y_cell_index += 1;
			ptr->pacman -> x_cell_index =0; 
		}


	printf("pacman position final: (%d, %d)\n", pacman_obj.y_cell_index, pacman_obj.x_cell_index);


	return 0;
}


/*waits for input then calls clear_screen();*/
void next_test(UINT32* base) {

	while(!Cconis()){

	}
	Cnecin();
	clear_screen_q(base);
}



void set_input(Pacman *pacman, char input)
{

	pacman -> delta_y = 0;
    pacman -> delta_x = 0;              /* make this better? how to reset it everytime?*/
    /*pacman -> direction = 0;*/

	switch(input)
	{
		case W_KEY: 
			pacman -> delta_y = -1;   		/* UP 1*/
            pacman -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> delta_x = -1;			/*Left 3*/
            pacman -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> delta_y = 1;			/*Down 2*/
            pacman -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> delta_x = 1;			/* Right 4*/
            pacman -> direction = RIGHT;
			break;

		default:
			printf("Invalid input\n");
            pacman-> delta_x = 0;
            pacman -> delta_y = 0;
			/*pacman -> direction = 0;*/
			break;
	}

}

void move_pacman_test(Pacman *pacman)
{

	pacman -> x_cell_index += pacman->delta_x;
	pacman -> y_cell_index += pacman->delta_y;

}

void move_ghost_test(Ghost *ghost)
{

	UINT8 direction = ghost -> direction;

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