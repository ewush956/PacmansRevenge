# 1 "model.c" 1
# 1 "./TYPES.H" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef signed char bool;
# 1 "model.c" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 1 "./bitmaps.h" 1
# 1 "./TYPES.H" 1
# 4 "./bitmaps.h" 2


extern const UINT32 pac_1[];
extern const UINT32 pac_2[];
extern const UINT32 pac_3[];
extern const UINT32 pac_4[];

extern const UINT32 evil_pac_1[];
extern const UINT32 evil_pac_2[];
extern const UINT32 evil_pac_3[];
extern const UINT32 evil_pac_4[];

extern const UINT32 ghost_1_up[];
extern const UINT32 ghost_1_down[];
extern const UINT32 ghost_1_left[];
extern const UINT32 ghost_1_right[];

extern const UINT32 ghost_2_up[];
extern const UINT32 ghost_2_down[];
extern const UINT32 ghost_2_left[];
extern const UINT32 ghost_2_right[];

extern const UINT32 ghost_3_up[];
extern const UINT32 ghost_3_down[];
extern const UINT32 ghost_3_left[];
extern const UINT32 ghost_3_right[];

extern const UINT32 ghost_4_up[];
extern const UINT32 ghost_4_down[];
extern const UINT32 ghost_4_left[];
extern const UINT32 ghost_4_right[];

extern const UINT32 wall_left_down_right[];
extern const UINT32 wall_up_down[];
extern const UINT32 wall_left_right[];
extern const UINT32 wall_down_right[];

extern const UINT32 tombstone[];
extern const UINT32 ghost_run[];
extern const UINT32 ghost_freeze[];

extern const UINT32 wall1_all[];
extern const UINT32 wall2_all[];

extern const UINT32 wall1_vert[];
extern const UINT32 wall2_vert[];

extern const UINT32 wall1_horz[];
extern const UINT32 wall2_horz[];

extern const UINT32 wall1_URD[];
extern const UINT32 wall1_LD[];
extern const UINT32 wall1_LUR[];
extern const UINT32 wall2_RDL[];
extern const UINT32 wall2_RD[];
extern const UINT32 wall2_DLU[];
extern const UINT32 wall2_LU[];
extern const UINT32 wall2_UR[];
extern const UINT32 wall2_UR[];

extern const UINT32 null_sprite_32[];

extern const UINT32 test64[];
# 5 "./model.h" 2
# 16 "./model.h"
typedef struct
{
	UINT16 x, y;
	int delta_x, delta_y;

	int current_frame;
	UINT8 direction;
	bool is_evil;

}Pacman;

typedef struct
{
	UINT16 x,y;
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	UINT8 is_scared;

}Ghost;


extern const UINT16 tile_map[11][18];

void move_pacman(Pacman* pac_ptr);
void move_ghost(Ghost* ghost_ptr);


void clock_tick_handle();
# 2 "model.c" 2
# 1 "./bitmaps.h" 1
# 3 "model.c" 2
# 27 "model.c"
const UINT16 tile_map[11 ][18 ] = {

{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
{2,0,4,1,1,1,0,1,0,1,0,1,1,1,1,3,0,2},
{2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2},
{2,0,2,0,1,1,0,4,0,0,3,0,1,1,0,2,0,2},
{2,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,2},
{2,0,2,0,1,1,0,0,0,0,0,0,1,1,0,2,0,2},
{2,0,2,0,0,0,0,0,1,1,1,0,0,0,0,2,0,2},
{2,0,2,1,1,1,1,0,1,1,1,0,1,1,1,1,0,2},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


const UINT8 map[][25];

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
    0,0,
    0,0,
    0,
    1 ,
    0 
};
