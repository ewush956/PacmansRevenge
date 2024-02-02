#include "raster.h"

void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32* bitmap, unsigned int height) {
    int row;
    ULONG32* location = base + (y * 20) + (x >> 5);

    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        for (row = 0; row < height; row++) {
        
            *location |= bitmap[row] >> (x % SPRITE_WIDTH);     
            *(location + 1) |= bitmap[row] << SPRITE_WIDTH - (x % SPRITE_WIDTH);
            location += 20;
        
        }
    }
}