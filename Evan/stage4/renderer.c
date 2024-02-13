#include "renderer.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"

void clock_tick_handle() {
    /*Called once per clock tick*/

   /* If pacman->current_cell % 32 == 0 then update cell index based on current direction */
    switch(input)
	{
		case 'w': pacman -> delta_y = 1; 			/* UP*/
			break;
				
		case 'a': pacman -> delta_x = -1;			/*Left*/
			break;
				
		case 's': pacman -> delta_y = -1;			/*Down*/
			break;
				
		case 'd': pacman -> delta_x = 1;			/* Right*/
			break;

		default:
			/*printf("Invalid input\n");*/
			break;
	}
    move_packman();
    if (check_collision() != 0) {
        handle_collision();
    }

}
void plot_map(UINT32* base, UINT32* map[][20]) {
    /*Called once at beggining of game*/
    UINT32* walls[] = {
	wall
};

    }
        UINT16 tile_map[][MAP_TILE_LENGTH] = {

            {4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
            {2,0,4,1,1,1,0,1,0,1,0,1,1,1,1,3,0,2},
            {2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2},
            {2,0,2,0,4,3,0,4,0,0,3,0,4,3,0,2,0,2},
            {2,0,0,0,0,0,0,6,1,1,5,0,2,2,0,0,0,2},
            {2,0,2,0,6,5,0,0,0,0,0,0,6,5,0,2,0,2},
            {2,0,2,0,0,0,0,0,4,1,3,0,0,0,0,2,0,2},
            {2,0,6,1,1,1,1,0,6,1,5,0,1,1,1,5,0,2},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
            {6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5}
    };
    int i, j, x, y;
    x = X_PIXEL_OFFSET;
    y = Y_PIXEL_OFFSET;
    
    for (i = 0; i < 3; i++) {
        for(j = 0; j < 19; j++) {
            plot_bitmap_32(base, x, y, map[i][j], SPRITE_HEIGHT);
            x += 32;
        }
        x = X_OFFSET;
        y += 32;
    }
}

void init_game() {
    /*Called once at beggining of game*/
    init_map_cells(map);
    init_ghost_paths();
    plot_map(base, map);
    plot_bitmap_32(base, pacman->x, pacman->y, pacman->current_cell, SPRITE_HEIGHT);
}
