#include "Plane.h"
#include <stdlib.h>

Plane *createNewPlane(int aX, int aY)
{
    Plane* plane = malloc(sizeof(Plane));
    plane->height = PLANE_HEIGHT;
    plane->width = PLANE_WIDTH;
    plane->lives = PLANE_STARTING_LIVES;
    plane->x = aX;
    plane->y = aY;
    plane->score = 0;

    return plane;
}
