#ifndef RASTER_H
#define RASTER_H

#include "types.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 32
#define LETTER_HEIGHT 16
#define LETTER_WIDTH 8

void plot_bitmap_32(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_letter(UINT8* base, int x, int y, const UINT8 bitmap[], unsigned int letter);
void plot_screen(UINT32* base, const UINT32* bitmap);
void clear_screen(); 
void clear_screen_c(UINT32* base);

#endif
