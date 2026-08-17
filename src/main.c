#include <SDL2/SDL.h>   // Use <SDL3/SDL.h> for SDL3
#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "util.h"

bool initSDL();

int main(int argc, char *argv[]) {

    if (!initSDL()) {
        return -1;
    }
    
    GameData game;
    GameEvents events;
    TileHandler obj_handler;

    initGame(&game, &events, &obj_handler);
    gameLoop(&game);
    destroyGame(&game);

    SDL_Quit();

    printf("quit game!\n");

    return 0;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

