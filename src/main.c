#include <SDL2/SDL.h>   // Use <SDL3/SDL.h> for SDL3
#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "util.h"

/* all functions with beginning with 'p_' are (or should be) private to the corresponding .c file */

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    initUtil(); /* initialize anything that the utility functions need */

    GameData game;
    GameEvents events;
    TileHandler tile_handler;

    initGame(&game, &events, &tile_handler);
    gameLoop(&game);
    destroyGame(&game);

    SDL_Quit();

    printf("quit game!\n");

    return 0;
}

