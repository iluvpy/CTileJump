#pragma once

#include <stdbool.h>

#include "image.h"
#include "timeHandler.h"
#include "events.h"

/* 
   the current sprite sheet is a 256x256 image that consists of 16
   64x64 images (each representing one possible player sprite)
*/

extern const char MOVE_LEFT;
extern const char MOVE_RIGHT;
extern const char MOVE_UP;

typedef struct {
    double x, y;
    double dx, dy; /* pixels/second speed */
    int current_sprite_indexI;
    int current_sprite_indexJ;
    Image *sprite_sheet;
} Player;

Player *createPlayer(SDL_Renderer *renderer);
void drawPlayer(Player *player, SDL_Renderer *renderer);
void updatePlayer(Player *player, GameEvents *events, double dt);
double calcNextPos(double oldPos, double speed, double dt);
void movePlayer(Player *player, char direction);
void handlePlayerInput(Player *player, GameEvents *events);
void updatePlayerGravity(Player *player, double dt);
bool posInsindeGameWin(double x, double y);
void destroyPlayer(Player *player);