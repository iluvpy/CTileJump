#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void initUtil();

void p_utilInitRandom();

int random_int(int min, int max);
bool rect_collision(SDL_Rect r1, SDL_Rect r2);
bool isPointInRect(int x, int y, SDL_Rect r);