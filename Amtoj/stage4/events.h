#ifndef EVENTS_H
#define EVENTS_H

#include "TYPES.H"
#include "model.h"

void clock_tick_handle();		/* calls move pacman calls all synch event handlers */

void handle_collision(Pacman* pacman, UINT16 x_position, UINT16 y_position);        


#endif