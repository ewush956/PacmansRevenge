#include <osbind.h>
#include <stdio.h> /* for printf remove later */
#include <linea.h>

#include "struct.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"

#include "model.h"
#include "input.h"

#define LETTERS_PER_BLOCK 6

const ULONG32* sprites[] = {
	pac_1, pac_2, pac_3, pac_4,
	evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4,
	ghost_1_up, ghost_1_down, ghost_1_left, ghost_1_right,
	ghost_2_up, ghost_2_down, ghost_2_left, ghost_2_right,
	ghost_3_up, ghost_3_down, ghost_3_left, ghost_3_right,
	ghost_4_up, ghost_4_down, ghost_4_left, ghost_4_right,
	wall_left_down_right, wall_up_down, wall_left_right, wall_down_right,
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



void next_test(ULONG32* base);
void display_all_ascii(UCHAR8* base, int x0, int y0);
void test_arbitrary_letter(UCHAR8* base);

/*All below functions call next_test*/
void speed_test(ULONG32* base, ULONG32 sprite[], unsigned int height);
void display_all_sprites(ULONG32* base);
void test_boundaries(ULONG32* base);
void test_arbitrary_32(ULONG32* base);

/* for object testing */
void move_ghost_position (Ghost *ghost, int new_x, int new_y);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman_position (Pacman *pacman, int new_x, int new_y);


int main()
{
	
	/*

	void *base32 = Physbase();
	void *base8 = Physbase();
	int x, y, i, j, index, countx, county;

	clear_screen_q(base32);

	display_all_sprites(base32);
	next_test(base32);

	display_all_ascii(base8, 220, 150);
	next_test(base32);

	plot_bitmap_64(base32, 200+32, 80, test64, HITBOX_HEIGHT);
	plot_bitmap_32(base32, 200, 80, tombstone, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200, 80+32, tombstone, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200+32, 80+64, tombstone, SPRITE_HEIGHT);
	plot_bitmap_32(base32, 200+64, 80+64, tombstone, SPRITE_HEIGHT);
	next_test(base32);

	test_arbitrary_32(base32);
	next_test(base32);

	test_arbitrary_letter(base8);
	next_test(base32);

	test_boundaries(base32);
	next_test(base32);


/*Code below animates our beloved angry boi <3 :) */
/*
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


	/*testing speed and buffer limmits (commented because it's pretty slow)*/
	/* speed_test(base32, ghost_4_down, SPRITE_HEIGHT); */



/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- - */
/* - - - - - - - - - - - - - - - - - - -  - - - - -  - - - - - - - - - - - -  -- -*/
/* - - - - -  for testing the individual objects (ghosts or pac or both) - - - - */

/**/
	char input;
	Ghost crying_ghost = {100,100,0,0};
	Pacman pacman_obj = {0,0,0,0};
	
	printf("Initial position: (%d, %d)\n", crying_ghost.x, crying_ghost.y);
	
	move_ghost_position(&crying_ghost,-5,0);
	move_ghost_position(&crying_ghost,1,0);
	move_ghost_position(&crying_ghost,600,600); 		/* out of bounds test */
	increase_ghost_velocity(&crying_ghost,10,10);
	
	printf("New position: (%d, %d)\n", crying_ghost.x, crying_ghost.y);
	printf("New speed: (%d, %d)\n", crying_ghost.delta_x, crying_ghost.delta_y);	
	printf("pacman position old : (%d, %d)\n", pacman_obj.x, pacman_obj.y);

	
	/* use plot font to test (...?) */ 
	
	/* im trying to take keyboard input here and each time  w a s or d is pressed 
		i want to increment the position by 1 (we cna chnage this to whatever pixel amount)
		NOT taking input but works with hard-coded funtion calls */
		
		/*
		input = Cconin();
		printf("%c\n",input);
		*/
		

	while(!Cconis())
	{
		
		/*char input[2];*/
		/*Cconrs(input[0]);  /* 2 is the input channel to read from */
		
		/*input = Cconin();*/
		 input = Cauxin();

		switch(input)
		{
			case 'w': move_pacman_position(&pacman_obj, 0,1);
				break;
				
			case 'a':
				move_pacman_position(&pacman_obj, -1,0);
				printf("a pressed");
				break;
				
			case 's':
				move_pacman_position(&pacman_obj, 0,-1);
				printf("s pressed");
				break;
				
			case 'd':
				move_pacman_position(&pacman_obj, 1,0);
				printf("d pressed");
				break;
				
			default:
				printf("Invalid input\n");
				break;
				
		}
		
	}
	/*Cnecin();*/
	
	printf("pacman position new : (%d, %d)\n", pacman_obj.x, pacman_obj.y);


	return 0;
}
/*waits for input then calls clear_screen();*/
void next_test(ULONG32* base) {

	while(!Cconis()){

	}
	Cnecin();
	clear_screen_q(base);
}
void display_all_ascii(UCHAR8* base, int x0, int y0) {

	int x, y, i;
	int index = 0;

	for (y = y0; y < y0 + (LETTER_HEIGHT * LETTERS_PER_BLOCK); y += 16) {
		for (i = 0, x = x0; i < 16 ; i++, x += LETTER_WIDTH) {
			if (index < 95) 
				plot_letter(base, x, y, font, index++); /*a*/
		}
	}	
}
void speed_test(ULONG32* base, ULONG32 sprite[], unsigned int height) {

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
void display_all_sprites(ULONG32* base) {
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
void test_boundaries(ULONG32* base) {
    
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
void test_arbitrary_32(ULONG32* base) {
	int i;

	for (i=0; i < 95; i++) {
		plot_bitmap_32(base, arbitrary_numbers_640[i], arbitrary_numbers_400[i], sprites[i % 30], SPRITE_HEIGHT);
	}
}
void test_arbitrary_letter(UCHAR8* base) {
	int i;
	for(i = 0; i < 95; i++) {
		plot_letter(base, arbitrary_numbers_640[i], arbitrary_numbers_400[i], font, i);
	}
}




/* 
*	This is for checking if the ghost struct in 'model.h' is working correcctly 
*    
*	-Used ints for moving backwards by adding negatives 
*
*
*
*/
void move_ghost_position (Ghost *ghost, int new_x, int new_y)
{
		
	/* for now assume that the map will be 640x400 (chnage later once we figure out proper dimesn for map)*/
	
	if (!(ghost->move->x   + new_x > SCREEN_WIDTH || ghost->move->x    + new_x < 0 ||
		ghost->move->y  + new_y > SCREEN_HEIGHT || ghost->move->y  + new_y < 0))
	{
			ghost-> x += new_x;
			ghost->move->y  += new_y;
	}
	
	
} 

/* the end game conditon would call this..? 
*
* increase both vert and horizontal speed to capture pacman and end game
*  leave in x-y parameters now but later we can just use a constant 
*
*/

void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{
	
	ghost->move->delta_x = horizontal_velocity;
	ghost->move->delta_y  = vertical_velocity;
		
}


/* Same as move_ghost_position () as this does the same thing but with pacman object
*
*
*
*/
void move_pacman_position (Pacman *pacman, int new_x, int new_y) 
{
	
	
	if (!(pacman->move->x + new_x > SCREEN_WIDTH || pacman->move->x  + new_x < 0 ||
		pacman->move->y + new_y > SCREEN_HEIGHT || pacman->move->y + new_y < 0))
	{
			pacman-> x += new_x;
			pacman->move->y += new_y;
	}
	
	
	
}
