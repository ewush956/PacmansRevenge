#include <osbind.h>
#include "raster.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"

#define LETTERS_PER_BLOCK 6

const UINT32* sprites[] = {
	pac_1, pac_2, pac_3, pac_4,
	evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4,
	ghost_1_up, ghost_1_down, ghost_1_left, ghost_1_right,
	ghost_2_up, ghost_2_down, ghost_2_left, ghost_2_right,
	ghost_3_up, ghost_3_down, ghost_3_left, ghost_3_right,
	ghost_4_up, ghost_4_down, ghost_4_left, ghost_4_right,
	wall_left_down_right, wall_up_down, wall_left_right, wall_down_right,
	tombstone, ghost_run, ghost_freeze
};

void next_test(UINT32* base);
void display_all_ascii(UINT8* base, int x0, int y0);

/*All below functions call next_test*/
void speed_test(UINT32* base, UINT32 sprite[], unsigned int height);
void display_all_sprites(UINT32* base);
void test_boundaries(UINT32* base);
void test_arbitrary(UINT32* base);
int main()
{
	void *base32 = Physbase();
	void *base8 = Physbase();
	int x, y, i, index;

	next_test(base32);

	display_all_sprites(base32);
	next_test(base32);
	plot_bitmap_64(base32, 62, 80, test64, 64);
	plot_bitmap_32(base32, 0, 80, tombstone, 32);
	next_test(base32);
	test_arbitrary(base32);
	test_boundaries(base32);

	/*Testing all letters*/
	display_all_ascii(base8, 200, 150);
	next_test(base32);

	/*testing speed and buffer limmits (commented because it's pretty slow)*/
	/* speed_test(base32, ghost_4_down, SPRITE_HEIGHT); */
	
	return 0;
}
/*waits for input then calls clear_screen();*/
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
	next_test(base);
}
void display_all_sprites(UINT32* base) {
    int x, y, i;
    int spritesPerRow = 8; 
    int spriteWidth = 32; 
    int spriteHeight = 32; 
    int spacing = 10; 
    int startX = 20; 
    int startY = 20; 

    for (i = 0; i < 31; i++) {
        x = startX + (i % spritesPerRow) * (spriteWidth + spacing);
        y = startY + (i / spritesPerRow) * (spriteHeight + spacing);
        plot_bitmap_32(base, x, y, sprites[i], spriteHeight);
    }
	next_test(base);
}
/*Tests allowable plotting limmits*/
void test_boundaries(UINT32* base) {
    
    plot_bitmap_32(base, 0, 0, sprites[0], SPRITE_HEIGHT); 
    plot_bitmap_32(base, SCREEN_WIDTH - SPRITE_WIDTH, 0, sprites[1], SPRITE_HEIGHT); 
    plot_bitmap_32(base, 0, SCREEN_HEIGHT - SPRITE_HEIGHT, sprites[2], SPRITE_HEIGHT); 
    plot_bitmap_32(base, SCREEN_WIDTH - SPRITE_WIDTH, SCREEN_HEIGHT - SPRITE_HEIGHT, sprites[3], SPRITE_HEIGHT); 
    plot_bitmap_32(base, (SCREEN_WIDTH - SPRITE_WIDTH) / 2, 0, sprites[4], SPRITE_HEIGHT); 
    plot_bitmap_32(base, (SCREEN_WIDTH - SPRITE_WIDTH) / 2, SCREEN_HEIGHT - SPRITE_HEIGHT, sprites[5], SPRITE_HEIGHT); 
    plot_bitmap_32(base, 0, (SCREEN_HEIGHT - SPRITE_HEIGHT) / 2, sprites[6], SPRITE_HEIGHT); 
    plot_bitmap_32(base, SCREEN_WIDTH - SPRITE_WIDTH, (SCREEN_HEIGHT - SPRITE_HEIGHT) / 2, sprites[7], SPRITE_HEIGHT); 

    next_test(base);
}
/*Displays all prites within allowable range at aribitrary (x,y)*/
void test_arbitrary(UINT32* base) {
	plot_bitmap_32(base, 21, 20, sprites[0], SPRITE_HEIGHT);
	plot_bitmap_32(base, 92, 20, sprites[0], SPRITE_HEIGHT);
	plot_bitmap_32(base, 64, 101, sprites[1], SPRITE_HEIGHT);
	plot_bitmap_32(base, 36, 10, sprites[1], SPRITE_HEIGHT);
	plot_bitmap_32(base, 123, 181, sprites[2], SPRITE_HEIGHT);
	plot_bitmap_32(base, 87, 81, sprites[2], SPRITE_HEIGHT);
	plot_bitmap_32(base, 188, 268, sprites[3], SPRITE_HEIGHT);
	plot_bitmap_32(base, 247, 22, sprites[4], SPRITE_HEIGHT);
	plot_bitmap_32(base, 302, 100, sprites[5], SPRITE_HEIGHT);
	plot_bitmap_32(base, 368, 188, sprites[6], SPRITE_HEIGHT);
	plot_bitmap_32(base, 429, 264, sprites[7], SPRITE_HEIGHT);
	plot_bitmap_32(base, 481, 21, sprites[8], SPRITE_HEIGHT);
	plot_bitmap_32(base, 541, 102, sprites[9], SPRITE_HEIGHT);
	plot_bitmap_32(base, 27, 347, sprites[10], SPRITE_HEIGHT);
	plot_bitmap_32(base, 83, 322, sprites[11], SPRITE_HEIGHT);
	plot_bitmap_32(base, 148, 343, sprites[12], SPRITE_HEIGHT);
	plot_bitmap_32(base, 209, 328, sprites[13], SPRITE_HEIGHT);
	plot_bitmap_32(base, 260, 344, sprites[14], SPRITE_HEIGHT);
	plot_bitmap_32(base, 322, 227, sprites[15], SPRITE_HEIGHT);
	plot_bitmap_32(base, 52, 341, sprites[16], SPRITE_HEIGHT);
	plot_bitmap_32(base, 446, 10, sprites[17], SPRITE_HEIGHT);
	plot_bitmap_32(base, 507, 344, sprites[18], SPRITE_HEIGHT);
	plot_bitmap_32(base, 568, 90, sprites[19], SPRITE_HEIGHT);
	plot_bitmap_32(base, 159, 152, sprites[20], SPRITE_HEIGHT);
	plot_bitmap_32(base, 211, 213, sprites[21], SPRITE_HEIGHT);
	plot_bitmap_32(base, 272, 277, sprites[22], SPRITE_HEIGHT);
	plot_bitmap_32(base, 333, 333, sprites[23], SPRITE_HEIGHT);
	plot_bitmap_32(base, 399, 157, sprites[24], SPRITE_HEIGHT);
	plot_bitmap_32(base, 456, 212, sprites[25], SPRITE_HEIGHT);
	plot_bitmap_32(base, 513, 275, sprites[26], SPRITE_HEIGHT);
	plot_bitmap_32(base, 578, 334, sprites[27], SPRITE_HEIGHT);
	plot_bitmap_32(base, 607, 154, sprites[28], SPRITE_HEIGHT);
	plot_bitmap_32(base, 601, 211, sprites[29], SPRITE_HEIGHT);

	next_test(base);
}
