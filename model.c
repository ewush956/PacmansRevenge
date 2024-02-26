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

void move_pacman (Pacman *pacman)
{
    if (pacman -> state == DEFAULT) {
    pacman->move->x += (pacman->move->delta_x) * 2;
    pacman->move->y += (pacman->move->delta_y) * 2;
    }
    else {
        pacman->move->x += pacman->move->delta_x * 4;
        pacman->move->y += pacman->move->delta_y * 4;
    }
   /* update_cell(&pacman->x_cell_index, &pacman->y_cell_index, pacman->x, pacman->y, pacman->move->direction); */
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
    
	UCHAR8 direction = ghost->move->direction;

	/*ghost -> delta_x = 0;
	ghost -> delta_y = 0;
    */
	
	if (ghost -> move ->x > SCREEN_WIDTH - MAP_PIXEL_LENGTH && ghost -> move-> x < MAP_PIXEL_LENGTH
		&& ghost -> move -> y + Y_PIXEL_OFFSET > SCREEN_HEIGHT - MAP_PIXEL_HEIGHT && ghost -> move-> y < MAP_PIXEL_HEIGHT) 
	
	{
		switch(direction)
		{
			case UP:
				ghost->move->delta_y = -1;
				ghost->move->delta_x = 0;
				break;
			
			case DOWN:
				ghost -> move-> delta_y = 1;
				ghost -> move-> delta_x = 0;
				break;
			
			case RIGHT:
				ghost -> move ->delta_x = 1;
				ghost -> move ->delta_y = 0;
				break;
			
			case LEFT:
				ghost -> move ->delta_x = -1;
				ghost -> move ->delta_y = 0;
				break;
		}
        if (ghost->move->direction == UP || ghost->move->direction == DOWN) 
            ghost->move->x = ghost->move->x_cell_index * PIXELS_PER_CELL;
        
        else if (ghost->move->direction == LEFT|| ghost->move->direction == RIGHT) 
        {
            ghost->move->y = ghost->move->y_cell_index * PIXELS_PER_CELL + PIXELS_PER_CELL;
        }

        ghost->move-> x += ghost->move->delta_x;
        ghost->move-> y += ghost->move->delta_y;
    }

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
ObjectType check_collision(Entities* all, UINT16 object_y_index, UINT16 object_x_index, int y_delta, int x_delta,
                           ObjectType curr_type)
{  
    
    ObjectType collision = OPEN_PATH;
    int i;


    Ghost *all_ghosts[4];
    all_ghosts[0] = all->crying_ghost;
    all_ghosts[1] = all->awkward_ghost;
    all_ghosts[2] = all->cyclops_ghost;
    all_ghosts[3] = all->moustache_ghost;

    for (i = 0; i < 4; i++){
        /*printf("OBJECTS occupy these locations (%u,%u)",all_ghosts[i]->y_cell_index,all_ghosts[i]->x_cell_index);*/
        
        if (all_ghosts[i]->type != curr_type) /* no collsiion with ghost itself only other objs*/
        {
            if ((all_ghosts[i]->move->x_cell_index == object_x_index + x_delta &&
                all_ghosts[i]->move->y_cell_index == object_y_index + y_delta) ||
                (all_ghosts[i]->move->x_cell_index == object_x_index && 
                all_ghosts[i]->move->y_cell_index == object_y_index))
                /* collision = OBJECT; */
                collision = all_ghosts[i]->type;
        }
    }
    return collision;
}    
/*************************************************************
 * Function: check_pacman_collision
 * Purpose: Checks for collisions between an object and walls.
 * Parameters: Entities* entity - Pointer to the entities structure containing
 *              ghosts, UINT16 object_y_index - Y index of the object,
 *              UINT16 object_x_index - X index of the object,
 *              UINT16 y_delta - Y direction movement delta,
 *              UINT16 x_delta - X direction movement delta.
 * Details: Determines if the specified object's next position (based on deltas)
 *          will result in a collision with a wall.
 *          It returns WALL if a wall collision is detected, and 0 if no collision
 *          is detected.
 *************************************************************/
ObjectType check_wall_collision(Movement* entity) {

    UINT16 effective_y_position;
    UINT16 effective_x_position;
    UINT16 COLLISION_THRESHOLD = 4;
    UINT16 object_y_index = entity->y_cell_index;
    UINT16 object_x_index = entity->x_cell_index;
    int y_delta = entity->delta_y;
    int x_delta = entity->delta_x;


    if (cell_map[object_y_index + y_delta][object_x_index + x_delta].open_path == FALSE) {
        if ((entity->direction == UP || entity->direction == DOWN)) {
            effective_y_position = entity->y - COLLISION_THRESHOLD;
            if (effective_y_position <= (UINT16)cell_map[object_y_index][object_x_index].y_position)
                return WALL;
        }
        if ((entity->direction == LEFT || entity->direction == RIGHT)) {
            effective_x_position = entity->x - COLLISION_THRESHOLD;
            if (effective_x_position <= (UINT16)cell_map[object_y_index][object_x_index].x_position)
                return WALL;  
        }
    }
    return OPEN_PATH;
}
void check_proximity(Entities* all) {
    int ghostCountWithinRange = 0;
    int i;
    UINT16 pacman_x_index, pacman_y_index;
    UINT16 ghost_x_index, ghost_y_index;
    UINT16 x_distance, y_distance;

    Ghost *ghosts[4];
    ghosts[0] = all->crying_ghost;
    ghosts[1] = all->awkward_ghost;
    ghosts[2] = all->cyclops_ghost;
    ghosts[3] = all->moustache_ghost;

    pacman_x_index = all->pacman->move->x_cell_index;
    pacman_y_index = all->pacman->move->y_cell_index;

    for (i = 0; i < 4; i++) {
        ghost_x_index = ghosts[i]->move->x_cell_index;
        ghost_y_index = ghosts[i]->move->y_cell_index;

        if (pacman_x_index > ghost_x_index) {
            x_distance = pacman_x_index - ghost_x_index;
        } else {
            x_distance = ghost_x_index - pacman_x_index;
        }

        if (pacman_y_index > ghost_y_index) {
            y_distance = pacman_y_index - ghost_y_index;
        } else {
            y_distance = ghost_y_index - pacman_y_index;
        }

        if (x_distance <= 4 && y_distance <= 4) {
            ghostCountWithinRange++;
            change_pacman_state(all->pacman, EVIL); 
            change_ghost_state(ghosts[i], RUNNING); 
        }
        else {
            change_ghost_state(ghosts[i], DEFAULT);
        }
    }
    if (ghostCountWithinRange == 0) {
        change_pacman_state(all->pacman, DEFAULT);
    }
    else if (ghostCountWithinRange >= 2) {
        end_game();
    }
}

void change_pacman_state(Pacman* pacman, UCHAR8 new_state) {
    pacman->state = new_state;
}
void change_ghost_state(Ghost* ghost, UCHAR8 new_state) {
    ghost->state = new_state;
}
void end_game() {
    
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
            cell_map[i][j].x_position = (j << 4);  /* MULTIPLYING by 16 */
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
void update_cells(Entities* all) {
    
    
    Pacman* pacman = all->pacman;
    Ghost* crying = all->crying_ghost;
    Ghost* moustache = all->moustache_ghost;
    Ghost* cyclops = all->cyclops_ghost;
    Ghost* awkward = all->awkward_ghost;
    

    update_cell(pacman->move, DEFAULT);
    /*Pacmans state doesn't matter here, probably faster to pass in const value*/

    update_cell(crying->move, crying->state);

    update_cell(moustache->move, moustache->state);

    update_cell(cyclops->move, cyclops->state);

    update_cell(awkward->move, awkward->state);
}
void update_cell(Movement* entity, UCHAR8 state) {

    int x_index = entity->x_cell_index;
    int y_index = entity->y_cell_index;

    set_occupied(FALSE, y_index, x_index);
    if (state == DEAD) {
        return;
    }
    entity->x_cell_index = entity->x >> 4; 
    entity->y_cell_index = (entity->y >> 4) - 1;
    set_occupied(TRUE, y_index, x_index);
}
void set_occupied(bool set, int y_index, int x_index) {
    cell_map[y_index][x_index].occupied = set;
    cell_map[y_index + 1][x_index].occupied = set;
    cell_map[y_index][x_index + 1].occupied = set;
    cell_map[y_index + 1][x_index + 1].occupied = set;
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
   add_wall_to_map(cell_map, ghost->move->y, ghost->move->x);
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
void align_axis(Movement* entity) {
        if (entity->direction == UP || entity->direction == DOWN) {
            entity->x = entity->x_cell_index * PIXELS_PER_CELL;
        }
        else if (entity->direction == LEFT || entity->direction == RIGHT) {
            entity->y = entity->y_cell_index  * PIXELS_PER_CELL + PIXELS_PER_CELL;
        }
}

