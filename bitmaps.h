#ifndef BITMAPS_H
#define BITMAPS_H

#include "TYPES.H"

#define DIRECTIONS 5 

extern const ULONG32* default_pacman_sprites[DIRECTIONS][9];
extern const ULONG32* evil_pacman_sprites[DIRECTIONS][9]; 
extern const ULONG32* crying_ghost_sprites[DIRECTIONS][2]; 
extern const ULONG32* awkward_ghost_sprites[DIRECTIONS][2]; 
extern const ULONG32* cyclops_ghost_sprites[DIRECTIONS][2]; 
extern const ULONG32* moustache_ghost_sprites[DIRECTIONS][2]; 
extern const ULONG32* frozen_ghost_sprites[DIRECTIONS][2];
extern const ULONG32* running_ghost_sprites[DIRECTIONS][2];

extern const ULONG32 evil_pac_up_2[32];
extern const ULONG32 evil_pac_down_1[32];
extern const ULONG32 pac_left_2[32];
extern const ULONG32 cyclops_ghost_down_2[32];
extern const ULONG32 evil_pac_up_3[32];
extern const ULONG32 pac_up_2[32];
extern const ULONG32 pac_left_3[32];
extern const ULONG32 evil_pac_down_4[32];
extern const ULONG32 pac_up_3[32];
extern const ULONG32 pac_left_1[32];
extern const ULONG32 evil_pac_left_2[32];
extern const ULONG32 cyclops_ghost_left_2[32];
extern const ULONG32 moustache_ghost_right_2[32];
extern const ULONG32 evil_pac_left_4[32];
extern const ULONG32 moustache_ghost_down_2[32];
extern const ULONG32 evil_pac_up_1[32];
extern const ULONG32 cyclops_ghost_right_2[32];
extern const ULONG32 moustache_ghost_up_2[32];
extern const ULONG32 crying_ghost_left_2[32];
extern const ULONG32 crying_ghost_down_2[32];
extern const ULONG32 pac_up_4[32];
extern const ULONG32 evil_pac_left_3[32];
extern const ULONG32 evil_pac_up_4[32];
extern const ULONG32 awkward_ghost_down_2[32];
extern const ULONG32 awkward_ghost_left_2[32];
extern const ULONG32 pac_left_4[32];
extern const ULONG32 cyclops_ghost_up_2[32];
extern const ULONG32 awkward_ghost_up_2[32];
extern const ULONG32 evil_pac_down_2[32];
extern const ULONG32 crying_ghost_right_2[32];
extern const ULONG32 moustache_ghost_left_2[32];
extern const ULONG32 evil_pac_left_1[32];
extern const ULONG32 pac_down_1[32];
extern const ULONG32 pac_down_2[32];
extern const ULONG32 crying_ghost_up_2[32];
extern const ULONG32 evil_pac_down_3[32];
extern const ULONG32 pac_down_4[32];
extern const ULONG32 pac_up_1[32];
extern const ULONG32 awkward_ghost_right_2[32];
extern const ULONG32 pac_down_3[32];


extern const ULONG32 pac_1[];
extern const ULONG32 pac_2[];
extern const ULONG32 pac_3[];
extern const ULONG32 pac_4[];

extern const ULONG32 evil_pac_1[];
extern const ULONG32 evil_pac_2[];
extern const ULONG32 evil_pac_3[];
extern const ULONG32 evil_pac_4[];

extern const ULONG32 moustache_ghost_up_1[];
extern const ULONG32 moustache_ghost_down_1[];
extern const ULONG32 moustache_ghost_left_1[];
extern const ULONG32 moustache_ghost_right_1[];

extern const ULONG32 awkward_ghost_up_1[];
extern const ULONG32 awkward_ghost_down_1[];
extern const ULONG32 awkward_ghost_left_1[];
extern const ULONG32 awkward_ghost_right_1[];

extern const ULONG32 crying_ghost_up_1[];
extern const ULONG32 crying_ghost_down_1[];
extern const ULONG32 crying_ghost_left_1[];
extern const ULONG32 crying_ghost_right_1[];

extern const ULONG32 cyclops_ghost_left_1[];
extern const ULONG32 cyclops_ghost_right_1[];
extern const ULONG32 cyclops_ghost_up_1[];
extern const ULONG32 cyclops_ghost_down_1[];

extern const ULONG32 tombstone[];
extern const ULONG32 ghost_run_1[];
extern const ULONG32 ghost_freeze_1[];
extern const ULONG32 splash[8000];

extern const UINT16 wall_single_16[];

extern const ULONG32 null_sprite_16[];
extern const ULONG32 null_sprite_32[];

extern const ULONG32 test64[];
extern const UCHAR8 pellet[8];

extern const ULONG32* wall_map[][20];


extern UCHAR8 direction_map[][MAP_TILE_LENGTH];
extern UCHAR8 direction_map2[][MAP_TILE_LENGTH];
extern UCHAR8 direction_map3[][MAP_TILE_LENGTH];
extern UCHAR8 direction_map4[][MAP_TILE_LENGTH];

extern UINT16 tile_map[][MAP_TILE_LENGTH];

#endif 