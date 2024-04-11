#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#include <unistd.h>
#include <termios.h>
struct termios original;

#include "src/GameBoard.h"
#include "src/Snek.h"
#include "src/Food.h"

#define KEY_LEFT 'D'
#define KEY_UP 'A'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

Snek* snek;
Food* food;
pthread_t id_game, id_read;

void* thread_game(void*);
void* thread_keys(void*);

void runGame(GameBoard*, Snek*, Food*);
void endProcess(int);
void enableRAWMode();
void disableRAWMode();

int main () {
    srand(time(NULL));
    signal(SIGINT, endProcess);
    enableRAWMode();

    pthread_create(&id_game, NULL, &thread_game, NULL);
    pthread_create(&id_read, NULL, &thread_keys, NULL);

    pthread_join(id_game, NULL);
    pthread_join(id_read, NULL);

    return 0;
}

/** Thread principal que inicia o jogo */
void* thread_game(void* args) {
    GameBoard* gameBoard = createGameBoard(BOARD_HEIGHT, BOARD_WIDTH);
    snek = createNewSnek();
    food = createFood();
    runGame(gameBoard, snek, food);

    free(food);
    free(snek);
    free(gameBoard);
    endProcess(SIGINT);
}

/** Thread que roda em paralelo com a thread_game.
 * Esta tem a finalidade de controlar as teclas
 * pressionadas para definir a direção da cobrinha */
void* thread_keys(void* args) {
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

/** Função que controla a passagem de tempo do jogo, executa
 * a atualização da tela e a movimentação dos objetos */
void runGame(GameBoard* gameBoard, Snek* snek, Food* food) {
    while (!gameOver) {
        moveSnek(gameBoard, snek, food);
        render(gameBoard, snek, food);
        usleep(200*1000);
    }
    pthread_cancel(id_read);
}

/** Função executada ao finalizar o programa com para evitar
 * deixar o terminal pauleado*/
void endProcess(int sig) {
    disableRAWMode();
    printf("Game Over\n");
    raise(SIGTSTP);
}

/** Habilita o terminal "read-only" */
void enableRAWMode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    tcgetattr(STDIN_FILENO, &original);
    atexit(&disableRAWMode);
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
};

/** Desabilita o terminal "read-only" */
void disableRAWMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}