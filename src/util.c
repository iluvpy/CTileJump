#include "util.h"



void initUtil() {
    p_utilInitRandom();
}

void p_utilInitRandom() {
    srand(time(NULL));
}


int random_int(int min, int max) {
    return (rand() % max) + min;
}

bool rect_collision(SDL_Rect r1, SDL_Rect r2) { 
    /* check if one point of the corners of r1 is inside of r2 */
    return r1.x < r2.x + r2.w &&
           r1.x + r1.w > r2.x &&
           r1.y < r2.y + r2.h &&
           r1.y + r1.h > r2.y;
}

bool isPointInRect(int x, int y, SDL_Rect r) {
    return x >= r.x && 
           x <= r.x + r.w && 
           y >= r.y && 
           y <= r.y + r.h;
}

void drawThickRect(SDL_Renderer *renderer, SDL_Rect r, int thickness)
{
    // Top
    SDL_Rect top = {
        r.x,
        r.y,
        r.w,
        thickness
    };

    // Bottom
    SDL_Rect bottom = {
        r.x,
        r.y + r.h - thickness,
        r.w,
        thickness
    };

    // Left
    SDL_Rect left = {
        r.x,
        r.y + thickness,
        thickness,
        r.h - 2 * thickness
    };

    // Right
    SDL_Rect right = {
        r.x + r.w - thickness,
        r.y + thickness,
        thickness,
        r.h - 2 * thickness
    };

    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
}