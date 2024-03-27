#ifndef PACMAN_H
#define PACMAN_H

#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"
#include "events.h"
#include "psg.h"
/*#include "isr.h"*/


#include <osbind.h>
#include <stdio.h>
#include <linea.h>

typedef unsigned char GAME_STATE;

#define QUIT ((UCHAR8)0)
#define PLAY ((UCHAR8)1)
#define PAUSE ((UCHAR8)2)
#define GAMEOVER ((UCHAR8)3)
#define WIN ((UCHAR8)4)

#define ALLIGNMENT 256

#define FIRST_STOP 16
#define SECOND_STOP 16
#define THIRD_STOP 32


#define BUFFER_SIZE_BYTES 32256                  
#define VIDEO_ADDR_HIGH  0xFF8201
#define VIDEO_ADDR_MID  0xFF8203


void swap_buffers(ULONG32** base32, ULONG32** back_buffer_ptr);
void render_to_buffer(ULONG32* base32, Entities* entity, UINT16 ticks,char input);
void update_movement(Entities* entity, /*char input,*/ UINT16 ticks); 
void initialize_game(ULONG32* base32, ULONG32* back_buffer_ptr, ULONG32* background_ptr, Entities* entity);

ULONG32 get_time();
void set_video_base(ULONG32*);

GAME_STATE update_game_state(GAME_STATE new_state, char input, Entities* all);
void debug_print(UCHAR8* base, UINT16 x, UINT16 y, UINT16 value);
void debug_cells_pac(UCHAR8* base, Pacman* pacman);
void update_entities();
void free_ghosts(ULONG32* base32, UCHAR8* base8, Entities* entity);
void manually_move_ghost(ULONG32* base, Entities* entity, int frame_index, bool enable);
ULONG32* byte_allign(ULONG32* array_address);
void debug_pacman_movement(ULONG32* base32, Pacman* pacman);

ULONG32* get_video_base();

void set_first_movements(ULONG32* base32, UCHAR8* base8, Entities* entity);
void set_second_movements(ULONG32* base32, UCHAR8* base8, Entities* entity);
void set_third_movements(ULONG32* base32, UCHAR8* base8, Entities* entity);

void clear_and_render_entities(ULONG32* base32, ULONG32* back_buffer_ptr, Entities* entity);
void clear_and_render_maps(ULONG32* base32, ULONG32* back_buffer_ptr);

bool execute_movements_and_render_frame(ULONG32* base32, UCHAR8* base8, UCHAR8* back8, Entities* entity, int* moves_index, int initial_moves[5]);
void initialize_sound(long* old_ssp, MusicState* trebleState, MusicState* bassState);
bool update_sound(long* old_ssp, ULONG32* time_then, MusicState* trebleState, MusicState* bassState, int treble_song_length, int bass_song_length, int* intro_duration);


extern UCHAR8 background[BUFFER_SIZE_BYTES];
extern UCHAR8 screen_buffer[BUFFER_SIZE_BYTES];

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

extern Entities entity;

#endif
