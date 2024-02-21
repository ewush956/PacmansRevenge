#include "renderer.h"
#include "types.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"
#include "map_plot.c"

const ULONG32* default_pacman_sprites[4][7] = {
    {pac_1, pac_2, pac_3, pac_4, pac_3, pac_2},   /*UP*/
    {pac_1, pac_2, pac_3, pac_4, pac_3, pac_2},   /*DOWN*/
    {pac_1, pac_2, pac_3, pac_4, pac_3, pac_2},   /*LEFT*/
    {pac_1, pac_2, pac_3, pac_4, pac_3, pac_2}    /*RIGHT*/
};
const ULONG32* evil_pacman_sprites[4][7] = {
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4, evil_pac_3, evil_pac_2},   /*UP*/
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4, evil_pac_3, evil_pac_2},   /*DOWN*/
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4, evil_pac_3, evil_pac_2},   /*LEFT*/
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4, evil_pac_3, evil_pac_2}    /*RIGHT*/
};
const ULONG32* crying_ghost_sprites[4][2] = {
    {ghost_1_up, ghost_1_up},   /*UP*/
    {ghost_1_down, ghost_1_down},   /*DOWN*/
    {ghost_1_left, ghost_1_left},   /*LEFT*/
    {ghost_1_right, ghost_1_right}    /*RIGHT*/
};
const ULONG32* awkward_ghost_sprites[4][2] = {
    {ghost_2_up, ghost_2_up},   /*UP*/
    {ghost_2_down, ghost_2_down},   /*DOWN*/
    {ghost_2_left, ghost_2_left},   /*LEFT*/
    {ghost_2_right, ghost_2_right}    /*RIGHT*/
};
const ULONG32* cyclops_ghost_sprites[4][2] = {
    {ghost_3_up, ghost_3_up},   /*UP*/
    {ghost_3_down, ghost_3_down},   /*DOWN*/
    {ghost_3_left, ghost_3_left},   /*LEFT*/
    {ghost_3_right, ghost_3_right}    /*RIGHT*/
};
const ULONG32* moustache_ghost_sprites[4][2] = {
    {ghost_4_up, ghost_4_up},   /*UP*/
    {ghost_4_down, ghost_4_down},   /*DOWN*/
    {ghost_4_left, ghost_4_left},   /*LEFT*/
    {ghost_4_right, ghost_4_right}    /*RIGHT*/
};

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
void render_frame(ULONG32* base, Entities* entity) {

    render_pacman(base, &entity->pacman);
    render_ghosts(base, entity);
    render_timer(base, entity->timer);
}

void render_pacman(ULONG32* base32, Pacman* pacman) {

    if (pacman->is_evil == TRUE) {
        plot_bitmap_32(base32, pacman->x, pacman->y, evil_pac_sprites[pacman->current_frame][pacman->direction], SPRITE_HEIGHT);
    }
    else {
        plot_bitmap_32(base32, pacman->x, pacman->y, default_pacman_sprites[pacman->current_frame][pacman->direction], SPRITE_HEIGHT);
    }    /* pacman->current_frame++; */
}
void render_ghosts(ULONG32* base32, Entities* entity) {

    Ghost* awkward = entity->awkward_ghost;
    Ghost* moustache = entity->moustache_ghost;
    Ghost* crying = entity->crying_ghost;
    Ghost* cyclops = entity->cyclops_ghost;

    if (awkward->state == DEFAULT) {
        plot_bitmap_32(base32, awkward->x, awkward->y, awkward_ghost_sprites[awkward->current_frame][awkward->direction], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, awkward);
    }

    if (moustache->state == DEFAULT) {
        plot_bitmap_32(base32, moustache->x, moustache->y, moustache_ghost_sprites[moustache->current_frame][moustache->direction], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, moustache);
    }

    if (crying->state == DEFAULT) {
        plot_bitmap_32(base32, crying->x, crying->y, crying_ghost_sprites[crying->current_frame][crying->direction], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, crying);
    }

    if (cyclops->state == DEFAULT) {
        plot_bitmap_32(base32, cyclops->x, cyclops->y, cyclops_ghost_sprites[cyclops->current_frame][cyclops->direction], SPRITE_HEIGHT);
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
void clear_sprite(ULONG32* base, int x, int y) {
    /*
    Evan
    plot_bitmap_32(null_sprite_32)*/
    plot_bitmap_32(base, x, y, null_sprite_32, SPRITE_HEIGHT);
}
void de_render_ghost(ULONG32* base32, Ghost* ghost) {
    plot_bitmap_32(base32, ghost->x, ghost->y, null_sprite_32, SPRITE_HEIGHT);
    kill_ghost(ghost);

}
void render_non_default_ghost(ULONG32* base32, Ghost* ghost) {
    if (ghost->state == RUNNING) {
        plot_bitmap_32(base32, ghost->x, ghost->y, ghost_run, SPRITE_HEIGHT);
    }
    else if (ghost->state == FROZEN) {
        plot_bitmap_32(base32, ghost->x, ghost->y, ghost_freeze, SPRITE_HEIGHT);
    }

}

