#pragma once

#include <SDL2/SDL.h>

#include "tiles.h"
#include "player.h"
#include "constants.h"
#include "events.h"


typedef struct GameData {
    SDL_Window *window;
    SDL_Renderer *renderer;

    TileHandler *tile_handler;
    GameEvents *events;
    bool quit;

} GameData;

int gameLoop(GameData *game);
void initGame(GameData *game, GameEvents *events, TileHandler *tile_handler);
void drawGame(GameData *game);
void destroyGame(GameData *game);