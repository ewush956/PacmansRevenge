#include <osbind.h>
#include <linea.h>
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
	wall_all, wall_horz, wall_vert, wall_LD, wall_ULD,
	tombstone, ghost_run, ghost_freeze
};

int arbitrary_numbers_400[] = {
	141, 276, 392, 345, 72, 307, 51, 17, 198, 63, 
	366, 304, 383, 71, 111, 190, 255, 39, 110, 307, 
	297, 324, 393, 95, 386, 53, 222, 368, 85, 325, 
	88, 100, 12, 92, 62, 275, 221, 131, 372, 300,
	388, 262, 174, 356, 84, 121, 276, 142, 210, 
	21, 336, 300, 392, 238, 92, 369, 88, 210, 
	262, 174, 356, 84, 121, 276, 142, 400, 365,
	18, 336, 300, 392, 238, 97, 369, 88, 210, 
	8, 21, 57, 299, 238, 97, 369, 88, 210, 327,
	333, 1, 32, 109, 238, 97, 369, 0, 210 
};

int arbitrary_numbers_640[] = {
	339, 287, 372, 220, 597, 186, 93, 429, 258, 
	70, 496, 20, 633, 612, 333, 61, 556, 404, 0,
	369, 591, 383, 511, 433, 123, 320, 106, 268,
	508, 122, 602, 280, 617, 482, 460, 218, 246, 
	11, 138, 317, 213, 326, 36, 456, 94, 9, 253, 
	269, 226, 381, 303, 29, 154, 251, 537, 604, 340, 
	647, 466, 367, 144, 123, 626, 389, 168, 638, 
	240, 389, 110, 281, 444, 565, 18, 211, 44, 
	213, 625, 603, 98, 94, 47, 382, 119, 312, 9,
	210, 240, 39, 255, 492, 515, 174, 377, 255, 37
};

void next_test(UINT32* base);
void display_all_ascii(UINT8* base, int x0, int y0);
void test_arbitrary_letter(UINT8* base);

/*All below functions call next_test*/
void speed_test(UINT32* base, UINT32 sprite[], unsigned int height);
void display_all_sprites(UINT32* base);
void test_boundaries(UINT32* base);
void test_arbitrary_32(UINT32* base);
int main()
{
	void *base32 = Physbase();
	void *base16 = Physbase();
	void *base8 = Physbase();
	int x, y, i, j, index, countx, county, offset_x, offset_y;

	clear_screen_q(base32);

	display_all_sprites(base32);
	next_test(base32);

	display_all_ascii(base8, 220, 150);
	next_test(base32);

	plot_bitmap_64(base32, 200+32, 80, test64, HITBOX_HEIGHT);
	clear_bitmap_32(base32, 200+32, 80, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200, 80, tombstone, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200, 80+32, tombstone, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200+32, 80+64, tombstone, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200+64, 80+64, tombstone, SPRITE_HEIGHT);
	next_test(base32);

	plot_bitmap_32(base32, 200+32, 80+64, tombstone, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200+64, 80+64, tombstone, SPRITE_HEIGHT);
	clear_bitmap_32(base32, 200+32, 80+64, SPRITE_HEIGHT);
	next_test(base32);

	test_arbitrary_32(base32);

	test_arbitrary_letter(base8);
	next_test(base32);

	test_boundaries(base32);
	next_test(base32);

	/*Code below animates our beloved angry boi <3*/

	

	while(!Cconis()){

		for (i = 0; i < 4; i++) {
			Vsync();
			plot_bitmap_32(base32, 200, 200, sprites[i], SPRITE_HEIGHT);
			for (j = 0; j < 9999; j++) {
			}
			clear_screen_q(base32);
		}
		for (i = 3; i >= 0; i--) {
			Vsync();
			plot_bitmap_32(base32, 200, 200, sprites[i], SPRITE_HEIGHT);
			for (j = 0; j < 9999; j++) {
			}
			clear_screen_q(base32);
		}
	}
	Cnecin();
	clear_screen_q(base32);
	countx = 0;
	while (!Cconis()) {
		for (i = 4; i < 8; i++) {
			plot_bitmap_32(base32, 100 + countx, 200, sprites[i], SPRITE_HEIGHT);
			for (j = 0; j < 5999; j++) {
			}
			Vsync();
			clear_screen_q(base32);
			countx += 2;
		}
		for (i = 7; i >= 4; i--) {
			plot_bitmap_32(base32, 100 + countx, 200, sprites[i], SPRITE_HEIGHT);
			for (j = 0; j < 5999; j++) {
			}
			Vsync();
			clear_screen_q(base32);
			countx += 2;
		}
	}
	Cnecin();
	clear_screen_q(base32);
	next_test(base32);


	/*18 x 11 !!!!!!!!!!!!!!!!/


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
	clear_screen_q(base);
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
}
/*Displays all prites within allowable range at aribitrary (x,y)*/
void test_arbitrary_32(UINT32* base) {
	int i;

	for (i=0; i < 95; i++) {
		plot_bitmap_32(base, arbitrary_numbers_640[i], arbitrary_numbers_400[i], sprites[i % 30], SPRITE_HEIGHT);
	}
}
void test_arbitrary_letter(UINT8* base) {
	int i;
	for(i = 0; i < 95; i++) {
		plot_letter(base, arbitrary_numbers_640[i], arbitrary_numbers_400[i], font, i);
	}
}