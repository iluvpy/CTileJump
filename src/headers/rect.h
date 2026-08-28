#pragma once

#include <SDL2/SDL.h>

typedef struct {
    int x, y, w, h;
    SDL_Color *color;
} GameRect;

GameRect *createGameRect(int x, int y, int w, int h, SDL_Color color);
void fillGameRect(GameRect *g_rect, SDL_Renderer *renderer);
void destroyGameRect(GameRect *object);