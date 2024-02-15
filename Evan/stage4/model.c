#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include "map_plot.c"
#include "events.h"

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
    PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE,       /*Initial state*/
    FALSE,
    21,19          /*Cell index -> y, x*/
};

Ghost crying_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
    0,0,
    0,
    UP,
    FALSE,
    FALSE,
    10, 17
               /*Or whatever cell it starts in*/
 
};
Ghost moustache_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE,
    FALSE,
    10, 21
};
Ghost cyclops_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE,
    FALSE,
    12, 17
};
Ghost awkward_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE,
    FALSE,
    12, 21
};

Timer timer = {
    0,0,
    20, 28, 44, 52
};

void move_pacman_position (Pacman *pacman, UINT16 delta_x, UINT16 delta_y) 
{
    /*Amtoj*/
}


void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{
	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;		
}

void move_ghost_position (Ghost *ghost, int new_x, int new_y)
{
    /*Amtoj is doing this, if you are evan you should NOT even be READING this, GO AWAY!*/
}
UINT8 check_collision(Ghost *ghost, Pacman *pacman, UINT16 object_y_position, UINT16 object_x_position)
{  
    UINT8 collision = 0;
    
    if (cell_map[object_y_position][object_x_position].open_path == FALSE) 
        collision = WALL;                       /*defined in types.h*/

    else if (ghost -> x == pacman -> x && ghost -> y == pacman->y)
        collision = OBJECT;

    return collision;

}
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH]){

    int i, j;
    for (i=0; i <= MAP_TILE_HEIGHT; i++){
        for(j=0; j <= MAP_TILE_LENGTH; j ++){
            cell_map[i][j].x_position = X_PIXEL_OFFSET + (j << 4); /*MULTIPLYING!!! by 16:))))*/
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

    /*

    probably wont use this, might use djsktras from running
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
    */
}
void update_cells(int* x_index, int* y_index) { 
    /*Evans Doing this
    update sprite cell indeces, mod 16 or something idfk
    */
   if (*x_index % PIXELS_PER_CELL == 0) {
       *x_index = (*x_index)++;
   }

   if (*y_index % PIXELS_PER_CELL == 0) {
       *y_index = (*y_index)++;
   }
   
}
void kill_ghost(Ghost* ghost) {
   ghost->is_dead = TRUE;
}
void init_tombstone(Ghost* ghost, Tombstone* tombstone_object) {
    tombstone_object->x = ghost->x;
    tombstone_object->x = ghost->y;
}

