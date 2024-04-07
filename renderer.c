#include "renderer.h"
#include "types.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"
#include "font.h"
#include "globals.h"

#include <stdio.h>
/*************************************************************
* Function: render_map
* Purpose: Initialize game map rendering by plotting tiles.
* Parameters:
*     - base: Pointer to frame buffers memory's base address.
*     - tile_map: 2D array of tile map layout.
* Details: Uses plot_bitmap_16 to render tiles based on tile_map.
*          This function is called once at the beginning of the game.
*************************************************************/
void render_map(ULONG32* base, UINT16 tile_map[][MAP_TILE_LENGTH]) {
    UINT16* base16 = (UINT16*)base;
    UCHAR8* base8 = (UCHAR8*)base; 
    int i, j, x, y;
    x = X_PIXEL_OFFSET;
    y = Y_PIXEL_OFFSET;
    
    for (i = 0; i < MAP_TILE_HEIGHT; i++) {
        for(j = 0; j < MAP_TILE_LENGTH; j++) {
            switch (tile_map[i][j]) {
            case 1:
                plot_bitmap_16(base16, x, y, wall_single_16, WALL_SIZE);
                break;
            case 0: 
                plot_8(base8, x + 12, y + 12, pellet, 8);
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

    UCHAR8* base8 = (UCHAR8*)base;

    Ghost* awk;
    Pacman* pacman = entity->pacman;
    Movement* crying = entity->crying_ghost->move;
    Movement* moustache = entity->moustache_ghost->move;
    Movement* awkward = entity->awkward_ghost->move;
    Movement* cyclops = entity->cyclops_ghost->move;


    int crying_x = crying->x_cell_index;
    int crying_y = crying->y_cell_index;
    int moustache_x = moustache->x_cell_index;
    int moustache_y = moustache->y_cell_index;
    int awkward_x = awkward->x_cell_index;
    int awkward_y = awkward->y_cell_index;
    int cyclops_x = cyclops->x_cell_index;
    int cyclops_y = cyclops->y_cell_index;
    
    render_timer(base8);
    clear_entities(base, pacman->move, crying, moustache,
                   awkward, cyclops); 

    render_ghosts(base, entity);
    render_pacman(base, pacman);

    render_pellet(base8, crying_x, crying_y, crying->direction);
    render_pellet(base8, moustache_x, moustache_y, moustache->direction);
    render_pellet(base8, awkward_x, awkward_y, awkward->direction);
    render_pellet(base8, cyclops_x, cyclops_y, cyclops->direction);
    render_pellet(base8, pacman->move->x_cell_index, pacman->move->y_cell_index, pacman->move->direction);
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

    Movement* move = pacman->move;
    UINT16 x = move->x;
    UINT16 y = move->y;

    UCHAR8 frame = pacman->current_frame;
    UCHAR8 direction = move->direction;

    if (pacman->state == EVIL) {
        plot_bitmap_32(base32, x, y, evil_pacman_sprites[direction][frame], SPRITE_HEIGHT);
    }
    else {
        plot_bitmap_32(base32, x, y, default_pacman_sprites[direction][frame], SPRITE_HEIGHT);
    }    
    
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

    Movement* awkward = entity->awkward_ghost->move;
    Movement* moustache = entity->moustache_ghost->move;
    Movement* crying = entity->crying_ghost->move;
    Movement* cyclops = entity->cyclops_ghost->move;

    Ghost* awkward_g = entity->awkward_ghost;
    Ghost* moustache_g = entity->moustache_ghost;
    Ghost* crying_g = entity->crying_ghost;
    Ghost* cyclops_g = entity->cyclops_ghost;
    
    if (derender_awkward_flag == TRUE) 
        de_render_ghost(base32, awkward_g, cell_map);
    else if (entity->awkward_ghost->state == DEFAULT) 
        plot_bitmap_32(base32, awkward->x, awkward->y, awkward_ghost_sprites[awkward->direction][awkward_g->current_frame], SPRITE_HEIGHT);
    else 
        render_non_default_ghost(base32, awkward_g);
    
    if (derender_moustache_flag == TRUE) 
        de_render_ghost(base32, moustache_g, cell_map);
    else if (entity->moustache_ghost->state == DEFAULT) 
        plot_bitmap_32(base32, moustache->x, moustache->y, moustache_ghost_sprites[moustache->direction][moustache_g->current_frame], SPRITE_HEIGHT);
    else 
        render_non_default_ghost(base32, moustache_g);

    if (derender_crying_flag == TRUE)
        de_render_ghost(base32, crying_g, cell_map);
    else if (entity->crying_ghost->state == DEFAULT) 
        plot_bitmap_32(base32, crying->x, crying->y, crying_ghost_sprites[crying->direction][crying_g->current_frame], SPRITE_HEIGHT);
    else 
        render_non_default_ghost(base32, crying_g);
    
    if (derender_cyclops_flag == TRUE)
        de_render_ghost(base32, cyclops_g, cell_map);
    else if (entity->cyclops_ghost->state == DEFAULT) 
        plot_bitmap_32(base32, cyclops->x, cyclops->y, cyclops_ghost_sprites[cyclops->direction][cyclops_g->current_frame], SPRITE_HEIGHT);
    else 
        render_non_default_ghost(base32, cyclops_g);
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
        
    UCHAR8 pacman_cell_x = pacman.move->x_cell_index;
    UCHAR8 pacman_cell_y = pacman.move->y_cell_index;
    UCHAR8 pacman_direction = pacman.move->direction;

    UCHAR8 ghost_cell_x = ghost->move->x_cell_index;
    UCHAR8 ghost_cell_y = ghost->move->y_cell_index;

    UCHAR8 ghost_direction = ghost->move->direction;

    switch (ghost_direction) {
        case DOWN: 
                ghost->move->x = (ghost->move->x_cell_index << 4);
                ghost->move->last_x = ghost->move->x;
                ghost->move->last_last_x = ghost->move->x;
            if (cell_map[ghost_cell_y - 2][ghost_cell_x].open_path == TRUE) {
                ghost->move->y = ((ghost->move->y_cell_index + 2) << 4);
            } else {
                ghost->move->y = ((ghost->move->y_cell_index + 1) << 4);
            }
                ghost->move->last_y = ghost->move->y;
                ghost->move->last_last_y = ghost->move->y;
            break;
        case RIGHT:
            /*if (cell_map[ghost_cell_y][ghost_cell_x + 2].open_path == TRUE) {*/

                ghost->move->x = ((ghost->move->x_cell_index + 1)<< 4);
                ghost->move->last_x = ghost->move->x;
                ghost->move->last_last_x = ghost->move->x;

                ghost->move->y = ((ghost->move->y_cell_index + 1) << 4);
                ghost->move->last_y = ghost->move->y;
                ghost->move->last_last_y = ghost->move->y;
            /*}*/
            break;
    }
    set_derender_ghost_flag(ghost, FALSE);
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
    Movement* move = ghost->move;
    UCHAR8 frame = ghost->current_frame;

    if (ghost->state == RUNNING) {
        plot_bitmap_32(base32, move->x, move->y, running_ghost_sprites[move->direction][frame], SPRITE_HEIGHT);
    }
    /*
    else if (ghost->state == FROZEN) {
        plot_bitmap_32(base32, move->x, move->y, frozen_ghost_sprites[move->direction][frame], SPRITE_HEIGHT);
    }
    */
    else {
        clear_bitmap_32(base32, move->x, move->y, SPRITE_HEIGHT);
        /*clear_bitmap_32(base32, move->last_last_x, move->last_last_y, SPRITE_HEIGHT);*/
        plot_bitmap_32(base32, move->x, move->y, tombstone, SPRITE_HEIGHT);
    }
}
/*BOTH FUNCTIONS BELOW ARE INCOMPLETE*/
void render_gameover() {
    /* Renderes game over screen, we arent sure how to do that yet.*/
}
void render_timer(UCHAR8* base8) {

    plot_letter(base8, TIMER_MS_X, TIMER_Y, font, timer.MS_digit_ascii);
    plot_letter(base8, TIMER_LS_X, TIMER_Y, font, timer.LS_digit_ascii);
    
}
void render_initial_timer(UCHAR8* base) {

    int start_x = 280;
    int y = 4;
/*
    plot_string(base, start_x, y, font, "Time: 60");
    */
    plot_string(base, start_x, y, font, "Time: 99\0");
/*    plot_letter(base, start_x, y, font, 'T');
    plot_letter(base, start_x + LETTER_WIDTH, y, font, 'i');
    plot_letter(base, start_x + (LETTER_WIDTH * 2), y, font, 'm');
    plot_letter(base, start_x + (LETTER_WIDTH * 3), y, font, 'e');
    plot_letter(base, start_x + (LETTER_WIDTH * 4), y, font, ':');
    plot_letter(base, start_x + (LETTER_WIDTH * 5), y, font, ' ');
    plot_letter(base, start_x + (LETTER_WIDTH * 6), y, font, '6');
    plot_letter(base, start_x + (LETTER_WIDTH * 7), y, font, '0');
    */
}
/********************************************************************
* Clears the previous positions of entities from the specified base buffer.**
* @param base32   The base buffer to clear.
* @param pacman   The movement data for Pacman.
* @param crying   The movement data for the crying ghost.
* @param moustache   The movement data for the moustache ghost.
* @param awkward   The movement data for the awkward ghost.
* @param cyclops   The movement data for the cyclops ghost.
*******************************************************************/
void clear_entities(ULONG32* base32, Movement* pacman, Movement* crying,
                    Movement* moustache, Movement* awkward, Movement* cyclops) {


    clear_bitmap_32(base32, awkward->last_last_x, awkward->last_last_y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, moustache->last_last_x, moustache->last_last_y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, cyclops->last_last_x, cyclops->last_last_y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, crying->last_last_x, crying->last_last_y, SPRITE_HEIGHT);
    
    clear_bitmap_32(base32, pacman->last_last_x, pacman->last_last_y, SPRITE_HEIGHT);
    clear_bitmap_32(base32, pacman->last_x, pacman->last_y, SPRITE_HEIGHT);
    
}
/*
void render_pellet(UCHAR8* base8, Movement* move) {
*/
void render_pellet(UCHAR8* base8, UINT16 x_cell_index, UINT16 y_cell_index, UCHAR8 direction) {


    int pellet_plot_x = (x_cell_index << 4) + 12;
    /*int pellet_plot_y = (y_cell_index << 4) + 12 + Y_PIXEL_OFFSET; */
    int pellet_plot_y = (y_cell_index << 4) + 28;

    
    if (direction == LEFT) {
       render_pellet_helper_left(base8,x_cell_index,y_cell_index,pellet_plot_x,pellet_plot_y);
    }
    else if (direction == RIGHT) {
        render_pellet_helper_right(base8,x_cell_index,y_cell_index,pellet_plot_x,pellet_plot_y);
    }
    else if (direction == DOWN) {
        render_pellet_helper_down(base8,x_cell_index,y_cell_index,pellet_plot_x,pellet_plot_y);
    }
    else if (direction == UP) {
        render_pellet_helper_up(base8,x_cell_index,y_cell_index,pellet_plot_x,pellet_plot_y);
    }
    
}
void render_pellets(ULONG32* base32, Entities* all) {
    UCHAR8 *base8 = (UCHAR8*)base32;
}
void render_mouse(UINT16* base16)
{
    UCHAR8 height = 16;
    plot_mouse(base16,global_mouse_x,global_mouse_y,mouse_cursor);
    
}
void render_pellet_helper_left(UCHAR8* base8, UINT16 x_cell_index, UINT16 y_cell_index, int pellet_plot_x, int pellet_plot_y)
{
    int pellet_right_2  = pellet_plot_x + 32;
    int pellet_down_1   = pellet_plot_y + 16;
    int pellet_down_2   = pellet_plot_y + 32;
    int pellet_up_1     = pellet_plot_y - 16;
    
    if (cell_map[y_cell_index][x_cell_index + 2].has_pellet == TRUE) {
        plot_8(base8, pellet_right_2, pellet_plot_y, pellet, 8);
    }
    if (cell_map[y_cell_index + 1][x_cell_index + 2].has_pellet == TRUE) {
        plot_8(base8, pellet_right_2, pellet_down_1, pellet, 8);
    }
    if (cell_map[y_cell_index - 1][x_cell_index + 2].has_pellet == TRUE) {
        plot_8(base8, pellet_right_2, pellet_up_1, pellet, 8);
    }
    if (cell_map[y_cell_index + 2][x_cell_index + 2].has_pellet == TRUE) {
        plot_8(base8, pellet_right_2, pellet_down_2, pellet, 8);
    }
}
void render_pellet_helper_right(UCHAR8* base8, UINT16 x_cell_index, UINT16 y_cell_index, int pellet_plot_x, int pellet_plot_y)
{
    int pellet_left_2   = pellet_plot_x - 32;
    int pellet_left_1   = pellet_plot_x - 16;

    int pellet_down_1   = pellet_plot_y + 16;
    int pellet_down_2   = pellet_plot_y + 32;
    int pellet_up_1     = pellet_plot_y - 16;

    int x_cell_left     = x_cell_index - 1;
    int x_cell_left_2   = x_cell_index - 2;
    int y_cell_down     = y_cell_index + 1;
    int y_cell_up       = y_cell_index - 1;   
    int y_cell_down_2   = y_cell_index + 2;

    if (cell_map[y_cell_index][x_cell_left].has_pellet == TRUE) {
        plot_8(base8, pellet_left_1, pellet_plot_y, pellet, 8);
    }
    if (cell_map[y_cell_down][x_cell_left].has_pellet == TRUE) {
        plot_8(base8, pellet_left_1, pellet_down_1, pellet, 8);
    }
    if (cell_map[y_cell_up][x_cell_left].has_pellet == TRUE) {
        plot_8(base8, pellet_left_1, pellet_up_1, pellet, 8);
    }
    if (cell_map[y_cell_down_2][x_cell_left_2].has_pellet == TRUE) {
        plot_8(base8, pellet_left_2, pellet_down_2, pellet, 8);
    }
}

void render_pellet_helper_up(UCHAR8* base8, UINT16 x_cell_index, UINT16 y_cell_index, int pellet_plot_x, int pellet_plot_y)
{
    int pellet_left_2   = pellet_plot_x - 32;
    int pellet_left_1   = pellet_plot_x - 16;
    int pellet_down_2   = pellet_plot_y + 32;
    int pellet_right_2  = pellet_plot_x + 32;
    int pellet_right_1  = pellet_plot_x + 16;
    int pellet_down_3   = pellet_plot_y + 48;
    int x_cell_left     = x_cell_index - 1;
    int x_cell_left_2   = x_cell_index - 2;
    int x_cell_right    = x_cell_index + 1;
    int x_cell_right_2  = x_cell_index + 2;
    int y_cell_down_2   = y_cell_index + 2;
    int y_cell_down_3   = y_cell_index + 3;

    if (cell_map[y_cell_down_2][x_cell_index].has_pellet == TRUE) 
        plot_8(base8, pellet_plot_x, pellet_down_2, pellet, 8);

    if (cell_map[y_cell_down_2][x_cell_right].has_pellet == TRUE) 
        plot_8(base8, pellet_right_1, pellet_down_2, pellet, 8);

    if (cell_map[y_cell_down_2][x_cell_left].has_pellet == TRUE) 
        plot_8(base8, pellet_left_1, pellet_down_2, pellet, 8);

    if (cell_map[y_cell_down_3][x_cell_left].has_pellet == TRUE)
        plot_8(base8, pellet_left_1, pellet_down_3, pellet, 8);

    if (cell_map[y_cell_down_3][x_cell_right].has_pellet == TRUE)
        plot_8(base8, pellet_right_1, pellet_down_3, pellet, 8);  

    if (cell_map[y_cell_down_2][x_cell_left_2].has_pellet == TRUE) 
        plot_8(base8, pellet_left_2, pellet_down_2, pellet, 8); 

    if (cell_map[y_cell_down_2][x_cell_right_2].has_pellet == TRUE)
        plot_8(base8, pellet_right_2, pellet_down_2, pellet, 8);
}

void render_pellet_helper_down(UCHAR8* base8, UINT16 x_cell_index, UINT16 y_cell_index, int pellet_plot_x, int pellet_plot_y)
{
    int x_cell_left     = x_cell_index - 1;
    int x_cell_right    = x_cell_index + 1;
    int x_cell_right_2  = x_cell_index + 2;
    int y_cell_up       = y_cell_index - 1;   
    int pellet_left_1   = pellet_plot_x - 16;
    int pellet_up_1     = pellet_plot_y - 16;
    int pellet_right_2  = pellet_plot_x + 32;
    int pellet_right_1  = pellet_plot_x + 16;

    if (cell_map[y_cell_up][x_cell_index].has_pellet == TRUE) {
        plot_8(base8, pellet_plot_x, pellet_up_1, pellet, 8);
    }
    if (cell_map[y_cell_up][x_cell_right].has_pellet == TRUE) {
        plot_8(base8, pellet_right_1, pellet_up_1, pellet, 8);
    }
    if (cell_map[y_cell_up][x_cell_left].has_pellet == TRUE) {
        plot_8(base8, pellet_left_1, pellet_up_1, pellet, 8);
    }
    if (cell_map[y_cell_up][x_cell_right_2].has_pellet == TRUE) {
        plot_8(base8, pellet_right_2, pellet_up_1, pellet, 8);
    }
}

