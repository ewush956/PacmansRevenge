
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

/*
*   We are using an XOR algorithm to generate a random number to mod it by 4 to select a random
*   direction for the ghosts to choose from if they encounter multiple open paths after colliding with a wall 
*
*
**/
void handle_ghost_collision(UINT8 collision_type, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *xor_shift_struct) {
  
    UINT8 possible_direction = 0;
    UINT32 random_number;
    UINT8 counter = 0;
    UINT8 prev_direction = ghost -> direction;

  
    if (collision_type == WALL)
    {
     
        if (cell_map[ghost->y_cell_index][ghost -> x_cell_index + 1].open_path == TRUE )
        {
            possible_direction |= RIGHT;
            counter++;
            printf("right \n");
            /*ghost -> direction = RIGHT;*/
        }

       if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == TRUE)
        {
            possible_direction |= LEFT;
            counter++;
            printf("left \n");
            /*ghost -> direction = LEFT;*/
        }

       if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == TRUE)
        {
            possible_direction |= DOWN;
            counter++;
            printf("down \n");
            /*ghost -> direction = DOWN;*/
        }

       if (cell_map[ghost-> y_cell_index - 1][ghost->x_cell_index].open_path == TRUE)
        {
            possible_direction |= UP;
            counter++;
            printf("up \n");
            /*ghost -> direction = UP;*/
        }


        random_number = random_number_generator(xor_shift_struct);          /* random number */
        /*
        random_number &= 0xFF;                                              /*clear upper bits no need for them 
        random_number %= 16;                                                   /* range 0 - F
        possible_direction &= random_number;
        */

     
        if (possible_direction & 0x01)
            ghost -> direction = UP;
        else if(possible_direction & 0x08)
            ghost -> direction = RIGHT;
        else if( possible_direction & 0x04)
            ghost -> direction = LEFT;
        else
            ghost -> direction = DOWN;

/*
        switch(random_number) 
        {
            case 0:
                ghost->direction = UP;
                break;
             case 1:
                ghost->direction = LEFT;
                break;
            case 2:
                ghost->direction = DOWN;
                break;
            case 3:
                ghost->direction = RIGHT;
                break;
        }*/


    printf("ghost direction: %u",ghost->direction);

    }
    else
        printf("Not a wall in the switch struct\n");
    

}
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman) {

    
    /*if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone*/
    

    pacman->delta_y = 0;
    pacman->delta_x = 0;
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
   /*
    state*=2;
    state++;
    */
    xor->value = state;

    return state;
}

