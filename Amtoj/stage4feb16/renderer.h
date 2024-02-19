
#include "model.h"
#include "bitmaps.h"
#include "types.h"



void clock_tick_handle();
void render_map(UINT16* base, UINT16 tile_map[][MAP_TILE_LENGTH]);
void render_frame(UINT32* base, Entities* entity);
void render_pacman(UINT32* base32, Pacman* pacman);
void render_ghosts(UINT32* base32, Entities* entity);
void render_gameover();
void render_timer();
void de_render_ghost(UINT32* base32, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]);
void render_non_default_ghost(UINT32* base32, Ghost* ghost);
void clr_sprite(UINT32* base, int x, int y);

