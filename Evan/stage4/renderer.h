
#include "model.h"
#include "bitmaps.h"
#include "types.h"

typedef struct Xor {
    
    UINT32 value;
};

void clock_tick_handle();
void render_map(UINT16* base);
void render_frame(UINT32* base, Entities* entity);
void render_pacman(Pacman* pacman, Ghost* ghost);
void render_ghost(Pacman* pacman, Ghost* ghost);
void render_gameover();
void render_timer();
UINT32 random_number_generator(Xor *xor);