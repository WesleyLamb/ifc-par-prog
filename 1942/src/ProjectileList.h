#ifndef ProjectileList_h
#define ProjectileList_h

#include "Projectile.h"

typedef struct {
    Projectile* head;
    Projectile* tail;
    int size;
} ProjectileList;

ProjectileList* createProjectileList();
void insertProjectileNode(ProjectileList* aList, Projectile* aProjectile);
void removeProjectileNode(ProjectileList* aList, Projectile* aProjectile);

#endif