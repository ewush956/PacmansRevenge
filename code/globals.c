

#include "TYPES.H"
#include "globals.h"
#include "model.h"


bool request_to_render = FALSE;

volatile ULONG32 time_now = 0;
UINT16 ticks = 0;
bool waka_playing = FALSE;
bool single_waka_playing = FALSE;
bool end_game_flag = FALSE;
bool game_over_flag = FALSE;
bool kill_ghost_flag = FALSE;
bool second_has_passed = FALSE;
bool game_start = FALSE;
bool derender_moustache_flag = FALSE;
bool derender_awkward_flag = FALSE;
bool derender_crying_flag = FALSE;
bool derender_cyclops_flag = FALSE;


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
    AWKWARD_PATH,
    &awkward_ghost_movement
};
Timer timer = {
    99, '9', '9'
};
Entities entity = {
        &pacman,
        &crying_ghost,
        &awkward_ghost,
        &moustache_ghost,
        &cyclops_ghost,
        &timer
    };