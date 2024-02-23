
#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"
/*
void clock_tick_handle(UINT16* clock_count, Entites* entity) {

    Evan
    Called 70 times per second, renders all sprites, determines states (next position/collision status, etc.)

    do stuff to figure out delta x,y then render sprite

    TODO
    */
    
    /*
    TODO FOR EVAN MAKE UPDATE_CELL UPDATE ALL THE CELSS AND TAKE IN ENTITY TYPE 
    if (*clock_count % 4 == 0) {

        Pacman* pac = entity->pacman;
        Ghost* moustache = entity->moustache_ghost;
        Ghost* crying = entity->crying_ghost;
        Ghost* cyclops = entity->cyclops_ghost;
        Ghost* awkward = entity->awkward_ghost;
        
        pac->move-> direction = UP;
        render_pacman(pac);
        render_ghosts()
        update_cell(&pac->move-> x_cell_index, &pacman->y_cell_index);

        update_cell(&crying_ghost->x_cell_index, &crying_ghost->y_cell_index);

        update_cell(&moustache_ghost->x_cell_index, &moustache_ghost->y_cell_index);

        update_cell(&cyclops_ghost->x_cell_index, &cyclops_ghost->y_cell_index);

        update_cell(&awkward_ghost->x_cell_index, &awkward_ghost->y_cell_index);

    }
    if (clock_count == 70) {
        render_timer();
        clock_count = 0;
    }
    (*clock_count)++;

}
*/


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
void handle_ghost_collision (UINT8 collision_type, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *xor_shift_struct) {
  
    UINT8 possible_direction = 0;
    UINT32 random_number;

    
    if (collision_type == WALL)
    {
        if (ghost->move->x_cell_index  + 1 == TRUE )
        {
            possible_direction |= RIGHT;
            printf("right \n");
        }

        if (ghost->move->x_cell_index  - 1 == TRUE)
        {
            possible_direction |= LEFT;
            printf("left \n");
        }

        if (ghost->move->y_cell_index  + 1 == TRUE)
        {
            possible_direction |= DOWN;
            printf("down \n");
        }

        if (ghost-> y_cell_index - 1 == TRUE)
        {
            possible_direction |= UP;
            printf("up \n");
        }
           random_number = random_number_generator(xor_shift_struct);
           random_number %= possible_direction; 
           possible_direction = random_number % possible_direction;
           ghost -> direction = possible_direction;

           printf("ghost direction: %u",ghost->move->direction);
    }
    else{

        printf("Not a wall collsion struct\n");
    }
}

/***************************************************************************
*   This function handles collisions involving the Pacman character in the game environment.
*   It updates Pacman's movement deltas based on the collision type and performs additional actions
*   if Pacman collides with a ghost or an object.
*   
*   Parameters:
*      - collision_type: An integer representing the type of collision (e.g., WALL, OBJECT).
*      - pacman: A pointer to the Pacman structure representing the Pacman character.
**********************************************************************************/
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman) {

    
    /*if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone*/
    

    pacman->move->delta_y = 0;
    pacman->move->delta_x = 0;
    switch(collision_type)
    {
    case WALL: 
        printf("COLLISION WITH A WALL\n\n");
        break;

    case OBJECT:                            
        printf("COLLIDED with an OBJECT\n\n");
        /*add_wall_to_map(cell_map,ghost)*/
        break;
    
    default:
        printf("NO COLLSION");

    }

}
/***********************************************************
*  Uses an XOR shift algorthm to generate a random number 
*   -For randomizing direction of any ghost
*    
*   @return 'state' this is the random number that is returned
*
***********************************************************/
UINT32 random_number_generator(Xor *xor)
{

    UINT32 state = xor->value;

	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
    xor->value = state;

    return state;
}

