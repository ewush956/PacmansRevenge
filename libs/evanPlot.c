#include <osbind.h>

#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  400
#define SPRITE_HEIGHT 32

typedef unsigned int UINT32;

void plot_bitmap_32(UINT32* base, int x, int y, const UINT32* bitmap, unsigned int height);

const UINT32 spriteMap[SPRITE_HEIGHT] = {
0x003FFC00,
0x007FFE00,
0x01C00380,
0x038001C0,
0x1C000038,
0x3800001C,
0xF0C0030F,
0xE0C00307,
0xC1B00DC3,
0xC31808C3,
0xC70810E3,
0xC60C30E3,
0xC60C3023,
0xC0000003,
0xC0000003,
0xC0000003,
0xC0000003,
0xC0000003,
0xC0000003,
0xC0000003,
0xC0000003,
0xC0E00303,
0xC0600703,
0xC07FFE03,
0xC03FFC03,
0xC0000003,
0xC0000003,
0xC0000003,
0xC6060604,
0xCF0F0F0C,
0x30F0F0F0,
0x20606060
};


int main()
{
    UINT32 *base = Physbase();
    int x, y;

    x = 0;
    y = 0;
    plot_bitmap_32(base, x, y, spriteMap, SPRITE_HEIGHT);
    /*
    for (y = 0; y < SCREEN_HEIGHT; y += SPRITE_HEIGHT)
        for (x = 0; x < SCREEN_WIDTH; x += sizeof UINT32)
            plot_bitmap_32(base, x, y, spriteMap, SPRITE_HEIGHT);
    */
    return 0;
}

void plot_bitmap_32(UINT32* base, int x, int y, const UINT32* bitmap, unsigned int height)
{
    int row;
    UINT32* location = base + (y * 20) + (x >> 4);
    
    for (row = 0; row < height; row++)
    {
        *location |= bitmap[row];     /* danger (no bounds checking!) */
        location += 20;
    }
}
