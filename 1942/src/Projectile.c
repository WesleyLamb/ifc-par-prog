#include "Projectile.h"
#include <stdlib.h>

Projectile* createProjectile(int aX, int aY, int aStepX, int aStepY) {
    Projectile* projectile = malloc(sizeof(Projectile));
    projectile->x = aX;
    projectile->y = aY;
    projectile->stepX = aStepX;
    projectile->stepY = aStepY;
    projectile->next = NULL;
    projectile->prev = NULL;
    return projectile;
}