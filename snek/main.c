#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __linux
#include<unistd.h>
#elif _WIN32
#include<windows.h>
#endif

#include "src/GameBoard.h"
#include "src/Snek.h"
#include "src/Food.h"

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 30

void startGame(GameBoard*, Snek*, Food*);

int main () {
    GameBoard* gameBoard = createGameBoard(BOARD_HEIGHT, BOARD_WIDTH);
    Snek* snek = createNewSnek();
    Food* food = createFood();
    startGame(gameBoard, snek, food);

    free(food);
    free(snek);
    free(gameBoard);
}

void startGame(GameBoard* gameBoard, Snek* snek, Food* food) {
    bool gameOver = false;
    while (!gameOver) {
        render(gameBoard, snek, food);
        #ifdef __linux
        sleep(1);
        #elif _WIN32
        Sleep(1000);
        #endif
    }
}