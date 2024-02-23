
#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"
#include <stdio.h>

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
void handle_ghost_collision(UCHAR8 collision_type, Ghost* ghost1, Ghost* ghost2) {
  
    UCHAR8 possible_direction = 0;
    ULONG32 random_number;
    UCHAR8 counter = 0;
    UCHAR8 prev_direction = ghost1 -> move-> direction;

  
    if (collision_type == WALL)
    {
     
        if (cell_map[ghost1->move->y_cell_index][ghost1 -> move -> x_cell_index + 1].open_path == TRUE )
            possible_direction |= RIGHT_RANDOM;

        if (cell_map[ghost1->move->y_cell_index][ghost1->move->x_cell_index  - 1].open_path == TRUE)
            possible_direction |= LEFT_RANDOM;

        if (cell_map[ghost1->move->y_cell_index  + 1][ghost1-> move->x_cell_index].open_path == TRUE)
            possible_direction |= DOWN_RANDOM;

        if (cell_map[ghost1->move-> y_cell_index - 1][ghost1-> move->x_cell_index].open_path == TRUE)
            possible_direction |= UP_RANDOMN;
     
        if (possible_direction & 0x01)
            ghost1 -> move->direction = UP_RANDOMN;

        else if(possible_direction & 0x08)
            ghost1 ->move-> direction = RIGHT_RANDOM;

        else if( possible_direction & 0x04)
            ghost1 -> move->direction = LEFT_RANDOM;

        else
            ghost1 -> move->direction = DOWN_RANDOM;
    }
    else {
        /*Ghost 1 and 2 colliding with eachother*/
        ghost1 ->move-> delta_x = -1 * ghost1 ->move-> delta_x;
        ghost2 -> move->delta_x = -1 * ghost2 -> move->delta_x;
    }
}
/*************************************************************
 * Function: handle_pacman_collision
 * Purpose: Handles collisions between pacman and other entities
 * Parameters: ObjectType object_type - The type of object
 *              Entities* entity - Pointer to the entity
 * Details: 
 * the OPEN_PATH case will lock pacmans x / y movement to valid positions
****************************************************************/
void handle_pacman_collision(ObjectType object_type, Entities* entity) {

    /*if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone*/
    Pacman *pacman = entity->pacman;
    
    switch(object_type)
    {
    case OPEN_PATH:
        if (entity->pacman->move->direction == UP || entity->pacman->move->direction == DOWN) {
            pacman->move->x = pacman->move->x_cell_index * PIXELS_PER_CELL;
        }
        else if (entity->pacman->move->direction == LEFT || entity->pacman->move->direction == RIGHT) {
            pacman->move->y = pacman->move->y_cell_index  * PIXELS_PER_CELL + PIXELS_PER_CELL;
        }
        break;
    case WALL:

        pacman->move->delta_y = 0;
        pacman->move->delta_x = 0;
        
        break;
    case GHOST_TYPE_CRYING:
       /* kill_ghost(&entity->crying_ghost, cell_map);       */                     
        break;

    case GHOST_TYPE_AWKWARD:
        break;
    
    case GHOST_TYPE_MOUSTACHE:
        break;

    case GHOST_TYPE_CYCLOPS:
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
void handle_collisions(Entities* entity, Xor *xor) {

    ObjectType collision_type;
    Pacman* pac = entity->pacman;
    Ghost* moustache = entity->moustache_ghost;
    Ghost* crying = entity->crying_ghost;
    Ghost* cyclops = entity->cyclops_ghost;
    Ghost* awkward = entity->awkward_ghost;

    collision_type = check_wall_collision(entity->pacman->move);
    handle_pacman_collision(collision_type, entity); 
    /*NOTE:
     currently handle_pacman_collision is handling all cases, thats why it's not in an if block
    we should change that at some point but my brain hurts and I no no wanna :(*/

/*
    collision_type = check_collision(entity, awkward->move->y_cell_index, 
                                    awkward->move->x_cell_index, 
                                    awkward->move->delta_y, 
                                    awkward->move->delta_x,
                                    awkward->type);

    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, awkward, cell_map, xor);
    
                
    collision_type = check_collision(entity, moustache->move->y_cell_index, 
                                    moustache->move->x_cell_index, 
                                    moustache->move->delta_y, 
                                    moustache->move->delta_x,
                                    moustache->type);
    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, moustache, cell_map, xor);
    

    collision_type = check_collision(entity, crying->move->y_cell_index, 
                                    crying->move->x_cell_index, 
                                    crying->move->delta_y, 
                                    crying->move->delta_x,
                                    crying->type);
    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, crying, cell_map, xor);

    collision_type = check_collision(entity, cyclops->move->y_cell_index, 
                                    cyclops->move->x_cell_index, 
                                    cyclops->move->delta_y, 
                                    cyclops->move->delta_x,
                                    cyclops->type);
    if (collision_type == OPEN_PATH)
    {
        handle_ghost_collision(collision_type, cyclops, cell_map, xor);
    }
    */
}
ULONG32 random_number_generator(Xor *xor)
{

    ULONG32 state = xor->value;

	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
    xor->value = state;

    return state;
}
void set_input(Pacman *pacman, char input)
{

	pacman -> move -> delta_y = 0;
    pacman -> move -> delta_x = 0;
      

	switch(input)
	{
		case W_KEY: 
			pacman -> move -> delta_y = -1;   		/* UP 1*/
            pacman -> move -> delta_x = 0;
            pacman -> move -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> move -> delta_x = -1;			/*Left 3*/
            pacman -> move -> delta_y = 0;
            pacman -> move -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> move -> delta_y = 1;			/*Down 2*/
            pacman -> move -> delta_x = 0;
            pacman -> move -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> move -> delta_x = 1;			/* Right 4*/
            pacman -> move -> delta_y = 0;
            pacman -> move -> direction = RIGHT;
			break;

		default:
            pacman -> move -> delta_x = 0; 
            pacman -> move -> delta_y = 0; 		
			break;
	}

}

