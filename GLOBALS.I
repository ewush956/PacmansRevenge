# 1 "globals.c" 1
# 1 "./TYPES.H" 1



typedef unsigned char UCHAR8;
typedef unsigned int  UINT16;
typedef unsigned long ULONG32;

typedef signed char bool;
# 3 "globals.c" 2
# 1 "./globals.h" 1
# 1 "./TYPES.H" 1
# 4 "./globals.h" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 1 "./bitmaps.h" 1
# 1 "./TYPES.H" 1
# 4 "./bitmaps.h" 2




extern const ULONG32* default_pacman_sprites[5 ][9];
extern const ULONG32* evil_pacman_sprites[5 ][9];
extern const ULONG32* crying_ghost_sprites[5 ][2];
extern const ULONG32* awkward_ghost_sprites[5 ][2];
extern const ULONG32* cyclops_ghost_sprites[5 ][2];
extern const ULONG32* moustache_ghost_sprites[5 ][2];
extern const ULONG32* frozen_ghost_sprites[5 ][2];
extern const ULONG32* running_ghost_sprites[5 ][2];

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


extern UCHAR8 direction_map[][40 ];
extern UINT16 direction_map2[][40 ];

extern UINT16 tile_map[][40 ];
# 5 "./model.h" 2
# 31 "./model.h"
typedef enum {
    GHOST_TYPE_CRYING,
    GHOST_TYPE_AWKWARD,
    GHOST_TYPE_CYCLOPS,
    GHOST_TYPE_MOUSTACHE,
	PACMAN,
	WALL,
	OPEN_PATH,
	INVISIBLE_WALL,
	GHOST

}ObjectType;

typedef struct {
	int x_position, y_position;
	bool open_path;
	bool occupied;
	bool has_pellet;

	bool can_go_up;
	bool can_go_down;
	bool can_go_left;
	bool can_go_right;

	UCHAR8 path;
	UCHAR8 alt_path;
}Cell;


typedef struct {
    UINT16 x;
    UINT16 y;
    int delta_x;
    int delta_y;
    UCHAR8 direction;
    UCHAR8 y_cell_index;
    UCHAR8 x_cell_index;

	UINT16 last_x;
	UINT16 last_y;

	UINT16 last_last_x;
	UINT16 last_last_y;

	bool changed_direction;

}Movement;

extern Movement* move;

typedef struct
{
	int current_frame;
	UCHAR8 state;
	ObjectType type;

	Movement* move;
}Pacman;

typedef struct
{
	int current_frame;
	UCHAR8 state;
	ObjectType type;
	bool has_collided;

	Movement* move;
}Ghost;

typedef struct{
	UINT16 seconds, minutes,
	MS_digit_minutes, LS_digit_minutes,
	MS_digit_seconds, LS_digit_seconds;

}Timer;


extern Cell cell_map[24 ][40 ];

extern Pacman pacman;
extern Ghost awkward_ghost;
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;

typedef struct {
    Pacman *pacman;
	Ghost *crying_ghost;
	Ghost *awkward_ghost;
	Ghost *moustache_ghost;
	Ghost *cyclops_ghost;

	Timer *timer;
}Entities;

void move_ghost (Ghost *ghost);
void move_pacman (Pacman *pacman);
ObjectType check_collision(Entities* entity, UINT16 object_y_index, UINT16 object_x_index, int y_delta, int x_delta,
                           ObjectType curr_type);
ObjectType check_pacman_collision(Entities* entity, UINT16 object_y_index,
                                  UINT16 object_x_index, int y_delta, int x_delta);





