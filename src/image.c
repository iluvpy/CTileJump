#include "image.h"

Image *createImage(SDL_Renderer *renderer, int x, int y, const char *image_path) {

    Image *image = malloc(sizeof(Image));
    image->texture = IMG_LoadTexture(renderer, image_path);
    
    if (!image->texture) {
        printf("failed to load player texture...");
    }

    imageSetPos(image, x, y);

    int w, h;
    SDL_QueryTexture(image->texture, NULL, NULL, &w, &h);
   
    image->w = w;
    image->h = h;

    return image;
}

void drawImage(Image *image, SDL_Renderer *renderer) {

    SDL_Rect tmp_rect = {
        image->x, 
        image->y, 
        image->w,
        image->h
    };
    
    SDL_RenderCopy(renderer, image->texture, NULL, &tmp_rect);

}

void imageSetPos(Image *image, int x, int y) {
    image->x = x;
    image->y = y;
}

void destroyImage(Image *image) {
    free(image);
}
