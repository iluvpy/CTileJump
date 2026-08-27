#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "rect.h"

typedef struct {
    int x, y;
    int w, h;
    float scale;
    SDL_Texture *texture;    
} Image;

Image *createImage(SDL_Renderer *renderer, int x, int y, const char *image_path);
void imageSetPos(Image *image, int x, int y); 
void drawImage(Image *image, SDL_Renderer *renderer);
void destroyImage(Image *image);