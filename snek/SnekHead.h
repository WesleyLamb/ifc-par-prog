#ifndef SnekHead_h
#define SnekHead_h

#include <stdlib.h>
#include "SnekBody.h"

typedef struct {
    int x;
    int y;
    int x_step;
    int y_step;
    SnekSeg *body;
} SnekHead;

SnekHead* createSnek();
void moveSnek(SnekHead*);
void setSnekDirection(SnekHead*);

#endif