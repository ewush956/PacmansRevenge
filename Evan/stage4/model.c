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
const UINT32* default_pacman_sprites[4][4] = {
    {pac_1, pac_2, pac_3, pac_4},
    {pac_1, pac_2, pac_3, pac_4}
};
const UINT32* evil_pacman_sprites[4][4] = {
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4},
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4}
};
Pacman pacman = {
    0,0,
    0,0,
    UP,
    []
    FALSE
};

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

crying_ghost
moustache_ghost
cyclops_ghost
awkward_ghost