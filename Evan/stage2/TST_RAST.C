#include <osbind.h>
#include "raster.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"

#define LETTERS_PER_BLOCK 6

void next_test(UINT32* base);
void display_all_ascii(UINT8* base, int x0, int y0);
void speed_test(UINT32* base, UINT32 sprite[], unsigned int height);
int main()
{
	void *base32 = Physbase();
	void *base8 = Physbase();
	int x, y, i, index;
	/*
	plot_something_1(base, 100, 100);
	plot_something_2(base, 200, 200);

	/*waits for input then calls clear_screen();*/
	next_test(base32);

	/*Testing arbitrary (x,y) and close proximities*/
	plot_bitmap_32(base32, 20, 20, testSprite, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 25, 25, testSprite, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 237, 193, testSprite, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 77, 101, testSprite, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 78, 102, testSprite, SPRITE_HEIGHT);

	next_test(base32);

	plot_bitmap_32(base32, 20, 20, sprite1, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 25, 25, sprite2, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 237, 193, sprite3, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 77, 101, sprite4, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 78, 102, sprite5, SPRITE_HEIGHT);

	next_test(base32);

	/*Testing allowable plotting limmits*/
	plot_bitmap_32(base32, 0, 0, testSprite, SPRITE_HEIGHT);
	plot_bitmap_32(base32, SCREEN_WIDTH - SPRITE_WIDTH, 0, testSprite, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 0, SCREEN_HEIGHT - SPRITE_HEIGHT, testSprite, SPRITE_HEIGHT);
	plot_bitmap_32(base32, SCREEN_WIDTH - SPRITE_WIDTH, SCREEN_HEIGHT - SPRITE_HEIGHT, testSprite, SPRITE_HEIGHT);

	next_test(base32);

	/*Testing all letters*/
	display_all_ascii(base8, 100, 200);
	next_test(base32);

	/*testing speed and buffer limmits*/
	speed_test(base32, testSprite, SPRITE_HEIGHT);
	next_test(base32);
	
	return 0;
}
void next_test(UINT32* base) {

	while(!Cconis()){

	}
	Cnecin();
	clear_screen_c(base);
}
void display_all_ascii(UINT8* base, int x0, int y0) {

	int x, y, i;
	int index = 0;

	for (y = y0; y < y0 + (LETTER_HEIGHT * LETTERS_PER_BLOCK); y += 16) {
		for (i = 0, x = x0; i < 16 ; i++, x += LETTER_WIDTH) {
			if (index < 95) 
				plot_letter(base, x, y, font, index++); /*a*/
		}
	}	
}
void speed_test(UINT32* base, UINT32 sprite[], unsigned int height) {

	int i;

	for (i = 0; i < 608; i++) {
		plot_bitmap_32(base, i, 0, sprite, height);
		plot_bitmap_32(base, i, 50, sprite, height);
		plot_bitmap_32(base, i, 100, sprite, height);
		plot_bitmap_32(base, i, 150, sprite, height);
		plot_bitmap_32(base, i, 200, sprite, height);
		plot_bitmap_32(base, i, 250, sprite, height);
		plot_bitmap_32(base, i, 300, sprite, height);
		plot_bitmap_32(base, i, 350, sprite, height);
	}
}