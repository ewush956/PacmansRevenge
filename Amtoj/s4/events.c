#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"
#include "renderer.h"


/* need to add paramters for ghost obj and such here */
/*
void clock_tick_handle(UINT16* clock_count,Ghost* ghost, Pacman *pacman,Timer *timer) {
    /*
    Evan
    Called 70 times per second, renders all sprites, determines states (next position/collision status, etc.)

    do stuff to figure out delta x,y then render sprite

    TODO
    
    if (*clock_count % 4 == 0) {

        pacman->move->direction = UP; /*get_input();*/
        /*mod 4 because 70 ticks per second is very fast
        render_pacman(&pacman,&ghost);              /*added &ghost here
        update_cell(&pacman.x_cell_index, &pacman.y_cell_index);

        render_ghost(&crying_ghost);
        update_cell(&crying_ghost.x_cell_index, &crying_ghost.y_cell_index);

        render_ghost(&moustache_ghost);
        update_cell(&moustache_ghost.x_cell_index, &moustache_ghost.y_cell_index);

        render_ghost(&cyclops_ghost);
        update_cell(&cyclops_ghost.x_cell_index, &cyclops_ghost.y_cell_index);

        render_ghost(&awkward_ghost);
        update_cell(&awkward_ghost.x_cell_index, &awkward_ghost.y_cell_index);
    
    }
    if (clock_count == 70) {
        /*Rendered every second
        render_timer(&timer);
        clock_count = 0;
    }
    *clock_count++;

}
*/

void handle_ghost_collision() {
    /*
    Amtoj
    if ghost collided returns true then check directions and move based on that */
    return;
}
void handle_pacman_collision(UINT8 collision_type,Pacman *pacman) {

    /*  Amtoj
    if pacman check_collison returns true, then dont move him 
    otherwise update his position 
    */

    switch(collision_type)
    {
        case WALL:
            pacman -> move -> delta_x = 0;              /* do we want pacman to move while holding key or each press and he moves until collsion?*/
            pacman -> move -> delta_y = 0;              /* if want automatic then take out input reset in set_input and leave it here */
            break;
        case OBJECT:                            /* ask evan  */
            break;
        
       
    }


}

/* * * * * *  
*  Uses an XOR algorthm to generate a random number 
*   -For randomizing direction of any ghost
*    
*@return 'state' this is the random number that is returned
*
* * * * * * */
UINT32 random_number_generator(Xor *xor)
{

    UINT32 state = xor->value;

	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
    xor->value = state;

    return state;
}
