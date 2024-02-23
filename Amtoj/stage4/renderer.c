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
void render_frame(ULONG32* base, Entities* entity) {

    render_pacman(base, entity->pacman);
    render_ghosts(base, entity);
    render_timer(base, entity->timer);
}


void render_pacman(ULONG32* base32, Pacman* pacman) {

    if (pacman->is_evil == TRUE) {
        plot_bitmap_32(base32, pacman->x, pacman->y, evil_pacman_sprites[pacman->current_frame][pacman->move->direction], SPRITE_HEIGHT);
    }
    else {
        plot_bitmap_32(base32, pacman->x, pacman->y, default_pacman_sprites[pacman->current_frame][pacman->move->direction], SPRITE_HEIGHT);
    }    /* pacman->current_frame++; */
}
void render_ghosts(ULONG32* base32, Entities* entity) {

    Ghost* awkward = entity->awkward_ghost;
    Ghost* moustache = entity->moustache_ghost;
    Ghost* crying = entity->crying_ghost;
    Ghost* cyclops = entity->cyclops_ghost;
    
    if (awkward->state == DEFAULT) {
        plot_bitmap_32(base32, awkward->move->x, awkward->move->y, awkward_ghost_sprites[awkward->current_frame][awkward->move->direction], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, awkward);
    }

    if (moustache->state == DEFAULT) {
        plot_bitmap_32(base32, moustache->x, moustache->y, moustache_ghost_sprites[moustache->current_frame][moustache->move->direction], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, moustache);
    }

    if (crying->state == DEFAULT) {
        plot_bitmap_32(base32, crying->move->x, crying->move->y, crying_ghost_sprites[crying->current_frame][crying->direction], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, crying);
    }

    if (cyclops->state == DEFAULT) {
        plot_bitmap_32(base32, cyclops->move->x, cyclops->move->y, cyclops_ghost_sprites[cyclops->current_frame][cyclops->move->direction], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, cyclops);
    }
    
}
void render_gameover() {
    /* Renderes game over screen, we arent sure how to do that yet.*/
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
void clr_sprite(ULONG32* base, int x, int y) {
    /*
    Evan
    plot_bitmap_32(null_sprite_32)*/
    plot_bitmap_32(base, x, y, null_sprite_32, SPRITE_HEIGHT);
}
void de_render_ghost(ULONG32* base32, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]) {
    plot_bitmap_32(base32, ghost->x, ghost->y, null_sprite_32, SPRITE_HEIGHT);
    kill_ghost(ghost, cell_map);

}
void render_non_default_ghost(ULONG32* base32, Ghost* ghost) {
    if (ghost->state == RUNNING) {
        plot_bitmap_32(base32, ghost->x, ghost->y, ghost_run, SPRITE_HEIGHT);
    }
    else if (ghost->state == FROZEN) {
        plot_bitmap_32(base32, ghost->x, ghost->y, ghost_freeze, SPRITE_HEIGHT);
    }

}

