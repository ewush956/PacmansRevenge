#include "struct.h"
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
void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height) {
    int row;
    ULONG32* location = base + (y * LONGS_PER_ROW) + (x >> 5);

    if (x >= 0 && x <= (SCREEN_WIDTH - SPRITE_WIDTH) && y >= 0 && y <= (SCREEN_HEIGHT - SPRITE_HEIGHT) ) {
        for (row = 0; row < height; row++) {
        
            *location |= bitmap[row] >> (x % SPRITE_WIDTH);     
            *(location + 1) |= bitmap[row] << (SPRITE_WIDTH - (x % SPRITE_WIDTH));
            location += LONGS_PER_ROW;        
        }
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
void plot_bitmap_64(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height) {
    int row;
    ULONG32* location = base + (y * LONGS_PER_ROW) + (x >> 5);

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
void plot_letter(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int letter) {
    int row;
    int index = letter << 3;
    UCHAR8* location = base + (y * BYTES_PER_ROW) + (x >> 3);

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
void plot_screen(ULONG32* base, const ULONG32* bitmap) {
    return;
}
/**
 * Clears the screen by clearing each pixel in the frame buffer.
 *
 * @param base Pointer to the base adress of the frame buffer
 
void clear_screen_c(ULONG32* base) {

    const ULONG32 zero = 0;
    int row, col;
    ULONG32* location = base;

        for (row = 0; row < SCREEN_WIDTH; row++) {

            for (col = 0; col < LONGS_PER_ROW; col++) {
        
                *location = zero;     
                *(location + col) = zero;  
            } 
            location += LONGS_PER_ROW;     
        }
}
*/