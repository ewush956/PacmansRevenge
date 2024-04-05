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
    /* state must be global*/

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
            /*
            if(input == ENTER || left_button_pressed == TRUE) {/*&& within_button_range) 
                left_button_pressed = FALSE;
                /*state = PLAY; 
            }*/

            break;
        default:
            break;

    }
}
