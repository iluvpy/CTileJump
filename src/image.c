#include "image.h"
#include "util.h"
#include "debug.h"

Image *createImage(SDL_Renderer *renderer, int x, int y, const char *image_path) {

    Image *image = malloc(sizeof(Image));
    image->texture = IMG_LoadTexture(renderer, image_path);
    
    if (!image->texture) {
        DEBUG_STR("failed to load player texture...\n");
    }

    setImagePos(image, x, y);

    int w, h;
    SDL_QueryTexture(image->texture, NULL, NULL, &w, &h);
   
    image->w = w;
    image->h = h;

    return image;
}

void drawFullImage(Image *image, SDL_Renderer *renderer) {
    SDL_Rect tmp_rect = imageToSDLRect(image);
    SDL_RenderCopy(renderer, image->texture, NULL, &tmp_rect);
}


void drawClippedImage(Image *image, SDL_Renderer *renderer, SDL_Rect *clip_rect) {
    SDL_Rect tmp_rect = imageToSDLRect(image);
    tmp_rect.w *= image->scale;
    tmp_rect.h *= image->scale;
    SDL_RenderCopy(renderer, image->texture, clip_rect, &tmp_rect);
}

SDL_Rect imageToSDLRect(Image *image) {
    SDL_Rect tmp_rect = {
        image->x, 
        image->y, 
        image->w,
        image->h
    };
    return tmp_rect;
}

void setImagePos(Image *image, int x, int y) {
    image->x = x;
    image->y = y;
}

void setImageScale(Image * image, float scale) {
    image->scale = scale;
}

void destroyImage(Image *image) {
    if (!image) {
        DEBUG_STR("tried to free nullptr image*\n");
    }
    free(image);
}
