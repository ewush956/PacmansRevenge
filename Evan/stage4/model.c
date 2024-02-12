#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
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
    0,0,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE       /*Initial state*/
};

Ghost crying_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE,
};
Ghost moustache_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE
};
Ghost cyclops_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE
};
Ghost awkward_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE
};

#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include "events.h"


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
Cell cell_0_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET, FALSE};
Cell cell_0_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET, FALSE};

Cell cell_1_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 32, FALSE};
Cell cell_1_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 32, TRUE};
Cell cell_1_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 32, FALSE};

Cell cell_2_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 64, TRUE};
Cell cell_2_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 64, TRUE};
Cell cell_2_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 64, TRUE};
Cell cell_2_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 64, TRUE};
Cell cell_2_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 64, FALSE};
Cell cell_2_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 64, TRUE};
Cell cell_2_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 64, FALSE};

Cell cell_3_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 96, FALSE};
Cell cell_3_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 96, FALSE};
Cell cell_3_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 96, FALSE};
Cell cell_3_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 96, FALSE};
Cell cell_3_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 96, FALSE};
Cell cell_3_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 96, FALSE};

/* LEFT OFF HERE, BELOW NEEDS UPDATED WALL BOOLS!!!!!*/


Cell cell_3_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 96, TRUE};
Cell cell_3_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 96, FALSE};

Cell cell_4_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 128, FALSE};
Cell cell_4_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 128, TRUE};
Cell cell_4_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 128, FALSE};

Cell cell_5_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 160, FALSE};
Cell cell_5_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 160, TRUE};
Cell cell_5_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 160, FALSE};

Cell cell_6_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 192, FALSE};
Cell cell_6_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 192, TRUE};
Cell cell_6_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 192, FALSE};

Cell cell_7_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 224, FALSE};
Cell cell_7_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 224, TRUE};
Cell cell_7_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 224, FALSE};

Cell cell_8_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 256, FALSE};
Cell cell_8_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 256, TRUE};
Cell cell_8_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 256, FALSE};

Cell cell_9_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 288, FALSE};
Cell cell_9_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 288, TRUE};
Cell cell_9_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 288, FALSE};

Cell cell_10_0 = {X_PIXEL_OFFSET, Y_PIXEL_OFFSET + 320, FALSE};
Cell cell_10_1 = {X_PIXEL_OFFSET + 32, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_2 = {X_PIXEL_OFFSET + 64, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_3 = {X_PIXEL_OFFSET + 96, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_4 = {X_PIXEL_OFFSET + 128, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_5 = {X_PIXEL_OFFSET + 160, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_6 = {X_PIXEL_OFFSET + 192, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_7 = {X_PIXEL_OFFSET + 224, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_8 = {X_PIXEL_OFFSET + 256, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_9 = {X_PIXEL_OFFSET + 288, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_10 = {X_PIXEL_OFFSET + 320, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_11 = {X_PIXEL_OFFSET + 352, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_12 = {X_PIXEL_OFFSET + 384, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_13 = {X_PIXEL_OFFSET + 416, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_14 = {X_PIXEL_OFFSET + 448, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_15 = {X_PIXEL_OFFSET + 480, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_16 = {X_PIXEL_OFFSET + 512, Y_PIXEL_OFFSET + 320, TRUE};
Cell cell_10_17 = {X_PIXEL_OFFSET + 544, Y_PIXEL_OFFSET + 320, FALSE};

/*Continue until cell_10_18*/


const Cell tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {

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

void move_pacman_position (Pacman *pacman, char input) 
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