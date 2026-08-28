#include "player.h"

#include "debug.h"
#include "util.h"
#include "timeHandler.h"
#include "constants.h"

/* 
   the current sprite sheet is a 256x256 image that consists of 16
   64x64 images (each representing one possible player sprite)
*/


const char *SPRITE_SHEET_PATH = "./assets/player.png";
const int PLAYER_SPRITE_WIDTH_HEIGHT = 64;
const int PLAYER_FORWARD = 1;
const int PLAYER_SPEED = 100;
const float SPRITE_SCALE = .2f;
const int PLAYER_WIDTH = PLAYER_SPRITE_WIDTH_HEIGHT * SPRITE_SCALE - 10; /*-10 for transparent part of sprite */


Player *createPlayer(SDL_Renderer *renderer) {
    Player *new_player = malloc(sizeof(Player));

    Image *new_sprite_sheet = createImage(renderer, 0, 0, SPRITE_SHEET_PATH);
    new_player->sprite_sheet = new_sprite_sheet;   
    new_player->current_sprite_indexI = 0;
    new_player->current_sprite_indexJ = 0;

    new_player->x = 0;
    new_player->y = 0;

    new_player->dx = 20;
    setImageScale(new_player->sprite_sheet, SPRITE_SCALE);
    return new_player;
}

void drawPlayer(Player *player, SDL_Renderer *renderer) {
    /* rect that points to the sprite in the sprite sheet*/
    int x = player->current_sprite_indexI * PLAYER_SPRITE_WIDTH_HEIGHT;
    int y = player->current_sprite_indexJ * PLAYER_SPRITE_WIDTH_HEIGHT;
    SDL_Rect clip_rect = {
        x,
        y,
        PLAYER_SPRITE_WIDTH_HEIGHT,
        PLAYER_SPRITE_WIDTH_HEIGHT
    };
    
    drawClippedImage(player->sprite_sheet, renderer, &clip_rect);
}

void updatePlayer(Player *player, TimeHandler *time_handler) {
    printf("delta time ms: %f\n", time_handler->dt_ms);
    double new_x = player->x + ((time_handler->dt_ms/1000) * player->dx); 
    printf("new x: %f\n", new_x);
    printf("ms: %f\n", 1000/time_handler->dt_ms);
    if (new_x >= 0 && new_x - PLAYER_WIDTH <= WINDOW_WIDTH) {
        player->x = new_x;
    }

    setImagePos(player->sprite_sheet, (int)player->x, (int)player->y);
}


void destroyPlayer(Player *player) {
    if (!player) {
        DEBUG_STR("tried to destroy Player* - NULPTR\n");
        return;
    }
    
    free(player->sprite_sheet);
    free(player);
}