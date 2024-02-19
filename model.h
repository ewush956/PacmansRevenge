#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "bitmaps.h"

#define UP ((UINT8)0)
#define DOWN ((UINT8)1)
#define LEFT ((UINT8)2)
#define RIGHT ((UINT8)3)

#define MAP_TILE_LENGTH 40        /* 1 tile = 16 pixels*/ 
#define MAP_TILE_HEIGHT 24   

#define MAP_PIXEL_LENGTH 576	/* 18 horiz walls x 32 pixels = 576 */
#define MAP_PIXEL_HEIGHT 352    /* 11 vert walls x 32 pixels = 352   */

#define PIXELS_PER_CELL  16

#define RUNNING ((UINT8)1)
#define FROZEN ((UINT8)2)
#define DEAD ((UINT8)3)
#define DEFAULT ((UINT8)0)
#define EVIL ((UINT8)1)

typedef struct {
	int x_position, y_position;
	bool open_path;
}Cell;

typedef struct 
{
	UINT16 x, y;					/*positon */
	int delta_x, delta_y; 		    /* displacement (horzontal or vertical) */

	int current_frame;		        /* current sprite (state) index */
	UINT8 direction;		        /*UP, DOWN, LEFT, RIGHT*/
	UINT8 state;					/*DEFAULT OR EVIL*/

	UINT16 y_cell_index, x_cell_index;
	struct Cell *current_cell; 
}Pacman;

typedef struct
{
	UINT16 x,y;			
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	UINT8 state;		

	UINT16 y_cell_index, x_cell_index;
	struct Cell *current_cell;

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
UINT8 check_collision(Entities* entity, UINT16 object_y_position, UINT16 object_x_position,UINT16 y_delta, UINT16 x_delta);

void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH], UINT16 tile_map[][MAP_TILE_LENGTH]);
void update_cell(int* x_index, int* y_index);
void kill_ghost(Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]);
void add_wall_to_map(Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH], int y_cell_index, int x_cell_index);

#endif