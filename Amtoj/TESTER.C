/* for bitmap testing */ 
/* for now */
#include <osbind.h>
#include <stdio.h>
#include <linea.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 32
typedef unsigned long LONG32;
void plot_bitmap_32(LONG32 *base, int x, int y, const LONG32 *bitmap, LONG32 height);

/* void draw_at_location (LONG32 *base, int x, int y, const LONG32 *bitmap, LONG32 height); */

/* it was supposed to be a unsiogned long not int as ints are 16 bits in m68k assembly 
	thats why it was only printing half of the sprite */
	
const LONG32 sprite_bitmap[SPRITE_HEIGHT] =
{
   	   
	0x00000000,
	0x00000000,
	0x000FFC00,
	0x001FFE00,
	0x00F103C0,
	0x01F0C3C0,
	0x030F20C0,
	0x030B11C0,
	0x0D0F0380,
	0x0C0E0780,
	0x35000FC0,
	0x38180EC0,
	0x30003E40,
	0x70203E40,
	0xD000F680,
	0xC000E300,
	0xC803C200,
	0xD003C000,
	0xC000E000,
	0xC000F000,
	0x70003800,
	0x30003800,
	0x30001C00,
	0x30000E00,
	0x0C000700,
	0x0C000380,
	0x03000180,
	0x030001C0,
	0x00F00F00,
	0x00F00F00,
	0x000FF000,
	0x000FF000

   
};

const LONG32 square_bitmap[SPRITE_HEIGHT] =
{
	
	
	0xFFFFFFFF,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0x80000001,
	0XFFFFFFFF
		
	
	
};
int main()
{
	int x;
	int y = 200;
	int width = 32;


	
	LONG32 *base = Physbase();
    
	/*
	x = 120;
	plot_bitmap_32(base, x, y, sprite_bitmap, SPRITE_HEIGHT);
	
	x = 250;
	plot_bitmap_32(base, x, y, sprite_bitmap, SPRITE_HEIGHT);
	
	x = 252;
	plot_bitmap_32(base, x, y, sprite_bitmap, SPRITE_HEIGHT);

	/*
	plot_bitmap_32(base, x, y, square_bitmap, SPRITE_HEIGHT);
	*/
/*
    for (y = 0; y < SCREEN_HEIGHT; y += SPRITE_HEIGHT)
        for (x = 0; x < SCREEN_WIDTH; x += 32)
            plot_bitmap_32(base, x, y, sprite_bitmap, SPRITE_HEIGHT);
    
*/


		y = 150;
		x = 0;
		
	  for (x = 0; x < SCREEN_WIDTH; x+=20)
	  {
            plot_bitmap_32(base, x, y, sprite_bitmap, SPRITE_HEIGHT);
			/*plot_bitmap_32(base, x, y, square_bitmap, SPRITE_HEIGHT);*/
			
	  }
  
	  /*
	  while (!Cconis()) {
		  
		  
		  
	  }
	printf("\033E\033f\n");     
	linea0();
	*/
	
    return 0;
}

void plot_bitmap_32(LONG32 *base, int x, int y, const LONG32 *bitmap, LONG32 height)
{
    int row;
    
	LONG32 *location = base + y * 20 + (x >> 5);
	

    for (row = 0; row < height; row++)
    {
		if ( x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		{
		*location |= bitmap[row] >> (x % SPRITE_WIDTH);     
        *(location + 1) |= bitmap[row] << SPRITE_WIDTH - (x % SPRITE_WIDTH);
        location += 20;
		}
    }
	
	
}


/*
void draw_at_location (LONG32 *base, int x, int y, const LONG32 *bitmap, LONG32 height)
{
	SPRITE_WIDTH = 32;
	int start = x;
	int end = y;
	int i; 
	int how_many = 10;    /* put in header 
	
		
	for (i = 0; i < how_many; i++) 
	{
		
		plot_bitmap_32(
		
		
		
	}
		
		
		

	
}
*/