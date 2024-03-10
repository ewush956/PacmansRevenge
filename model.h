#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "bitmaps.h"

#define UP ((UCHAR8)0)
#define DOWN ((UCHAR8)1)
#define LEFT ((UCHAR8)2)
#define RIGHT ((UCHAR8)3)

#define MOVEMENT_MULTIPLIER 3 

#define MAP_TILE_LENGTH 40        /* 1 tile = 16 pixels*/ 
#define MAP_TILE_HEIGHT 24   

#define MAP_PIXEL_LENGTH 576	/* 18 horiz walls x 32 pixels = 576 */
#define MAP_PIXEL_HEIGHT 352    /* 11 vert walls x 32 pixels = 352   */

#define PIXELS_PER_CELL  16

#define RUNNING ((UCHAR8)1)
#define FROZEN ((UCHAR8)2)
#define DEAD ((UCHAR8)3)
#define DEFAULT ((UCHAR8)0)
#define EVIL ((UCHAR8)1)

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
}Cell;


typedef struct {
    UINT16 x;
    UINT16 y;
    int delta_x;
    int delta_y;
    UCHAR8 direction;
    UCHAR8 y_cell_index;
    UCHAR8 x_cell_index;
}Movement;

extern Movement* move;

typedef struct 
{
	int current_frame;		        /* current sprite (state) index */
	UCHAR8 state;					/*DEFAULT OR EVIL*/
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


extern Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

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

/*
ObjectType process_ghost_collision(Entities* all);
*/

void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH], UINT16 tile_map[][MAP_TILE_LENGTH]);
void update_cell(Movement* entity, UCHAR8 state);
void set_occupied(bool set, int y_index, int x_index); 
bool check_shared_occupied(Movement* ghost1_move, Movement* ghost2_move);
void update_cells(Entities* entity);
void kill_ghost(Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]);
void add_wall_to_map(Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH], int y_cell_index, int x_cell_index);

ObjectType check_wall_collision(Movement* entity);

void check_proximity(Entities* entity);
void change_pacman_state(Pacman* pacman, UCHAR8 new_state);
void change_ghost_state(Ghost* ghost, UCHAR8 new_state);
void end_game();

void align_axis(Movement* entity);
void flip_direction(Movement* ghost);
void update_current_frame(Entities* all, int clock);

#endif