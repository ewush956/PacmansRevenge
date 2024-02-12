#include "renderer.h"
#include "model.h"
#include "bitmaps.h"
#include "RASTER.H"

void clock_tick_handle() {
    /*Called once per clock tick*/

    /*If pacman->current_cell +1 % 32 == 0 then update cell index based on current direction*/
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

}
void plot_map(UINT32* base, UINT32* map[][20]) {
    /*Called once at beggining of game*/
    int i, j, x, y;
    x = X_OFFSET;
    y = Y_OFFSET;
    for (i = 0; i < 3; i++) {
        for(j = 0; j < 19; j++) {
            plot_bitmap_32(base, x, y, map[i][j], SPRITE_HEIGHT);
            x += 32;
        }
        x = X_OFFSET;
        y += 32;
    }
}