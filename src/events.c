#include "events.h"


#include <SDL2/SDL.h>
#include <stdio.h>

// polls events and updates the GameEvents struct accordinglys
void updateGameEvents(GameEvents *game_events) {
    SDL_Event event;
    game_events->pressed_space = false;
    game_events->released_left = false;
    game_events->released_right = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game_events->quit = true;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                game_events->pressed_space = true;
            } 
            
            if (event.key.keysym.sym == SDLK_a) {
                game_events->holdLeft = true;
            } 
            
            if (event.key.keysym.sym == SDLK_d) {
                game_events->holdright = true;
            }
        }

        if (event.type == SDL_KEYUP) {
            printf("oh keyup!!\n");
            if (event.key.keysym.sym == SDLK_a) {
                game_events->released_left = true;
                game_events->holdLeft = false;
            } 
            
            if (event.key.keysym.sym == SDLK_d) {
                game_events->released_right = true;
                game_events->holdright = false;
            } 
        }
    }
}

void initGameEvents(GameEvents *game_events) {
    game_events->holdLeft = false;
    game_events->holdright = false;
    game_events->released_left = false;
    game_events->released_right = false;
    game_events->pressed_space = false;
    game_events->quit = false;
}