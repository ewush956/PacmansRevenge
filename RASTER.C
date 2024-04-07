#include <osbind.h>
#include "raster.h"
#include "TYPES.H"
#include "font.h"

volatile UCHAR8* ptr_to_highbyte = VIDEO_ADDR_HIGH;
volatile UCHAR8* ptr_to_midbyte  = VIDEO_ADDR_MID;


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
    int dx = x;
    int dy = y;
    ULONG32* location = base + (y * LONGS_PER_ROW) + (x >> 5);
            if (x >= 0 && x <= (SCREEN_WIDTH - SPRITE_WIDTH) && dy >= 0 && y <= (SCREEN_HEIGHT - SPRITE_HEIGHT) ) {
        for (row = 0; row < height; row++) {
                *location |= bitmap[row] >> (x & 31);
                *(location + 1) |= bitmap[row] << (SPRITE_WIDTH - (x & 31));
            location += LONGS_PER_ROW;
            dy++; /*For bounds checking*/
            }
            /* dx++; Can't get dx working :(*/
        }
}
/******************************************************************************
 * Function: clear_bitmap
 * does NOT clear outer walls
******************************************************************************/
void clear_bitmap_32(ULONG32* base, int x, int y, unsigned int height) {
    int row;
    int dy = y;
    ULONG32* location = base + (y * LONGS_PER_ROW) + (x >> 5);
    ULONG32 mask1, mask2;

    if (x >= 16 && x <= (SCREEN_WIDTH - SPRITE_WIDTH - 16) && y >= 16 && y <= (SCREEN_HEIGHT - SPRITE_HEIGHT - 16)) {
        for (row = 0; row < height; row++) {

            mask1 = ~(0xFFFFFFFF >> (x & 31));
            mask2 = ~(0xFFFFFFFF << (SPRITE_WIDTH - (x & 31)));

            *location &= mask1;
            if ((x & 31) + SPRITE_WIDTH > 32) {
                *(location + 1) &= mask2;
            }
            location += LONGS_PER_ROW; 
        }
    }
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

void plot_mouse(UINT16 *base, int x, int y, const UINT16 bitmap[]) {

    int row;
    int dy = y;
    int height = 19;
    UINT16* location = base + (y * WORDS_PER_ROW) + (x >> 4); 

    for (row = 0; row < height; row++) {
        if (x >= 0 && x <= (SCREEN_WIDTH - WALL_SIZE) && dy >= 0 && y <= (SCREEN_HEIGHT - WALL_SIZE)) {
            *location ^= bitmap[row] >> (x % WALL_SIZE);
            *(location + 1) ^= bitmap[row] << (16 - (x % WALL_SIZE)); 
        }
        location += WORDS_PER_ROW; 
        dy++; 
    }
}

void restore_mouse_background(ULONG32* base32, ULONG32 background[], int x, int y)
{   
    int i;
    
    ULONG32* location = base32 + (y * 20) + (x >> 5);
    ULONG32* splash = background + (y * 20) + (x >> 5);

    for (i = 0; i < SPRITE_WIDTH; i++)
    {
        *location++ = *splash++;       
        *location = *splash;
        location += LONGS_PER_ROW - 1;
        splash += LONGS_PER_ROW - 1;
    }
}

/******************
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
void plot_8(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int height) {
    int row;
    int dx = x;
    int dy = y;
    UCHAR8* location = base + (y * BYTES_PER_ROW) + (x >> 3); 

    if (x >= 0 && x < SCREEN_WIDTH && dy >= 0 && dy < SCREEN_HEIGHT) {
        for (row = 0; row < height; row++) {
            *location |= bitmap[row] >> (x & 7);     
            *(location + 1) |= bitmap[row] << 8 - (x & 7);
            location += BYTES_PER_ROW;     
        }
    }
}
/*****************************************************************************
 * Plots a letter on the screen at the specified (x,y) coordinates.
 *
 * @param base pointer to the base of the frame buffer
 * @param x x-coordinate of the upper-left corner of the screen
 * @param y y-coordinate of the upper-left corner of the screen
 * @param bitmap array of bytes containing the bitmap of the letter
 * @param letter index of the letter in the bitmap array 
 */
void plot_letter(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int letter) {
	int i = 0;
	const UCHAR8 *char_hex = GLYPH_START(letter);
	
	for(i = 0; i < 8; i++, char_hex++) {
		*(base + (y + i) * 80 + (x >> 3)) = *char_hex;
	}
}
void clear_letter(UCHAR8* base, int x, int y) {
    int row;
    UCHAR8* location = base + (y * BYTES_PER_ROW) + (x >> 3);

        if (x >= 0 && x < (SCREEN_WIDTH - LETTER_WIDTH) && y >= 0 && y < (SCREEN_HEIGHT - LETTER_HEIGHT)) {
        for (row = 0; row < 15; row++) {
        
            *location = 0;    
            *(location + 1) = 0;
            location += BYTES_PER_ROW;       
        }
    }
}
void clear_8(UCHAR8* base, int x, int y, unsigned int height) {
    int row;
    int dx = x;
    int dy = y;
    UCHAR8* location = base + (y * BYTES_PER_ROW) + (x >> 3); 
    if (x >= 0 && x < SCREEN_WIDTH - 8 && dy >= 0 && dy < (SCREEN_HEIGHT - height)) {
        for (row = 0; row < height; row++) {
            *location = 0;    
            *(location + 1) = 0;
            location += BYTES_PER_ROW;     
        }
    }
}
void plot_string(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], const char* str) {
    int current_x = x;
    while (*str != '\0') {
        plot_letter(base, current_x, y, bitmap, *str);
        current_x += LETTER_WIDTH; 
        str++;
    }
}
/**
 * Plots a 640 x 400 bitmap on the screen. 
 * Not complete
 * @param base pointer to the base adress of the frame buffer
 * @param bitmap array of longs containing the bitmap data
 */
void plot_screen(ULONG32* base, const ULONG32 bitmap[]) {
    int i, j, index = 0;
    for (i = 0; i < 400; i++) {
        for (j = 0; j < 20; j++) {
            *(base + j + (i*20)) = bitmap[index];
            index++;
        }
    }
    return;
}

ULONG32* get_video_base()
{
	ULONG32 old_ssp;
    ULONG32 combined_address;
    UCHAR8 high_byte; 
    UCHAR8 mid_byte ;

	old_ssp = Super(0); 				
    high_byte = *ptr_to_highbyte;
    mid_byte = *ptr_to_midbyte;
    Super(old_ssp); 		
    
    combined_address = ((ULONG32)high_byte << 16) | ((ULONG32)mid_byte  << 8);
   
    return (ULONG32*)combined_address;

}
