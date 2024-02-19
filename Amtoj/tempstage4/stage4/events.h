/*
#include "TYPES.H"
#include "model.h"

typedef struct
{

    UINT32 value;

}Xor;

void handle_ghost_collision (UINT8 collision_type, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *xor_shift_struct);
UINT32 random_number_generator(Xor *xor);
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman);
*/

/******************
 * @file TYPES.h
 * @brief Header file containing type definitions and function prototypes for the game model.
 *******************/

#ifndef TYPES_H
#define TYPES_H
#include "model.h"

/*********************************************
 * @struct Xor
 * @brief Structure representing a random number generator using XOR algorithm.
 * @var Xor::value
 * Member 'value' holds the current state of the random number generator.
 *******************************************/
typedef struct {
    UINT32 value; /**< Current state of the random number generator. */
} Xor;

/****************************************
 * @brief Handles collisions involving a ghost character in the game environment.
 * @param collision_type An integer representing the type of collision (e.g., WALL, OBJECT).
 * @param ghost A pointer to the Ghost structure representing the ghost character.
 * @param cell_map A 2D array of Cell structures representing the game map.
 * @param xor_shift_struct A pointer to the Xor structure used for random number generation.
 ***********************************/
void handle_ghost_collision(UINT8 collision_type, Ghost *ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *xor_shift_struct);

/**********************************
 * @brief Generates a random number using the XOR algorithm.
 * @param xor A pointer to the Xor structure used for random number generation.
 * @return An unsigned 32-bit integer representing the generated random number.
 *****************************/
UINT32 random_number_generator(Xor *xor);

/*************************************
 * @brief Handles collisions involving the Pacman character in the game environment.
 * @param collision_type An integer representing the type of collision (e.g., WALL, OBJECT).
 * @param pacman A pointer to the Pacman structure representing the Pacman character.
 **************************************/
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman);

#endif /* TYPES_H */