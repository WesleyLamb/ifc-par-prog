#include "Food.h"
#include "GameBoard.h"

/** Aloca uma nova instância de comida */
Food* createFood() {
    Food* food = malloc(sizeof(Food));
    food->x = 6;
    food->y = 0;
}