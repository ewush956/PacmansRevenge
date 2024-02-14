#include "raster.h"
#include "TYPES.H"

/**
 * Plot a bitmap on the screen at the specified coordinates.
 *
 * @param base pointer to the base adress of the frame buffer
 * @param x x-coordinate of the top-left corner of the screen
 * @param y y-coordinate of the top-left corner of the screen
 * @param bitmap array of longs containing the bitmap data
 * @param height height of the bitmap
 */
void plot_bitmap_32(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height) {
    int row;
    int dx = x;
    int dy = y;
    UINT32* location = base + (y * LONGS_PER_ROW) + (x >> 5);

   /* if (x >= 0 && x <= (SCREEN_WIDTH - SPRITE_WIDTH) && y >= 0 && y <= (SCREEN_HEIGHT - SPRITE_HEIGHT) ) { */
        for (row = 0; row < height; row++) {
            if (x >= 0 && x <= (SCREEN_WIDTH - SPRITE_WIDTH) && dy >= 0 && y <= (SCREEN_HEIGHT - SPRITE_HEIGHT) ) {
                *location |= bitmap[row] >> (x % SPRITE_WIDTH);
                *(location + 1) |= bitmap[row] << (SPRITE_WIDTH - (x % SPRITE_WIDTH));
            }
            location += LONGS_PER_ROW;
            dy++; /*For bounds checking*/
            /* dx++; Can't get dx working :(*/
        }
    /*}*/
}
void plot_bitmap_16(UINT16* base, int x, int y, const UINT16 bitmap[], unsigned int height) {
    int row;
    int dy = y;
    UINT16* location = base + (y * WORDS_PER_ROW) + (x >> 4); 

    for (row = 0; row < height; row++) {
        if (x >= 0 && x <= (SCREEN_WIDTH - WALL_SIZE) && dy >= 0 && y <= (SCREEN_HEIGHT - WALL_SIZE)) {
            *location |= bitmap[row] >> (x % WALL_SIZE);
            *(location + 1) |= bitmap[row] << (16 - (x % WALL_SIZE)); 
        }
        location += WORDS_PER_ROW; 
        dy++; 
    }
}
/**
 * Plots a bitmap at the specified x, y position on the screen.
 *
 * @param base pointer to the base address of the frame buffer
 * @param x x-coordinate of the position
 * @param y y-coordinate of the position
 * @param bitmap array containing the bitmap data
 * @param height height of the bitmap
 */
void plot_bitmap_64(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height) {
    int row;
    UINT32* location = base + (y * LONGS_PER_ROW) + (x >> 5);

    if (x >= 0 && x <= (SCREEN_WIDTH - HITBOX_WIDTH) && y >= 0 && y <= (SCREEN_HEIGHT - height)) {
        for (row = 0; row <= height*2; row += 2) {
        
            *location |= bitmap[row] >> (x % SPRITE_WIDTH);     
            *(location + 1) |= bitmap[row] << (SPRITE_WIDTH - (x % SPRITE_WIDTH));

            *(location + 1) |= bitmap[row + 1] >> (x % SPRITE_WIDTH);
            *(location + 2) |= bitmap[row + 1] << (SPRITE_WIDTH - (x % SPRITE_WIDTH));

            location += LONGS_PER_ROW;        
        }
    }
}
/**
 * Plots a letter on the screen at the specified (x,y) coordinates.
 *
 * @param base pointer to the base of the frame buffer
 * @param x x-coordinate of the upper-left corner of the screen
 * @param y y-coordinate of the upper-left corner of the screen
 * @param bitmap array of bytes containing the bitmap of the letter
 * @param letter index of the letter in the bitmap array 
 */
void plot_letter(UINT8* base, int x, int y, const UINT8 bitmap[], unsigned int letter) {
    int row;
    int index = letter << 3;
    UINT8* location = base + (y * BYTES_PER_ROW) + (x >> 3);

    if (x >= 0 && x < (SCREEN_WIDTH - LETTER_WIDTH) && y >= 0 && y < (SCREEN_HEIGHT - LETTER_HEIGHT)) {
        for (row = index; row < index + 8; row++) {
        
            *location |= bitmap[row] >> (x % LETTER_WIDTH);     
            *(location + 1) |= bitmap[row] << LETTER_WIDTH - (x % LETTER_WIDTH);
            location += BYTES_PER_ROW;       
        }
    }
}
/**
 * Plots a 640 x 400 bitmap on the screen. 
 * Not complete
 * @param base pointer to the base adress of the frame buffer
 * @param bitmap array of longs containing the bitmap data
 */
void plot_screen(UINT32* base, const UINT32* bitmap) {
    return;
}
