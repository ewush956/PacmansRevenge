#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "bitmaps.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define MAP_TILE_LENGTH 40        /* 1 tile = 16 pixels*/ 
#define MAP_TILE_HEIGHT 24   

#define MAP_PIXEL_LENGTH 576	/* 18 horiz walls x 32 pixels = 576 */
#define MAP_PIXEL_HEIGHT 352    /* 11 vert walls x 32 pixels = 352   */

#define PIXELS_PER_CELL  16


/* use the tile defn's for this */


/*
#define WALL 1;
#define PATH 0;
*/
 /* move_ghost(int x, int y, Object *ref_to_object) */
 

typedef struct {

	int x_position, y_position;
	bool open_path;
	
}Cell;

typedef struct 
{
	UINT16 x, y;					/*positon */
	int delta_x, delta_y; 		/* displacement (horzontal or vertical) */

	int current_frame;		/* current sprite (state) index */
	UINT8 direction;		/*UP, DOWN, LEFT, RIGHT*/
	bool is_evil;
	bool has_collided; 

	int x_cell_index, y_cell_index; 
	/*Check things like this:		
	if (pacman->direction == DOWN) {check cell_map[pacman->x_cell_index][pacman->y_cell_index + 1].open_path}
	*/

}Pacman;

typedef struct
{
	UINT16 x,y;			
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	bool is_scared;		

	int x_cell_index, y_cell_index;
	struct Cell *current_cell;


}Ghost;

typedef struct{
	UINT16 seconds, minutes,
	MS_digit_minutes, LS_digit_minutes,
	MS_digit_seconds, LS_digit_seconds; /*x positions*/

}Timer;

typedef struct 
{
    struct Pacman *pacman;
	struct Ghost *crying_ghost;
	struct Ghost *awkward_ghost;
	struct Ghost *moustache_ghost;
	struct Ghost *cyclops_ghost;
	/*srruct Tombstone*/
}Entities;


extern int tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];
extern Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];


extern Pacman pacman;
extern Ghost awkward_ghost;
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;


/* for object testing */
void move_ghost (Ghost *ghost, Cell *cell_map[][MAP_TILE_LENGTH], int new_x, int new_y);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman (Pacman *pacman);/*,UINT16 delta_x, UINT16 delta_y); (may need this later so leaving parameters)*/ 

/*UINT8 check_collision(Ghost *ghost, Pacman *pacman);*/

UINT8 check_collision(Entities *entity, UINT16 object_y_position, UINT16 object_x_position);

/*bool check_collision(UINT16 object_x_position, UINT16 object_y_position);*/
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH]);
void set_ghost_path(Ghost *ghost, UINT16* path_array[][MAP_TILE_LENGTH], Cell cell_map[][MAP_TILE_LENGTH]);

/*void init_ghost_paths(Ghost *ghost1, Ghost *ghost2, Ghost *ghost3, Ghost *ghost4, Cell cell_map[][MAP_TILE_LENGTH]);*/
void update_cell(int* x_index, int* y_index);

#endif