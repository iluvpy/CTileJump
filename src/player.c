#include "player.h"



/* 
   the current sprite sheet is a 256x256 image that consists of 16
   64x64 images (each representing one possible player sprite)
*/


const char *SPRITE_SHEET_PATH = "./assets/player.png";
const int PLAYER_SPRITE_WIDTH_HEIGHT = 64;

const int PLAYER_FORWARD = 1;
const int MAX_PLAYER_SPEED_X = 200; /* 80 pixels/second */
const int MAX_PLAYER_SPEED_Y = 800; /* 80 pixels/second */
const float SPRITE_SCALE = .2f;

/* 
    these are to be adjusted based on what sprite size one uses,
    and based on how much of the sprite is transparent
*/
const int PLAYER_WIDTH = PLAYER_SPRITE_WIDTH_HEIGHT * SPRITE_SCALE; 
/* for transparent part of sprite */
const int PLAYER_TRANSPARENT_PADDING = 25;
const int PLAYER_TRANSPARENT_PADDING_Y = 25 * 1.3;

/* PLAYER-IMAGE X,Y,W,H OFFSETS*/
const int PLAYER_IMAGE_X_OFFSET = 10;
const int PLAYER_IMAGE_Y_OFFSET = 7;
const int PLAYER_IMAGE_W_OFFSET = -35;
const int PLAYER_IMAGE_H_OFFSET = -22;

/* current direction the player is accelerating toward*/
const char MOVE_LEFT = 1;
const char MOVE_RIGHT = 2;
const char MOVE_UP = 3;


const double PLAYER_GRAVITY = 300; 
const double PLAYER_JUMP_SPEED = 300; /* pixels/second */

const double PLAYER_DECELERATION = .2; /* lose 80% of velocity when releasing A or D key */

Player *createPlayer(SDL_Renderer *renderer) {
    Player *new_player = malloc(sizeof(Player));

    Image *new_sprite_sheet = createImage(renderer, 0, 0, SPRITE_SHEET_PATH);
    new_player->sprite_sheet = new_sprite_sheet;   
    new_player->current_sprite_indexI = 0;
    new_player->current_sprite_indexJ = 0;

    new_player->x = 0;
    new_player->y = 0;

    new_player->dx = 0;
    new_player->dy = 0;
    new_player->on_tile = false;
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

    DEBUG_THIS(
        /* draw rect showing collision border */
        clip_rect.x = player->x + PLAYER_IMAGE_X_OFFSET;
        clip_rect.y = player->y + PLAYER_IMAGE_Y_OFFSET;
        clip_rect.w += PLAYER_IMAGE_W_OFFSET;
        clip_rect.h += PLAYER_IMAGE_H_OFFSET;
        SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
        SDL_RenderDrawRect(renderer, &clip_rect);
    )
}

void updatePlayer(Player *player, TileHandler *tile_handler, GameEvents *events,  double dt) {
    double new_x = p_calcNextPlayerPos(player->x, player->dx, dt); 
    double new_y = p_calcNextPlayerPos(player->y, player->dy, dt);

    if (p_playerInsindeGameWin(new_x, player->y)) {
        player->x = new_x;
    }

    if (p_playerInsindeGameWin(player->x, new_y)) {
        player->y = new_y;
    } else if (player->y <= 20) { /* player has hit the top of the window */
        player->dy = 0;
    }

    /* key presses */
    p_handlePlayerInput(player, events);

    /* physics */
    p_updatePlayerGravity(player, dt);


    setImagePosOnScreen(player->sprite_sheet, (int)player->x, (int)player->y);
}


void p_handlePlayerInput(Player *player, GameEvents *events) {
    if (events->pressed_space) {
        player->dy = -PLAYER_JUMP_SPEED;
    }
    if (events->holdLeft) {
        p_movePlayer(player, MOVE_LEFT);
    } 

    if (events->holdright) {
        p_movePlayer(player, MOVE_RIGHT);
    }

    if (events->released_left || events->released_right) {
        player->dx *= PLAYER_DECELERATION;
    }
}


void p_movePlayer(Player *player, char direction) {
    if (direction == MOVE_LEFT &&
        player->dx - 1 > -MAX_PLAYER_SPEED_X) {
        player->dx--;
        
    }

    if (direction == MOVE_RIGHT &&
        player->dx < MAX_PLAYER_SPEED_X) {
        player->dx++;
    }

    // if (direction == MOVE_DOWN &&
    //     player->dy - 1 < MAX_PLAYER_SPEED_Y) {
    //     player->dy++;
    // }
}

void p_updatePlayerGravity(Player *player, double dt) {
    double new_dy = player->dy + PLAYER_GRAVITY * dt;
    if (new_dy <= MAX_PLAYER_SPEED_Y) {
        player->dy = new_dy;
    }
}

bool p_playerInsindeGameWin(double x, double y) {
    return x >= 0 && 
           y >= 0 &&
           x + PLAYER_WIDTH + PLAYER_TRANSPARENT_PADDING <= WINDOW_WIDTH &&
           y + PLAYER_WIDTH + PLAYER_TRANSPARENT_PADDING_Y  <= WINDOW_HEIGHT;
}

double p_calcNextPlayerPos(double oldPos, double speed, double dt) {
    return oldPos + dt * speed; /* ms to second conversion through 1000 division */
}

bool p_onTile(Player *player, TileHandler *tile_handler) {

    return false;
}


void p_destroyPlayer(Player *player) {
    if (!player) {
        DEBUG_STR("tried to destroy Player* - NULPTR\n");
        return;
    }
    
    free(player->sprite_sheet);
    free(player);
}