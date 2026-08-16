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
    ObjectHandler objHandler;

    initGame(&game, &events, &objHandler);
    gameLoop(&game);

    printf("quit game because gameLoop() finished");

    destroyGame(&game);

    SDL_Quit();
    return 0;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

