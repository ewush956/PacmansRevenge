#ifndef RASTER_H
#define RASTER_H

#include "types.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 32

typedef unsigned long ULONG32;

void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32* bitmap, unsigned int height);
void plot_screen(ULONG32* base, const ULONG32* bitmap);


/* [TO DO] the functions below are examples. Replace them! */

void plot_something_1(UINT16 *base, int x, int y, ...);
void plot_something_2(UINT32 *base, int x, int y, ...);

#endif
