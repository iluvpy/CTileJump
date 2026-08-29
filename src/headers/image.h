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
void setImagePosOnScreen(Image *image, int x, int y); 
void drawFullImage(Image *image, SDL_Renderer *renderer);
void drawClippedImage(Image *image, SDL_Renderer *renderer, SDL_Rect *rect);
void setImageScale(Image * image, float scale);
SDL_Rect imageToSDLRect(Image *image);
void destroyImage(Image *image);