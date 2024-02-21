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

ULONG32 get_time();
GAME_STATE update_game_state(GAME_STATE new_state, char input);
#endif
