#include "player.h"



/* 
   the current sprite sheet is a 256x256 image that consists of 16
   64x64 images (each representing one possible player sprite)
*/


const char *SPRITE_SHEET_PATH = "./assets/player.png";
const int PLAYER_SPRITE_WIDTH_HEIGHT = 64;

const int MAX_PLAYER_SPEED_X = 200; /* pixels/second */
const int MAX_PLAYER_SPEED_Y = 800; /* pixels/second */


/* PLAYER-IMAGE X,Y,W,H OFFSETS
   since part of the texture is transparent these are needed
*/

/* ============================================================
   THE ONE KNOB — change this to resize the player.
   1.0f = current default size, 1.5f = 150%, 0.5f = 50%, etc.
   ============================================================ */
const float PLAYER_SIZE_PERCENT = 1.0f;

/* ---- base values, tuned by eye at PLAYER_SIZE_PERCENT == 1.0 ---- */
const float BASE_SPRITE_SCALE          = .2f;
const int   BASE_PLAYER_IMAGE_X_OFFSET = 10;
const int   BASE_PLAYER_IMAGE_Y_OFFSET = 7;
const int   BASE_ACTUAL_PLAYER_WIDTH   = 29; 
const int   BASE_ACTUAL_PLAYER_HEIGHT  = 42; 
const int   BASE_PLAYER_FEET_HEIGHT    = 3;

/* ---- derived values — these are what the rest of the file uses ---- */
const float SPRITE_SCALE          = BASE_SPRITE_SCALE          * PLAYER_SIZE_PERCENT;
const int   PLAYER_IMAGE_X_OFFSET = (int)(BASE_PLAYER_IMAGE_X_OFFSET * PLAYER_SIZE_PERCENT);
const int   PLAYER_IMAGE_Y_OFFSET = (int)(BASE_PLAYER_IMAGE_Y_OFFSET * PLAYER_SIZE_PERCENT);
const int   ACTUAL_PLAYER_WIDTH   = (int)(BASE_ACTUAL_PLAYER_WIDTH   * PLAYER_SIZE_PERCENT);
const int   ACTUAL_PLAYER_HEIGHT  = (int)(BASE_ACTUAL_PLAYER_HEIGHT  * PLAYER_SIZE_PERCENT);
const int   PLAYER_FEET_HEIGHT    = (int)(BASE_PLAYER_FEET_HEIGHT    * PLAYER_SIZE_PERCENT) > 0
                                     ? (int)(BASE_PLAYER_FEET_HEIGHT * PLAYER_SIZE_PERCENT) : 1;

/* current direction the player is accelerating toward*/
const char MOVE_LEFT = 1;
const char MOVE_RIGHT = 2;
const char MOVE_UP = 3;

/* physics */
const double PLAYER_BASE_DOWN_VELOCITY = TILE_SPEED;
const double PLAYER_GRAVITY = 400 - PLAYER_BASE_DOWN_VELOCITY; 

const double PLAYER_JUMP_SPEED = 300; /* pixels/second */
const double PLAYER_DECELERATION = .98; /* lose 80% of velocity when releasing A or D key */


Player *createPlayer(SDL_Renderer *renderer) {
    Player *new_player = malloc(sizeof(Player));

    Image *new_sprite_sheet = createImage(renderer, 0, 0, SPRITE_SHEET_PATH);
    new_player->sprite_sheet = new_sprite_sheet;   
    setImageScale(new_player->sprite_sheet, SPRITE_SCALE);

    new_player->current_sprite_indexI = 0;
    new_player->current_sprite_indexJ = 0;

    new_player->x = PLAYER_IMAGE_X_OFFSET;
    new_player->y = PLAYER_IMAGE_Y_OFFSET;

    new_player->dx = 0;
    new_player->dy = 0;
    new_player->can_jump = false;
    new_player->can_fall = true;
    new_player->is_moving = false;
    new_player->standing_on = NULL;

    SDL_Rect collision_rect;
    collision_rect.x = new_player->x;
    collision_rect.y = new_player->y;
    collision_rect.w = ACTUAL_PLAYER_WIDTH;
    collision_rect.h = ACTUAL_PLAYER_HEIGHT;
    new_player->collision_rect = collision_rect;

    new_player->should_jump = false;
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
    
    /* image position is updated in updatePlayer */
    drawClippedImage(player->sprite_sheet, renderer, &clip_rect);

    ON_DEBUG(
        /* draw collision rect */
        SDL_Rect collision_rect = p_getPlayerCollisionRect(player);
        int r = 255;
        int g = 50;
        if (player->can_jump) /* change color when can_jump*/
            r = 50; g = 250;
        SDL_SetRenderDrawColor(renderer, r, g, 50, 255);
        drawThickRect(renderer, collision_rect, DEBUG_LINE_THICKNESS);

        /* draw Texture Rect*/
        SDL_Rect texture_rect = clip_rect;
        texture_rect.x = player->x - PLAYER_IMAGE_X_OFFSET;
        texture_rect.y = player->y - PLAYER_IMAGE_Y_OFFSET;
        SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
        SDL_RenderDrawRect(renderer, &texture_rect);
    )
}

