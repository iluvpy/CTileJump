#include "game.h"


// the loop which checks for events and renders each frame
int gameLoop(GameData *game) {
    
    while (!game->quit) {
        /* check events */
        updateEvents(game->events);
        game->quit = game->events->quit;

        /* set white background */
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255); 
        SDL_RenderClear(game->renderer);

        /* rendering happens here */

        SDL_RenderPresent(game->renderer);

        SDL_Delay(10); 

    }

    return 0;
}



void initGame(GameData *game, GameEvents *events, ObjectHandler *obj_handler) {
    game->quit = false;

    SDL_Window *window = SDL_CreateWindow(
        "TILEJUMP",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    game->window = window;
    game->renderer = renderer;

    game->obj_handler = obj_handler;
    initObjectHandler(game->obj_handler);
    game->events = events;
    initGameEvents(game->events);

}


void destroyGame(GameData *game) {

    destroyObjectHandler(game->obj_handler);
}

