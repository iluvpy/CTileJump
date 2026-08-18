#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG /* TODO comment out to delete debug messages */

#ifdef DEBUG
    #define DEBUG_STR(str) printf("%s", str)
#else 
    #define DEBUG_STR(str)
#endif

void initUtil();

void p_utilInitRandom();

int random_int(int min, int max);