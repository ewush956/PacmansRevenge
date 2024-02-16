#include <osbind.h>
#include <linea.h>
#include "raster.h"
#include "model.h"
#include "renderer.h"
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
void test_pacman_movement(UINT32* base, Entities* entity);

void test_arbitrary_letter(UINT8* base);

/*All below functions call next_test*/
void display_all_sprites(UINT32* base);
void test_boundaries(UINT32* base);

int main()
{
	Entities entity = {
		&pacman,
		&crying_ghost,
		&moustache_ghost,
		&awkward_ghost,
		&cyclops_ghost
	};
	
	void *base32 = Physbase();
	void *base16 = Physbase();
	void *base8 = Physbase();

	int x, y, i, j, index, countx, county, offset_x, offset_y;

	clear_screen_q(base32); 
	next_test(base32);
    render_map(base16, tile_map);
	render_frame(base32, &entity);

	next_test(base32);
	clear_bitmap_32(base32, pacman.x, pacman.y, SPRITE_HEIGHT);
	next_test(base32);
	pacman.delta_x = 1;
	pacman.delta_y = 0;
	test_pacman_movement(base32, &entity);
	next_test(base32);

	/*
	plot_bitmap_32(base32, pacman.x, pacman.y, sprites[2], SPRITE_HEIGHT);
	plot_bitmap_32(base32, crying_ghost.x, crying_ghost.y, sprites[8], SPRITE_HEIGHT);
	plot_bitmap_32(base32, moustache_ghost.x, moustache_ghost.y, sprites[12], SPRITE_HEIGHT);
	plot_bitmap_32(base32, cyclops_ghost.x, cyclops_ghost.y, sprites[16], SPRITE_HEIGHT);
	plot_bitmap_32(base32, awkward_ghost.x, awkward_ghost.y, sprites[20], SPRITE_HEIGHT);
	next_test(base32);
	*/


	/*18 x 11 !!!!!!!!!!!!!!!!*/

	
	return 0;
}
/*waits for input then calls clear_screen();*/
void next_test(UINT32* base) {

	while(!Cconis()){

	}
	Cnecin();
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
    
}
/*Displays all prites within allowable range at aribitrary (x,y)*/
void test_pacman_movement(UINT32* base, Entities* entity) {
	int i;
	for (i=0; i < 200; i++) {
		clear_bitmap_32(base, entity->pacman->x, entity->pacman->y, SPRITE_HEIGHT);
		move_pacman(entity->pacman);
		render_frame(base, entity);
		entity->pacman->current_frame = ((entity->pacman->current_frame) + 1) % 6;
		/* next_test(base); */
	}
}
void test_ghost_movement(UINT32* base, Entities* entity) {
	int i;
	for (i=0; i < 16; i++) {
		
	}
}