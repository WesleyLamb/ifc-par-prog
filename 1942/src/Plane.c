#include "Plane.h"
#include <stdlib.h>

Plane *createNewPlane(int aX, int aY)
{
    Plane* plane = malloc(sizeof(Plane));
    plane->height = PLANE_HEIGHT;
    plane->width = PLANE_WIDTH;
    plane->lifes = PLANE_STARTING_LIFES;
    plane->x = aX;
    plane->y = aY;

    return plane;
}
