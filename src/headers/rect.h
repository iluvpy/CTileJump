#pragma once

#include <SDL2/SDL.h>

typedef struct {
    double x, y, w, h;
    SDL_Color color;
} GameRect;

GameRect *createGameRect(double x, double y, double w, double h, SDL_Color color);
void fillGameRect(GameRect *g_rect, SDL_Renderer *renderer);
SDL_Rect gRectGetSDLRect(GameRect *g_rect);
void destroyGameRect(GameRect *object);