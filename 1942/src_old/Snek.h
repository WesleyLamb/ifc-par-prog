#ifndef Snek_h
#define Snek_h 1
#include <stdbool.h>

extern bool canChangeDirection;
extern bool gameOver;
typedef struct sSnek {
    int x;
    int y;
    int x_step;
    int y_step;
    struct sSnek *prev;
    struct sSnek *next;
} Snek;

Snek* createNewSnek();
void createSnekSeg(Snek*);
void applyMove(Snek*);
void setSnekDirection(Snek*, int, int);

#endif