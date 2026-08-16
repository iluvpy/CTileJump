#include "events.h"
#include "util.h"

#include <SDL2/SDL.h>

// polls events and updates the GameEvents struct accordinglys
void updateEvents(GameEvents *game_events) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_events->quit = true;
            printf("quit event!"); // REMOVE
        }
    }
}

void initGameEvents(GameEvents *game_events) {
    game_events->holdLeft = false;
    game_events->holdright = false;
    game_events->pressed_space = false;
    game_events->quit = false;
}