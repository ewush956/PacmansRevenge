#include <osbind.h>
#include "TYPES.H"
#include "events.h"
#include "globals.h"


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
            
        case MENU:  
            break;

        default:
            break;

    }
}
