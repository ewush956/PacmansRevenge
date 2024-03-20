
#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"
#include <stdio.h>

const UCHAR8 DIRECTION_ARRAY[4] = {UP, DOWN, LEFT, RIGHT};

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
/*******************************************************************
 * Function: process_ghost_collision
 * Purpose: To handle collisions between ghost and wall and eachother
 *******************************************************************/
ObjectType process_ghost_collision(Entities* all, UINT16 tick)
{  
    
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

    for (i = 3; i > -1; i--){
        for (n = 1; n <= i; n++){
            if (check_shared_occupied(all_ghosts[i], all_ghosts[i-n]) == TRUE) {
                handle_ghost_collision(all_ghosts[i], all_ghosts[i-n]);
            }
        }
    }

    for (i = 0; i < 4; i++){
        if (check_wall_collision(all_ghosts[i]) != OPEN_PATH && ghost_array[i]->state != DEAD) {
            handle_wall_collision(all_ghosts[i], i);   
            /*update_ghost_direction(ghost_array[i], all->pacman);*/
            /*return WALL;*/
        }        
    }
    
    
    
}
void handle_wall_collision(Movement* ghost, int ghost_identifier) {
    
    int i, direction;
    UCHAR8 possible_direction = 0;
    UCHAR8 number_of_open_paths = get_valid_paths(ghost);

    direction = ghost->direction;
    /*for (i = 0; i < 4; i++) {
        /*
        direction++;
        if (direction > 3) 
            direction = (direction % 3) - 1;
        ghost -> direction = DIRECTION_ARRAY[direction];
        */
            /*
        switch(direction)
		{
			case UP:
				ghost->delta_y = -1;
				ghost->delta_x = 0;
				break;
			
			case DOWN:
				ghost-> delta_y = 1;
				ghost-> delta_x = 0;
				break;
			
			case RIGHT:
				ghost ->delta_x = 1;
				ghost ->delta_y = 0;
				break;
			
			case LEFT:
				ghost ->delta_x = -1;
				ghost ->delta_y = 0;
				break;
                */
        switch (cell_map[ghost->y_cell_index][ghost->x_cell_index].path) {
            case UP:
                if (cell_map[ghost->y_cell_index - 1][ghost->x_cell_index].open_path == TRUE) {
    				ghost->delta_y = -1;
				    ghost->delta_x = 0;
                }
                else {
                    ghost->direction = get_optimal_direction(ghost);
                    ghost->delta_y = 0;
				    ghost->delta_x = 0;
                }
                break;
            case DOWN:
                if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == TRUE) {
    				ghost->delta_y = 1;
                    ghost->delta_x = 0;
                } else {
                    ghost->direction = get_optimal_direction(ghost);
                    ghost->delta_y = 0;
                    ghost->delta_x = 0;
                }
                break;
            case RIGHT:
                if (cell_map[ghost->y_cell_index][ghost->x_cell_index + 1].open_path == TRUE) {
    				ghost->delta_y = 0;
                    ghost->delta_x = 1;
                }
                else {
                                        ghost->direction = get_optimal_direction(ghost);

                    ghost->delta_y = 0;
                    ghost->delta_x = 0;
                }
                break;
            case LEFT:
                if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == TRUE) {
    				ghost->delta_y = 0;
                    ghost->delta_x = -1;
                }
                else {
                    ghost->delta_y = 0;
                    ghost->delta_x = 0;
                }
        }
        /*
        if (cell_map[ghost->y_cell_index + ghost->delta_y][ghost->x_cell_index + ghost->delta_x].open_path == TRUE)
            return;*/
   /* }*/          
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
    case OPEN_PATH:
        /*align_axis(pacman); */
        break;
    case WALL:

        pacman->delta_y = 0;
        pacman->delta_x = 0;
        
        break;
    case GHOST:

        switch (object_type)
        {
        case GHOST_TYPE_CRYING:
            kill_ghost(entity->crying_ghost, cell_map);
            break;
        
        case GHOST_TYPE_AWKWARD:
            kill_ghost(entity->awkward_ghost, cell_map);
            break;
        
        case GHOST_TYPE_MOUSTACHE:
            kill_ghost(entity->moustache_ghost, cell_map);
            break;
        
        case GHOST_TYPE_CYCLOPS:
            kill_ghost(entity->cyclops_ghost, cell_map);
            break;
        
        default:
            break;
        }
        break;
    }
}
/***********************************************************
*  Uses an XOR shift algorthm to generate a random number 
*   -For randomizing direction of any ghost
*    
*   @return 'state' this is the random number that is returned
*
***********************************************************/
void handle_collisions(Entities* entity, UINT16 ticks) {
    int i;
    ObjectType collision_type = OPEN_PATH;
    Movement* pacman = entity->pacman->move;


    /*collision_type = process_ghost_collision(entity);*/
    collision_type = process_ghost_collision(entity, ticks);


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
    /*
	pacman -> move -> delta_y = 0;
    pacman -> move -> delta_x = 0;

	switch(input)
	{
		case W_KEY: 
			pacman -> move -> delta_y = -1;   		
            pacman -> move -> delta_x = 0;
            pacman -> move -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> move -> delta_x = -1;			
            pacman -> move -> delta_y = 0;
            pacman -> move -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> move -> delta_y = 1;			
            pacman -> move -> delta_x = 0;
            pacman -> move -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> move -> delta_x = 1;			
            pacman -> move -> delta_y = 0;
            pacman -> move -> direction = RIGHT;
			break;

		default:
            pacman -> move -> delta_x = 0; 
            pacman -> move -> delta_y = 0;
	
			break;
	}
    */
   /*
   	movement -> delta_y = 0;
    movement -> delta_x = 0;
    */

	switch(input)
	{
		case W_KEY: 
            if (movement->direction != UP) {
                movement->changed_direction = TRUE;
                movement -> delta_y = -1;   		
                movement -> delta_x = 0;
                movement -> direction = UP; 
            }
            else {
                movement->changed_direction = FALSE;
            }
			break;
				
		case A_KEY: 
            if (movement->direction != LEFT) {
                movement->changed_direction = TRUE;
                movement -> delta_x = -1;			
                movement -> delta_y = 0;
                movement -> direction = LEFT;
            }
            else {
                movement->changed_direction = FALSE;
            }
			break;
				
		case S_KEY: 
            if (movement->direction != DOWN) {
                movement->changed_direction = TRUE;
                movement -> delta_y = 1;
                movement -> delta_x = 0;
                movement -> direction = DOWN;
            }
            else {
                movement->changed_direction = FALSE;
            }
			break;
				
		case D_KEY: 
            if (movement->direction != RIGHT) {
                movement->changed_direction = TRUE;
                movement -> delta_x = 1;
                movement -> delta_y = 0;
                movement -> direction = RIGHT;
            }
            else {
                movement->changed_direction = FALSE;
            }
			break;

		default:
            movement->changed_direction = FALSE;
            movement -> delta_x = 0; 
            movement -> delta_y = 0;
	
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
    if (cell_map[ghost->y_cell_index - 1][ghost->x_cell_index].open_path == TRUE)
        count++;
    if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == TRUE)
        count++;
    if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == TRUE)
        count++;
    if (cell_map[ghost->y_cell_index][ghost->x_cell_index + 1].open_path == TRUE)
        count++;
    return count;
}
void eat_pellet(Movement* pacman) {
    cell_map[pacman->y_cell_index][pacman->x_cell_index].has_pellet = FALSE;
    
}
