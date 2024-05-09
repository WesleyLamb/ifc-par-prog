#ifndef EnemyList_h
#define EnemyList_h

#include "Enemy.h"

typedef struct {
    Enemy* head;
    Enemy* tail;
    int size;
} EnemyList;

EnemyList* createEnemyList();
void insertEnemyNode(EnemyList* aList, Enemy* aEnemy);
void removeEnemyNode(EnemyList* aList, Enemy* aEnemy);

#endif