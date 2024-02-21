#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include <stdio.h>

/*************************************************************
* Declaration: Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH]
* Purpose: Represents the game's map, storing the state of each
*          cell (e.g., open path and relative pixle position).
*************************************************************/
Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

/*************************************************************
* Declaration: Pacman pacman
* Purpose: Initializes the player character, Pacman, with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Pacman pacman = {
    PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 19 + Y_PIXEL_OFFSET-1,  
    0,-1,           /*Initial Displacement*/
    0,             /*Initial state index*/
    UP,            /*Initial direction*/
    DEFAULT,       /*Initial state*/
    19,19          /*Cell index -> y, x*/
};
/*************************************************************
* Declaration: Ghost crying_ghost
* Purpose: Initializes the 'crying' ghost entity with its starting
*          position, movement displacement, state, direction, 
*          and cell index on the game map.
*************************************************************/
Ghost crying_ghost = {
    PIXELS_PER_CELL * 17 + 1, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,     
    1,0,
    0,
    STOP,
    DEFAULT,
    (UINT16)10, (UINT16)17 
};
/*************************************************************
* Declaration: Ghost cyclops_ghost
* Purpose: Initializes the 'cyclops' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost cyclops_ghost = {
    PIXELS_PER_CELL * 17 + 1, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    STOP,
    DEFAULT,
    12, 17
};
/*************************************************************
* Declaration: Ghost moustache_ghost
* Purpose: Initializes the 'moustache' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost moustache_ghost = {
    PIXELS_PER_CELL * 21 - 1, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    0,0,
    0,
    STOP,
    DEFAULT,
    (UINT16)10, (UINT16)21
};
/*************************************************************
* Declaration: Ghost awkward_ghost
* Purpose: Initializes the 'awkward' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Ghost awkward_ghost = {
    PIXELS_PER_CELL * 21 - 1, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    STOP,
    DEFAULT,
    12, 21
};
/*************************************************************
* Declaration: Timer timer
* Purpose: Initializes the game timer with starting values
*          and thresholds for various game events.
*************************************************************/
Timer timer = {
    0,0,
    20, 28, 44, 52
};
/*************************************************************
* Function: move_pacman
* Purpose: Updates Pacman's position based on its current velocity.
* Parameters: Pacman* pacman - Pointer to the Pacman structure.
* Details: Adjusts Pacman's x and y coordinates by adding the current
*          delta_x and delta_y values, effectively moving Pacman in the
*          direction and speed specified by these delta values.
*************************************************************/
void move_pacman (Pacman *pacman)
{
    pacman -> x += pacman->delta_x;
    pacman -> y += pacman->delta_y;
   /* update_cell(&pacman->x_cell_index, &pacman->y_cell_index, pacman->x, pacman->y, pacman->direction); */
}
/*************************************************************
* Function: move_ghost
* Purpose: Updates a ghost's position based on its current velocity.
* Parameters: Ghost* ghost - Pointer to the Ghost structure.
* Details: Modifies the ghost's x and y coordinates by adding the current
*          delta_x and delta_y values. This change moves the ghost according to
*          its velocity, facilitating motion in the game world.
*************************************************************/
void move_ghost (Ghost *ghost)
{
    ghost -> x += ghost -> delta_x;
    ghost -> y += ghost -> delta_y;
   /* update_cell(&ghost->x_cell_index, &ghost->y_cell_index, ghost->x, ghost->y, ghost->direction); */
}
/*************************************************************
* Function: check_collision
* Purpose: Checks for collisions between an object and ghosts or walls.
* Parameters: Entities* entity - Pointer to the entities structure containing ghosts,
*             UINT16 object_y_index - Y index of the object,
*             UINT16 object_x_index - X index of the object,
*             UINT16 y_delta - Y direction movement delta,
*             UINT16 x_delta - X direction movement delta.
* Details: Determines if the specified object's next position (based on deltas)
*          will result in a collision with either any of the ghosts or a wall.
*          It returns WALL if a wall collision is detected, OBJECT if a collision
*          with any ghost is detected, and 0 if no collision is detected. The function
*          also logs the collision location for ghost collisions.
*************************************************************/
UINT8 check_collision(Entities* entity, UINT16 object_y_index, UINT16 object_x_index,UINT16 y_delta, UINT16 x_delta)
{  
    UINT8 collision = 0;
    int i;

    Ghost *all_ghosts[4];
    all_ghosts[0] = entity->crying_ghost;
    all_ghosts[1] = entity->awkward_ghost;
    all_ghosts[2] = entity->cyclops_ghost;
    all_ghosts[3] = entity->moustache_ghost;

    if (cell_map[object_y_index + y_delta][object_x_index + x_delta].open_path ==FALSE)
        collision = WALL;

    else{
        for (i = 0; i < 4; i++){
            if (all_ghosts[i]->x_cell_index == object_x_index + x_delta &&
                all_ghosts[i]->y_cell_index == object_y_index + y_delta )
            {
                collision = OBJECT;
                /*This is only for testing, will be removed in final version*/
                printf("COLLISION AT LOCATION (y,x) ->(%u,%u)",all_ghosts[i]->y_cell_index,all_ghosts[i]->x_cell_index);
                break;
            }
        }
    }  
    return collision;
}
/*************************************************************
* Function: init_map_cells
* Purpose: Initializes the cell map with positions and path openness based on the tile map.
* Parameters: Cell cell_map[][MAP_TILE_LENGTH] - 2D array to store cell positions and status,
*             UINT16 tile_map[][MAP_TILE_LENGTH] - 2D array representing the layout of the map.
* Details: Iterates through each cell in the cell_map, setting its x and y positions based on
*          predefined offsets and its index. The open_path flag for each cell is set based on
*          the corresponding tile_map value, indicating whether the path is open (TRUE) or blocked (FALSE).
*************************************************************/
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH], UINT16 tile_map[][MAP_TILE_LENGTH]){
    int i, j;
    for (i=0; i < MAP_TILE_HEIGHT; i++){
        for(j=0; j < MAP_TILE_LENGTH; j ++){
            cell_map[i][j].x_position = X_PIXEL_OFFSET + (j << 4);  /* MULTIPLYING by 16 */
            cell_map[i][j].y_position = Y_PIXEL_OFFSET + (i << 4);
            if (tile_map[i][j] == 0) {
                cell_map[i][j].open_path = TRUE;
            } else {
                cell_map[i][j].open_path = FALSE;
            }
        }
    }
}
/*************************************************************
* Function: update_cells
* Purpose: Updates the cell indices for movement calculations.
* Parameters: int* x_index - Pointer to the x index of a cell,
*             int* y_index - Pointer to the y index of a cell.
* Details: Increments the x and y cell indices if they are perfectly divisible by
*          PIXELS_PER_CELL, indicating a complete move into a new cell. This function
*          aids in tracking movement across cells in the game grid.
*************************************************************/
void update_cells(Entities* entity) {
    Pacman* pacman = entity->pacman;
    Ghost* crying = entity->crying_ghost;
    Ghost* moustache = entity->moustache_ghost;
    Ghost* cyclops = entity->cyclops_ghost;
    Ghost* awkward = entity->awkward_ghost;

    update_cell(&pacman->x_cell_index, &pacman->y_cell_index, pacman->x, pacman->y, pacman->direction, DEFAULT);
    /*Pacmans state doesn't matter here, probably faster to pass in const value*/

    update_cell(&crying->x_cell_index, &crying->y_cell_index, crying->x, crying->y, crying->direction, crying->state);
    update_cell(&moustache->x_cell_index, &moustache->y_cell_index, moustache->x, moustache->y, moustache->direction, moustache->state);
    update_cell(&cyclops->x_cell_index, &cyclops->y_cell_index, cyclops->x, cyclops->y, cyclops->direction, cyclops->state);
    update_cell(&awkward->x_cell_index, &awkward->y_cell_index, awkward->x, awkward->y, awkward->direction, awkward->state);
}
void update_cell(UINT16* x_index, UINT16* y_index, UINT16 x_position, UINT16 y_position, UINT8 direction, UINT8 state) {

    if (state == DEAD || direction == STOP) {
        return;
    }
    if (x_position % PIXELS_PER_CELL == 0) {

        if (direction == LEFT) {
            (*x_index) = (*x_index)-1;
        } 
        else if (direction == RIGHT) {
            (*x_index) = (*x_index)+1;
        }

    }
    else if (y_position % PIXELS_PER_CELL == 0) {
        if (direction == UP) {
            (*y_index) = (*y_index)-1;
        } 
        else if (direction == DOWN) {
            (*y_index) = (*y_index)+1;
        }
    }
}
/*************************************************************
* Function: kill_ghost
* Purpose: Marks a ghost as dead and updates the map accordingly.
* Parameters: Ghost* ghost - Pointer to the ghost to be marked dead,
*             Cell cell_map[][MAP_TILE_LENGTH] - The game's cell map.
* Details: This function changes the specified ghost's state to DEAD
*          and adds a wall (tombstone) to the map at the ghost's last position,
*          effectively removing the ghost from play and altering the map.
*************************************************************/
void kill_ghost(Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]) {
   ghost->state = DEAD;
   add_wall_to_map(cell_map, ghost->y, ghost->x);
}
/*************************************************************
* Function: add_wall_to_map
* Purpose: Marks a specified cell in the map as a wall.
* Parameters: Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] - The game map's cell matrix,
*             int y_cell_index - The Y index of the cell to mark as a wall,
*             int x_cell_index - The X index of the cell to mark as a wall.
* Details: This function updates the cell at the specified indices
*          in the game map to indicate it is not an open path, effectively
*          making it a wall. This is used to dynamically alter the map's layout.
*************************************************************/
void add_wall_to_map(Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH], int y_cell_index, int x_cell_index) {
   cell_map[y_cell_index][x_cell_index].open_path = FALSE;
}

