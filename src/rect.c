#include "rect.h"
#include "util.h"
#include "debug.h"

GameRect *createGameRect(double x, double y, double w, double h, SDL_Color color) {
    GameRect *g_rect = malloc(sizeof(GameRect));

    g_rect->x = x;
    g_rect->y = y;
    g_rect->w = w;
    g_rect->h = h;

    g_rect->color.r = color.r;
    g_rect->color.g = color.g;
    g_rect->color.b = color.b;
    g_rect->color.a = color.a;

    return g_rect;
}

void fillGameRect(GameRect *g_rect, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer,
                           g_rect->color.r, 
                           g_rect->color.g,
                           g_rect->color.b,
                           g_rect->color.a);
    
    
    SDL_Rect sdl_rect = {
        (int)g_rect->x, 
        (int)g_rect->y, 
        (int)g_rect->w, 
        (int)g_rect->h 
    };
    
    SDL_RenderFillRect(renderer, &sdl_rect);
}

SDL_Rect gRectGetSDLRect(GameRect *g_rect) {
    SDL_Rect r;
    r.x = g_rect->x;
    r.y = g_rect->y;
    r.w = g_rect->w;
    r.h = g_rect->h;
    return r;
}

void destroyGameRect(GameRect *g_rect) {
    if (g_rect == NULL){
        DEBUG_STR("destroyGameRect got NULL as ptr!\n");
        return;
    }
    free(g_rect);
}

