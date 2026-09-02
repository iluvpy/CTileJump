#pragma once 

#include <stdio.h>

#ifndef DEBUG
    #define DEBUG /* TODO comment out to delete debug messages */
#endif

#ifndef DEBUG_CODE   /* TODO comment out to remove extra debug info*/
    #define DEBUG_CODE
#endif

#if defined(DEBUG_CODE) && !defined(ON_DEBUG)
    #define ON_DEBUG(code) code
    #define DEBUG_LINE_THICKNESS 4
#endif

#ifdef DEBUG
    //#define NO_TILE_MOVEMENT uncomment to stop tile movement
    #define DEBUG_STR(str) printf("in %s debug on line %d: \n%s",__FILE__, __LINE__, str)
#else 
    #define DEBUG_STR(str)
#endif


