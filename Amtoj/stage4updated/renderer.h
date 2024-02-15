
#include "model.h"
#include "bitmaps.h"
#include "types.h"

typedef struct {
    
    UINT32 value;

}Xor;

void clock_tick_handle();
void render_map(UINT16* base);
void render_pacman(Pacman *pacman, Ghost *ghost);
void render_ghosts(Ghost *ghost);
void render_gameover();

void render_timer(Timer *timer);

void clear_sprite(UINT32* base, int x, int y);
bool check_next_cell(int dirrection, int x_cell_index, int y_cell_index);
UINT32 random_number_generator(Xor* xor); 
