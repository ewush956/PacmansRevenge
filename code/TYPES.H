#ifndef TYPES_H
#define TYPES_H

typedef unsigned char UCHAR8;
typedef unsigned int  UINT16;
typedef unsigned long ULONG32;

typedef signed char bool; 

typedef UCHAR8 SCANCODE;
typedef unsigned char GAME_STATE;

#define TRUE -1
#define FALSE 0

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define WALL_SIZE     16

#define X_PIXEL_OFFSET 0
#define Y_PIXEL_OFFSET 16

#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 32

#define MAP_TILE_LENGTH 40        /* 1 tile = 16 pixels*/ 
#define MAP_TILE_HEIGHT 24   

#define HITBOX_HEIGHT 64
#define HITBOX_WIDTH 64

#define LETTER_HEIGHT 16
#define LETTER_WIDTH 8

#define LONGS_PER_ROW 20
#define WORDS_PER_ROW 40
#define BYTES_PER_ROW 80

#define SPLASH_SIZE 8000

#endif
