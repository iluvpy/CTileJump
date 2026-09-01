#pragma once

#include <stdbool.h>

#include "image.h"
#include "timeHandler.h"
#include "events.h"
#include "tiles.h"
#include "debug.h"
#include "util.h"
#include "constants.h"

/* 
   the current sprite sheet is a 256x256 image that consists of 16
   64x64 images (each representing one possible player sprite)
*/


typedef struct {
    double x, y;
    double dx, dy; /* pixels/second speed */
    int current_sprite_indexI;
    int current_sprite_indexJ;
    bool on_tile;
    Image *sprite_sheet;
} Player;

Player *createPlayer(SDL_Renderer *renderer);
void drawPlayer(Player *player, SDL_Renderer *renderer);
void updatePlayer(Player *player, TileHandler *tile_handler, GameEvents *events, double dt);
double p_calcNextPlayerPos(double oldPos, double speed, double dt);
void p_movePlayer(Player *player, char direction);
void p_handlePlayerInput(Player *player, GameEvents *events);

void p_updatePlayerGravity(Player *player, double dt);
bool p_playerInsindeGameWin(double x, double y);
bool p_onTile(Player *player, TileHandler *tile_handler);
void p_destroyPlayer(Player *player);