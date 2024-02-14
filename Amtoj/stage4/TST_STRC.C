#include <osbind.h>
#include <stdio.h> /* for printf remove later */
#include <linea.h>

#include "struct.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"

#include "model.h"
#include "input.h"

#define LETTERS_PER_BLOCK 6

/*
const UINT32* sprites[] = {
	pac_1, pac_2, pac_3, pac_4,
	evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4,
	ghost_1_up, ghost_1_down, ghost_1_left, ghost_1_right,
	ghost_2_up, ghost_2_down, ghost_2_left, ghost_2_right,
	ghost_3_up, ghost_3_down, ghost_3_left, ghost_3_right,
	ghost_4_up, ghost_4_down, ghost_4_left, ghost_4_right,
	wall_left_down_right, wall_up_down, wall_left_right, wall_down_right,
	tombstone, ghost_run, ghost_freeze
};

*/
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


/* for object testing 

void move_ghost_position (Ghost *ghost, int new_x, int new_y);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman_position (Pacman *pacman, char input);
*/

int main()
{
/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- - */
/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- -*/
/* - - - - -  for testing the individual objects (ghosts or pac or both) - - - - */

/**/
	char input;
	Pacman pacman_obj = {1,9,0,0,0,0,0,0};

	init_map_cells(cell_map);

	/*init_ghost_paths()*/
	
	/*
	Ghost crying_ghost = {100,100,0,0};
	printf("Initial position: (%d, %d)\n", crying_ghost.x, crying_ghost.y);
	move_ghost_position(&crying_ghost,-5,0);
	move_ghost_position(&crying_ghost,1,0);
	move_ghost_position(&crying_ghost,600,600); 		/* out of bounds test */
	/*increase_ghost_velocity(&crying_ghost,10,10);
	/*printf("New position: (%d, %d)\n", crying_ghost.x, crying_ghost.y);
	printf("New speed: (%d, %d)\n", crying_ghost.delta_x, crying_ghost.delta_y);	*/


	printf("pacman position old : (%d, %d)\n", pacman_obj.y, pacman_obj.x);
	

	
	/* use plot font to test (...?) */ 
	
	/* im trying to take keyboard input here and each time  w a s or d is pressed 
		i want to increment the position by 1 (we cna chnage this to whatever pixel amount)
		NOT taking input but works with hard-coded funtion calls */
		
		/*
		input = Cconin();
		printf("%c\n",input);
		*/
		

	while(!Cconis())
	{
		
		/*char input[2];*/
		/*Cconrs(input[0]);  /* 2 is the input channel to read from */
		
		input = Cconin();
		 /*input = Cauxin();*/

		 printf("RAND::::%u\n",random_generator());

		 set_input(&pacman_obj,input);
		
		 if (move_pacman_position(&pacman_obj) == FALSE)
		 	printf("HE ISGOD TO MOVE \n");
		else
			printf("STOPPED\n");


		 printf("pacman position now: (%d, %d)\n", pacman_obj.y, pacman_obj.x);

	}

	/*Cnecin();*/
	
	printf("pacman position new : (%d, %d)\n", pacman_obj.y, pacman_obj.x);


	return 0;
}

/*waits for input then calls clear_screen();*/
void next_test(UINT32* base) {

	while(!Cconis()){

	}
	Cnecin();
	clear_screen_q(base);
}




/*----------------------------------------------------------------------------------------*/
/* 
*	This is for checking if the ghost struct in 'model.h' is working correcctly 
*    
*	-Used ints for moving backwards by adding negatives 
*
*
*

void move_ghost_position (Ghost *ghost, int new_x, int new_y)
{
		
	/* for now assume that the map will be 640x400 (chnage later once we figure out proper dimesn for map)
	
	if (!(ghost->x + new_x > SCREEN_WIDTH || ghost->x  + new_x < 0 ||
		ghost->y + new_y > SCREEN_HEIGHT || ghost->y + new_y < 0))
	{
			ghost-> x += new_x;
			ghost->y += new_y;
	}
	
	
} 

/* the end game conditon would call this..? 
*
* increase both vert and horizontal speed to capture pacman and end game
*  leave in x-y parameters now but later we can just use a constant 
*


void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{
	
	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;
		
}


/* Same as move_ghost_position () as this does the same thing but with pacman object
*
*
*

void move_pacman_position (Pacman *pacman, char input) 
{
	int new_x_position, new_y_position; 

	switch(input)
	{
		case 'w': pacman -> delta_y = 1; 			
			break;
				
		case 'a': pacman -> delta_x = -1;			
			break;
				
		case 's': pacman -> delta_y = -1;			
			break;
				
		case 'd': pacman -> delta_x = 1;			
			break;

		default:
			printf("Invalid input\n");
			break;
	}
		
	new_x_position = pacman->x + pacman->delta_x;
	new_y_position = pacman->y + pacman->delta_y;

	if (new_x_position < SCREEN_WIDTH && new_x_position >= 0 && 
		new_y_position < SCREEN_HEIGHT && new_y_position >= 0)
		{
			pacman->x = new_x_position;
			pacman->y = new_y_position;

		}



	/*
	if (!(pacman->x + new_x > SCREEN_WIDTH || pacman->x  + new_x < 0 ||
		pacman->y + new_y > SCREEN_HEIGHT || pacman->y + new_y < 0))
	{
			pacman-> x += new_x;
			pacman->y += new_y;
	}
	
	
	
}
*/

void set_input(Pacman *pacman, char input)
{

	pacman -> delta_y = 0;
    pacman -> delta_x = 0;              /* make this better? how to reset it everytime?*/
    pacman -> direction = 0;

	switch(input)
	{
		case 'w': 
			pacman -> delta_y = -1;   		/* UP*/
            pacman -> direction = 1; 
			break;
				
		case 'a': 
			pacman -> delta_x = -1;			/*Left*/
            pacman -> direction = 3;
			break;
				
		case 's': 
			pacman -> delta_y = 1;			/*Down*/
            pacman -> direction = 2;
			break;
				
		case 'd': 
			pacman -> delta_x = 1;			/* Right*/
            pacman -> direction = 4;
			break;

		default:
			printf("Invalid input\n");
            pacman-> delta_x = 0;
            pacman -> delta_y = 0;
			pacman -> direction = 0;
			break;
	}
		



}