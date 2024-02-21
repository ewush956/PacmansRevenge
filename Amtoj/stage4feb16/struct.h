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

/* has old prototypes in it can use them for testing so leave them until submission */

void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void plot_bitmap_64(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void plot_letter(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int letter);
void plot_screen(ULONG32* base, const ULONG32* bitmap);
void clear_screen_q(ULONG32* base); 
void plot_screen(ULONG32* base, const ULONG32* bitmap);



#endif
