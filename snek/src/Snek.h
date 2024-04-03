#ifndef Snek_h
#define Snek_h

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

#endif