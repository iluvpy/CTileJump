#pragma once

#include <time.h>

typedef struct {
    double dt_ms;
    struct timespec start, end;
} TimeHandler;

TimeHandler *createTimeHandler();
void dt_start(TimeHandler *time_handler);
void dt_end(TimeHandler *time_handler);
void destroyTimeHandler(TimeHandler *time_handler);