#pragma once

#include "constants.h"

typedef struct {
    bool pressed_space;
    bool holdLeft;
    bool holdright;
    bool was_holdingLeft;
    bool was_holdingright;
    bool quit;
} GameEvents;

// polls events and updates the GameEvents struct accordinglys
void updateGameEvents(GameEvents *game_events);
void initGameEvents(GameEvents *game_events);