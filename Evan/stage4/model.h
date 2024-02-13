#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "bitmaps.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define MAP_TILE_LENGTH 18        /* 1 tile = 32 pixels*/ 
#define MAP_TILE_HEIGHT 11   

#define MAP_PIXEL_LENGTH 576	/* 18 horiz walls x 32 pixels = 576 */
#define MAP_PIXEL_HEIGHT 352    /* 11 vert walls x 32 pixels = 352   */

/* use the tile defn's for this */


/*
#define WALL 1;
#define PATH 0;
*/
 /* move_ghost(int x, int y, Object *ref_to_object) */
typedef struct 
{
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

typedef struct {

	int x_position, y_position;
	bool open_path;
}Cell;

extern Cell tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

extern Pacman pacman;
extern Ghost awkward_ghost;
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;

/*
void move_pacman(Pacman* pac_ptr);
void move_ghost(Ghost* ghost_ptr);
*/

/* for object testing */
void move_ghost_position (Ghost *ghost, int new_x, int new_y);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman_position (Pacman *pacman);
bool check_collision(int x, int y); 

/* get pacmans current posisiton -> then in the check colision function check whether that 
 [i][j] value has a 1 2 3 4 5 or 6 using (OR) if its true then there is a collsion otherise continue
 -Start pacman at a defined location within the bounds of the tile array and make sure he cannot
 go out of bounds */
		


#endif