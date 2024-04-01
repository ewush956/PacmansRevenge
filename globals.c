
#include "TYPES.H"
#include "globals.h"
#include "model.h"


bool request_to_render = FALSE;
volatile ULONG32 time_now = 0;
volatile UINT16 ticks = 0;

char keyboard_buffer[256];         
UCHAR8 head = 0;
int tail = -1;
UCHAR8 fill_level = 0;

int global_mouse_x = 200;
int global_mouse_y = 200;


/**************************************************************************
* Declaration: Pacman pacman
* Purpose: Initializes the player character, Pacman, with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement pacman_movement = {
        PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,        
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
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,     
        0,0,
        RIGHT,
        10, 17,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost crying_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CRYING,
    FALSE,
    &crying_ghost_movement
};

/*************************************************************
* Declaration: Ghost cyclops_ghost
* Purpose: Initializes the 'cyclops' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement cyclops_ghost_movement = {
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        12, 17,
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      
        PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost cyclops_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_CYCLOPS,
    FALSE,
    &cyclops_ghost_movement
};
/*************************************************************
* Declaration: Ghost moustache_ghost
* Purpose: Initializes the 'moustache' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement moustache_ghost_movement = {
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        10, 21,
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost moustache_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_MOUSTACHE,
    FALSE,
    &moustache_ghost_movement
};

/*************************************************************
* Declaration: Ghost awkward_ghost
* Purpose: Initializes the 'awkward' ghost entity with its
*          starting position, movement displacement, state,
*          direction, and cell index on the game map.
*************************************************************/
Movement awkward_ghost_movement = {
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,      
        0,0,
        LEFT,
        12, 21,
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET, 
        PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
        FALSE
};
Ghost awkward_ghost = {
    0,
    DEFAULT,
    GHOST_TYPE_AWKWARD,
    FALSE,
    &awkward_ghost_movement
};

Timer timer = {
    0,0,
    20, 28, 44, 52
};

 Entities entity = {
        &pacman,
        &crying_ghost,
        &awkward_ghost,
        &moustache_ghost,
        &cyclops_ghost,
    };

/*
typedef struct {

    char keyboard_buffer[256];         
    int head;
    int tail;
    int fill_level;

}Queue;
*/
