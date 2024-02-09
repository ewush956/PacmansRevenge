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