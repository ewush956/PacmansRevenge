#ifndef PACMAN_H
#define PACMAN_H

#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "TYPES.H"
#include "font.h"
#include "bitmaps.h"
#include "events.h"
#include <osbind.h>
#include <stdio.h>
#include <linea.h>

typedef unsigned char GAME_STATE;

#define QUIT ((UCHAR8)0)
#define PLAY ((UCHAR8)1)
#define PAUSE ((UCHAR8)2)
#define GAMEOVER ((UCHAR8)3)
#define WIN ((UCHAR8)4)

#define FIRST_STOP 16
#define SECOND_STOP 16
#define THIRD_STOP 32

ULONG32 get_time();
GAME_STATE update_game_state(GAME_STATE new_state, char input);
void debug_print(UCHAR8* base, UINT16 x, UINT16 y, UINT16 value);
void debug_cells_pac(UCHAR8* base, Pacman* pacman);
void update_pacman();
void update_ghosts();
void free_ghosts(ULONG32* base32, UCHAR8* base8, Entities* entity);
void manually_move_ghost(ULONG32* base, Entities* entity, int frame_index);

void set_first_movements(ULONG32* base32, UCHAR8* base8, Entities* entity);
void set_second_movements(ULONG32* base32, UCHAR8* base8, Entities* entity);
void set_third_movements(ULONG32* base32, UCHAR8* base8, Entities* entity);



#endif
