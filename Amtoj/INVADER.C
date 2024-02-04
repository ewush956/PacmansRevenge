#include <osbind.h>
#include <stdio.h>
typedef unsigned int UINT16;
typedef unsigned char UINT8;

#define INVADER_H 16
#define FONT_H 16
#define FONT_WIDTH 16
#define SPRITE_WIDTH 16

const UINT16 invader_bitmap[INVADER_H] = {
	
	
	0x0000,
	0x0810,
	0x0810,
	0x0420,
	0x1FF8,
	0x2004,
	0x4662,
	0x4002,
	0x43C2,
	0x2424,
	0x1008,
	0x0FF0,
	0x0240,
	0x0E70,
	0x0000
	
};


const UINT16 font_bitmap[FONT_H] = {
	
	0x0000,
	0x7800,
	0x8000,
	0xF800,
	0x8400,
	0x8400,
	0x7800,
	0x0000, 
	0x0000, 
	0x0000, 
	0x0000, 
	0x0000, 
	0x0000, 
	0x0000, 
	0x0000,
	0x0000

	
};


void plot_bitmap_16 (UINT16* base, int x, int y, const UINT16 *bitmap,
					unsigned int height);

void plot_bitmap_8 (UINT16* base, int x, int y, const UINT16 *bitmap,
					unsigned int height);


int main(){

	int i, x, y;
	UINT16* base;
	base = Physbase();

	x = 120;
	y = 200;
 
	
	/*
	for (y = 0; y < 400; y+= INVADER_H)
		for(x = 0; x < 640; x+=32)						/* if 8 then the invaders are very close and the higher you get (multiples of 16) the more it gets spaced out horzontally*/
			/*plot_bitmap_16(base, x, y, invader_bitmap, 16);	
			*/
	

	x = 150;
	y = 200;
	plot_bitmap_16 (base, x, y, font_bitmap,16);
	
	x = 150 ;
	y = 203;
	plot_bitmap_16 (base, x, y, font_bitmap,16);
	
	
	return 0;
	
}
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap,
			unsigned int height) {
	
	
	UINT16 *location = base + y * 40 + (x >> 4);

	int row;

	for (row = 0; row < INVADER_H; row++){

		*location |= bitmap[row] >> (x % FONT_WIDTH);     
        *(location + 1) |= bitmap[row] << FONT_WIDTH - (x % FONT_WIDTH);
        location += 40;

	}
}


/*      -------------------------                 */


void plot_bitmap_8 (UINT16* base, int x, int y, const UINT16 *bitmap,
					unsigned int height)
{

	int row;
	UINT16* location = base + y * 40 + (x >> 3);


	for (row = 0; row < INVADER_H; row++)
	{

		*location |= bitmap[row] >> (x % FONT_WIDTH);     
        *(location + 1) |= bitmap[row] << FONT_WIDTH - (x % FONT_WIDTH);
        location += 40;

	}
	
	
}

