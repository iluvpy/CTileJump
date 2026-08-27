#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "rect.h"
#include "constants.h"

#define TILES_PADDING (int)20

typedef struct TileHandler {
    GameRect **tiles; 
    GameRect *last_tile;
    uint16_t count;
} TileHandler;

/* initializes TileHandler members */
void initTileHandler(TileHandler *tile_handler);

// adds one object to the object handler, uses heap
void updateTileHandler(TileHandler *tile_handler);
void drawTiles(TileHandler *tile_handler, SDL_Renderer *renderer);
void p_addTile(TileHandler *tile_handler, int x, int y);
void p_updateTileCount(TileHandler *tile_handler, int count);
bool p_checkAddTiles(TileHandler *tile_handler);
GameRect *p_getTile(TileHandler *tile_handler, u_int32_t index);


// frees the space the object handler has used
void destroyTileHandler(TileHandler *tile_handler);

