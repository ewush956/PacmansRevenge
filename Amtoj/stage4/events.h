
#include "TYPES.H"
#include "model.h"


typedef struct
{

    UINT32 value;

}Xor;

void clock_tick_handle(UINT16* clock_count, Entities* entity);		/* calls move pacman calls all synch event handlers */
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman);
void handle_ghost_collision(UINT8 collision_type);
UINT32 random_number_generator(Xor *xor);
