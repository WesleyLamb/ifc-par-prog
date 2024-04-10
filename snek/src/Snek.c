#include "Snek.h"
#include <stdlib.h>

Snek* createNewSnek() {
    Snek *snek = malloc(sizeof(Snek));
    snek->x = 3;
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
    seg->next->x_step = seg->x_step;
    seg->next->y_step = seg->y_step;

    seg->next->x = seg->x - seg->x_step;
    seg->next->y = seg->y - seg->y_step;

    seg->next->prev = seg;
}

void moveSnek(Snek* snek) {
    Snek* sn = snek;
    while (NULL != sn->next) {
        sn = sn->next;
    }
    while (NULL != sn) {
        if (NULL != sn->prev) {
            sn->x_step = sn->prev->x_step;
            sn->y_step = sn->prev->y_step;
            applyMove(sn);
        } else {
            applyMove(sn);
        }
        sn = sn->prev;
    }
}

void applyMove(Snek* snek) {
    snek->x += snek->x_step;
    snek->y += snek->y_step;
}

void setSnekDirection(Snek* snek, int x, int y) {
    if ((snek->x_step + x != 0) && (snek->y_step + y != 0)) {
        snek->x_step = x;
        snek->y_step = y;
    }
}