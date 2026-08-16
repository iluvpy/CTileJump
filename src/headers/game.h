#pragma once

#include <SDL2/SDL.h>

#include "object.h"
#include "player.h"
#include "constants.h"
#include "events.h"


typedef struct GameData {
    SDL_Window *window;
    SDL_Renderer *renderer;

    ObjectHandler *obj_handler;
    GameEvents *events;
    bool quit;

} GameData;

int gameLoop(GameData *game);
void initGame(GameData *game, GameEvents *events, ObjectHandler *obj_handler);
void destroyGame(GameData *game);