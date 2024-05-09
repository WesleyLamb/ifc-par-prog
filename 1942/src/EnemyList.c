#include "EnemyList.h"
#include <stdlib.h>
#include <stdbool.h>

EnemyList *createEnemyList()
{
    EnemyList* list = malloc(sizeof(EnemyList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void insertEnemyNode(EnemyList *aList, Enemy *aEnemy) {
    if (aList->tail != NULL) {
        aList->tail->next = aEnemy;
        aEnemy->prev = aList->tail;
        aList->tail = aEnemy;
    } else {
        aList->head = aEnemy;
        aList->tail = aEnemy;
    }
    aList->size++;
}

void removeEnemyNode(EnemyList *aList, Enemy *aEnemy) {
    bool removed = false;
    if (aEnemy == aList->head) {
        aList->head = aEnemy->next;
        removed = true;
    }
    if (aEnemy == aList->tail) {
        aList->tail = aEnemy->prev;
        removed = true;
    }
    if (aEnemy->next != NULL) {
        aEnemy->next->prev = aEnemy->prev;
        removed = true;
    }
    if (aEnemy->prev != NULL) {
        aEnemy->prev->next = aEnemy->next;
        aEnemy->next->prev = aEnemy->prev;
        removed = true;
    }

    if (removed) {
        free(aEnemy);
        aList->size--;
    }
}