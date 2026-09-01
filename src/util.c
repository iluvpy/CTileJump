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
    return isPointInRect(r1.x, r1.y, r2) || 
           isPointInRect(r1.x + r1.w, r1.y, r2) ||
           isPointInRect(r1.x, r1.y + r1.h, r2) ||
           isPointInRect(r1.x + r1.w, r1.y + r1.h, r2);
}

bool isPointInRect(int x, int y, SDL_Rect r) {
    return x >= r.x && 
           x <= r.x + r.w && 
           y >= r.y && 
           y <= r.y + r.h;
}