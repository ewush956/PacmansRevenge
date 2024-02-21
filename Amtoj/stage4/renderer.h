
#include "model.h"
#include "bitmaps.h"
#include "types.h"



void clock_tick_handle();
void render_map(UINT16* base, UINT16 tile_map[][MAP_TILE_LENGTH]);
void render_frame(ULONG32* base, Entities* entity);
void render_pacman(ULONG32* base32, Pacman* pacman);
void render_ghosts(ULONG32* base32, Entities* entity);
void render_gameover();
void render_timer();
void de_render_ghost(ULONG32* base32, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]);
void render_non_default_ghost(ULONG32* base32, Ghost* ghost);
void clr_sprite(ULONG32* base, int x, int y);

