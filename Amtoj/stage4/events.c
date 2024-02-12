#include "types.h"
#include "events.h"
#include "model.h"


/*make sure that the posision is within the bounds iof the tile map for pacman for collsion check*/



void handle_collision(Pacman* pacman, UINT16 pacman_x_position, UINT16 pacman_y_position)
{

    /*UINT8 collision = 0;    /* 0 is for 'false 1 is for true*/

    if (tile_map[pacman_y_position][pacman_x_position] == 1 || 
        tile_map[pacman_y_position][pacman_x_position] == 2 ||
        tile_map[pacman_y_position][pacman_x_position] == 3 ||
        tile_map[pacman_y_position][pacman_x_position] == 4 ||
        tile_map[pacman_y_position][pacman_x_position] == 5 ||
        tile_map[pacman_y_position][pacman_x_position] == 6)
        {
            /*collision = 1;*/
            pacman-> has_collided = 1;
        }
        else
            pacman->has_collided = 0;


    


}  
