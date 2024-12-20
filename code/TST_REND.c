#include <osbind.h>
#include <linea.h>
#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"
#include "globals.h"
#include "effects.h"
#include "events.h"

#include <stdio.h>

#define LETTERS_PER_BLOCK 6

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

void next_test(ULONG32* base);
void test_pacman_movement(ULONG32* base, UCHAR8* base8, Entities* entity, int stop);
void test_ghost_movement(ULONG32* base, UCHAR8* base8, Entities* entity, Ghost* ghost, int stop);
void debug_print(UCHAR8* base, UINT16 x, UINT16 y, UINT16 value);


void test_arbitrary_letter(UCHAR8* base);

int main()
{
	
	Entities entity = {
		&pacman,
		&crying_ghost,
		&moustache_ghost,
		&awkward_ghost,
		&cyclops_ghost
	};
	
	/*
	Pacman* pac = entity.pacman;
	Ghost* moustache = entity.moustache_ghost;
	Ghost* crying = entity.crying_ghost;
	Ghost* awkward = entity.awkward_ghost;
	Ghost* cyclops = entity.cyclops_ghost;
	*/

	void *base32 = Physbase();
	void *base16 = Physbase();
	void *base8 = Physbase();

	int x, y, i, j, index, countx, county, offset_x, offset_y;

	init_map_cells(cell_map, tile_map);

	clear_screen_q(base32); 
	next_test(base32);
    render_map(base16, tile_map);
	render_frame(base32, &entity);
	next_test(base32);

	test_pacman_movement(base32, base8, &entity, 15);

	entity.pacman->move->direction = RIGHT;
	entity.pacman->move->delta_x = 1;
	entity.pacman->move->delta_y = 0;

	next_test(base32);
	test_pacman_movement(base32, base8, &entity, 16 * 15);

	entity.pacman->move->direction = UP;
	entity.pacman->move->delta_x = 0;
	entity.pacman->move->delta_y = -1;
	test_pacman_movement(base32, base8, &entity, 32 + 16);
	next_test(base32);
	
	entity.crying_ghost->move->delta_x = 1;
	entity.crying_ghost->move->delta_y  = 0;
	entity.crying_ghost->move->direction = RIGHT;

	test_ghost_movement(base32, base8, &entity, entity.crying_ghost, 31);

	entity.crying_ghost->move->delta_x = 0;
	entity.crying_ghost->move->delta_y  = -1;
	entity.crying_ghost->move->direction = UP;
	test_ghost_movement(base32, base8, &entity, entity.crying_ghost, 32+16);
	
	de_render_ghost(base32, entity.moustache_ghost, cell_map);
	next_test(base32);
	

/*
	awkward->move->delta_x = -1;
	awkward->move->delta_y = 0;
	awkward->move->direction = LEFT;
	test_ghost_movement(base32, base8, &entity, awkward, 32);

	moustache->move->delta_x = 0;
	moustache->move->delta_y = -1;
	moustache->move->direction = UP;
	test_ghost_movement(base32, base8, &entity, moustache, 16);

	moustache->move->delta_x = 1;
	moustache->move->delta_y = 0;
	moustache->move->direction = RIGHT;
	test_ghost_movement(base32, base8, &entity, moustache, 64);
*/
	next_test(base32);

	/* *moustache->current_cell = *cell_map[11][23]; */

	return 0;
}
/*waits for input then calls clear_screen();*/
void next_test(ULONG32* base) {
	while(!Cconis()){
	}
	Cnecin();
}
/*Displays all prites within allowable range at aribitrary (x,y)*/
void test_pacman_movement(ULONG32* base, UCHAR8* base8, Entities* entity, int stop) {
	int i;
	UINT16 cell_x = entity->pacman->move->x_cell_index;
	UINT16 cell_y = entity->pacman->move->y_cell_index;

	for (i=0; i < stop; i++) {
		clear_bitmap_32(base, entity->pacman->move->x, entity->pacman->move->y, SPRITE_HEIGHT); 
		move_pacman(entity->pacman);
		update_cells(entity);
		debug_print(base8, 0, 0, entity->pacman->move->x_cell_index);
		render_frame(base, entity);
		
		if (i % 4 == 0) {
			entity->pacman->current_frame = ((entity->pacman->current_frame) + 1) % 6;
		}
		if (entity->pacman->move->y_cell_index  != cell_y && entity->pacman->move->delta_x == 0) {
			next_test(base);
			cell_y = entity->pacman->move->y_cell_index;
		}
	}
}
void test_ghost_movement(ULONG32* base, UCHAR8* base8, Entities* entity, Ghost* ghost, int stop) {
	int i;
	int cell_x = ghost->move->x_cell_index;
	int cell_y = ghost->move->y_cell_index;

	const char strx[] = "X: ";
	const char stry[] = "Y: ";	
	/*
	next_test(base);
	printf("X: %d\n", ghost->x_cell_index);
	next_test(base);
	printf("Y: %d\n", ghost->y_cell_index);
	*/

	for (i=0; i < stop; i++) {
		int j;
		clear_bitmap_32(base, ghost->move->x, ghost->move->y, SPRITE_HEIGHT); 
		move_ghost(ghost);
		update_cells(entity);
		
		for (j = 0; j < 14; j++) {
			clear_letter(base8, j*LETTER_WIDTH, 0);
		}

		plot_string(base8, 0, 0, font, strx);
		debug_print(base8, 4*LETTER_WIDTH, 0, ghost->move->x_cell_index);
		plot_string(base8, 8*LETTER_WIDTH, 0, font, stry);
		debug_print(base8, 12*LETTER_WIDTH, 0, ghost->move->y_cell_index);
		render_frame(base, entity);
		if (i % 8 == 0) {
			ghost->current_frame = ((ghost->current_frame) + 1) % 2;
		}
	}
}

void debug_print(UCHAR8* base, UINT16 x, UINT16 y, UINT16 value){
    UINT16 tens = value / 10;
    UINT16 ones = value % 10;

    unsigned int tens_char = tens + '0';
    unsigned int ones_char = ones + '0';

	clear_letter(base, x, y);
	clear_letter(base, x+LETTER_WIDTH, y);
    plot_letter(base, x , y, font, tens_char);
    plot_letter(base, x + LETTER_WIDTH, y, font, ones_char);
}