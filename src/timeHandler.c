
#define _POSIX_C_SOURCE 199309L /*for clock_gettime*/

#include "timeHandler.h"
#include "debug.h"

#include <stdlib.h> /*makes malloc work here for some reason*/

TimeHandler *createTimeHandler() {
    
    TimeHandler *new_time_handler = malloc(sizeof(TimeHandler));
    new_time_handler->dt_ms = 0;
    return new_time_handler;
}

void dt_start(TimeHandler *time_handler) {
    clock_gettime(CLOCK_MONOTONIC, &time_handler->start);
}
void dt_end(TimeHandler *time_handler) {
    clock_gettime(CLOCK_MONOTONIC, &time_handler->end);
    time_handler->dt_ms = (time_handler->end.tv_sec - time_handler->start.tv_sec) * 1000.0 +
                          (time_handler->end.tv_nsec - time_handler->start.tv_nsec) / 1.0e6;
}

void destroyTimeHandler(TimeHandler *handler) {
    if (!handler) {
        DEBUG_STR("tried to destroy TimeHandler nullptr!");
        return;
    }
    free(handler);
}