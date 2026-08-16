#pragma once

#include <stdio.h>

#define CHECK_ALLOCATED(PTR, VAR_NAME) if (PTR == NULL) {printf("%s could not be allocated", VAR_NAME);}