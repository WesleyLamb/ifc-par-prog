#include "Enemy.h"
#include <stdlib.h>

Enemy *createEnemy(int aX, int aY, int aStepX, int aStepY)
{
    Enemy* enemy = malloc(sizeof(Enemy*));
    enemy->x = aX;
    enemy->y = aY;
    enemy->stepX = aStepX;
    enemy->stepY = aStepY;
    enemy->prev = NULL;
    enemy->next = NULL;
    return enemy;
}
