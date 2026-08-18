#pragma once

#include <stdbool.h>

// window
#define WINDOW_HEIGHT (int)600
#define WINDOW_WIDTH (int)250

/* tiles.h */
#define TILE_HEIGHT (int)5
#define TILE_WIDTH (int)20
#define INITAL_TILE_HEIGHT (int)(WINDOW_HEIGHT - 50)
#define TILE_R (int)100
#define TILE_G (int)100
#define TILE_B (int)100
#define TILE_A (int)255

/* range of delta x or y when adding a new tile*/
#define TILE_X_MAX_DIST (int)20
#define TILE_X_MIN_DIST (int)20
#define TILE_Y_MAX_DIST (int)20
#define TILE_Y_MIN_DIST (int)20

/* end tiles.h */