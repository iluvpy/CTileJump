#pragma once

#include <SDL2/SDL.h>


typedef struct GameObject {
    int dx, dy;
    int x, y, w, h;
    SDL_Color *color;
} GameObject;

void initGameObject(GameObject *object, int x, int y, int w, int h, SDL_Color);
void destroyGameObject(GameObject *object);

typedef struct ObjectHandler {
    GameObject **obj_handler; 
    uint16_t count;
} ObjectHandler;

void initObjectHandler(ObjectHandler *obj_handler);
void destroyObjectHandler(ObjectHandler *obj_handler);

// frees the space the object handler has used
void destroyObjectHandler(ObjectHandler *obj_handler);

// adds one object to the object handler, uses heap
void addObject(ObjectHandler *obj_handler, GameObject *object);