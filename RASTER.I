# 1 "raster.c" 1
# 1 "./raster.h" 1
# 1 "./types.h" 1



typedef unsigned char UCHAR8;
typedef unsigned int  UINT16;
typedef unsigned long ULONG32;

typedef signed char bool;
# 4 "./raster.h" 2
# 22 "./raster.h"
void plot_bitmap_16(UINT16* base, int x, int y, const UINT16 bitmap[], unsigned int height);
void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void clear_letter(UCHAR8* base, int x, int y);
void plot_string(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], const char* str);
void clear_bitmap_32(ULONG32* base, int x, int y, unsigned int height);
void plot_8(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int height);

void plot_bitmap_32_quick(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void plot_bitmap_64(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void plot_letter(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int letter);
void plot_screen(ULONG32* base, const ULONG32* bitmap);
void clear_screen_q(ULONG32* base);



void plot_screen(ULONG32* base, const ULONG32* bitmap);
# 1 "raster.c" 2
# 1 "./TYPES.H" 1
# 2 "raster.c" 2
# 13 "raster.c"
void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height) {
    int row;
    int dx = x;
    int dy = y;
    ULONG32* location = base + (y * 20 ) + (x >> 5);
            if (x >= 0 && x <= (640  - 32 ) && dy >= 0 && y <= (400  - 32 ) ) {
        for (row = 0; row < height; row++) {
                *location |= bitmap[row] >> (x & 31);
                *(location + 1) |= bitmap[row] << (32  - (x & 31));
            location += 20 ;
            dy++;
            }

        }
}
void clear_bitmap_32(ULONG32* base, int x, int y, unsigned int height) {
    int row;
    int dy = y;
    ULONG32* location = base + (y * 20 ) + (x >> 5);
    ULONG32 mask1, mask2;

    if (x >= 0 && x <= (640  - 32 ) && y >= 0 && y <= (400  - 32 )) {
        for (row = 0; row < height; row++) {

            mask1 = ~(0xFFFFFFFF >> (x & 31));
            mask2 = ~(0xFFFFFFFF << (32  - (x & 31)));

            *location &= mask1;
            if ((x & 31) + 32  > 32) {
                *(location + 1) &= mask2;
            }
            location += 20 ;
        }
    }
}

void plot_bitmap_16(UINT16* base, int x, int y, const UINT16 bitmap[], unsigned int height) {
    int row;
    int dy = y;
    UINT16* location = base + (y * 40 ) + (x >> 4);

    for (row = 0; row < height; row++) {
        if (x >= 0 && x <= (640  - 16 ) && dy >= 0 && y <= (400  - 16 )) {
            *location |= bitmap[row] >> (x % 16 );
            *(location + 1) |= bitmap[row] << (16 - (x % 16 ));
        }
        location += 40 ;
        dy++;
    }
}
# 72 "raster.c"
void plot_bitmap_64(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height) {
    int row;
    ULONG32* location = base + (y * 20 ) + (x >> 5);

    if (x >= 0 && x <= (640  - 64 ) && y >= 0 && y <= (400  - height)) {
        for (row = 0; row <= height*2; row += 2) {

            *location |= bitmap[row] >> (x % 32 );
            *(location + 1) |= bitmap[row] << (32  - (x % 32 ));

            *(location + 1) |= bitmap[row + 1] >> (x % 32 );
            *(location + 2) |= bitmap[row + 1] << (32  - (x % 32 ));

            location += 20 ;
        }
    }
}
void plot_8(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int height) {
    int row;
    int dx = x;
    int dy = y;
    UCHAR8* location = base + (y * 80 ) + (x >> 3);

    if (x >= 0 && x < 640  && dy >= 0 && dy < 400 ) {
        for (row = 0; row < height; row++) {
            *location |= bitmap[row] >> (x & 7);
            *(location + 1) |= bitmap[row] << 8 - (x & 7);
            location += 80 ;
        }
    }
}
# 112 "raster.c"
void plot_letter(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int letter) {
    int row;
    int index = ((letter - ' ') << 3);

    UCHAR8* location = base + (y * 80 ) + (x >> 3);

    if (x >= 0 && x < (640  - 8 ) && y >= 0 && y < (400  - 16 )) {
        for (row = index; row < index + 8; row++) {

            *location |= bitmap[row] >> (x % 8 );
            *(location + 1) |= bitmap[row] << 8  - (x % 8 );
            location += 80 ;
        }
    }
}
void clear_letter(UCHAR8* base, int x, int y) {
    int row;
    UCHAR8* location = base + (y * 80 ) + (x >> 3);

        if (x >= 0 && x < (640  - 8 ) && y >= 0 && y < (400  - 16 )) {
        for (row = 0; row < 15; row++) {

            *location = 0;
            *(location + 1) = 0;
            location += 80 ;
        }
    }
}
void plot_string(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], const char* str) {
    int current_x = x;
    while (*str != '\0') {
        plot_letter(base, current_x, y, bitmap, *str);
        current_x += 8 ;
        str++;
    }
}
# 154 "raster.c"
void plot_screen(ULONG32* base, const ULONG32* bitmap) {
    return;
}
