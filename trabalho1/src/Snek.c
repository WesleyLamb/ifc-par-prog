#include "Snek.h"
#include <stdlib.h>
#include <stdbool.h>
#include "GameBoard.h"

bool canChangeDirection = true;
bool gameOver = false;

/** Aloca uma nova instância da cobrinha */
Snek* createNewSnek() {
    Snek *snek = malloc(sizeof(Snek));
    snek->x = 3;
    snek->y = 0;
    snek->x_step = 1;
    snek->y_step = 0;
    snek->next = NULL;
    createSnekSeg(snek);
    createSnekSeg(snek);

    return snek;
}

/** Cria um novo segmento */
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
    seg->next->next = NULL;
}

/** Move para tal direção */
void applyMove(Snek* snek) {
    snek->x += snek->x_step;
    snek->y += snek->y_step;
}

/** Muda a direção do prox movimento da cobrinha */
void setSnekDirection(Snek* snek, int x, int y) {
    if ((snek->x_step + x != 0) && (snek->y_step + y != 0) && canChangeDirection) {
        snek->x_step = x;
        snek->y_step = y;
        canChangeDirection = false;
    }
}

