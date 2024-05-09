#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#include <unistd.h>
#include <termios.h>
struct termios original;

#include "src/Battlefield.h"
#include "src/Plane.h"
#include "src/EnemyList.h"
#include "src/ProjectileList.h"

#define KEY_LEFT 'D'
#define KEY_UP 'A'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

Battlefield* battlefield;
Plane* plane;
EnemyList* enemies;
ProjectileList* planeProjectiles;
ProjectileList* enemyProjectiles;

bool gameOver = false;

pthread_t id_game, id_read;

void* thread_game(void*);
void* thread_keys(void*);

void endProcess(int);
void enableRAWMode();
void disableRAWMode();

void runGame();

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
    battlefield = createNewBattlefield();
    plane = createNewPlane(battlefield->width / 2, battlefield->height - 10);
    enemies = createEnemyList();
    enemyProjectiles = createProjectileList();
    planeProjectiles = createProjectileList();

    runGame();

    free(plane);
    free(battlefield);
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
        if (getchar() == 32) { // space
            insertProjectileNode(planeProjectiles, createProjectile(plane->x, plane->y - 1, 0, -1));
        }
    }

};

/** Função que controla a passagem de tempo do jogo, executa
 * a atualização da tela e a movimentação dos objetos */
void runGame() {
    while (!gameOver) {
        update(battlefield, plane, enemies, planeProjectiles, enemyProjectiles);
        render(battlefield, plane, enemies, planeProjectiles, enemyProjectiles);
        if (plane->lives <= 0)
            gameOver == true;
        usleep(100*1000);
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