#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#include <unistd.h>
#include <termios.h>
struct termios original;

#include "src/BattleField.h"
#include "src/Plane.h"

#define KEY_LEFT 'D'
#define KEY_UP 'A'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

BattleField* battleField;
Plane* plane;

pthread_t id_game, id_read;

void* thread_game(void*);
void* thread_keys(void*);

void endProcess(int);
void enableRAWMode();
void disableRAWMode();

// void runGame(GameBoard*, Snek*, Food*);

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
    battleField = createNewBattleField();
    plane = createNewPlane(battleField->width / 2, battleField->height - 10);

    runGame(battleField, plane);

    free(plane);
    free(battleField);
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
                    movePlane(plane, -1, 0);
                    break;
                case KEY_UP:
                    movePlane(plane, 0, -1);
                    break;
                case KEY_RIGHT:
                    movePlane(plane, 1, 0);
                    break;
                case KEY_DOWN:
                    movePlane(plane, 0, 1);
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
        render(gameBoard, plane, enemies);
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