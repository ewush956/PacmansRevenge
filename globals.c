

#include "TYPES.H"
#include "globals.h"
#include "model.h"


bool request_to_render = FALSE;

volatile ULONG32 time_now = 0;
volatile UINT16 ticks = 0;
volatile bool waka_playing = FALSE;
volatile bool single_waka_playing = FALSE;
volatile bool game_over_flag = FALSE;
volatile bool kill_ghost_flag = FALSE;

char keyboard_buffer[256];         
UCHAR8 head = 0;
int tail = -1;
UCHAR8 fill_level = 0;

int global_mouse_x = MIDDLE_OF_SCREEN_X;
int global_mouse_y = MIDDLE_OF_SCREEN_Y;

int old_mouse_x;
int old_mouse_y;


bool left_button_pressed = FALSE;
bool right_button_pressed = FALSE;

/*const char digits[10] = {'0','1','2','3','4','5','6','7','8','9'}; /* */

const char* digits[10] = {"0","1","2","3","4","5","6","7","8","9"};
/*char* tail_timer_ptr = &digits[9];*/



/**************************************************************************
* Declaration: Pacman pacman
* Purpose: Initializes the player character, Pacman, with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement pacman_movement = {
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,      /* x y*/  
        0,0,        /*Initial Displacement*/
        UP,
        21,19,          /*Cell index -> y, x*/
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,
        FALSE
};
Pacman pacman = {
    0,
    UP,
    PACMAN,
    &pacman_movement
};
/*************************************************************
* Declaration: Ghost crying_ghost
* Purpose: Initializes the 'crying' ghost entity with its starting
*          position, movement displacement, state, direction, 
*          and cell index on the game map.
*************************************************************/
Movement crying_ghost_movement = {
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 7 + Y_PIXEL_OFFSET,     
        0,0,
        RIGHT,
        7, 19, /* y x*/
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 7 + Y_PIXEL_OFFSET,
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 7 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost crying_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CRYING,
    FALSE,
    CRYING_PATH,
    &crying_ghost_movement
};

/*************************************************************
* Declaration: Ghost cyclops_ghost
* Purpose: Initializes the 'cyclops' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement cyclops_ghost_movement = {
        PIXELS_PER_CELL * 13, PIXELS_PER_CELL * 11 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        11, 13, /* y x*/
        PIXELS_PER_CELL * 13, PIXELS_PER_CELL * 11 + Y_PIXEL_OFFSET,      
        PIXELS_PER_CELL * 13, PIXELS_PER_CELL * 11 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost cyclops_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CYCLOPS,
    FALSE,
    CYCLOPS_PATH,
    &cyclops_ghost_movement
};
/*************************************************************
* Declaration: Ghost moustache_ghost
* Purpose: Initializes the 'moustache' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement moustache_ghost_movement = {
        PIXELS_PER_CELL * 25, PIXELS_PER_CELL * 11 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        11, 25, /* y x*/
        PIXELS_PER_CELL * 25, PIXELS_PER_CELL * 11 + Y_PIXEL_OFFSET,      
        PIXELS_PER_CELL * 25, PIXELS_PER_CELL * 11 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost moustache_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_MOUSTACHE,
    FALSE,
    MOUSTACHE_PATH,
    &moustache_ghost_movement
};

/*************************************************************
* Declaration: Ghost awkward_ghost
* Purpose: Initializes the 'awkward' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement awkward_ghost_movement = {
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 15 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        15, 19, /* y x*/
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 15 + Y_PIXEL_OFFSET, 
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 15 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost awkward_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_AWKWARD,
    FALSE,
    AWKWARD_PATH,
    &awkward_ghost_movement
};
/*
Timer timer = {
    0,0,
    20, 28, 44, 52
};*/

Timer timer = {

    0,1,0,0
};


 Entities entity = {
        &pacman,
        &crying_ghost,
        &awkward_ghost,
        &moustache_ghost,
        &cyclops_ghost,
    };
