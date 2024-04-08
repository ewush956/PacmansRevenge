#include <osbind.h>
#include "TYPES.H"
#include "events.h"
#include "globals.h"
#include "input.h"


/*****************************
* A simple finite state machine 
*  that handles keyboard input
*
******************************/
void process_keyboard_input(UCHAR8 input)
{   
    switch(state)
    {   
        case PLAY:
            if (input == ESC_MAKE){
                state = WAITING_FOR_ESC_BREAK;
            } 
            else{
                set_input(entity.pacman,input);
            }
            break;
        case WAITING_FOR_ESC_BREAK:
            if (input == ESC_BREAK){
                state = QUIT;
            }
            else{
                state = PLAY;
            }
            break;
            
        default:
            break;

    }
}
void set_input(Pacman *pacman, char input)
{
    Movement* movement = pacman->move;
    set_deltas(movement, 0, 0);    
	switch(input)
	{
		case W_MAKE: 
            set_deltas(movement, 0, -1); 
            movement->direction = UP;     
            break;	

		case A_MAKE: 
            set_deltas(movement, -1, 0);
            movement -> direction = LEFT;
			break;
				
		case S_MAKE: 
            set_deltas(movement, 0, 1);
            movement -> direction = DOWN;
			break;

		case D_MAKE: 
            set_deltas(movement, 1, 0);
            movement -> direction = RIGHT;
			break;

		default:
            set_deltas(movement, 0, 0);	
			break;
	}
    

}
