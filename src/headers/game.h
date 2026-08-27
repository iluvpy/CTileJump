#pragma once

#include <SDL2/SDL.h>

#include "tiles.h"
#include "player.h"
#include "constants.h"
#include "events.h"
#include "image.h"

typedef struct GameData {
    SDL_Window *window;
    SDL_Renderer *renderer;

    TileHandler *tile_handler;
    GameEvents *events;
    Image *player_img;
    bool quit;

} GameData;

int gameLoop(GameData *game);
void initGame(GameData *game, GameEvents *events, TileHandler *tile_handler);
void drawGame(GameData *game);
void destroyGame(GameData *game);