void updatePlayer(Player *player, TileHandler *tile_handler, GameEvents *events,  double dt) {

    /* key presses */
    p_handlePlayerInput(player, events);

    /* friction: runs continuously whenever neither direction is held */
    if (!events->holdLeft && !events->holdright) {
        player->dx *= PLAYER_DECELERATION;
        if (fabs(player->dx) < 1.0) {
            player->dx = 0;
        }
    }

    /* physics */
    p_updatePlayerGravity(player, dt);
    
    // calculate next player position based on velocity (dx, dy) and time passed in last frame
    double next_x = player->x + player->dx * dt; 
    double next_y = player->y + player->dy * dt;

    next_y += PLAYER_BASE_DOWN_VELOCITY * dt; /* base speed is = tile speed */

    if (p_playerInsindeGameWin(
        next_x, 
        player->y, 
        player->collision_rect.w, 
        player->collision_rect.h
    )) {
        player->x = next_x;
    }

    if (p_playerInsindeGameWin(
        player->x, 
        next_y,
        player->collision_rect.w,
        player->collision_rect.h
    )) {
        if (player->can_fall || !p_playerIsFalling(player))  {
            player->y = next_y;
        }
    } else if (next_y <= 0) { /* player has hit the top of the window */
        player->dy = 0;
    }


    /* if player can jump */
    player->can_jump = p_canPlayerJump(player, tile_handler);
    // player->can_jump = true;

    player->is_falling = p_playerIsFalling(player);

    SDL_Rect next_collision_rect = player->collision_rect;
    next_collision_rect.x = next_x;
    next_collision_rect.y = next_y;


    /* disable/enable gravity */
    player->can_fall = p_canPlayerFall(player, next_collision_rect, tile_handler);

    /* 
       update the player sprite position on screen adjusting with offset, 
       since the image has transparent parts
    */
    setImagePosOnScreen(
        player->sprite_sheet, 
        (int)player->x - PLAYER_IMAGE_X_OFFSET, 
        (int)player->y - PLAYER_IMAGE_Y_OFFSET
    );

    player->collision_rect.x = (int)player->x;
    player->collision_rect.y = (int)player->y;


}


void p_handlePlayerInput(Player *player, GameEvents *events) {

    if (events->pressed_space && player->can_jump) {
        player->should_jump = true;
    }

    
    if (player->should_jump && player->can_jump) {
        player->dy = -PLAYER_JUMP_SPEED;
        player->should_jump = false;
    }

    if (events->holdLeft) {
        p_movePlayer(player, MOVE_LEFT);
    } 

    if (events->holdright) {
        p_movePlayer(player, MOVE_RIGHT);
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
    if (!player->can_fall && p_playerIsFalling(player)) return;
    double new_dy = player->dy + PLAYER_GRAVITY * dt;
    if (new_dy <= MAX_PLAYER_SPEED_Y) {
        player->dy = new_dy;
    }
}

bool p_playerInsindeGameWin(double x, double y, double w, double h) {
    return x >= 0 && 
           y >= 0 &&
           x + w <= WINDOW_WIDTH &&
           y + h  <= WINDOW_HEIGHT;
}

/* 
    if the next player position (of the next frame) collides with the actual tile (not collision rect)
*/

bool p_canPlayerFall(Player *player, SDL_Rect next_collision_rect, TileHandler *tile_handler) {
    if (p_isPlayerJumping(player)) return true; /* only tiles matter while moving downward */

    SDL_Rect next_player_feet_rect = p_getPlayerFeetRect(next_collision_rect);  

    for (int i = 0; i < tile_handler->count; i++) {
        GameRect *tile = getTile(tile_handler, i);
        
        SDL_Rect r = gRectGetSDLRect(tile);
        if (rect_collision(r, next_player_feet_rect)) {
            return false;
        }
    }

    return true;
}

SDL_Rect p_getPlayerFeetRect(SDL_Rect player_rect) {
    SDL_Rect feet = player_rect;
    feet.y = player_rect.y + player_rect.h - PLAYER_FEET_HEIGHT;
    feet.h = PLAYER_FEET_HEIGHT;
    return feet;
}




bool p_canPlayerJump(Player *player, TileHandler *tile_handler) {
    
    for (int i = 0; i < tile_handler->count; i++) {
        GameRect *tile = getTile(tile_handler, i);
        SDL_Rect tile_collision = getTileJumpingCollisionRect(tile);

        if (rect_collision(tile_collision, player->collision_rect)) {
            return (tile->y + TILE_HEIGHT * 2) >= player->y + player->collision_rect.h;
        }
    }
    return false;
}

bool p_playerIsFalling(Player *player) {
    return player->dy > 0;
}



SDL_Rect p_getPlayerCollisionRect(Player *player) {
    SDL_Rect collision_rect;
    collision_rect.x = player->x;
    collision_rect.y = player->y;
    collision_rect.w = ACTUAL_PLAYER_WIDTH;
    collision_rect.h = ACTUAL_PLAYER_HEIGHT;
    return collision_rect;
}
bool p_isPlayerJumping(Player *player) {
    return player->dy <= 0;
}


void p_destroyPlayer(Player *player) {
    if (!player) {
        DEBUG_STR("tried to destroy Player* - NULPTR\n");
        return;
    }
    
    free(player->sprite_sheet);
    free(player);
}