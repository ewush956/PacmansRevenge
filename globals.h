#ifndef GLOBALS_H
#define GLOBALS_H

#include "TYPES.H"
#include "model.h"


extern bool request_to_render;   
extern volatile UINT16 ticks;           
extern volatile ULONG32 time_now;
extern volatile bool waka_playing;


 /*extern Entities entity;*/
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