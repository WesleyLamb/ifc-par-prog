#ifndef Projectile_h
#define Projectile_h

#define PROJECTILE "|"

typedef struct sProjectile {
    int x;
    int y;
    int stepX;
    int stepY;
    struct sProjectile* next;
    struct sProjectile* prev;
} Projectile;

Projectile* createProjectile(int, int, int, int);

#endif