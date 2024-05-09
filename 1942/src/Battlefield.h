#ifndef Battlefield_h
#define Battlefield_h

#include <stdbool.h>
#include "Plane.h"
#include "EnemyList.h"
#include "ProjectileList.h"

#define BATTLEFIELD_HEIGHT 30
#define BATTLEFIELD_WIDTH 30

#define DOUBLE_LEFT_INTERSECTION "\u2563" // ╣
#define DOUBLE_VERTICAL "\u2551" // ║
#define DOUBLE_UPPER_RIGHT_CORNER "\u2557" // ╗
#define DOUBLE_LOWER_RIGHT_CORNER "\u255D" // ╝
#define DOUBLE_LOWER_LEFT_CORNER "\u255A" // ╚
#define DOUBLE_UPPER_LEFT_CORNER "\u2554" // ╔
#define DOUBLE_RIGHT_INTERSECTION "\u2560" // ╠
#define DOUBLE_HORIZONTAL "\u2550" // ═
#define DOUBLE_CROSS_INTERSECTION "\u256C" // ╬

typedef struct {
    int width;
    int height;
} Battlefield;

Battlefield* createNewBattlefield();
void render(Battlefield*, Plane*, EnemyList*, ProjectileList*, ProjectileList*);
void movePlane(Plane *, int, int);
void update(Battlefield*, Plane*, EnemyList*, ProjectileList*, ProjectileList*);

#endif