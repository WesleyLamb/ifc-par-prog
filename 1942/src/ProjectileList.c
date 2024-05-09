#include "ProjectileList.h"
#include <stdlib.h>
#include <stdbool.h>

ProjectileList *createProjectileList()
{
    ProjectileList* list = malloc(sizeof(ProjectileList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void insertProjectileNode(ProjectileList *aList, Projectile *aProjectile)
{
    if (aList->tail != NULL) {
        aList->tail->next = aProjectile;
        aProjectile->prev = aList->tail;
        aList->tail = aProjectile;
    } else {
        aList->head = aProjectile;
        aList->tail = aProjectile;
    }
    aList->size++;
}

void removeProjectileNode(ProjectileList *aList, Projectile *aProjectile)
{
    bool removed = false;
    if (aProjectile == aList->head) {
        aList->head = aProjectile->next;
        removed = true;
    }
    if (aProjectile == aList->tail) {
        aList->tail = aProjectile->prev;
        removed = true;
    }
    if (aProjectile->next != NULL) {
        aProjectile->next->prev = aProjectile->prev;
        removed = true;
    }
    if (aProjectile->prev != NULL) {
        aProjectile->prev->next = aProjectile->next;
        aProjectile->next->prev = aProjectile->prev;
        removed = true;
    }

    if (removed) {
        free(aProjectile);
        aList->size--;
    }
}
