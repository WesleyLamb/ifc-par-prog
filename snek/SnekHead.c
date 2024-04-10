#include "SnekHead.h"
#include <stdlib.h>

SnekHead* createSnek() {
    SnekHead* sn = malloc(sizeof(SnekHead));
    sn->x = 3;
    sn->y = 0;
    sn->x_step = 1;
    sn->y_step = 0;



    return sn;
}