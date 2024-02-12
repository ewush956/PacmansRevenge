#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include "cells.c"
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

const UINT8 map[][25];	/* I don't know how many*/

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

Pacman pacman = {
    cell_0_0->x_position, cell_0_0->y_position,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE,       /*Initial state*/
    &cell_0_0;    /*Initial cell*/

};

Ghost crying_ghost = {
    cell_0_0->x_position, cell_0_0->y_position,
    0,0,
    0,
    UP,
    FALSE,
    &cell_0_0;    /*Or whatever cell it starts in*/
};
Ghost moustache_ghost = {
    cell_0_0->x_position, cell_0_0->y_position,
    0,0,
    0,
    UP,
    FALSE,
    &cell_0_0;
};
Ghost cyclops_ghost = {
    cell_0_0->x_position, cell_0_0->y_position,
    0,0,
    0,
    UP,
    FALSE,
    &cell_0_0;
};
Ghost awkward_ghost = {
    cell_0_0->x_position, cell_0_0->y_position,
    0,0,
    0,
    UP,
    FALSE,
    &cell_0_0;
};

void move_pacman_position (Pacman *pacman, UINT16 delta_x, UINT16 delta_y) 
{
    
	UINT16 new_x_position, new_y_position; 
    switch(input)
	{
		case 'w': pacman -> delta_y = 1; 			/* UP*/
			break;
				
		case 'a': pacman -> delta_x = -1;			/*Left*/
			break;
				
		case 's': pacman -> delta_y = -1;			/*Down*/
			break;
				
		case 'd': pacman -> delta_x = 1;			/* Right*/
			break;

		default:
			/*printf("Invalid input\n");*/
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

    handle_collsion(pacman, new_x_position, new_y_position);
    
    if (pacman->has_collided == 0)  /*false (i.e. he has NOT collided)*/
    {
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
void move_ghost_position (Ghost *ghost, int new_x, int new_y)
{
		
	/* for now assume that the map will be 640x400 (chnage later once we figure out proper dimesn for map)*/
	
	if (!(ghost->x + new_x > SCREEN_WIDTH || ghost->x  + new_x < 0 ||
		ghost->y + new_y > SCREEN_HEIGHT || ghost->y + new_y < 0))
	{
			ghost-> x += new_x;
			ghost->y += new_y;
	}
	
	
} 