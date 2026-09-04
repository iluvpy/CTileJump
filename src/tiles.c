#include "tiles.h"

const int TILE_HEIGHT = 5;
const int TILE_WIDTH = 20;
const int TILE_R = 100;
const int TILE_G = 100;
const int TILE_B = 100;
const int TILE_A = 255;

const int TILE_X_MAX_DIST = 20;
const int TILE_X_MIN_DIST = 20;
const int TILE_Y_MAX_DIST = 40;
const int TILE_Y_MIN_DIST = 20;

const int TILES_PADDING = 20;
const int INITIAL_TILE_HEIGHT = WINDOW_HEIGHT - 50;

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
        
        ON_DEBUG(
            SDL_Rect collision = getTileJumpingCollisionRect(tile_handler->tiles[i]);
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderDrawRect(renderer, &collision);
        )
    }
}

/* TODO implement update tile handler */
void updateTileHandler(TileHandler *tile_handler, double dt) {
    
    // if (tile_handler->count < 1) {
    //     p_addTile(tile_handler, 30, 30);
    //     p_addTile(tile_handler, 30, 50);
    // }

    if (tile_handler->last_tile == NULL) { /* the first generation of tiles has yet to be done. */
        int y = INITIAL_TILE_HEIGHT;
        int x = random_int(0, WINDOW_WIDTH - TILE_WIDTH); 
        p_addTile(tile_handler, x, y); /* last tile gets updated inside this function */
        return; 
    }



    /* first tile already generated, now check if new tiles need to be  */
    GameRect *last_tile = getTile(tile_handler, tile_handler->count - 1);
    int last_tile_y = last_tile->y;
    if (last_tile_y > 30) { /* the last tile is below y 30, so we need to add a tile*/
        int new_tile_x = random_int(0 + TILES_PADDING, WINDOW_WIDTH - TILE_WIDTH - TILES_PADDING);
        int new_tile_y = last_tile_y - random_int(TILE_Y_MIN_DIST, TILE_Y_MAX_DIST);
        p_addTile(tile_handler, new_tile_x, new_tile_y);

    } 

    for (int i = 0; i < tile_handler->count; i++) {
        GameRect *tile = getTile(tile_handler, i);
        
        #ifndef NO_TILE_MOVEMENT /* debug.h */
            tile->y += TILE_SPEED * dt;
        #endif
        
        if (tile->y > WINDOW_HEIGHT && i == 0) {
            /* this tile is always i=0*/
            /* move array memory by +1*/
            p_deleteTileAt(tile_handler, i);
        }
    }

}

void p_deleteTileAt(TileHandler *tile_handler, int i) {
    destroyGameRect(tile_handler->tiles[i]);

    memmove(
        &tile_handler->tiles[i],
        &tile_handler->tiles[i + 1],
        (tile_handler->count - i - 1) * sizeof(GameRect*)
    );

    p_updateTileCount(tile_handler, tile_handler->count - 1);

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
}

GameRect *getTile(TileHandler *tile_handler, u_int32_t index) {
    if (index < tile_handler->count) {
        return tile_handler->tiles[index];
    }
    return NULL;
}

/* the collision rect stands a little bit above the actually visible tile */
SDL_Rect getTileJumpingCollisionRect(GameRect *tile) {
    SDL_Rect collision_rect = {
        tile->x - 5,
        tile->y - TILE_HEIGHT,
        tile->w + 10, 
        tile->h + TILE_HEIGHT / 2
    };

    return collision_rect;
}


bool p_checkAddTiles(TileHandler *tile_handler) {
    GameRect *tile;
    int last_tile_index = tile_handler->count - 1;
    if ((tile = getTile(tile_handler, last_tile_index))) {

    }
    return true;
}