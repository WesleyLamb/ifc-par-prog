#include "Snek.h"
#include <stdlib.h>

Snek* createNewSnek() {
    Snek *snek = malloc(sizeof(Snek));
    snek->x = 4;
    snek->y = 0;
    snek->x_step = 1;
    snek->y_step = 0;
    createSnekSeg(snek);
    createSnekSeg(snek);

    return snek;
}

void createSnekSeg(Snek* snek) {
    Snek* seg = snek;
    while (NULL != seg->next) {
        seg = seg->next;
    };
    seg->next = malloc(sizeof(Snek));
    seg->next->x = seg->x - seg->x_step;
    seg->next->y = seg->y - seg->y_step;
    seg->next->prev = seg;
}