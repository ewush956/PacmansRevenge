#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"

const UINT8 map[][25];	/* I don't know how many*/

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
Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

Pacman pacman = {
    16*19, 16*21 + Y_PIXEL_OFFSET,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE,       /*Initial state*/
};

Ghost crying_ghost = {
    16*17,16*10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
    0,0,
    0,
    UP,
    FALSE
               /*Or whatever cell it starts in*/
 
};
Ghost moustache_ghost = {
    16*21,16*10 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE
};
Ghost cyclops_ghost = {
    16*17,16*12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE
};
Ghost awkward_ghost = {
    16*21,16*12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE
};

void move_pacman_position (Pacman *pacman, UINT16 delta_x, UINT16 delta_y) 
{
    
	UINT16 new_x_position, new_y_position; 
    char input = 'w';
    switch(input)
	{
		case 'w': pacman -> delta_y = 1; 			/* UP*/
			break;
				
		case 'a': pacman -> delta_x = -1;			/*Left*/
			break;
				
		case 's': pacman -> delta_y = -1;			/*Down*/
			break;
				
		case 'd': pacman -> delta_x = 1;			/* Right*/
			break;

		default:
			/*printf("Invalid input\n");*/
			break;
	}
		
	new_x_position = pacman->x + pacman->delta_x;
	new_y_position = pacman->y + pacman->delta_y;

    
    /*
	if (new_x_position < SCREEN_WIDTH && new_x_position >= 0 && 
		new_y_position < SCREEN_HEIGHT && new_y_position >= 0)
		{
			pacman->x = new_x_position;
			pacman->y = new_y_position;

		}
    */

    /*check_collsion(pacman, new_x_position, new_y_position); */
    
    if (pacman->has_collided == 0)  /*false (i.e. he has NOT collided)*/
    {
        pacman->x = new_x_position;
		pacman->y = new_y_position;
    
    }


	/* old code
	if (!(pacman->x + new_x > SCREEN_WIDTH || pacman->x  + new_x < 0 ||
		pacman->y + new_y > SCREEN_HEIGHT || pacman->y + new_y < 0))
	{
			pacman-> x += new_x;
			pacman->y += new_y;
	}
	*/
	
	
}


/* the end game conditon would call this..? 
*
* increase both vert and horizontal speed to capture pacman and end game
*  leave in x-y parameters now but later we can just use a constant 
*
*/
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{
	
	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;
		
}


/* 
*	This is for checking if the ghost struct in 'model.h' is working correcctly 
*    
*	-Used ints for moving backwards by adding negatives 
*
*
* (..hard-coded path)
*/
void move_ghost_position (Ghost *ghost, int new_x, int new_y)
{
	if (!(ghost->x + new_x > SCREEN_WIDTH || ghost->x  + new_x < 0 ||
		ghost->y + new_y > SCREEN_HEIGHT || ghost->y + new_y < 0))
	{
			ghost-> x += new_x;
			ghost->y += new_y;
	}
}
bool check_collision(int x, int y) {
    return TRUE;
} 
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH]){

    UINT16 tile_map[][MAP_TILE_LENGTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1},
        {1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1},
        {1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1},
        {1, 0, 2, 1, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 0, 2, 1},
        {1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 2, 1, 1, 0, 2, 1, 1, 0, 2, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 0, 2, 2, 0, 2, 1, 0, 2, 1, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 0, 2, 1, 0, 2, 2, 0, 2, 2, 0, 2, 1},
        {1, 2, 2, 1, 0, 2, 1, 0, 0, 0, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 0, 0, 0, 2, 1, 0, 2, 1, 2, 2, 1},
        {1, 1, 1, 1, 0, 2, 1, 0, 2, 2, 0, 2, 1, 0, 2, 1, 1, 0, 0, 0, 0, 0, 2, 1, 1, 0, 2, 1, 0, 2, 2, 0, 2, 1, 0, 2, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 2, 2, 0, 2, 2, 0, 2, 1, 0, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 2, 0, 2, 1, 0, 2, 2, 0, 2, 2, 0, 2, 2},
        {1, 0, 2, 1, 0, 2, 1, 0, 2, 2, 0, 2, 1, 0, 2, 1, 1, 2, 2, 0, 2, 2, 2, 1, 1, 0, 2, 1, 0, 0, 0, 0, 2, 1, 0, 2, 1, 0, 2, 1},
        {1, 0, 2, 1, 0, 2, 1, 0, 2, 2, 0, 2, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 2, 1, 0, 2, 2, 0, 2, 1, 0, 2, 1, 0, 2, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        {1, 0, 2, 2, 0, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 0, 2, 2, 0, 2, 1},
        {1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 0, 2, 1},
        {1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 2, 1},
        {1, 0, 2, 1, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 1, 0, 2, 1},
        {1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    int i, j;
    for (i=0; i <= MAP_TILE_HEIGHT; i++){
        for(j=0; j <= MAP_TILE_LENGTH; j ++){
            cell_map[i][j].x_position = X_PIXEL_OFFSET + (j << 4);
            cell_map[i][j].y_position = Y_PIXEL_OFFSET + (i << 4);
            if (tile_map[i][j] == 0) {
                cell_map[i][j].open_path = TRUE;
            } else {
                cell_map[i][j].open_path = FALSE;
            }
        }
    }
}
void set_ghost_path(Ghost *ghost, UINT16* path_array[][MAP_TILE_LENGTH], Cell cell_map[][MAP_TILE_LENGTH]) {
    int i, j;
    for (i = 0; i < MAP_TILE_HEIGHT; i++) {
        for (j = 0; j < MAP_TILE_LENGTH; j++) {
            ghost->path[i][j].x_position = cell_map[i][j].x_position;
            ghost->path[i][j].y_position = cell_map[i][j].y_position;
            if (path_array[i][j] == 0) {
                ghost->path[i][j].open_path = TRUE;
            } else {
                ghost->path[i][j].open_path = FALSE;
            }

        }

    }
}
void init_ghost_paths(Ghost *ghost1, Ghost *ghost2, Ghost *ghost3, Ghost *ghost4, Cell cell_map[][MAP_TILE_LENGTH]) {
    UINT16 crying_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    UINT16 awkward_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    UINT16 moustache_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    UINT16 cyclops_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    set_ghost_path(ghost1, &crying_ghost_path, cell_map);
    set_ghost_path(ghost2, &moustache_ghost_path, cell_map);
    set_ghost_path(ghost3, &cyclops_ghost_path, cell_map);
    set_ghost_path(ghost4, &awkward_ghost_path, cell_map);
}
