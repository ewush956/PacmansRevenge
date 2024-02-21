#ifndef BITMAPS_H
#define BITMAPS_H

#include "TYPES.H"

#define DIRECTIONS 4 

extern const ULONG32* default_pacman_sprites[DIRECTIONS][7];
extern const ULONG32* evil_pacman_sprites[DIRECTIONS][7]; 
extern const ULONG32* crying_ghost_sprites[DIRECTIONS][2]; 
extern const ULONG32* awkward_ghost_sprites[DIRECTIONS][2]; 
extern const ULONG32* cyclops_ghost_sprites[DIRECTIONS][2]; 
extern const ULONG32* moustache_ghost_sprites[DIRECTIONS][2]; 

extern const ULONG32 pac_1[];
extern const ULONG32 pac_2[];
extern const ULONG32 pac_3[];
extern const ULONG32 pac_4[];

extern const ULONG32 evil_pac_1[];
extern const ULONG32 evil_pac_2[];
extern const ULONG32 evil_pac_3[];
extern const ULONG32 evil_pac_4[];

extern const ULONG32 ghost_1_up[];
extern const ULONG32 ghost_1_down[];
extern const ULONG32 ghost_1_left[];
extern const ULONG32 ghost_1_right[];

extern const ULONG32 ghost_2_up[];
extern const ULONG32 ghost_2_down[];
extern const ULONG32 ghost_2_left[];
extern const ULONG32 ghost_2_right[];

extern const ULONG32 ghost_3_up[];
extern const ULONG32 ghost_3_down[];
extern const ULONG32 ghost_3_left[];
extern const ULONG32 ghost_3_right[];

extern const ULONG32 ghost_4_up[];
extern const ULONG32 ghost_4_down[];
extern const ULONG32 ghost_4_left[];
extern const ULONG32 ghost_4_right[];

extern const ULONG32 cyclops_ghost_L[];
extern const ULONG32 cyclops_ghost_R[];
extern const ULONG32 cyclops_ghost_U[];
extern const ULONG32 cyclops_ghost_D[];

extern const ULONG32 tombstone[];
extern const ULONG32 ghost_run[];
extern const ULONG32 ghost_freeze[];

extern const ULONG32 wall_ULD[];
extern const ULONG32 wall_all[];
extern const ULONG32 wall_vert[];
extern const ULONG32 wall_UL[];
extern const ULONG32 wall_UR[];
extern const ULONG32 wall_LDR[];
extern const ULONG32 wall_ULR[];
extern const ULONG32 wall_UDR[];
extern const ULONG32 wall_LD[];
extern const ULONG32 wall_DR[];
extern const ULONG32 wall_horz[];
extern const ULONG32 wall_single[];
extern const UINT16 wall_single_16[];

extern const ULONG32 wall_horz_end_L[];

extern const ULONG32 null_sprite_16[];
extern const ULONG32 null_sprite_32[];

extern const ULONG32 test64[];

extern const ULONG32* wall_map[][20];

extern UINT16 tile_map[][MAP_TILE_LENGTH];
#endif 