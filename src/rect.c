#include "rect.h"

GameRect *createGameRect(int x, int y, int w, int h, SDL_Color color) {
    GameRect *g_rect = malloc(sizeof(GameRect));

    g_rect->x = x;
    g_rect->y = y;
    g_rect->w = w;
    g_rect->h = h;

    g_rect->color = malloc(sizeof(SDL_Color));

    g_rect->color->r = color.r;
    g_rect->color->g = color.a;
    g_rect->color->b = color.b;
    g_rect->color->a = color.a;

    return g_rect;
}

void fillGameRect(GameRect *g_rect, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer,
                           g_rect->color->r,
                           g_rect->color->g,
                           g_rect->color->b,
                           g_rect->color->a);
    
    SDL_Rect sdl_rect = {
        g_rect->x, 
        g_rect->y, 
        g_rect->w, 
        g_rect->h 
    };
    SDL_RenderFillRect(renderer, &sdl_rect);
}


void destroyGameRect(GameRect *g_rect) {
    free(g_rect->color);
    free(g_rect);
}

