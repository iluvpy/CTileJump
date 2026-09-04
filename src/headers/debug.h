#pragma once 

#include <stdio.h>

#ifndef DEBUG
    #define DEBUG /* TODO comment out to delete debug messages */
#endif

/* comment out "code" to remove specific debug code (mostly used for rendering useful visualizations)*/
#ifndef DEBUG_CODE 
    #define ON_DEBUG(code) //code /* <- 'code' */
    #define DEBUG_LINE_THICKNESS 4
#endif

#ifdef DEBUG
    //#define NO_TILE_MOVEMENT uncomment to stop tile movement
    #define DEBUG_STR(str) printf("in %s debug on line %d: \n%s",__FILE__, __LINE__, str)
#else 
    #define DEBUG_STR(str)
#endif


