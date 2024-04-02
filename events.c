
#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"
#include "psg.h"
#include "renderer.h"
#include "globals.h"
#include <stdio.h>

const UCHAR8 DIRECTION_ARRAY[4] = {UP, DOWN, LEFT, RIGHT};

/*******************************************************************
 * Function: process_ghost_collision
 * Purpose: To handle collisions between ghost and wall and eachother
 *******************************************************************/
ObjectType process_ghost_collision(Entities* all) {  
    
    ObjectType collision = OPEN_PATH;
    int i, n;

    Ghost* ghost_array[4];

    Movement *all_ghosts[4];
    all_ghosts[0] = all->crying_ghost->move;
    all_ghosts[1] = all->awkward_ghost->move;
    all_ghosts[2] = all->cyclops_ghost->move;
    all_ghosts[3] = all->moustache_ghost->move;

    ghost_array[0] = all->crying_ghost;
    ghost_array[1] = all->awkward_ghost;
    ghost_array[2] = all->cyclops_ghost;
    ghost_array[3] = all->moustache_ghost;
}
void handle_wall_collision(Movement* ghost, UCHAR8 state, UCHAR8 path_number) {
    
    int i, direction;
    UCHAR8 possible_direction = 0;
    UCHAR8 path_direction;
    switch (path_number) {
        case CRYING_PATH:    path_direction = cell_map[ghost->y_cell_index][ghost->x_cell_index].crying_path;    break;
        case AWKWARD_PATH:   path_direction = cell_map[ghost->y_cell_index][ghost->x_cell_index].awkward_path;   break;
        case CYCLOPS_PATH:   path_direction = cell_map[ghost->y_cell_index][ghost->x_cell_index].cyclops_path;   break;
        case MOUSTACHE_PATH: path_direction = cell_map[ghost->y_cell_index][ghost->x_cell_index].moustache_path; break;
    }
    direction = ghost->direction;
    switch(path_direction)
	{
        case UP:    set_deltas(ghost, 0, -1); break;        
        case DOWN:  set_deltas(ghost, 0, 1); break;        
        case RIGHT: set_deltas(ghost, 1, 0); break;        
        case LEFT:  set_deltas(ghost, -1, 0); break;
    }       
}
/*************************************************************
 * Function: handle_pacman_collision
 * Module: events
 * Purpose: Handles collisions between pacman and other entities
 * Parameters: ObjectType object_type - The type of object
 *              Entities* entity - Pointer to the entity
 * Details: 
 * the OPEN_PATH case will lock pacmans x / y movement to valid positions
****************************************************************/
void handle_pacman_collision(ObjectType object_type, Entities* entity) {

    Movement* pacman = entity->pacman->move;
    
    switch(object_type)
    {
    case WALL: set_deltas(pacman, 0, 0); break;
    case GHOST:
        switch (object_type)
        {
        case GHOST_TYPE_CRYING:    kill_ghost(entity->crying_ghost, cell_map);    break;
        case GHOST_TYPE_AWKWARD:   kill_ghost(entity->awkward_ghost, cell_map);   break;
        case GHOST_TYPE_MOUSTACHE: kill_ghost(entity->moustache_ghost, cell_map); break; 
        case GHOST_TYPE_CYCLOPS:   kill_ghost(entity->cyclops_ghost, cell_map);   break;
        }
        pacman->y -= pacman->delta_y;
        pacman->x -= pacman->delta_x;
        break;
    break;
    }
}
/************************************************************
 * Function: handle_collisions
 * Purpose: Master call for checking and handling collisions
 **********************************************************/
void handle_collisions(Entities* entity) {
    int i;
    ObjectType collision_type = OPEN_PATH;
    Movement* pacman = entity->pacman->move;

    collision_type = check_wall_collision(pacman);
    handle_pacman_collision(collision_type, entity); 

    if (check_shared_occupied(pacman, entity->awkward_ghost->move) == TRUE)
        kill_ghost(entity->awkward_ghost, cell_map);

    if (check_shared_occupied(pacman, entity->moustache_ghost->move) == TRUE)
        kill_ghost(entity->moustache_ghost, cell_map);

    if (check_shared_occupied(pacman, entity->cyclops_ghost->move) == TRUE)
        kill_ghost(entity->cyclops_ghost, cell_map);

    if (check_shared_occupied(pacman, entity->crying_ghost->move) == TRUE)
        kill_ghost(entity->crying_ghost, cell_map);

}
void set_input(Pacman *pacman, char input)
{
    Movement* movement = pacman->move;
    set_deltas(movement, 0, 0);    
	switch(input)
	{
		case W_MAKE: 
            set_deltas(movement, 0, -1); 
            movement->direction = UP;     
            break;	

		case A_MAKE: 
            set_deltas(movement, -1, 0);
            movement -> direction = LEFT;
			break;
				
		case S_MAKE: 
            set_deltas(movement, 0, 1);
            movement -> direction = DOWN;
			break;

		case D_MAKE: 
            set_deltas(movement, 1, 0);
            movement -> direction = RIGHT;
			break;

		default:
            set_deltas(movement, 0, 0);	
			break;
	}
    

}
/*******************************************
 * Function: get_valid_paths
 * Purpose: Returns the number of valid paths a ghost can take in a cell
 * Parameters: Movement* ghost
*/
UCHAR8 get_valid_paths(Movement *ghost)
{
    UCHAR8 count = 0;
    if (cell_map[ghost->y_cell_index - 1][ghost->x_cell_index].open_path == TRUE) { count++; }
    if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == TRUE) { count++; }
    if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == TRUE) { count++; }
    if (cell_map[ghost->y_cell_index][ghost->x_cell_index + 1].open_path == TRUE) { count++; }
    return count;
}
/*********************************************************************************
*   This function handles collisions between a ghost and a wall in the game environment.
*   If a collision with a wall occurs, the function determines possible directions the ghost
*   can move to and selects one of them randomly. It uses an XOR algorithm to generate a random 
*   number, which is then modded by the available directions to choose a random direction.
*   
*   Parameters:
*      - collision_type: An integer representing the type of collision (e.g., WALL).
*      - ghost: A pointer to the Ghost structure representing the ghost involved in the collision.
*      - cell_map: A 2D array representing the game map.
*      - xor_shift_struct: A pointer to the XOR shift structure used for random number generation.
*
*   Note: This function is currently not functional due to a bug with random number generation
*         and a logic error.
 *************************************************************************************/
void handle_ghost_collision(Movement* ghost1, Movement* ghost2) {
    
    flip_direction(ghost1);
    flip_direction(ghost2);   
}
void eat_pellet(Movement* pacman) {
    cell_map[pacman->y_cell_index][pacman->x_cell_index].has_pellet = FALSE;
}
