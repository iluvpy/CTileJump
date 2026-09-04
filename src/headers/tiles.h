#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "globals.h"
#include "rect.h"

#include "util.h"
#include "debug.h"


/* tiles.h */
extern const int TILE_HEIGHT;
extern const int TILE_WIDTH;
extern const int TILE_R;
extern const int TILE_G;
extern const int TILE_B;
extern const int TILE_A;

/* range of delta x or y when adding a new tile*/
extern const int TILE_X_MAX_DIST;
extern const int TILE_X_MIN_DIST;
extern const int TILE_Y_MAX_DIST;
extern const int TILE_Y_MIN_DIST;

#define TILE_SPEED 100

typedef struct {
    GameRect **tiles; 
    GameRect *last_tile;
    uint16_t count;
} TileHandler;

/* initializes TileHandler members */
void initTileHandler(TileHandler *tile_handler);

// adds one object to the object handler, uses heap
void updateTileHandler(TileHandler *tile_handler, double dt);
void drawTiles(TileHandler *tile_handler, SDL_Renderer *renderer);
void p_addTile(TileHandler *tile_handler, int x, int y);
void p_updateTileCount(TileHandler *tile_handler, int count);
bool p_checkAddTiles(TileHandler *tile_handler);
SDL_Rect getTileJumpingCollisionRect(GameRect *tile);
void p_deleteTileAt(TileHandler *tile_handler, int i);
GameRect *getTile(TileHandler *tile_handler, u_int32_t index);


// frees the space the object handler has used
void destroyTileHandler(TileHandler *tile_handler);

