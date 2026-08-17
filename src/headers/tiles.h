#pragma once

#include <SDL2/SDL.h>

#include "rect.h"

typedef struct TileHandler {
    GameRect **tiles; 
    uint16_t count;
} TileHandler;

void initTileHandler(TileHandler *tile_handler);

// adds one object to the object handler, uses heap
void updateTileHandler(TileHandler *tile_handler, GameRect *object);
void drawTiles(TileHandler *tile_handler, SDL_Renderer *renderer);

// frees the space the object handler has used
void destroyTileHandler(TileHandler *tile_handler);

