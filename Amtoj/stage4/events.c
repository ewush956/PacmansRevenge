
#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"

#include <stdio.h>
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
        
        pac->direction = UP;
        render_pacman(pac);
        render_ghosts()
        update_cell(&pac->x_cell_index, &pacman->y_cell_index);

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

void handle_ghost_collision(UINT8 collision_type, Ghost* ghost,Cell cell_map[][MAP_TILE_LENGTH]) {
    /*
    Amtoj
    if ghost collided returns true then check directions and move based on that */

    UINT16 possible_directions;
    switch (collision_type)
    {
        case WALL:
          if ( ghost->current_= + 1 == TRUE )


            random_direction |= ghost -> direction;
        possible_direction |= ghost->direction;
            break;




    }


}
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman) {

/*  Amtoj
    if pacman check_collison returns true, then dont move him 
    otherwise update his position 
    
    if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone
    */

    pacman->delta_y = 0;
    pacman->delta_x = 0;
    switch(collision_type)
    {
    case WALL: 
        printf("COLLISION WITH A WALL\n\n");
        break;

    case OBJECT:                            /* ask evan  */
        printf("COLLIDED with an OBJECT\n\n");
        /*add_wall_to_map(cell_map,ghost)*/
        break;
    
    default:
        printf("NO COLLSION");

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

/* * * * * * * * * * * * *
*  Uses an XOR shift algorthm to generate a random number 
*   -For randomizing direction of any ghost
*    
*@return 'state' this is the random number that is returned
*
* * * * * * * * * * */
UINT32 random_number_generator(Xor *xor)
{

    UINT32 state = xor->value;

	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
    xor->value = state;

    return state;
}

