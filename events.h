#ifndef EVENTS_H
#define EVENTS_H
#include "model.h"


typedef struct {
    UINT32 value; /**< Current state of the random number generator. */
}Xor;

void handle_ghost_collision(UINT8 collision_type, Ghost *ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *xor_shift_struct);

UINT32 random_number_generator(Xor *xor);

void handle_pacman_collision(UINT8 collision_type, Pacman *pacman);

#endif