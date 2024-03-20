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
   Movement* pacman_movement = pacman->move;

    if (pacman_movement->delta_x == 0 && pacman_movement->delta_y == 0) {
        pacman_movement->last_last_x = pacman_movement->x;
        pacman_movement->last_last_y = pacman_movement->y;
        return;
    }
    
    pacman_movement->last_last_x = pacman_movement->last_x;
    pacman_movement->last_last_y = pacman_movement->last_y;

    pacman_movement->last_x = pacman_movement->x;
    pacman_movement->last_y = pacman_movement->y;

    pacman_movement->x += (pacman_movement->delta_x << 1);
    pacman_movement->y += (pacman_movement->delta_y << 1);
    align_axis(pacman_movement);

    /*
    if (pacman -> state == DEFAULT) {
    pacman_movement->x += (pacman_movement->delta_x << 1);
    pacman_movement->y += (pacman_movement->delta_y << 1);
    }
    else {
        pacman_movement->x += (pacman_movement->delta_x << 2);
        pacman_movement->y += (pacman_movement->delta_y << 2);
    }
    */
}
/*************************************************************
* Function: move_ghost
* Module: model
* Purpose: Updates a ghost's position based on its current velocity.
* Parameters: Ghost* ghost - Pointer to the Ghost structure.
* Details: Modifies the ghost's x and y coordinates by adding the current
*          delta_x and delta_y values. This change moves the ghost according to
*          its velocity, facilitating motion in the game world.
*************************************************************/
void move_ghost (Ghost *ghost)
{
    Movement* ghost_movement = ghost->move;
	UCHAR8 direction = ghost->move->direction;

	/*ghost -> delta_x = 0;
	ghost -> delta_y = 0;
    */
	/*
	if (ghost -> move ->x > SCREEN_WIDTH - MAP_PIXEL_LENGTH && ghost -> move-> x < MAP_PIXEL_LENGTH
		&& ghost -> move -> y + Y_PIXEL_OFFSET > SCREEN_HEIGHT - MAP_PIXEL_HEIGHT && ghost -> move-> y < MAP_PIXEL_HEIGHT) 
	{
	*/
    if (ghost->state == DEAD)
    {
        return;
    }
    if (ghost->state == RUNNING) {
        if (ghost_movement->delta_x == 0 && ghost_movement->delta_y == 0) {
                    
            ghost_movement->last_last_x = ghost_movement->last_x;
            ghost_movement->last_last_y = ghost_movement->last_y;

            ghost_movement->last_x = ghost_movement->x;
            ghost_movement->last_y = ghost_movement->y;
            align_axis(ghost_movement);
            return;
        }
    }
		switch(direction)
		{
			case UP:
				ghost_movement->delta_y = -1;
				ghost_movement->delta_x = 0;
				break;
			
			case DOWN:
				ghost_movement->delta_y = 1;
				ghost_movement->delta_x = 0;
				break;
			
			case RIGHT:
				ghost_movement->delta_x = 1;
				ghost_movement->delta_y = 0;
				break;
			
			case LEFT:
				ghost_movement->delta_x = -1;
				ghost_movement->delta_y = 0;
				break;
		}
        
        ghost_movement->last_last_x = ghost_movement->last_x;
        ghost_movement->last_last_y = ghost_movement->last_y;
        
        ghost_movement->last_x = ghost_movement->x;
        ghost_movement->last_y = ghost_movement->y;

        ghost_movement-> x += ghost_movement->delta_x;
        ghost_movement-> y += ghost_movement->delta_y;
        align_axis(ghost_movement);
    

}
/*************************************************************
* Function: check_collision
* Module: model
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
        
        if (all_ghosts[i]->type != curr_type) 
        {
            if ((all_ghosts[i]->move->x_cell_index == object_x_index + x_delta &&
                all_ghosts[i]->move->y_cell_index == object_y_index + y_delta) ||
                (all_ghosts[i]->move->x_cell_index == object_x_index && 
                all_ghosts[i]->move->y_cell_index == object_y_index))
                collision = all_ghosts[i]->type;
        }
    }
    return collision;
    
}    
/*************************************************************
 * Function: check_pacman_collision
 * Module: model
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
/***************************************************
 * Function: check_proximity
 * Module: model
 * Purpose: Checks if pacman and ghost are close, if they are it changes states
 * Parameters: Entities* all - Pointer to the entities structure containing
*******************************************************/
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
        if (ghosts[i]->state == DEAD) {
            continue;
        }
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

        if (x_distance <= 5 && y_distance <= 5) {
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
    printf("GAME OVER\n");
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
                cell_map[i][j].has_pellet = TRUE;
            } else {
                cell_map[i][j].open_path = FALSE;
                cell_map[i][j].has_pellet = FALSE;
            }
            if (tile_map[i+1][j] == 0 && i < MAP_PIXEL_HEIGHT - 1) {
                cell_map[i][j].can_go_down = TRUE;
            } else {
                cell_map[i][j].can_go_down = FALSE;
            }

            if (tile_map[i][j+1] == 0 && j < MAP_PIXEL_LENGTH - 1) {
                cell_map[i][j].can_go_right = TRUE;
            } else {
                cell_map[i][j].can_go_right = FALSE;
            }

            if (tile_map[i-1][j] == 0 && i > 0) {
                cell_map[i][j].can_go_up = TRUE;
            } else {
                cell_map[i][j].can_go_up = FALSE;
            }

            if (tile_map[i][j-1] == 0 && j > 0) {
                cell_map[i][j].can_go_left = TRUE;
            } else {
                cell_map[i][j].can_go_left = FALSE;
            }
            switch (direction_map[i][j]) {
                case '^':
                    cell_map[i][j].path = UP;
                    break;
                case 'v':
                    cell_map[i][j].path = DOWN;
                    break;
                case '<':
                    cell_map[i][j].path = LEFT;
                    break;
                case '>':
                    cell_map[i][j].path = RIGHT;
                    break;
            }
        }
    }
    cell_map[10][17].has_pellet = FALSE;
    cell_map[10][18].has_pellet = FALSE;

    cell_map[10][20].has_pellet = FALSE;
    cell_map[10][21].has_pellet = FALSE;

    cell_map[12][17].has_pellet = FALSE;
    cell_map[12][18].has_pellet = FALSE;

    cell_map[12][20].has_pellet = FALSE;
    cell_map[12][21].has_pellet = FALSE;
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
    
    if (update_cell(awkward->move, awkward->state) == TRUE) {
        update_ghost_direction(awkward, pacman);
    }
    if (update_cell(moustache->move, moustache->state) == TRUE) {
        update_ghost_direction(moustache, pacman);
    }
    if (update_cell(crying->move, crying->state) == TRUE) {
        update_ghost_direction(crying, pacman);
    }
    if (update_cell(cyclops->move, cyclops->state) == TRUE) {
        update_ghost_direction(cyclops, pacman);
    }

    update_cell(pacman->move, DEFAULT);

}
/*Returns true if entity has entered a new cell*/
bool update_cell(Movement* entity, UCHAR8 state) {

    int x_index = entity->x_cell_index;
    int y_index = entity->y_cell_index;

    set_occupied(FALSE, y_index, x_index);
    if (state == DEAD) {
        return FALSE;
    }
    entity->x_cell_index = entity->x >> 4; 
    entity->y_cell_index = (entity->y >> 4) - 1;
    set_occupied(TRUE, y_index, x_index);

    if (entity->x_cell_index != x_index || entity->y_cell_index != y_index) {
        return TRUE;
    }
    return FALSE;
}
void update_ghost_direction(Ghost* ghost, Pacman* pacman) 
{
    Movement* ghost_movement = ghost->move;
    Movement* pacman_movement = pacman->move;
    if (ghost->state == DEAD) {
        return;
    }
    if (ghost->state == RUNNING) {
        if (check_valid_path(ghost_movement) == TRUE) {
            ghost_movement->direction = pacman_movement->direction;
        }
        return;
    }
    ghost_movement->direction = cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].path;
    /*
    switch (ghost_movement->direction) {
        case RIGHT:
            if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_right) {
                ghost_movement->direction = RIGHT;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_up) {
                ghost_movement->direction = UP;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_down) {
                ghost_movement->direction = DOWN;
            } else {
                ghost_movement->direction = LEFT;
            }
            break;
        case LEFT:
            if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_left) {
                ghost_movement->direction = LEFT;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_up) {
                ghost_movement->direction = UP;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_down) {
                ghost_movement->direction = DOWN;
            } else {
                ghost_movement->direction = RIGHT;
            }
            break;
        case UP:
            if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_up) {
                ghost_movement->direction = UP;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_right) {
                ghost_movement->direction = RIGHT;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_left) {
                ghost_movement->direction = LEFT;
            } else {
                ghost_movement->direction = DOWN;
            }
            break;
        case DOWN:
            if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_down) {
                ghost_movement->direction = DOWN;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_right) {
                ghost_movement->direction = RIGHT;
            } else if (cell_map[ghost_movement->y_cell_index][ghost_movement->x_cell_index].can_go_left) {
                ghost_movement->direction = LEFT;
            } else {
                ghost_movement->direction = UP;
            }
            break;
    }
    */

}
bool check_valid_path(Movement* movement) {
    switch (movement->direction) {
        case UP:
            return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_up;
        case DOWN:
            return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_down;
        case LEFT:
            return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_left;
        case RIGHT:
            return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_right;
    }
}
void set_occupied(bool set, int y_index, int x_index) {
    cell_map[y_index][x_index].occupied = set;
    cell_map[y_index + 1][x_index].occupied = set;
    cell_map[y_index][x_index + 1].occupied = set;
    cell_map[y_index + 1][x_index + 1].occupied = set;
}
/*Checks if two ghosts share an occupied region
A ghost occupies 4 cells*/
bool check_shared_occupied(Movement* entity1, Movement* entity2) {
    int i, j, k, l;
    int ghost1_y, ghost1_x, ghost2_y, ghost2_x;

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            ghost1_y = entity1->y_cell_index + i;
            ghost1_x = entity1->x_cell_index + j;
            for (k = 0; k < 2; ++k) {
                for (l = 0; l < 2; ++l) {
                    ghost2_y = entity2->y_cell_index + k;
                    ghost2_x = entity2->x_cell_index + l;
                    if (ghost1_y == ghost2_y && ghost1_x == ghost2_x && 
                        cell_map[ghost1_y][ghost1_x].occupied == TRUE) {
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
    
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
    int y_cell_index, x_cell_index;
    ghost->state = DEAD;
    /*
    ghost->move->x = ghost->move->x_cell_index * PIXELS_PER_CELL;
    ghost->move->y = ghost->move->y_cell_index * PIXELS_PER_CELL + Y_PIXEL_OFFSET;
    */
    ghost->move->x = (ghost->move->x_cell_index << 4);
    ghost->move->y = ((ghost->move->y_cell_index + 1) << 4);

    y_cell_index = ghost->move->y_cell_index;
    x_cell_index = ghost->move->x_cell_index;

    add_wall_to_map(cell_map, y_cell_index, x_cell_index);
    
   /* cell_map[y_cell_index][x_cell_index].open_path = FALSE;
    cell_map[y_cell_index+1][x_cell_index].open_path = FALSE;
    cell_map[y_cell_index][x_cell_index+1].open_path = FALSE;
    cell_map[y_cell_index+1][x_cell_index+1].open_path = FALSE;*/
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
    cell_map[y_cell_index][x_cell_index].has_pellet = FALSE;

    cell_map[y_cell_index+1][x_cell_index].open_path = FALSE;
    cell_map[y_cell_index+1][x_cell_index].has_pellet = FALSE;

    cell_map[y_cell_index][x_cell_index+1].open_path = FALSE;
    cell_map[y_cell_index][x_cell_index+1].has_pellet = FALSE;

    cell_map[y_cell_index+1][x_cell_index+1].open_path = FALSE;
    cell_map[y_cell_index+1][x_cell_index+1].has_pellet = FALSE;

    cell_map[y_cell_index-1][x_cell_index].occupied = FALSE;
    cell_map[y_cell_index-1][x_cell_index+1].occupied = FALSE;

    cell_map[y_cell_index][x_cell_index-1].open_path = FALSE;
    cell_map[y_cell_index][x_cell_index-1].has_pellet = FALSE;


}
void align_axis(Movement* entity) {

        if (entity->direction == UP || entity->direction == DOWN) { 
            entity->x = (entity->x_cell_index << 4);
        }
        else if (entity->direction == LEFT || entity->direction == RIGHT) {
            entity->y = (entity->y_cell_index + 1) << 4;
        }
}
void flip_direction(Movement* ghost) {
    if (ghost->delta_x == 0 && ghost->delta_y == 0) {
        return;
    }
    if (ghost->direction == UP)
        ghost->direction = DOWN;

    else if (ghost->direction == DOWN)
        ghost->direction = UP;

    else if (ghost->direction == LEFT)
        ghost->direction = RIGHT;

    else 
        ghost->direction = LEFT;
}
void update_current_frame(Entities* all, int clock) {
    Pacman* pacman = all->pacman;

    Ghost *ghosts[4];
    int i;
    ghosts[0] = all->crying_ghost;
    ghosts[1] = all->awkward_ghost;
    ghosts[2] = all->cyclops_ghost;
    ghosts[3] = all->moustache_ghost;

    if (pacman->state == DEFAULT) {

        pacman->current_frame = ((pacman->current_frame) + 1) & 7;
    }
    else {

        pacman->current_frame += 1;
        if (pacman->current_frame > 5) 
            pacman->current_frame -= 6;
        }
    
    for (i = 0; i < 4; i++) {

        if (ghosts[i]->state == DEFAULT && (clock & 3) == 0) {
            ghosts[i]->current_frame = (ghosts[i]->current_frame + 1) & 1;

        }

    }
}

/*
*
*   set position from 2 frames behind
*
*/
void set_prev(Entities* entity)
{
    Movement* pacman_movement = entity->pacman->move;
    Movement* awkward_move = entity->awkward_ghost->move;
    Movement* moustache_move = entity->moustache_ghost->move;
    Movement* crying_move = entity->crying_ghost->move;
    Movement* cyclops_move = entity->cyclops_ghost->move;

    pacman_movement->last_x = pacman_movement->x;
    pacman_movement->last_y = pacman_movement->y;
    
    moustache_move->last_x = moustache_move->x;
    moustache_move->last_y = moustache_move->y;

    crying_move->last_x = crying_move->x;
    crying_move->last_y = crying_move->y;
    
    awkward_move->last_x = awkward_move->x;
    awkward_move->last_y = awkward_move->y;
    
    cyclops_move->last_x = cyclops_move->x;
    cyclops_move->last_y = cyclops_move->y;
}
void set_prev_prev (Entities* entity) 
{/*
    Movement* pacman_movement = entity->pacman->move;
    Movement* moustache_move = entity->moustache_ghost->move;
    Movement* crying_move = entity->crying_ghost->move;
    Movement* awkward_move = entity->awkward_ghost->move;
    Movement* cyclops_move = entity->cyclops_ghost->move;

    pacman_movement->last_last_x = pacman_movement->last_x;
    pacman_movement->last_last_y = pacman_movement->last_y;

    moustache_move->last_last_x = moustache_move->last_x;
    moustache_move->last_last_y = moustache_move->last_y;

    crying_move->last_last_x = crying_move->last_x;
    crying_move->last_last_y = crying_move->last_y;

    awkward_move->last_last_x = awkward_move->last_x;
    awkward_move->last_last_y = awkward_move->last_y;

    cyclops_move->last_last_x = cyclops_move->last_x;
    cyclops_move->last_last_y = cyclops_move->last_y;
    */
}
