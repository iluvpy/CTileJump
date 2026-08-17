#include "game.h"


// the loop which checks for events and renders each frame
int gameLoop(GameData *game) {

    /* test drawing tiles*/
    SDL_Color color = {100, 100, 100, 255};
    GameRect *grect = createGameRect(100, 300, 50, 50, color);
    
    updateTileHandler(game->tile_handler, grect);

    while (!game->quit) {
        /* check events */
        updateEvents(game->events);
        game->quit = game->events->quit;

        /* set white background */
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255); 
        SDL_RenderClear(game->renderer);

        /* rendering happens here */ 
        drawTiles(game->tile_handler, game->renderer);

        SDL_RenderPresent(game->renderer);

        SDL_Delay(10); 

    }

    return 0;
}



void initGame(GameData *game, GameEvents *events, TileHandler *tile_handler) {
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

    game->tile_handler = tile_handler;
    initTileHandler(game->tile_handler);
    game->events = events;
    initGameEvents(game->events);

}


void destroyGame(GameData *game) {

    destroyTileHandler(game->tile_handler);
}

