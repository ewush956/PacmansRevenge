#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "bitmaps.h"

#define UP ((UINT8)1)
#define DOWN ((UINT8)2)
#define LEFT ((UINT8)3)
#define RIGHT ((UINT8)4)


#define MAP_TILE_LENGTH 18        /* 1 tile = 32 pixels*/ 
#define MAP_TILE_HEIGHT 11         

#define MAP_PIXEL_LENGTH 576	/* 18 horiz walls x 32 pixels = 576 */
#define MAP_PIXEL_HEIGHT 352    /* 11 vert walls x 32 pixels = 352   */

#define X_PIXEL_OFFSET 31
#define Y_PIXEL_OFFSET 20


/* use the tile defn's for this 
extern const UINT16 tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];
*/

/*
#define WALL 1;
#define PATH 0;
*/
 /* move_ghost(int x, int y, Object *ref_to_object) */

 typedef struct {

	UINT16 x_position, y_position;		/*changed from int*/
	bool open_path;
	
	
}Cell;

typedef struct 
{
    UINT32 value;

}Xor;

extern Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

typedef struct {
	UINT16 x, y;					/*positon */
	int delta_x, delta_y; 		/* displacement (horzontal or vertical) */

	int current_frame;		/* current sprite (state) index */
	UINT8 direction;		/*UP, DOWN, LEFT, RIGHT*/
	bool is_evil;
	bool has_collided; 

	Cell* current_cell;

}Pacman;

typedef struct 
{
	UINT16 x,y;			
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	bool is_scared;		/*chnaged from bool*/

	Cell* current_cell;
	Cell path[MAP_TILE_LENGTH][MAP_TILE_HEIGHT];

}Ghost;



/*extern Cell tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];*/

extern Pacman pacman;
extern Ghost awkward_ghost;
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;


/* for object testing */
/*void move_ghost_position (Ghost *ghost, Pacman *pacman ,int current_x, int current_y);*/
void move_ghost_position (Ghost *ghost, UINT16* ghost_path[][MAP_TILE_LENGTH],Cell *cell_map[][MAP_TILE_LENGTH]);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
bool move_pacman_position (Pacman *pacman);
 
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH]);
void set_ghost_path(Ghost *ghost, UINT16* path_array[][MAP_TILE_LENGTH], Cell cell_map[][MAP_TILE_LENGTH]);
void init_ghost_paths(Ghost *ghost1, Ghost *ghost2, Ghost *ghost3, Ghost *ghost4, Cell cell_map[][MAP_TILE_LENGTH]);
bool check_collision (UINT16 object_x_position, UINT16 object_y_position);
UINT32 random_generator(Xor *xor);

/*bool check_collision(Pacman* pacman, UINT16 pacman_x_position, UINT16 pacman_y_position); */

/* we dont even need to pass obejct ptrs , only the position of the object*/
/*bool check_collision (Pacman* pacman, UINT16 object_x_position, UINT16 object_y_position);*/

/* get pacmans current posisiton -> then in the check colision function check whether that 
 [i][j] value has a 1 2 3 4 5 or 6 using (OR) if its true then there is a collsion otherise continue
 -Start pacman at a defined location within the bounds of the tile array and make sure he cannot
 go out of bounds */


void clock_tick_handle();		/* calls move pacman calls all synch event handlers */
		


#endif