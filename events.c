
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
            possible_direction |= RIGHT_RANDOM;

        if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == TRUE)
            possible_direction |= LEFT_RANDOM;

        if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == TRUE)
            possible_direction |= DOWN_RANDOM;

        if (cell_map[ghost-> y_cell_index - 1][ghost->x_cell_index].open_path == TRUE)
            possible_direction |= UP_RANDOMN;
     
        if (possible_direction & 0x01)
            ghost -> direction = UP_RANDOMN;

        else if(possible_direction & 0x08)
            ghost -> direction = RIGHT_RANDOM;

        else if( possible_direction & 0x04)
            ghost -> direction = LEFT_RANDOM;

        else
            ghost -> direction = DOWN_RANDOM;
    }
}
void handle_pacman_collision(ObjectType object_type, Entities* entity) {

    /*if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone*/

    switch(object_type)
    {
    case WALL:
        entity->pacman->delta_y = 0;
        entity->pacman->delta_x = 0;
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

    /*move_pacman(&pacman);*/



/*
   if (pacman->direction == UP)
            pacman ->delta_y = 0;
        else if (pacman ->direction == DOWN)
            pacman->delta_y = 0;
        else if(pacman -> direction == RIGHT)
            pacman->delta_x = 0;
        else
            pacman ->delta_x = 0;

     /* pacman -> delta_x = 0;              /* do we want pacman to move while holding key or each press and he moves until collsion?*/
    /*  pacman -> delta_y = 0;              /* if want automatic then take out input reset in set_input and leave it here */
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

    collision_type = check_collision(entity, pac->y_cell_index, 
                                    pac->x_cell_index, 
                                    pac->delta_y, 
                                    pac->delta_x,
                                    pac->type);

    if (collision_type != OPEN_PATH)
        handle_pacman_collision(collision_type, entity);


    collision_type = check_collision(entity, awkward->y_cell_index, 
                                    awkward->x_cell_index, 
                                    awkward->delta_y, 
                                    awkward->delta_x,
                                    awkward->type);

    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, awkward, cell_map, xor);
    
                
    collision_type = check_collision(entity, moustache->y_cell_index, 
                                    moustache->x_cell_index, 
                                    moustache->delta_y, 
                                    moustache->delta_x,
                                    moustache->type);
    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, moustache, cell_map, xor);
    

    collision_type = check_collision(entity, crying->y_cell_index, 
                                    crying->x_cell_index, 
                                    crying->delta_y, 
                                    crying->delta_x,
                                    crying->type);
    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, crying, cell_map, xor);

    collision_type = check_collision(entity, cyclops->y_cell_index, 
                                    cyclops->x_cell_index, 
                                    cyclops->delta_y, 
                                    cyclops->delta_x,
                                    cyclops->type);
    if (collision_type == OPEN_PATH)
    {
        handle_ghost_collision(collision_type, cyclops, cell_map, xor);
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
            pacman -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> delta_x = -1;			/*Left 3*/
            pacman -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> delta_y = 1;			/*Down 2*/
            pacman -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> delta_x = 1;			/* Right 4*/
            pacman -> direction = RIGHT;
			break;

		default:
            pacman-> delta_x = 0; 
            pacman -> delta_y = 0; 		
			break;
	}

}

