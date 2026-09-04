#pragma once

#include <stdbool.h>

#include "image.h"
#include "timeHandler.h"
#include "events.h"
#include "tiles.h"
#include "debug.h"
#include "util.h"

/* 
   the current sprite sheet is a 256x256 image that consists of 16
   64x64 images (each representing one possible player sprite)
*/


typedef struct {
    double x, y;
    double dx, dy; /* pixels/second speed */
    int current_sprite_indexI;
    int current_sprite_indexJ;
    bool can_jump;
    bool can_fall;
    bool should_jump;
    bool is_moving;
    bool is_falling;
    bool is_jumping;
    SDL_Rect collision_rect;
    GameRect *standing_on;
    Image *sprite_sheet;
} Player;

Player *createPlayer(SDL_Renderer *renderer);
void drawPlayer(Player *player, SDL_Renderer *renderer);
void updatePlayer(Player *player, TileHandler *tile_handler, GameEvents *events, double dt);
void p_movePlayer(Player *player, char direction);
void p_handlePlayerInput(Player *player, GameEvents *events);

void p_updatePlayerGravity(Player *player, double dt);

bool p_playerInsindeGameWin(double x, double y, double w, double h);
bool p_canPlayerFall(Player *player, SDL_Rect next_collision_rect, TileHandler *tile_handler);
bool p_playerIsFalling(Player *player);
bool p_playerIsMoving(Player *player);
bool p_isPlayerMovingLeft(Player *player);
bool p_isPlayerMovingRight(Player *player);
bool p_canPlayerJump(Player *player, TileHandler *tile_handler);
bool p_isPlayerJumping(Player *player);
SDL_Rect p_getPlayerFeetRect(SDL_Rect player_rect);
// bool p_playerIsMoving(Player *player);
SDL_Rect p_getPlayerCollisionRect(Player *player);

void p_destroyPlayer(Player *player);


