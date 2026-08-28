#pragma once

#include "image.h"
#include "timeHandler.h"

/* 
   the current sprite sheet is a 256x256 image that consists of 16
   64x64 images (each representing one possible player sprite)
*/


typedef struct {
    double x, y;
    double dx, dy;
    int current_sprite_indexI;
    int current_sprite_indexJ;
    Image *sprite_sheet;
} Player;

Player *createPlayer(SDL_Renderer *renderer);
void drawPlayer(Player *player, SDL_Renderer *renderer);
void updatePlayer(Player *player, TimeHandler *time_handler);
void destroyPlayer(Player *player);