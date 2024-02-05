#include "raster.h"
#include "TYPES.H"

void plot_bitmap_32(UINT32* base, int x, int y, const UINT32* bitmap, unsigned int height) {
    int row;
    UINT32* location = base + (y * 20) + (x >> 5);

    if (x >= 0 && x < (SCREEN_WIDTH - SPRITE_WIDTH) && y >= 0 && y < (SCREEN_HEIGHT - SPRITE_HEIGHT) ) {
        for (row = 0; row < height; row++) {
        
            *location |= bitmap[row] >> (x % SPRITE_WIDTH);     
            *(location + 1) |= bitmap[row] << (SPRITE_WIDTH - (x % SPRITE_WIDTH));
            location += 20;        
        }
    }
}
void plot_letter(UINT8* base, int x, int y, const UINT8* bitmap) {
    int row;
    UINT8* location = base + (y * 80) + (x >> 3);

    if (x >= 0 && x < (SCREEN_WIDTH - LETTER_WIDTH) && y >= 0 && y < (SCREEN_HEIGHT - LETTER_HEIGHT)) {
        for (row = 0; row < LETTER_HEIGHT; row++) {
        
            *location |= bitmap[row] >> (x % LETTER_WIDTH);     
            *(location + 1) |= bitmap[row] << LETTER_WIDTH - (x % LETTER_WIDTH);
            location += 80;       
        }
    }
}
void plot_screen(UINT32* base, const UINT32* bitmap) {
    return;
}