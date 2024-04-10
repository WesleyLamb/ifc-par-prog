#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>

#ifdef __linux

#include <unistd.h>
#include <termios.h>
struct termios original; // A struct to save the original state of terminal

#elif _WIN32
#include<windows.h>

#endif

#include "src/GameBoard.h"
#include "src/Snek.h"
#include "src/Food.h"

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 30
#define KEY_LEFT 'D'
#define KEY_UP 'A'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

Snek* snek;
Food* food;
bool gameOver = false;

void startGame(GameBoard*, Snek*, Food*);
void endProcess(int);
void enableRAWMode();
void disableRAWMode();
void* runGame(void*);
void* readKeys(void*);

int main () {
    signal(SIGINT, endProcess);
    enableRAWMode();

    pthread_t id_game, id_read;

    pthread_create(&id_game, NULL, &runGame, NULL);
    pthread_create(&id_read, NULL, &readKeys, NULL);

    pthread_join(id_game, NULL);
    pthread_join(id_read, NULL);

    endProcess(SIGINT);
    return 0;
}

void startGame(GameBoard* gameBoard, Snek* snek, Food* food) {
    while (!gameOver) {
        moveSnek(snek);
        render(gameBoard, snek, food);
        #ifdef __linux
        sleep(1);
        #elif _WIN32
        Sleep(1000);
        #endif
    }
}

void endProcess(int sig) {
    disableRAWMode();
    raise(SIGTERM);
}

void enableRAWMode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    tcgetattr(STDIN_FILENO, &original);
    atexit(&disableRAWMode);
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
};

void disableRAWMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

void* runGame(void* args) {
    GameBoard* gameBoard = createGameBoard(BOARD_HEIGHT, BOARD_WIDTH);
    snek = createNewSnek();
    food = createFood();
    startGame(gameBoard, snek, food);

    free(food);
    free(snek);
    free(gameBoard);
}

void* readKeys(void* args) {
    char ch;
    while (!gameOver) {
        if (getchar() == '\033') {
            getchar();
            ch = getchar();
            switch (ch) {
            case KEY_LEFT:
                setSnekDirection(snek, -1, 0);
                break;
            case KEY_UP:
                setSnekDirection(snek, 0, -1);
                break;
            case KEY_RIGHT:
                setSnekDirection(snek, 1, 0);
                break;
            case KEY_DOWN:
                setSnekDirection(snek, 0, 1);
                break;
            default:
                break;
            }
        }
    }

};