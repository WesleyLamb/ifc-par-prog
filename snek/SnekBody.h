#ifndef SnekBody_h
#define SnekBody_h

#include "SnekHead.h"

typedef struct SnekSeg {
    int x;
    int y;
    struct sSnekBody *next;
} SnekSeg;

SnekSeg* createSnekSeg();

#endif