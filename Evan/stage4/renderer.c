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
void render_pacman(Pacman* pacman, Ghost* ghost) {
    /*
    Amtoj
    1) Figure out pacman->delta_x and y based on direction 
    2) call move_pacman_position and pass in new 
    3) check return status -> if true, call handle_pacman_collision
    
    use check_next_cell(pacman->direction, pacman->x_cell_index, pacman->y_cell_index)*/
    UINT8 collision_type; 

    collision_type = check_collision(&ghost,&pacman,pacman->y,pacman->x);

    if (check_collision(&ghost,&pacman,pacman->y,pacman->x) == FALSE) {
        move_ghost_position(&pacman);
    }
    else {
         handle_pacman_collsion(collision_type);
    }
}
void render_ghost(Pacman* pacman,Ghost* ghost) {
    /*
    Amtoj
    1) Figure out ghost->delta_x and y based on direction 
    2) call move_ghost_position and pass in new
    3) check return status -> if true, call handle_pacman_collision
    
    
    Use check_next_cell(ghost->direction, ghost->x_cell_index, ghost->y_cell_index)*/
    if (check_collision(&pacman,&ghost,ghost->y,ghost->x) == FALSE) {
        move_ghost_position(&ghost);
    }
}
void render_gameover() {
    /*
    Leave it for now
    */
}
void render_timer(Timer* timer) {
    /*
    Evan
    every 70 clock ticks timer.second++*/
    timer->seconds++;
    if (timer->seconds == 60) {
        timer->seconds = 0;
        timer->minutes++;
    }
    if (timer->minutes < 10) {
        /*plot_letter(base8, timer->MS_digit_minutes, 0, '0');
        plot_letter(base8, timer->x, timer->y, timer->minutes);
        */
    }
    else {
       
    }
    /*plot_letter(base8, timer) */
    
}
void clear_sprite(UINT32* base, int x, int y) {
    /*
    Evan
    plot_bitmap_32(null_sprite_32)*/
    plot_bitmap_32(base, x, y, null_sprite_32, SPRITE_HEIGHT);
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
void render_tombstone(UINT32* base32, Tombstone* tombstone_object) {
    plot_bitmap_32(base32, tombstone_object->x, tombstone_object->y, tombstone, SPRITE_HEIGHT);
}
void de_render_ghost(UINT32* base32, Ghost* ghost) {
    plot_bitmap_32(base32, ghost->x, ghost->y, null_sprite_32, SPRITE_HEIGHT);
    kill_ghost(ghost);
}


