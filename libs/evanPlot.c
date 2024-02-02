#include <osbind.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 32

typedef unsigned long ULONG32;

void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32* bitmap, unsigned int height);
void plot_screen(ULONG32* base, const ULONG32* bitmap);

const ULONG32 spriteMap[SPRITE_HEIGHT] = {
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
    ULONG32 *base = Physbase();
    int x, y, i, j;


    x = 100;
    y = 100;

    for (i = 0; j < 400; i++) {
        for (i = 0; i < 640; i++) {
            plot_bitmap_32(base, i, j, spriteMap, SPRITE_HEIGHT);
        }
    }

    return 0;
}

void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32* bitmap, unsigned int height) {
    int row;
    ULONG32* location = base + (y * 20) + (x >> 5);

    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        for (row = 0; row < height; row++) {
        
            *location |= bitmap[row] >> (x % SPRITE_WIDTH);     
            *(location + 1) |= bitmap[row] << SPRITE_WIDTH - (x % SPRITE_WIDTH);
            location += 20;
        
        }
    }
}
/*do 8 x 16 !!!*/
/*
void plot_screen(ULONG32* base, const ULONG32* bitmap) {
    int row, col;
    ULONG32* location;

    for (row = 0; row < SCREEN_HEIGHT; row++) {
        location = base + (row * 20); // 20 ULONG32s per row for 640 pixels

        for (col = 0; col < 20; col++) { // 20 ULONG32s per row
            *location = bitmap[row * 20 + col]; // Directly copying each 32-bit segment
            location++;
        }
    }
}
*/