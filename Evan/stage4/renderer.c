#include "renderer.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"

void clock_tick_handle() {
    /*Called once per clock tick*/

   /* If pacman->x or y position % 32 == 0 then update cell index based on current direction */
    /*

    move_packman();
    if (check_collision() != 0) {
        handle_collision();
    }
    */

}
void plot_map(UINT32* base) {
    /*Called once at beggining of game*/

    /*
    0 is a open square and 
    1 is a horizontal wall
    2 iS a vertical wall 
    3 is a left-down (LD)
    4 is RD
    5 is LU
    6 is UR (up -> right)
    7 is a single wall
    */   
    int i, j, x, y;
    UINT32* tile;
    UINT32* walls[] = {
	wall_horz, wall_vert, wall_LD, wall_DR, wall_UL, wall_UR
    };

    UINT16 tile_map[][MAP_TILE_LENGTH] = {

        {4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
        {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {2,0,4,1,1,1,0,7,0,7,0,1,1,1,1,3,0,2},
        {2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2},
        {2,0,2,0,4,3,0,4,0,0,3,0,4,3,0,2,0,2},
        {2,0,0,0,0,0,0,6,1,1,5,0,2,2,0,0,0,2},
        {2,0,2,0,6,5,0,0,0,0,0,0,6,5,0,2,0,2},
        {2,0,2,0,0,0,0,0,4,1,3,0,0,0,0,2,0,2},
        {2,0,6,1,1,1,1,0,6,1,5,0,1,1,1,5,0,2},
        {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5}
    };

    x = X_PIXEL_OFFSET;
    y = Y_PIXEL_OFFSET;
    
    for (i = 0; i < MAP_TILE_HEIGHT; i++) {
        for(j = 0; j < MAP_TILE_LENGTH; j++) {
            switch (tile_map[i][j]) {
            case 0:
                tile = null_sprite_32;
                break;
            case 1:
                tile = wall_horz;
                break;
            case 2:
                tile = wall_vert;
                break;
            case 3:
                tile = wall_LD;
                break;
            case 4:
                tile = wall_DR;
                break;
            case 5:
                tile = wall_UL;
                break;
            case 6:
                tile = wall_UR;
                break;
            case 7:
                tile = wall_single;
            
            default:
                tile = null_sprite_32;
                break;
            }
            plot_bitmap_32(base, x, y, tile, SPRITE_HEIGHT);
            x += 32;
        }
        x = X_PIXEL_OFFSET;
        y += 32;
    }
}

