#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "bitmaps.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
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

}Pacman;

typedef struct 
{
	UINT16 x,y;			
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	bool is_scared;

}Ghost;

extern const UINT8 map[][25];	/* I don't know how many*/

extern Pacman pacman;
 
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;
extern Ghost awkward_ghost;

extern const UINT32 default_pac_sprites[][4];
extern const UINT32 evil_pac_sprites[][4];
extern const UINT32 crying_ghost_sprites[][4];
extern const UINT32 moustache_ghost_sprites[][4];
extern const UINT32 cyclops_ghost_sprites[][4];
extern const UINT32 awkward_ghost_sprites[][4];

#endif