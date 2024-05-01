#ifndef EnemiesList_h
#define EnemiesList_h

#include "Enemy.h"

typedef struct {
    Enemy* enemy;
    Enemy* prev;
} EnemiesList;

#endif