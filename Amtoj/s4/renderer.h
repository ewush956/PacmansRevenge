
#include "model.h"
#include "bitmaps.h"
#include "types.h"
/*#include "map_plot.c"*/

extern const UINT32 default_pac_sprites[][4];
extern const UINT32 evil_pac_sprites[][4];
extern const UINT32 crying_ghost_sprites[][4];
extern const UINT32 moustache_ghost_sprites[][4];
extern const UINT32 cyclops_ghost_sprites[][4];
extern const UINT32 awkward_ghost_sprites[][4];

typedef struct Xor {
    
    UINT32 value;
};


void render_map(UINT16* base, UINT16 tile_map[][MAP_TILE_LENGTH]);
void render_frame(UINT32* base, Entities* entity);
void render_pacman(Pacman* pacman, Ghost* ghost);
void render_ghost(Pacman* pacman, Ghost* ghost);
void render_gameover();
void render_timer();
UINT32 random_number_generator(Xor *xor);