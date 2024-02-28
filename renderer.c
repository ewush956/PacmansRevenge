#include "renderer.h"
#include "types.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"
#include "font.h"
/*************************************************************
* Function: render_map
* Purpose: Initialize game map rendering by plotting tiles.
* Parameters:
*     - base: Pointer to frame buffers memory's base address.
*     - tile_map: 2D array of tile map layout.
* Details: Uses plot_bitmap_16 to render tiles based on tile_map.
*          This function is called once at the beginning of the game.
*************************************************************/
void render_map(UINT16* base, UINT16 tile_map[][MAP_TILE_LENGTH]) {
    int i, j, x, y;
    x = X_PIXEL_OFFSET;
    y = Y_PIXEL_OFFSET;
    
    for (i = 0; i < MAP_TILE_HEIGHT; i++) {
        for(j = 0; j < MAP_TILE_LENGTH; j++) {
            switch (tile_map[i][j]) {
            case 1:
                plot_bitmap_16(base, x, y, wall_single_16, WALL_SIZE);
                break;
            }
            x += WALL_SIZE;
        }
        x = X_PIXEL_OFFSET;
        y += WALL_SIZE;
    } 
}
/*************************************************************
* Function: render_frame
* Purpose: Renders a single frame of the game, updating the 
*          display with current game state visuals.
* Parameters:
*     - base: Pointer to frame buffers memory's base address.
*     - entity: Pointer to the Entities structure.
* Details: This function updates the game's display based on 
*          the current state of the game world, player 
*          positions, and any other dynamic elements. It 
*          might call other functions to draw specific 
*          game elements like characters, enemies, and 
*          terrain.
*************************************************************/
void render_frame(ULONG32* base, Entities* entity) {

    render_pacman(base, entity->pacman);
    render_ghosts(base, entity);
    render_timer(base, entity->timer);
}
/*************************************************************
* Function: render_pacman
* Purpose: Renders Pacman's current state to the screen.
* Parameters: 
*     - ULONG32* base32 - Base address for frame buffer,
*     - Pacman* pacman - Pointer to the Pacman structure.
* Details: This function draws Pacman at its current position,
*          orientation, and state, using the provided base address
*          for rendering operations. 
*************************************************************/
void render_pacman(ULONG32* base32, Pacman* pacman) {

    if (pacman->state == EVIL) {
        plot_bitmap_32(base32, pacman->move->x, pacman->move->y, evil_pacman_sprites[pacman->move->direction][pacman->current_frame], SPRITE_HEIGHT);
    }
    else {
        plot_bitmap_32(base32, pacman->move->x, pacman->move->y, default_pacman_sprites[pacman->move->direction][pacman->current_frame], SPRITE_HEIGHT);
    }    /* pacman->current_frame++; */
}
/*************************************************************
* Function: render_ghosts
* Purpose: Renders all ghosts' current states to the screen.
* Parameters: ULONG32* base32 - Pointer to the frame buffer's base address,
              Entities* entity - Pointer to the entities structure containing ghost data.
* Details: This function iterates through the ghost entities and draws each
*          one at its current position and state on the screen using the frame buffer's
*          base address. 
*************************************************************/
void render_ghosts(ULONG32* base32, Entities* entity) {

    Ghost* awkward = entity->awkward_ghost;
    Ghost* moustache = entity->moustache_ghost;
    Ghost* crying = entity->crying_ghost;
    Ghost* cyclops = entity->cyclops_ghost;
    
    if (awkward->state == DEFAULT) {
        plot_bitmap_32(base32, awkward->move->x, awkward->move->y, awkward_ghost_sprites[awkward->move->direction][awkward->current_frame], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, awkward);
    }

    if (moustache->state == DEFAULT) {
        plot_bitmap_32(base32, moustache->move->x, moustache->move->y, moustache_ghost_sprites[moustache->move->direction][moustache->current_frame], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, moustache);
    }

    if (crying->state == DEFAULT) {
        plot_bitmap_32(base32, crying->move->x, crying->move->y, crying_ghost_sprites[crying->move->direction][crying->current_frame], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, crying);
    }

    if (cyclops->state == DEFAULT) {
        plot_bitmap_32(base32, cyclops->move->x, cyclops->move->y, cyclops_ghost_sprites[cyclops->move->direction][cyclops->current_frame], SPRITE_HEIGHT);
    } else {
        render_non_default_ghost(base32, cyclops);
    }
}
/*************************************************************
* Function: de_render_ghost
* Purpose: Removes the ghost's sprite from its last position and marks its current position with a tombstone.
* Parameters: ULONG32* base32 - Pointer to the frame buffer's base address,
*             Ghost* ghost - Pointer to the ghost structure to be de-rendered,
*             Cell cell_map[][MAP_TILE_LENGTH] - The game's cell map for reference.
* Details: This function clears the ghost's sprite from its previous position using the
*          clear_bitmap_32 function. Then, it plots a tombstone bitmap at the ghost's current
*          cell position to indicate where it was caught or removed from the game.
*************************************************************/
void de_render_ghost(ULONG32* base32, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH]) {
    int tombstone_y = (ghost->move->y_cell_index  * PIXELS_PER_CELL) + Y_PIXEL_OFFSET;
    int tombstone_x = ghost->move->x_cell_index  * PIXELS_PER_CELL;

    clear_bitmap_32(base32, ghost->move->x, ghost->move->y, SPRITE_HEIGHT);
    plot_bitmap_32(base32, tombstone_x, tombstone_y, tombstone, SPRITE_HEIGHT);
}
/*************************************************************
* Function: render_non_default_ghost
* Purpose: Renders a ghost in a non-default state, such as RUNNING or FROZEN.
* Parameters: ULONG32* base32 - Pointer to the frame buffer's base address,
*             Ghost* ghost - Pointer to the ghost structure.
* Details: Depending on the ghost's state, this function renders the ghost with
*          a specific sprite (RUNNING or FROZEN) at its current position.
*          - RUNNING state uses the ghost_run sprite.
*          - FROZEN state uses the ghost_freeze sprite.
*************************************************************/
void render_non_default_ghost(ULONG32* base32, Ghost* ghost) {
    if (ghost->state == RUNNING) {
        plot_bitmap_32(base32, ghost->move->x, ghost->move->y, running_ghost_sprites[ghost->move->direction][ghost->current_frame], SPRITE_HEIGHT);
    }
    else if (ghost->state == FROZEN) {
        plot_bitmap_32(base32, ghost->move->x, ghost->move->y, frozen_ghost_sprites[ghost->move->direction][ghost->current_frame], SPRITE_HEIGHT);
    }
    else {
        plot_bitmap_32(base32, ghost->move->x, ghost->move->y, tombstone, SPRITE_HEIGHT);
    }
}
/*BOTH FUNCTIONS BELOW ARE INCOMPLETE*/
void render_gameover() {
    /* Renderes game over screen, we arent sure how to do that yet.*/
}
/*This code is incomplete. No timer functionality has been added yet.*/
void render_timer(Timer* timer) {

}
void refresh_screen(ULONG32* base32, Entities* entity) {
    /*removes all entities from the screen*/
    clear_bitmap_32(base32, entity->pacman->move->x, entity->pacman->move->y, SPRITE_HEIGHT);    
    clear_bitmap_32(base32, entity->crying_ghost->move->x, entity->crying_ghost->move->y, SPRITE_HEIGHT);    
    clear_bitmap_32(base32, entity->moustache_ghost->move->x, entity->moustache_ghost->move->y, SPRITE_HEIGHT);    
    clear_bitmap_32(base32, entity->awkward_ghost->move->x, entity->awkward_ghost->move->y, SPRITE_HEIGHT);    
    clear_bitmap_32(base32, entity->cyclops_ghost->move->x, entity->cyclops_ghost->move->y, SPRITE_HEIGHT);
}
void render_initial_timer(UCHAR8* base) {
    int start_x = 280;
    int y = 4;

    plot_string(base, start_x, y, font, "Time: 00:00");
}
void clear_entities(ULONG32* base32, Entities* entity) {
                clear_bitmap_32(base32, entity->pacman->move->x, entity->pacman->move->y, SPRITE_HEIGHT); 
                clear_bitmap_32(base32, entity->crying_ghost->move->x, entity->crying_ghost->move->y, SPRITE_HEIGHT);
                clear_bitmap_32(base32, entity->moustache_ghost->move->x, entity->moustache_ghost->move->y, SPRITE_HEIGHT);
                clear_bitmap_32(base32, entity->awkward_ghost->move->x, entity->awkward_ghost->move->y, SPRITE_HEIGHT);
                clear_bitmap_32(base32, entity->cyclops_ghost->move->x, entity->cyclops_ghost->move->y, SPRITE_HEIGHT);
}
