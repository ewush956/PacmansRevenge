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
	INVISIBLE_WALL
	
}ObjectType;

typedef struct {
	int x_position, y_position;
	bool open_path;
	bool occupied;
}Cell;

typedef struct 
{
	UINT16 x, y;					/*positon */
	int delta_x, delta_y; 		    /* displacement (horzontal or vertical) */

	int current_frame;		        /* current sprite (state) index */
	UCHAR8 direction;		        /*UP, DOWN, LEFT, RIGHT*/
	UCHAR8 state;					/*DEFAULT OR EVIL*/

	UINT16 y_cell_index, x_cell_index;
	ObjectType type;
}Pacman;

typedef struct
{
	UINT16 x,y;			
	int delta_x,delta_y;

	int current_frame;
	UCHAR8 direction;
	UCHAR8 state;		

	UINT16 y_cell_index, x_cell_index;
	ObjectType type;

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
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH], UINT16 tile_map[][MAP_TILE_LENGTH]);
void update_cell(UINT16* x_index, UINT16* y_index, UINT16 x_position, 
                UINT16 y_position, UCHAR8 state);
void update_cells(Entities* entity);
void kill_ghost(Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]);
void add_wall_to_map(Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH], int y_cell_index, int x_cell_index);

void check_proximity(Entities* entity);
void change_pacman_state(Pacman* pacman, UCHAR8 new_state);
void change_ghost_state(Ghost* ghost, UCHAR8 new_state);
void end_game();

#endif