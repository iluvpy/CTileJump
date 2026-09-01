#pragma once 

#include <stdio.h>

#ifndef DEBUG
    #define DEBUG /* TODO comment out to delete debug messages */
#endif

#ifndef DEBUG_CODE  
    #define DEBUG_CODE
#endif

#if defined(DEBUG_CODE) && !defined(DEBUG_THIS)
    #define DEBUG_THIS(code) code
#endif

#ifdef DEBUG
    #define DEBUG_STR(str) printf("in %s debug on line %d: \n%s",__FILE__, __LINE__, str)
#else 
    #define DEBUG_STR(str)
#endif

