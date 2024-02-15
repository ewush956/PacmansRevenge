#include "TYPES.H"


typedef struct
{

    UINT32 state;

}Xor;

/*void clock_tick_handle(UINT16 *clock_count, Entities *entity,Timer *timer)*/;
/*void clock_tick_handle(UINT16* clock_count);		/* calls move pacman calls all synch event handlers */
void handle_ghost_collision();
void handle_pacman_collision(UINT8 collision_type);
UINT32 random_number_generator(Xor *xor);
