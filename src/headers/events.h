#pragma once

#include "util.h"

typedef struct {
    bool pressed_space;
    bool released_left;
    bool released_right;
    bool holdLeft; /* A key */
    bool holdright; /* D key */
    // bool was_holdingLeft;
    // bool was_holdingright;
    bool quit;
} GameEvents;

// polls events and updates the GameEvents struct accordinglys
void updateGameEvents(GameEvents *game_events);
void initGameEvents(GameEvents *game_events);