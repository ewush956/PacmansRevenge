#ifndef EVENTS_H
#define EVENTS_H

#include "TYPES.H"
#include "model.h"

#define UP_RANDOMN ((UCHAR8)1)
#define DOWN_RANDOM ((UCHAR8)2)
#define LEFT_RANDOM ((UCHAR8)4)						/*usaing powers of 2 numbers*/
#define RIGHT_RANDOM ((UCHAR8)8)                    /*FOR numbers with only 1 bit showing up (eg 1000 0100) */

#define W_KEY 'w'
#define A_KEY 'a'
#define S_KEY 's'
#define D_KEY 'd'

typedef struct
{

    ULONG32 value;

}Xor;

void clock_tick_handle(UINT16* clock_count, Entities* entity);		/* calls move pacman calls all synch event handlers */
void handle_pacman_collision(ObjectType object_type, Entities* entity);
void handle_ghost_collision(UCHAR8 collision_type, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *random_int_struct);
void handle_collisions(Entities* entity, Xor *xor);
ULONG32 random_number_generator(Xor *xor);
void set_input(Pacman *pacman, char input);

void update_awkward_direction (Ghost *awkward );
void update_crying_direction(Ghost *crying);


#endif