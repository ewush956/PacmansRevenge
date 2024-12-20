#ifndef EVENTS_H
#define EVENTS_H

#include "TYPES.H"
#include "model.h"

#define UP_RANDOMN ((UCHAR8)1)
#define DOWN_RANDOM ((UCHAR8)2)
#define LEFT_RANDOM ((UCHAR8)4)						/*usaing powers of 2 numbers*/
#define RIGHT_RANDOM ((UCHAR8)8)                    /*FOR numbers with only 1 bit showing up (eg 1000 0100) */



extern const UCHAR8 DIRECTION_ARRAY[4];


void handle_pacman_collision(ObjectType object_type, Entities* entity);
void handle_ghost_collision(Movement* ghost1, Movement* ghost2);
void handle_wall_collision(Movement* ghost, UCHAR8 state, UCHAR8 path_number);
void handle_collisions(Entities* entity);
void reset_pacman();

UCHAR8 get_valid_paths(Movement *ghost);
void eat_pellet(Movement* pacman);
#endif