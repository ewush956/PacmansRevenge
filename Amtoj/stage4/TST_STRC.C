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

int arbitrary_numbers_400[] = {
	141, 276, 392, 345, 72, 307, 51, 17, 198, 63, 
	366, 304, 383, 71, 111, 190, 255, 39, 110, 307, 
	297, 324, 393, 95, 386, 53, 222, 368, 85, 325, 
	88, 100, 12, 92, 62, 275, 221, 131, 372, 300,
	388, 262, 174, 356, 84, 121, 276, 142, 210, 
	21, 336, 300, 392, 238, 92, 369, 88, 210, 
	262, 174, 356, 84, 121, 276, 142, 400, 365,
	18, 336, 300, 392, 238, 97, 369, 88, 210, 
	8, 21, 57, 299, 238, 97, 369, 88, 210, 327,
	333, 1, 32, 109, 238, 97, 369, 0, 210 
};

int arbitrary_numbers_640[] = {
	339, 287, 372, 220, 597, 186, 93, 429, 258, 
	70, 496, 20, 633, 612, 333, 61, 556, 404, 0,
	369, 591, 383, 511, 433, 123, 320, 106, 268,
	508, 122, 602, 280, 617, 482, 460, 218, 246, 
	11, 138, 317, 213, 326, 36, 456, 94, 9, 253, 
	269, 226, 381, 303, 29, 154, 251, 537, 604, 340, 
	647, 466, 367, 144, 123, 626, 389, 168, 638, 
	240, 389, 110, 281, 444, 565, 18, 211, 44, 
	213, 625, 603, 98, 94, 47, 382, 119, 312, 9,
	210, 240, 39, 255, 492, 515, 174, 377, 255, 37
};



void next_test(UINT32* base);
void display_all_ascii(UINT8* base, int x0, int y0);
void test_arbitrary_letter(UINT8* base);

void set_input(Pacman *pacman,char input);

	Pacman pacman_obj = {
    1,1,     		/*Initial position, */
    0,0,        	/*Initial Displacement*/
    0,          	/*Initial state index*/
    UP,         	/*Initial direction*/
    FALSE,       	/*Initial state*/
    TRUE,
    21,19          /*Cell index -> y, x*/
	};
	
	Ghost c_ghost = {
    10,1,      /*starts in [10][18]*/
    0,0,
    0,
    UP,
    DEFAULT,
    10, 17
	};

	Ghost m_ghost = {
	19,1,
    0,0,
    0,
    UP,
    DEFAULT,
    10, 21
	};

	Ghost cy_ghost = {
	25,1,
    0,0,
    0,
    UP,
    DEFAULT,
    12, 17
	};

	Ghost a_ghost = {
    29,1,
    0,0,
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
	int i,j,k;
	UINT8 collision_type; 

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
	
	printf("%u,%d:",ptr->pacman->x,ptr->pacman->has_collided);

	printf("pacman position old : (%d, %d)\n", pacman_obj.y, pacman_obj.x);

	printf("pacman direction before:(%u)\n\n", pacman_obj.direction);
	

	printf("%d,%d\n",ptr->pacman->y_cell_index,ptr->pacman->x_cell_index);
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
	
		

	while(!Cconis())
	{
		
		input = Cconin();

		 printf("RAND NUM::%u\n",random_number_generator(&xor));

		 set_input(&pacman_obj,input);
		
		
		  

    	collision_type = check_collision(&ptr,ptr->pacman->y, ptr->pacman->x, ptr->pacman->delta_y, ptr->pacman->delta_x);

    	if (collision_type == NO_COLLISION)
        	move_pacman(&pacman_obj);
    	else
        	handle_pacman_collision(collision_type,&pacman_obj);
		


		printf("pacman position now: (%d, %d)\n", pacman_obj.y, pacman_obj.x);
		printf("pacman direction........:(%u)\n\n", pacman_obj.direction); 

	}

	/*Cnecin();*/
	
	printf("pacman position new : (%d, %d)\n", pacman_obj.y, pacman_obj.x);


	return 0;
}


/*waits for input then calls clear_screen();
void next_test(UINT32* base) {

	while(!Cconis()){

	}
	Cnecin();
	clear_screen_q(base);
}

*/

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