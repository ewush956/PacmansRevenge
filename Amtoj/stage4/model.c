#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"

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


Pacman pacman = {
    0,0,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE       /*Initial state*/
};
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