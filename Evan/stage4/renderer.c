#include "renderer.h"
#include "types.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"
#include "map_plot.c"


void render_map(UINT16* base) {
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
void clock_tick_handle() {
    /*
    Evan
    Called 70 times per second, renders all sprites, determines states (next position/collision status, etc.)

    do stuff to figure out delta x,y then render sprite
    */

}
void render_sprite_32() {
    /*
    print pacman or ghost 32 at position passed into function*/
}
void render_pacman() {
    /*
    Amtoj
    1) Figure out pacman->delta_x and y based on direction 
    2) call move_pacman_position and pass in new 
    3) check return status -> if true, call handle_pacman_collision*/
}
void render_ghost() {
    /*
    Amtoj
    1) Figure out ghost->delta_x and y based on direction 
    2) call move_ghost_position and pass in new
    3) check return status -> if true, call handle_pacman_collision*/
}
void render_gameover() {
    /*
    Leave it for now
    */
}
void render_timer() {
    /*
    Evan
    every 70 clock ticks timer.second++*/
}
void clear_sprite(){
    /*
    Evan
    plot_bitmap_32(null_sprite_32)*/
}
bool check_next_cell(int dirrection, int x_cell_index, int y_cell_index){
    /*returns true if the next cell in corresponding dirrection has an an open path, false otherwise*/
    switch(dirrection) {
        case UP:
            if (cell_map[y_cell_index - 1][x_cell_index].open_path == FALSE) {
                return FALSE;
            }
            break;
        case DOWN:
            if (cell_map[y_cell_index + 1][x_cell_index].open_path == FALSE) {
                return FALSE;
            }
            break;
        case LEFT:
            if (cell_map[y_cell_index][x_cell_index - 1].open_path == FALSE) {
                return FALSE;
            }
            break;
        case RIGHT:
            if (cell_map[y_cell_index][x_cell_index + 1].open_path == FALSE) {
                return FALSE;
            }
            break;
        return TRUE;
    }
}

