#ifndef RASTER_H
#define RASTER_H

#include "types.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400

#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 32

#define HITBOX_HEIGHT 64
#define HITBOX_WIDTH 64

#define LETTER_HEIGHT 16
#define LETTER_WIDTH 8

#define LONGS_PER_ROW 20
#define WORDS_PER_ROW 40
#define BYTES_PER_ROW 80

void plot_bitmap_16(UINT16* base, int x, int y, const UINT16 bitmap[], unsigned int height);
void plot_bitmap_32(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_bitmap_32_quick(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_bitmap_64(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_letter(UINT8* base, int x, int y, const UINT8 bitmap[], unsigned int letter);
void plot_screen(UINT32* base, const UINT32* bitmap);
void clear_screen_q(UINT32* base); 
/*
void clear_screen_c(UINT32* base);
*/
void plot_screen(UINT32* base, const UINT32* bitmap);
#endif
