
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
void handle_ghost_collision(UCHAR8 collision_type, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *xor_shift_struct) {
  
    UCHAR8 possible_direction = 0;
    ULONG32 random_number;
    UCHAR8 counter = 0;
    UCHAR8 prev_direction = ghost -> direction;

    if (collision_type == WALL)
    {
        
        if (cell_map[ghost->y_cell_index][ghost -> x_cell_index + 1].open_path == TRUE )
        {
            possible_direction |= RIGHT_RANDOM;
          
        }
        if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == TRUE)
        {
            possible_direction |= LEFT_RANDOM;
          
        }
        if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == TRUE)
        {
            possible_direction |= DOWN_RANDOM;
          
        }

        if (cell_map[ghost-> y_cell_index - 1][ghost->x_cell_index].open_path == TRUE)
        {
            possible_direction |= UP_RANDOMN;
           
        }

        /* make an array of different possibilities.. to make it more random?
         if(possible_direction & 0x04)
            ghost -> direction = LEFT_RANDOM;*/             /*add this back later*/

        if (possible_direction & 0x01)
            ghost -> direction = UP_RANDOMN;

        else if(possible_direction & 0x08)
            ghost -> direction = RIGHT_RANDOM;

        else
            ghost -> direction = DOWN_RANDOM;
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
        if (entity->pacman->direction == UP || entity->pacman->direction == DOWN) {
            pacman->x = pacman->x_cell_index * PIXELS_PER_CELL;
        }
        else if (entity->pacman->direction == LEFT || entity->pacman->direction == RIGHT) {
            pacman->y = pacman->y_cell_index * PIXELS_PER_CELL + PIXELS_PER_CELL;
        }
        break;

    case WALL:
        pacman->delta_y = 0;
        pacman->delta_x = 0;
        
        break;
    case GHOST_TYPE_CRYING:
       /* kill_ghost(&entity->crying_ghost, cell_map);*/                     
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

    collision_type = check_pacman_collision(entity, pac->y_cell_index, 
                                    pac->x_cell_index, 
                                    pac->delta_y, 
                                    pac->delta_x);
    handle_pacman_collision(collision_type, entity); 
    /*NOTE:
     currently handle_pacman_collision is handling all cases, thats why it's not in an if block
    we should change that at some point but my brain hurts and I no no wanna :(*/
    


    collision_type = check_collision(entity, awkward->y_cell_index, 
                                    awkward->x_cell_index, 
                                    awkward->delta_y, 
                                    awkward->delta_x,
                                    awkward->type);
    
    if (collision_type != OPEN_PATH)
    {
        handle_ghost_collision(collision_type, awkward, cell_map, xor);
         

    }
    else
    {
        if (cell_map[awkward->y_cell_index + 1][awkward->x_cell_index].open_path == TRUE)
        {   
            awkward->direction = DOWN_RANDOM;
            move_ghost(awkward);
        }
         else if (cell_map[awkward->y_cell_index ][awkward->x_cell_index+1].open_path == TRUE)
        {   
            awkward->direction = RIGHT_RANDOM;
            move_ghost(awkward);
        }
        else if (cell_map[awkward->y_cell_index ][awkward->x_cell_index-1].open_path == TRUE)
        {   
            awkward->direction = LEFT_RANDOM;
            move_ghost(awkward);
        }
        else
        {
            awkward -> direction = DOWN_RANDOM;
            move_ghost(awkward);
        }



    }
                
    collision_type = check_collision(entity, moustache->y_cell_index, 
                                    moustache->x_cell_index, 
                                    moustache->delta_y, 
                                    moustache->delta_x,
                                    moustache->type);
    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, moustache, cell_map, xor);
    else   
    {    
        if (cell_map[moustache->y_cell_index - 1][moustache->x_cell_index].open_path == TRUE)
        {   
            moustache -> direction = UP_RANDOMN;
            move_ghost(moustache);
        }
        else if (cell_map[moustache->y_cell_index][moustache->x_cell_index+1].open_path == TRUE)
        {
            moustache -> direction = RIGHT_RANDOM;
            move_ghost(moustache);
        }

    }
    

    collision_type = check_collision(entity, crying->y_cell_index, 
                                    crying->x_cell_index, 
                                    crying->delta_y, 
                                    crying->delta_x,
                                    crying->type);
    if (collision_type != OPEN_PATH)
    {
        handle_ghost_collision(collision_type, crying, cell_map, xor);
        /*printf("inside of crying ghost handle_collsi call\n");*/

    }
    else   
    {    
        if (cell_map[crying->y_cell_index][crying->x_cell_index +1].open_path == TRUE)
 
        {   crying -> direction = RIGHT_RANDOM;
            move_ghost(moustache);
        }
    }

    collision_type = check_collision(entity, cyclops->y_cell_index, 
                                    cyclops->x_cell_index, 
                                    cyclops->delta_y, 
                                    cyclops->delta_x,
                                    cyclops->type);
    if (collision_type != OPEN_PATH)
    {
      
        handle_ghost_collision(collision_type, cyclops, cell_map, xor);
        /*printf("cyclops ghost direction after %u\n",cyclops->direction);*/
      
    }
    else
    {
        if (cell_map[cyclops->y_cell_index][cyclops->x_cell_index - 1].open_path == TRUE)
        {   
            cyclops -> direction = LEFT_RANDOM;
            move_ghost(moustache);
        }
    }

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

	pacman -> delta_y = 0;
    pacman -> delta_x = 0;
      

	switch(input)
	{
		case W_KEY: 
			pacman -> delta_y = -1;   		/* UP 1*/
            pacman -> delta_x = 0;
            pacman -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> delta_x = -1;			/*Left 3*/
            pacman -> delta_y = 0;
            pacman -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> delta_y = 1;			/*Down 2*/
            pacman -> delta_x = 0;
            pacman -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> delta_x = 1;			/* Right 4*/
            pacman -> delta_y = 0;
            pacman -> direction = RIGHT;
			break;

		default:	
			break;
	}

}

