/* for bitmap testing */ 
/* for now */

#include <osbind.h>

#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  400

#define SPRITE_HEIGHT 32

typedef unsigned int UINT32;

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, UINT32 height);

const UINT32 sprite_bitmap[SPRITE_HEIGHT] =
{
   
   
	0xFFFFFFFF,
	0xFFC003FF,
	0xFF8001FF,
	0xFC00013F,
	0xFC00003F,
	0xF0C0100F,
	0xE0C03007,
	0xC3F03F03,
	0xC3F03F03,
	0xCE30E303,
	0xCF30F303,
	0xCC0CC0C3,
	0xC40C40C3,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0003003,
	0xC0003003,
	0xC3C0F003,
	0xC3C0F003,
	0xC0FFC003,
	0xC07F8003,
	0xC0000003,
	0xC0000003,
	0xC7070707,
	0xCF0F0F0F,
	0xFFFFFFFF,
	0xFFFFFFFF
   
  
   
};

int main()
{
    int x = 48;
	int y = 200;
	

	UINT32 *base = Physbase();
    
	

	plot_bitmap_32(base, x, y, sprite_bitmap, SPRITE_HEIGHT);
	/*
    for (y = 0; y < SCREEN_HEIGHT; y += SPRITE_HEIGHT)
        for (x = 0; x < SCREEN_WIDTH; x += sizeof UINT32)
            plot_bitmap_32(base, x, y, sprite_bitmap, SPRITE_HEIGHT);
    
	*/
	
    return 0;
}

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
    int row;
    
	UINT32 *loc = base + (y * 20) + (x >> 5);
    
    for (row = 0; row < height; row++)
    {
		
		if ( x >=0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		{
			*loc |= bitmap[row];     
			loc += 20;
		}
    }
	
	
	
	
	
}
