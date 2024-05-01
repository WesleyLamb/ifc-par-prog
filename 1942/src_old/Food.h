#ifndef Food_h
#define Food_h
#include <stdlib.h>

#include "Snek.h"

typedef struct Food {
    int x;
    int y;
} Food;

Food* createFood();

#endif