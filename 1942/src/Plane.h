#ifndef Plane_h
#define Plane_h

#define PLANE_HEIGHT 5
#define PLANE_WIDTH 5
#define PLANE_STARTING_LIVES 3

#define PLANE_HEAD "^"
#define PLANE_LEFT_WING "<"
#define PLANE_HORIZONTAL_SEG "-"
#define PLANE_CROSS_SEG "+"
#define PLANE_VERTICAL_SEG "|"
#define PLANE_RIGHT_WING ">"
#define PLANE_TAIL "^"

typedef struct {
    int width;
    int height;
    int x;
    int y;
    int lives;
    int score;
} Plane;

Plane* createNewPlane(int aX, int aY);

#endif