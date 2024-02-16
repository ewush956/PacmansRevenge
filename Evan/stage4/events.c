
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

void handle_ghost_collision(UINT8 collision_type) {
    /*
    Amtoj
    if ghost collided returns true then check directions and move based on that */
}
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman) {

/*  Amtoj
    if pacman check_collison returns true, then dont move him 
    otherwise update his position 
    
    if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone
    */
    switch(collision_type)
    {
    case WALL:
        pacman -> delta_x = 0;              /* do we want pacman to move while holding key or each press and he moves until collsion?*/
        pacman -> delta_y = 0;              /* if want automatic then take out input reset in set_input and leave it here */
        break;

    case OBJECT:                            /* ask evan  */
        break;
    }
}

