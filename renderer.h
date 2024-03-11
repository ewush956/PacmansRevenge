
#include "model.h"
#include "bitmaps.h"
#include "types.h"

void clear_entities(ULONG32* base32, Movement* pacman, Movement* crying,
                    Movement* moustache, Movement* awkward, Movement* cyclops);
void render_map(UINT16* base, UINT16 tile_map[][MAP_TILE_LENGTH]);
void render_frame(ULONG32* base, Entities* entity);
void render_pacman(ULONG32* base32, Pacman* pacman);
void render_ghosts(ULONG32* base32, Entities* entity);
void render_gameover();
void render_timer();
void de_render_ghost(ULONG32* base32, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]);
void render_non_default_ghost(ULONG32* base32, Ghost* ghost);
void refresh_screen(ULONG32* base32, Entities* entity);
void render_initial_timer(UCHAR8* base);
void render_pellet(UCHAR8* base8, Movement* move);



