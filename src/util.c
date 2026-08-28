#include "util.h"



void initUtil() {
    p_utilInitRandom();
}

void p_utilInitRandom() {
    srand(time(NULL));
}


int random_int(int min, int max) {
    return (rand() % max) + min;
}