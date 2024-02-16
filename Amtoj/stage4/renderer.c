#include "renderer.h"
#include "types.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"


void render_map(UINT16* base, UINT16 tile_map[][MAP_TILE_LENGTH]) {
    /*Called once at beggining of game*/
  
    int i, j, x, y;
    x = X_PIXEL_OFFSET;
    y = Y_PIXEL_OFFSET;
    
    for (i = 0; i < MAP_TILE_HEIGHT; i++) {
        for(j = 0; j < MAP_TILE_LENGTH; j++) {
            switch (tile_map[i][j]) {
            case 1:
                plot_bitmap_16(base, x, y, wall_single_16, WALL_SIZE);
                break;
            default:
                break;
            }
            x += WALL_SIZE;
        }
        x = X_PIXEL_OFFSET;
        y += WALL_SIZE;
    }
}
void render_pacman(Pacman *pacman, Ghost *ghost) 
{

    return;
}
void render_ghost(Ghost* ghost) {
    /*
    Amtoj
    1) Figure out ghost->delta_x and y based on direction 
    2) call move_ghost_position and pass in new
    3) check return status -> if true, call handle_pacman_collision
    
    Use check_next_cell(ghost->direction, ghost->x_cell_index, ghost->y_cell_index)*/
}
void render_gameover() {
    /*
    Leave it for now 
    */
}

void clear_sprite(UINT32* base, int x, int y) {
    /*
    Evan
    plot_bitmap_32(null_sprite_32)*/
    plot_bitmap_32(base, x, y, null_sprite_32, SPRITE_HEIGHT);
}



