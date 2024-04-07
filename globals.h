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
#define LEFT_CLICK 0xFA

#define QUIT ((UCHAR8)0)
#define PLAY ((UCHAR8)1)
#define PAUSE ((UCHAR8)2)
#define GAMEOVER ((UCHAR8)3)
#define WIN ((UCHAR8)4)
#define WAITING_FOR_ESC_BREAK ((UCHAR8)5)
#define MENU ((UCHAR8)6)

extern GAME_STATE state;

extern bool request_to_render;   
extern UINT16 ticks;           
extern ULONG32 time_now;                    /* volatile...no remove later sorry*/
extern char keyboard_buffer[256];         
extern UCHAR8 head;
extern int tail;
extern UCHAR8 fill_level;
extern bool game_start;

extern int global_mouse_x;
extern int global_mouse_y;

extern int old_mouse_x;
extern int old_mouse_y;

extern bool left_button_pressed;
extern bool right_button_pressed;


extern bool waka_playing;
extern bool single_waka_playing;
extern bool end_game_flag;
extern bool game_over_flag;
extern bool kill_ghost_flag;
extern bool second_has_passed;

extern bool derender_moustache_flag;
extern bool derender_awkward_flag;
extern bool derender_crying_flag;
extern bool derender_cyclops_flag;

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

#endif