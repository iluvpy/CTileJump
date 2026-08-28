#pragma once 

#include <stdio.h>

#ifndef DEBUG
    #define DEBUG /* TODO comment out to delete debug messages */
#endif

#ifdef DEBUG
    #define DEBUG_STR(str) printf("in %s debug on line %d: \n%s",__FILE__, __LINE__, str)
#else 
    #define DEBUG_STR(str)
#endif
