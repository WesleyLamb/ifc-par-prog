#ifndef Plane_h
#define Plane_h

#define PLANE_HEIGHT 5
#define PLANE_WIDTH 5
#define PLANE_STARTING_LIFES 3

typedef struct {
    int width;
    int height;
    int x;
    int y;
    int lifes;
} Plane;

Plane* createNewPlane(int aX, int aY);

#endif