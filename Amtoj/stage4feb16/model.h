#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "bitmaps.h"

#define UP ((UCHAR8)1)
#define DOWN ((UCHAR8)2)
#define LEFT ((UCHAR8)4)				/*3*/		/*usaing powers of 2 numbers*/
#define RIGHT ((UCHAR8)8)			/*4*/

#define MAP_TILE_LENGTH 40        /* 1 tile = 16 pixels*/ 
#define MAP_TILE_HEIGHT 24   

#define MAP_PIXEL_LENGTH 576	/* 18 horiz walls x 32 pixels = 576 */
#define MAP_PIXEL_HEIGHT 352    /* 11 vert walls x 32 pixels = 352   */

#define PIXELS_PER_CELL  16

#define RUNNING 1
#define FROZEN 2
#define DEAD 3
#define DEFAULT 0



typedef enum {
    GHOST_TYPE_CRYING,
    GHOST_TYPE_AWKWARD,
    GHOST_TYPE_CYCLOPS,
    GHOST_TYPE_MOUSTACHE,
	PACMAN
	
} ObjectType;


typedef struct {

	int x_position, y_position;
	bool open_path;
	
}Cell;

typedef struct 
{
	UINT16 x, y;					/*positon */
	int delta_x, delta_y; 		/* displacement (horzontal or vertical) */
	int current_frame;		/* current sprite (state) index */
	UCHAR8 direction;		/*UP, DOWN, LEFT, RIGHT*/
	bool is_evil;
	bool has_collided; 
	UINT16 x_cell_index, y_cell_index; 
	/*Check things like this:		
	if (pacman->direction == DOWN) {check cell_map[pacman->x_cell_index][pacman->y_cell_index + 1].open_path}
	*/
	ObjectType type;

}Pacman;

typedef struct
{
	UINT16 x,y;						/*2 2 1 1 2 1 = 9*/
	int delta_x,delta_y;
	int current_frame;
	UCHAR8 direction;
	UCHAR8 state;		
	UINT16 x_cell_index, y_cell_index;
	struct Cell *current_cell;
	ObjectType type;
	

}Ghost;

typedef struct{
	UINT16 seconds, minutes,
	MS_digit_minutes, LS_digit_minutes,
	MS_digit_seconds, LS_digit_seconds; /*x positions*/

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
	/*srruct Tombstone*/
}Entities;





void move_ghost (Ghost *ghost);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman (Pacman *pacman);/*,UINT16 delta_x, UINT16 delta_y); (may need this later so leaving parameters)*/ 
/*UCHAR8 check_collision(Entities* entity, UINT16 object_y_index, UINT16 object_x_index,UINT16 y_delta, UINT16 x_delta);*/
UCHAR8 check_collision(Entities* entity, UINT16 object_y_index, UINT16 object_x_index,UINT16 y_delta, UINT16 x_delta,ObjectType curr_type);
/*
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH]);
*/

void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH], UINT16 tile_map[][MAP_TILE_LENGTH]);
void set_ghost_path(Ghost *ghost, UINT16* path_array[][MAP_TILE_LENGTH], Cell cell_map[][MAP_TILE_LENGTH]);
void update_cell(int* x_index, int* y_index);
void kill_ghost(Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]);
void add_wall_to_map(Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH], int y_cell_index, int x_cell_index);

#endif