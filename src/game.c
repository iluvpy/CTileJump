#include "game.h"


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
    game->player = createPlayer(game->renderer);

    game->tile_handler = tile_handler;
    initTileHandler(game->tile_handler);
    game->events = events;
    initGameEvents(game->events);

    game->time_handler = createTimeHandler();
}

// the loop which checks for events and renders each frame
int gameLoop(GameData *game) {


    while (!game->quit) {
        /* check events */
        updateGameEvents(game->events);
        game->quit = game->events->quit; /* check if quit */

        /* set white background */
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255); 
        SDL_RenderClear(game->renderer);

        /* rendering happens here */ 
        drawGame(game);
    

        SDL_RenderPresent(game->renderer);
        
        updateGame(game);


    }

    return 0;
}

void drawGame(GameData *game) {

    drawTiles(game->tile_handler, game->renderer);
    drawPlayer(game->player, game->renderer);
    
}

void updateGame(GameData *game) {
    dt_start(game->time_handler);
    updateTileHandler(game->tile_handler);
    updatePlayer(game->player, game->time_handler);
    SDL_Delay(10); 
    dt_end(game->time_handler);
}



void destroyGame(GameData *game) {
    
    destroyTileHandler(game->tile_handler);
    game->tile_handler = NULL;
    destroyPlayer(game->player);
    destroyTimeHandler(game->time_handler);

}

