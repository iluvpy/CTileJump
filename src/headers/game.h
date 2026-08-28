#pragma once

#include <SDL2/SDL.h>

#include "tiles.h"
#include "player.h"
#include "constants.h"
#include "events.h"
#include "player.h"
#include "timeHandler.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    TileHandler *tile_handler;
    GameEvents *events;
    Player *player;
    TimeHandler *time_handler;
    bool quit;

} GameData;

int gameLoop(GameData *game);
void initGame(GameData *game, GameEvents *events, TileHandler *tile_handler);
void drawGame(GameData *game);
void updateGame(GameData *game);
void destroyGame(GameData *game);