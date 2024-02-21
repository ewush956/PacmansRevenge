#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include "events.h"

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
    DEFAULT,
    10, 17
               /*Or whatever cell it starts in*/
 
};
Ghost moustache_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    DEFAULT,
    10, 21
};
Ghost cyclops_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    DEFAULT,
    12, 17
};
Ghost awkward_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    DEFAULT,
    12, 21
};

Timer timer = {
    0,0,
    20, 28, 44, 52
};

void move_pacman (Pacman *pacman)
{
    pacman -> x += pacman->delta_x;
    pacman -> y += pacman->delta_y;
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
UINT8 check_collision(Entities* entity, UINT16 object_y_position, UINT16 object_x_position)
{  
    UINT8 collision = 0;
    /*
    Entities *pac = entity->pacman;
    Entities *crying = entity.crying_ghost; 
    */

    if (cell_map[object_y_position][object_x_position].open_path == FALSE) 
        collision = WALL;                       /*defined in types.h*/

    else if (entity->crying_ghost->x == entity->pacman->x && entity->crying_ghost->y == entity->pacman->y)
        collision = OBJECT;
    
    else if (entity->moustache_ghost->x == entity->pacman->x && entity->moustache_ghost->y == entity->pacman->y)
        collision = OBJECT;
    
    else if (entity->awkward_ghost->x == entity->pacman->x && entity->awkward_ghost->y == entity->pacman->y)
        collision = OBJECT;

    else if (entity->cyclops_ghost->x == entity->pacman->x && entity->cyclops_ghost->y == entity->pacman->y)
        collision = OBJECT;


    return collision;

}
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH], UINT16 tile_map[][MAP_TILE_LENGTH]){

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
void kill_ghost(Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]) {
   ghost->state = DEAD;
   add_wall_to_map(cell_map, ghost->y, ghost->x);
}
void add_wall_to_map(Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH], int y_cell_index, int x_cell_index) {
   cell_map[y_cell_index][x_cell_index].open_path = FALSE;
}
