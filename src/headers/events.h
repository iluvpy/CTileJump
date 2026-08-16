#pragma once

#include "constants.h"

typedef struct GameEvents {
    bool pressed_space;
    bool holdLeft;
    bool holdright;
    bool quit;
} GameEvents;

// polls events and updates the GameEvents struct accordinglys
void updateEvents(GameEvents *game_events);
void initGameEvents(GameEvents *game_events);