void init_map_cells(Cell cell_map[][40 ], UINT16 tile_map[][40 ]);
bool update_cell(Movement* entity, UCHAR8 state);
void set_occupied(bool set, int y_index, int x_index);
bool check_shared_occupied(Movement* ghost1_move, Movement* ghost2_move);
void update_cells(Entities* entity);
void update_ghost_direction(Ghost* ghost, Pacman* pacman);
bool check_valid_path(Movement* movement, UCHAR8 direction);
void kill_ghost(Ghost* ghost, Cell cell_map[][40 ]);
void add_wall_to_map(Cell cell_map[24 ][40 ], int y_cell_index, int x_cell_index);
UCHAR8 get_optimal_direction(Movement* movement, Movement* pacman_movement);
UCHAR8 get_alternate_direction(bool can_go_up, bool can_go_down, bool can_go_left, bool can_go_right,
                               UINT16 ghost_x, UINT16 ghost_y, UINT16 pacman_x, UINT16 pacman_y);


ObjectType check_wall_collision(Movement* entity);

void check_proximity(Entities* entity);
void change_pacman_state(Pacman* pacman, UCHAR8 new_state);
void change_ghost_state(Ghost* ghost, UCHAR8 new_state);
void end_game();

void align_axis(Movement* entity);
void flip_direction(Movement* ghost);
void update_current_frame(Entities* all, int clock);

void set_prev_prev(Entities* entity);
void set_prev(Entities* entity);
# 5 "./globals.h" 2


extern bool request_to_render;
extern volatile UINT16 ticks;
extern volatile ULONG32 time_now;



extern Movement pacman_movements;
extern Pacman pacman;

extern Movement awkward_ghost_movement;
extern Ghost awkward_ghost;

extern Movement moustache_ghost_movement;
extern Ghost moustache_ghost;

extern Movement cyclops_ghost_movement;
extern Ghost cyclops_ghost;

extern Movement crying_ghost_movement;
extern Ghost crying_ghost;

extern Timer timer;

extern Entities entity;
# 4 "globals.c" 2
# 1 "./model.h" 1
# 5 "globals.c" 2



bool request_to_render = 0 ;

volatile ULONG32 time_now = 0;
volatile UINT16 ticks = 0;
# 19 "globals.c"
Movement pacman_movement = {
        16  * 19, 16  * 21 + 16 ,
        0,0,
        ((UCHAR8)0) ,
        21,19,
        16  * 19, 16  * 21 + 16 ,
        16  * 19, 16  * 21 + 16 ,
        0 
};
Pacman pacman = {
    0,
    ((UCHAR8)0) ,
    PACMAN,
    &pacman_movement
};
# 40 "globals.c"
Movement crying_ghost_movement = {
        16  * 17, 16  * 10 + 16 ,
        0,0,
        ((UCHAR8)3) ,
        10, 17,
        16  * 17, 16  * 10 + 16 ,
        16  * 17, 16  * 10 + 16 ,
        0 
};
Ghost crying_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_CRYING,
    0 ,
    &crying_ghost_movement
};
# 63 "globals.c"
Movement cyclops_ghost_movement = {
        16  * 17, 16  * 12 + 16 ,
        0,0,
        ((UCHAR8)2) ,
        12, 17,
        16  * 17, 16  * 12 + 16 ,
        16  * 17, 16  * 12 + 16 ,
        0 
};
Ghost cyclops_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_CYCLOPS,
    0 ,
    &cyclops_ghost_movement
};
# 85 "globals.c"
Movement moustache_ghost_movement = {
        16  * 21, 16  * 10 + 16 ,
        0,0,
        ((UCHAR8)2) ,
        10, 21,
        16  * 21, 16  * 10 + 16 ,
        16  * 21, 16  * 10 + 16 ,
        0 
};
Ghost moustache_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_MOUSTACHE,
    0 ,
    &moustache_ghost_movement
};
# 108 "globals.c"
Movement awkward_ghost_movement = {
        16  * 21, 16  * 12 + 16 ,
        0,0,
        ((UCHAR8)2) ,
        12, 21,
        16  * 21, 16  * 12 + 16 ,
        16  * 21, 16  * 12 + 16 ,
        0 
};
Ghost awkward_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_AWKWARD,
    0 ,
    &awkward_ghost_movement
};
Timer timer = {
    0,0,
    20, 28, 44, 52
};
 Entities entity = {
        &pacman,
        &crying_ghost,
        &awkward_ghost,
        &moustache_ghost,
        &cyclops_ghost,
    };
