#ifndef GLOBALS_H
#define GLOBALS_H

#include "TYPES.H"
#include "model.h"

#define W_MAKE 0x11
#define A_MAKE 0x1E
#define S_MAKE 0x1F
#define D_MAKE 0x20

#define ESC_MAKE 0x01
#define ESC_BREAK 0x81
#define ENTER 0x1C

extern bool request_to_render;   
extern volatile UINT16 ticks;           
extern volatile ULONG32 time_now;

extern char keyboard_buffer[256];         
extern UCHAR8 head;
extern int tail;
extern UCHAR8 fill_level;

extern int global_mouse_x;
extern int global_mouse_y;


extern Movement pacman_movements;
extern Pacman pacman;
extern Movement awkward_ghost_movement;
extern Ghost awkward_ghost;
extern Movement moustache_ghost_movement;
extern Ghost moustache_ghost;
extern Movement cyclops_ghost_movement;
extern Ghost cyclops_ghost;
extern Movement crying_ghost_movement;
extern Ghost crying_ghost;
extern Timer timer;
extern Entities entity;
/*extern Queue; */
 


#endif