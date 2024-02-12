#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include "events.h"
#include <stdio.h>

#define MAX_MAP_LENGTH 18          /* 18 horiz walls x 32 pixels = 576 */
#define MAX_MAP_HEIGHT 11         /* 11 vert walls x 32 pixels = 352   */

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

/*
0 is a open square and 
1 is a horizontal wall
2 iS a vertical wall 
3 is a left-down (LD)
4 is RD
5 is LU
6 is UR (up -> right)
*/
const UINT16 tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
/*0                               18*/
{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
{2,0,4,1,1,1,0,1,0,1,0,1,1,1,1,3,0,2},
{2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2},
{2,0,2,0,4,3,0,4,0,0,3,0,4,3,0,2,0,2},
{2,0,0,0,0,0,0,6,1,1,5,0,2,2,0,0,0,2},
{2,0,2,0,6,5,0,0,0,0,0,0,6,5,0,2,0,2},
{2,0,2,0,0,0,0,0,4,1,3,0,0,0,0,2,0,2},
{2,0,6,1,1,1,1,0,6,1,5,0,1,1,1,5,0,2},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
{6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5}
};


/*const UINT8 map[][25];	/* I don't know how many*/

Pacman pacman;
Ghost crying_ghost;
Ghost moustache_ghost;
Ghost cyclops_ghost;
Ghost awkward_ghost;

const UINT32 default_pac_sprites[][4];
const UINT32 evil_pac_sprites[][4];
const UINT32 crying_ghost_sprites[][4];
const UINT32 moustache_ghost_sprites[][4];
const UINT32 cyclops_ghost_sprites[][4];
const UINT32 awkward_ghost_sprites[][4];

const UINT32* default_pacman_sprites[4][4] = {
    {pac_1, pac_2, pac_3, pac_4},
    {pac_1, pac_2, pac_3, pac_4}
};
const UINT32* evil_pacman_sprites[4][4] = {
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4},
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4}
};

/*
Pacman pacman = {
    0,0,        /*Initial position, won't actually be 0,0*/
/*    0,0,        /*Initial Displacement*/
/*    0,          /*Initial state index*/
/*    UP,         /*Initial direction*/
/*    FALSE       /*Initial state*/
/*};
*/

/*
Ghost crying_ghost = {
    0,0,
    0,0,
    {ghost_4_up, ghost_4_down, ghost_4_left, ghost_4_right},
    FALSE,
    {
    {1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1,},
    {1, 0, 1, 0, 1, 0, 1},
    },
    {
    {1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 1,},
    {1, 0, 1, 0, 1, 0, 1},
    },


};
*/

/*
moustache_ghost
cyclops_ghost
awkward_ghost
*/
void move_pacman_position(Pacman *pacman, char input) 
{
    bool collision; 
	UINT16 new_x_position, new_y_position; 
    pacman -> delta_y = 0;
    pacman -> delta_x = 0;              /* make this better? how to reset it everytime?*/
    pacman->direction = 0;

	switch(input)
	{
		case 'w': pacman -> delta_y = -1;   		/* UP*/
            pacman->direction = 1;
			break;
				
		case 'a': pacman -> delta_x = -1;			/*Left*/
             /*pacman->direction = 2;*/
			break;
				
		case 's': pacman -> delta_y = 1;			/*Down*/
             /*pacman->direction = 3;*/
			break;
				
		case 'd': pacman -> delta_x = 1;			/* Right*/
            /*pacman->direction = 4;*/
			break;

		default:
			printf("Invalid input\n");
            pacman-> delta_x = 0;
            pacman -> delta_y = 0;
			break;
	}
		
	new_x_position = pacman->x + pacman->delta_x;
	new_y_position = pacman->y + pacman->delta_y;
    
    /*
	if (new_x_position < SCREEN_WIDTH && new_x_position >= 0 && 
		new_y_position < SCREEN_HEIGHT && new_y_position >= 0)
		{
			pacman->x = new_x_position;
			pacman->y = new_y_position;

		}
    */
    

    /*pacman->has_collided == FALSE) */

    collision = check_collision(&pacman, new_x_position, new_y_position);

   /*
    printf("%d\n",tile_map[4][5]);*/

    if (collision == 0)
    {
        printf("MOVING HIM");
        pacman->x = new_x_position;
		pacman->y = new_y_position;
       
    }


	/* old code
	if (!(pacman->x + new_x > SCREEN_WIDTH || pacman->x  + new_x < 0 ||
		pacman->y + new_y > SCREEN_HEIGHT || pacman->y + new_y < 0))
	{
			pacman-> x += new_x;
			pacman->y += new_y;
	}
	*/
	
	
}


/* the end game conditon would call this..? 
*
* increase both vert and horizontal speed to capture pacman and end game
*  leave in x-y parameters now but later we can just use a constant 
*
*/
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{
	
	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;
		
}


/* 
*	This is for checking if the ghost struct in 'model.h' is working correcctly 
*    
*	-Used ints for moving backwards by adding negatives 
*
*
* (..hard-coded path)
*/

/* pass in the current posiition into this and update accordingly 
/* make different instances of ghosts in test main program to call
*/
void move_ghost_position (Ghost *ghost, int current_x, int current_y)
{
		
	/* for now assume that the map will be 640x400 (chnage later once we figure out proper dimesn for map)*/
	/*
	if (!(ghost->x + new_x > SCREEN_WIDTH || ghost->x  + new_x < 0 ||
		ghost->y + new_y > SCREEN_HEIGHT || ghost->y + new_y < 0))
	{
			ghost-> x += new_x;
			ghost->y += new_y;
	}

	*/

  /* check pacmans posiition adn always go opposite of it */
  /* then check for collsion if collsion then try a different direction and repreat */
  


} 
/*bool check_collision (Pacman* pacman, UINT16 pacman_x_position, UINT16 pacman_y_position)*/
bool check_collision (Pacman* pacman, UINT16 object_x_position, UINT16 object_y_position)
{
    
    bool collision = 0; 

    /* checking if the location is occupied by a wall or corner sprite */
    if (tile_map[object_y_position][object_x_position] == 1 || 
        tile_map[object_y_position][object_x_position] == 2 ||
        tile_map[object_y_position][object_x_position] == 3 ||
        tile_map[object_y_position][object_x_position] == 4 ||
        tile_map[object_y_position][object_x_position] == 5 ||
        tile_map[object_y_position][object_x_position] == 6)
        {
            
            /*pacman-> has_collided = TRUE;*/
            printf(" collision \n");
            printf("This value is for collision is: %d\n",tile_map[object_y_position][object_x_position]);
         /*   printf("Direction: %d\n", pacman->direction);*/
            collision = 1;

        }

        else{

            printf(" YOURE GOOD: %d\n",tile_map[object_y_position][object_x_position]);
            printf("Direction: %u\n", pacman->direction);
        }
        /*
            pacman->has_collided = FALSE;
            */

        return collision; 

}