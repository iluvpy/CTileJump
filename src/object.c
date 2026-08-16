#include "object.h"

#include "util.h"


void initGameObject(GameObject *object, int x, int y, int w, int h, SDL_Color color) {
    object = malloc(sizeof(GameObject));

    object->x = x;
    object->y = y;
    object->w = w;
    object->h = h;

    object->color = malloc(sizeof(SDL_Color));

    object->color->r = color.r;
    object->color->g = color.a;
    object->color->b = color.b;
    object->color->a = color.a;
    
}


void destroyGameObject(GameObject *object) {
    free(object->color);
    free(object);
}


void initObjectHandler(ObjectHandler *obj_handler) {
    obj_handler->count = 0;
    obj_handler->obj_handler = malloc(sizeof(GameObject*));
}

void destroyObjectHandler(ObjectHandler *obj_handler) {

    if (obj_handler->count == 0) {
        free(obj_handler->obj_handler);
        return;
    }

    for (int i = 0; i <= obj_handler->count; i++) {
        destroyGameObject(obj_handler->obj_handler[i]);
    }
    free(obj_handler->obj_handler);
}

void addObject(ObjectHandler *obj_handler, GameObject *object) {
    if (obj_handler->count) {
        int new_count = obj_handler->count + 1;

        GameObject **new_objects = realloc(obj_handler->obj_handler, sizeof(GameObject) * new_count);
        CHECK_ALLOCATED(new_objects, "new_objects");

        obj_handler->obj_handler = new_objects;
        obj_handler->count++;
        obj_handler->obj_handler[obj_handler->count - 1] = object;

    }
}