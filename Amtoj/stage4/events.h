
#include "TYPES.H"
#include "model.h"


typedef struct
{

    ULONG32 value;

}Xor;

void clock_tick_handle(UINT16* clock_count, Entities* entity);		/* calls move pacman calls all synch event handlers */
void handle_pacman_collision(UCHAR8 collision_type, Pacman *pacman);
void handle_ghost_collision(UCHAR8 collision_type, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *random_int_struct);
ULONG32 random_number_generator(Xor *xor);
