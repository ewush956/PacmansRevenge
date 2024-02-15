
#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"

void clock_tick_handle(UINT16* clock_count) {
    /*
    Evan
    Called 70 times per second, renders all sprites, determines states (next position/collision status, etc.)

    do stuff to figure out delta x,y then render sprite

    TODO
    */
    if (*clock_count % 4 == 0) {

        pacman.direction = get_input();
        /*mod 4 because 70 ticks per second is very fast*/
        render_pacman(&pacman);
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
        /*Rendered every second*/
        render_timer();
        clock_count = 0;
    }
    (*clock_count)++;

}
void handle_ghost_collision() {
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
UINT8 get_input() {
    /*idk how the input stuff works so I just used this for now*/
    return UP;
}
