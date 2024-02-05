#include <osbind.h>


typedef unsigned int UINT16;


void plot_vline(int x, int y, int y0, UINT16 *base);

/* void clear_screen (UINT16 *base, int screen_len, int screen_width); */

void plot_hline(int x, int y, int x0, UINT16* base);


int main () 
{
	int y;
	int x;
	UINT16 *base = Physbase(); 	
	
	/*
	base += 15; */
	/* *base = *(base + 40) = *(base + 80) =0xFFFF; */
	
	/*
	*base = *(base + 40) = *(base + 80) = 0xFFFF; */
	
	/*
	for (y = 0; y < 400; y+= 8)
		for(x = 0; x < 640; x+=8)		
			plot_vline(x,y,639,base);
	
	/*
	clear_screen(base,400,640);
	*/
	
	/*
	plot_hline(10,10,639,base);
	plot_vline(100,100,350,base);
	
	*/


	/*x y x0*/
	y = 20;
	for (x = 64; x < 600; x+=8)
	{
		plot_hline(x,y,600,base);
		
	}
	
	y = 380;
	for (x = 64; x < 600; x+=8)
	{
		plot_hline(x,y,600,base);
		
	}
	
	for (y = 60; y < 380; y+= 8)		
			plot_vline(36,y,399,base);
	
	

	
	return 0;
}


/* plots a few vertical lines on the screen */ 

void plot_vline(int x, int y, int y0, UINT16 *base)
{
	int i;
	
	base += x;
	
	for( i = y; i < y0; i+= 16)
		*base = *(base + y * 40) = 0xFFFF;  
}


/* 
Not finsihed yet so fix it
void clear_screen( UINT16 *base, int screen_len, int screen_width)
{
	int x,y;
	int i = 0;
	
	 //*base = Physbase();
	
	
	for (y =0; y < screen_len; y+=8)
		for (x =0; y < screen_width; x+=8)
			*base = *(base + i * 40) = 0x0000;

	
}
*/

void plot_hline(int x, int y, int x0, UINT16* base)
{
	int i;
	
	base += y * 40;							/* moves the y postion to where you want the horizonal line drawn */
	
	
	for (i = x; i < x0; i +=16)
		*base = *(base + (x >> 4)) = 0xFFFF;
	
	
}