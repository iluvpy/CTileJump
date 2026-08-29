#include "events.h"
#include "util.h"

#include <SDL2/SDL.h>
#include <stdio.h>

// polls events and updates the GameEvents struct accordinglys
void updateGameEvents(GameEvents *game_events) {
    SDL_Event event;
    game_events->pressed_space = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_events->quit = true;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                game_events->pressed_space = true;
            } else if (event.key.keysym.sym == SDLK_a) {
                if (game_events->holdLeft) {
                    game_events->was_holdingLeft = true;
                }
                game_events->holdLeft = true;
            } else if (event.key.keysym.sym == SDLK_d) {
                if (game_events->holdright) {
                    game_events->was_holdingright = true;
                }
                game_events->holdright = true;
            }
        }

        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_a) {
                game_events->was_holdingLeft = false;
                game_events->holdLeft = false;
            } else if (event.key.keysym.sym == SDLK_d) {
                game_events->was_holdingright = false;
                game_events->holdright = false;
            }
        }
    }
}

void initGameEvents(GameEvents *game_events) {
    game_events->holdLeft = false;
    game_events->holdright = false;
    game_events->pressed_space = false;
    game_events->quit = false;
    game_events->was_holdingLeft = false;
    game_events->was_holdingright = false;
}