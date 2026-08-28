#include "tiles.h"

#include "util.h"
#include "debug.h"

const int TILES_PADDING = 20;

void initTileHandler(TileHandler *tile_handler) {
    tile_handler->tiles = malloc(sizeof(GameRect*));
    tile_handler->last_tile = NULL;
    tile_handler->count = 0;

}

void destroyTileHandler(TileHandler *tile_handler) {
    if (tile_handler == NULL) {
        DEBUG_STR("destroyTileHandler received NULL ptr!\n");
        return;
    }
    if (tile_handler->count == 0) {
        free(tile_handler->tiles);
        return;
    }
    for (int i = 0; i < tile_handler->count; i++) {
        destroyGameRect(tile_handler->tiles[i]);
    }
    
    if (!tile_handler->count) /* don't accidentally free the index 0 ptr twice*/
        free(tile_handler->tiles);
}

void drawTiles(TileHandler *tile_handler, SDL_Renderer *renderer) {
    for (int i = 0; i < tile_handler->count; i++) {
        fillGameRect(tile_handler->tiles[i], renderer);
    }
}

/* TODO implement update tile handler */
void updateTileHandler(TileHandler *tile_handler) {
    
    // if (tile_handler->count < 1) {
    //     p_addTile(tile_handler, 30, 30);
    //     p_addTile(tile_handler, 30, 50);
    // }

    if (tile_handler->last_tile == NULL) { /* the first generation of tiles has yet to be done. */
        int y = INITAL_TILE_HEIGHT;
        int x = random_int(0, WINDOW_WIDTH - TILE_WIDTH); 
        p_addTile(tile_handler, x, y); /* last tile gets updated inside this function */
        printf("added new tile!!!\n");
        return; 
    }



    /* first tile already generated, now check if new tiles need to be  */
    GameRect *last_tile = p_getTile(tile_handler, tile_handler->count - 1);
    int last_tile_y = last_tile->y;
    if (last_tile_y > 30) { /* the last tile is below y 30, so we need to add a tile*/
        int new_tile_x = random_int(0 + TILES_PADDING, WINDOW_WIDTH - TILE_WIDTH - TILES_PADDING);
        int new_tile_y = last_tile_y - random_int(TILE_Y_MIN_DIST, TILE_Y_MAX_DIST);
        p_addTile(tile_handler, new_tile_x, new_tile_y);

    } 
}


void p_updateTileCount(TileHandler *tile_handler, int count) {
    int count_diff = abs(tile_handler->count - count);
    if (count < 0 || count_diff > 1) {
        DEBUG_STR("p_updateTileCount had invalid count update argument!\n");
        return;
    }
    GameRect **new_tiles = realloc(tile_handler->tiles, sizeof(GameRect) * count);
    tile_handler->tiles = new_tiles;
    tile_handler->count = count;
}


void p_addTile(TileHandler *tile_handler, int x, int y) {

    int new_count = tile_handler->count + 1;
    p_updateTileCount(tile_handler, new_count);

    GameRect **new_tiles = realloc(tile_handler->tiles, sizeof(GameRect) * new_count);
    SDL_Color tile_color = {
        TILE_R,
        TILE_G,
        TILE_B,
        TILE_A
    };


    GameRect *new_tile = createGameRect(
        x,
        y,
        TILE_WIDTH,
        TILE_HEIGHT,
        tile_color
    );

    tile_handler->tiles = new_tiles;
    tile_handler->tiles[tile_handler->count - 1] = new_tile;
    tile_handler->last_tile = new_tile;
    printf("tile count updated, count: %d\n", tile_handler->count);  // p_addTile TODO REMOVE DEBUG PRINTF
}

GameRect *p_getTile(TileHandler *tile_handler, u_int32_t index) {
    if (index < tile_handler->count) {
        return tile_handler->tiles[index];
    }
    return NULL;
}


bool p_checkAddTiles(TileHandler *tile_handler) {
    GameRect *tile;
    int last_tile_index = tile_handler->count - 1;
    if ((tile = p_getTile(tile_handler, last_tile_index))) {

    }
    return true;
}