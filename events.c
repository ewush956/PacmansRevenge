
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
    
    /*

        if (ghost1->direction == UP || ghost1->direction == DOWN) {
            ghost1->delta_y = -1 * ghost1->delta_y;
        } else {
            ghost1->delta_x = -1 * ghost1->delta_x;
        }
        if (ghost2->direction == UP || ghost2->direction == DOWN)
            ghost2->delta_x = -1 * ghost2->delta_x;
        else
            ghost2->delta_y = -1 * ghost2->delta_y;
            */

    
}
ObjectType process_ghost_collision(Entities* all, int tick)
{  
    
    ObjectType collision = OPEN_PATH;
    int i, n;


    Movement *all_ghosts[4];
    all_ghosts[0] = all->crying_ghost->move;
    all_ghosts[1] = all->awkward_ghost->move;
    all_ghosts[2] = all->cyclops_ghost->move;
    all_ghosts[3] = all->moustache_ghost->move;

    for (i = 0; i < 4; i++){
        if (check_wall_collision(all_ghosts[i]) != OPEN_PATH) {
            /*Handle collision with wall, only changes direction*/
            handle_wall_collision(all_ghosts[i], i);   
        } 
        /*
        The stuff below is just fake randomness.
        */
        else {
            if (all_ghosts[i]->direction == UP || all_ghosts[i]->direction == DOWN) {
                if (cell_map[all_ghosts[i]->y_cell_index][all_ghosts[i]->x_cell_index + 1].open_path == TRUE) {
                    if (tick % 7+i == 0)
                        all_ghosts[i]->direction = RIGHT;
                }
                else if (cell_map[all_ghosts[i]->y_cell_index][all_ghosts[i]->x_cell_index - 1].open_path == TRUE) {
                    if (tick % 5 == i)
                        all_ghosts[i]->direction = LEFT;
                    else if (cell_map[all_ghosts[i]->y_cell_index][all_ghosts[i]->x_cell_index + 1].open_path == TRUE)
                        if (tick % 3 == 0) {
                            all_ghosts[i]->direction = RIGHT;
                        }
                    
                }
            }   
            
                else {
                    if (cell_map[all_ghosts[i]->y_cell_index + 1][all_ghosts[i]->x_cell_index].open_path == TRUE)
                        if (tick+i % 17 == 0)
                        {
                            all_ghosts[i]->direction = DOWN;
                        }
                        /*
                    else if (cell_map[all_ghosts[i]->y_cell_index - 1][all_ghosts[i]->x_cell_index].open_path == TRUE){
                        if (tick % 3+i == 0)
                            all_ghosts[i]->direction = UP;
                    }
                            
                    else if (cell_map[all_ghosts[i]->y_cell_index + 1][all_ghosts[i]->x_cell_index].open_path == TRUE)
                        if (tick % 11 == 0)
                            all_ghosts[i]->direction = DOWN;
                            */
                }
                
        }
    }
    for (i = 3; i > -1; i--){
        for (n = 1; n <= i; n++){
            if (check_shared_occupied(all_ghosts[i], all_ghosts[i-n]) == TRUE) {
                handle_ghost_collision(all_ghosts[i], all_ghosts[i-n]);
                /*return collision;  */
            }
        }
    }
    
   /* return collision;*/
}
/*void handle_wall_collision(Movement* entity) {*/
void handle_wall_collision(Movement* ghost, int ghost_identifier) {
    
    int i, direction;
    direction = ghost->direction;
    for (i = 0; i < 4; i++) {
        direction++;
        if (direction > 3) 
            direction = (direction % 3) - 1;
        ghost -> direction = DIRECTION_ARRAY[direction];
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
		}
        if (cell_map[ghost->y_cell_index + ghost->delta_y][ghost->x_cell_index + ghost->delta_x].open_path == TRUE)
            return;
        
    }
   /*

    UCHAR8 possible_direction = 0;

        if (cell_map[entity->y_cell_index][entity -> x_cell_index + 1].open_path == TRUE )
            possible_direction |= RIGHT_RANDOM;

        if (cell_map[entity->y_cell_index][entity->x_cell_index  - 1].open_path == TRUE)
            possible_direction |= LEFT_RANDOM;

        if (cell_map[entity->y_cell_index  + 1][entity-> x_cell_index].open_path == TRUE)
            possible_direction |= DOWN_RANDOM;

        if (cell_map[entity-> y_cell_index - 1][entity-> x_cell_index].open_path == TRUE)
            possible_direction |= UP_RANDOMN;
     
        if (possible_direction & 0x01)
            entity -> direction = UP;

        else if(possible_direction & 0x08)
            entity ->direction = RIGHT;

        else if( possible_direction & 0x04)
            entity -> direction = LEFT;

        else
            entity -> direction = DOWN;
            
    */
            
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

    /*if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone*/
    Movement* pacman = entity->pacman->move;
    
    switch(object_type)
    {
    case OPEN_PATH:
        align_axis(pacman); 
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
            /* code */
            break;
        
        case GHOST_TYPE_MOUSTACHE:
            kill_ghost(entity->moustache_ghost, cell_map);
            /* code */
            break;
        
        case GHOST_TYPE_CYCLOPS:
            kill_ghost(entity->cyclops_ghost, cell_map);
            /* code */
            break;
        
        default:
            break;
        }
        break;
        /*

    case GHOST_TYPE_CRYING:
        break;

    case GHOST_TYPE_AWKWARD:
        break;
    
    case GHOST_TYPE_MOUSTACHE:
        break;

    case GHOST_TYPE_CYCLOPS:
        break;  
        */      
    }
}
/***********************************************************
*  Uses an XOR shift algorthm to generate a random number 
*   -For randomizing direction of any ghost
*    
*   @return 'state' this is the random number that is returned
*
***********************************************************/
void handle_collisions(Entities* entity, int ticks) {
    int i;
    ObjectType collision_type = OPEN_PATH;
    Movement* pacman = entity->pacman->move;


    /*collision_type = process_ghost_collision(entity);*/
    process_ghost_collision(entity, ticks);


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



/*
    align_axis(entity->crying_ghost);
    align_axis(entity->awkward_ghost);
    align_axis(entity->moustache_ghost);
    align_axis(entity->cyclops_ghost);
*/

    

    /*

    collision_type = check_wall_collision(entity->awkward_ghost->move);
    if (collision_type != OPEN_PATH) {
        handle_ghost_collision(collision_type, entity->awkward_ghost, entity->pacman);
    }
    collision_type = check_wall_collision(entity->moustache_ghost->move);
    if (collision_type != OPEN_PATH && ) {
        handle_ghost_collision(collision_type, entity->moustache_ghost, entity->pacman);
    }
    */
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

