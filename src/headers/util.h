#pragma once

#include <stdio.h>

#define DEBUG /* comment out to delete debug messages */

#ifdef DEBUG
    #define DEBUG_STR(str) printf("%s", str)
#else 
    #define DEBUG_STR(str)
#endif