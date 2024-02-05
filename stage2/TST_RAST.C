#include <osbind.h>
#include <linea.h>
#include "raster.h"
#include "TYPES.H"

const UINT32 testSprite[32] = {
0x00000000,
0x00078000,
0x003FF000,
0x007FFC00,
0x01E82E00,
0x03C84700,
0x07840380,
0x070801C0,
0x0E0000E0,
0x1E000070,
0x1C7DEF78,
0x1E64CD38,
0x1C7CCF38,
0x1C68CC38,
0x1C65EC38,
0x1C000038,
0x1C000038,
0x1C000038,
0x1C000038,
0x1C640A38,
0x1CA06038,
0x1C000238,
0x1C000038,
0x1C010038,
0x1C101438,
0x1C482038,
0x1C000238,
0x1C000038,
0x1C000038,
0x1C000038,
0xFFFFFFFF,
0xFFFFFFFF
};

int main()
{
	void *baseC = Physbase();

	/*
	plot_something_1(base, 100, 100);
	plot_something_2(base, 200, 200);
	*/
	plot_bitmap_32(baseC, 0, 0, testSprite, 32);

	/*clear_screen();*/
	
	linea0();

	plot_bitmap_32(baseC, 20, 20, testSprite, 32);

	
	


	return 0;
}
