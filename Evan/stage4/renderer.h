
#include "model.h"
#include "bitmaps.h"
#include "types.h"

void clock_tick_handle();
void render_map(UINT16* base);
void render_pacman(Pacman* pacman, Ghost* ghost);
void render_ghost(Pacman* pacman, Ghost* ghost);
void render_gameover();
void render_timer();
