#include "tiles.h"

#include "util.h"



void initTileHandler(TileHandler *tile_handler) {
    tile_handler->count = 0;
    tile_handler->tiles = malloc(sizeof(GameRect*));
}

void destroyTileHandler(TileHandler *tile_handler) {

    if (tile_handler->count == 0) {
        free(tile_handler->tiles);
        return;
    }

    for (int i = 0; i <= tile_handler->count; i++) {
        if (i > 1) {
            destroyGameRect(tile_handler->tiles[i]);
        }
    }
    free(tile_handler->tiles);
}

void drawTiles(TileHandler *tile_handler, SDL_Renderer *renderer) {
    for (int i = 0; i < tile_handler->count; i++) {
        fillGameRect(tile_handler->tiles[i], renderer);
    }
}

/* TODO implement update tile handler */
void updateTileHandler(TileHandler *tile_handler, GameRect *object) {
    

    int new_count = tile_handler->count + 1;

    GameRect **new_objects = realloc(tile_handler->tiles, sizeof(GameRect) * new_count);

    tile_handler->tiles = new_objects;
    tile_handler->count++;
    tile_handler->tiles[tile_handler->count - 1] = object;
    return;

}