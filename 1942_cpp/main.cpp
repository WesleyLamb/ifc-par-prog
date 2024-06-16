#include <iostream>
#include <signal.h>
#include <termios.h>
#include <memory>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#include "src/Engine.hpp"
#include "src/Player.hpp"
#include "src/Enemy.hpp"

#define KEY_LEFT 'D'
#define KEY_UP 'A'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

struct termios original;
pthread_t id_game, id_read;
std::unique_ptr<Engine> engine;

void endProcess(int);
void enableRAWMode();
void disableRAWMode();
void* thread_keys(void*);
void* thread_game(void*);

int main() {
    signal(SIGINT, endProcess);
    srand(time(NULL));

    enableRAWMode();

    pthread_create(&id_game, NULL, &thread_game, NULL);
    pthread_create(&id_read, NULL, &thread_keys, NULL);

    pthread_join(id_game, NULL);
    pthread_join(id_read, NULL);

    disableRAWMode();
    return 0;
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

void* thread_game(void* args) {
    engine = std::unique_ptr<Engine>(new Engine());
    Player* player = new Player(BATTLEFIELD_HEIGHT - 4, (int)BATTLEFIELD_WIDTH / 2);
    engine->addPlayer(player);

    engine->start();
    endProcess(SIGINT);
    return 0;
}

/** Thread que roda em paralelo com a thread_game.
 * Esta tem a finalidade de controlar as teclas
 * pressionadas para definir a direção do jogador */
void* thread_keys(void* args) {
    // initscr();

    // cbreak();
    // noecho();
    // nodelay(stdscr, TRUE);

    // scrollok(stdscr, TRUE);
    // int ch;
    // while (1) {
    //     ch = getch();
    //     switch (ch) {
    //         case KEY_LEFT:
    //             engine->playerMove(0, -1);
    //             break;
    //         case KEY_UP:
    //             engine->playerMove(-1, 0);
    //             break;
    //         case KEY_RIGHT:
    //             engine->playerMove(0, 1);
    //             break;
    //         case KEY_DOWN:
    //             engine->playerMove(1, 0);
    //             break;
    //         case 32:
    //             engine->playerShoot();
    //             break;
    //         default:
    //             break;
    //     }
    //     usleep(100000);
    // }

    char ch;
    while (!engine->gameOver) {
        if (getchar() == '\033') {
            getchar();
            ch = getchar();
            switch (ch) {
                case KEY_LEFT:
                    engine->playerMove(0, -1);
                    break;
                case KEY_UP:
                    engine->playerMove(-1, 0);
                    break;
                case KEY_RIGHT:
                    engine->playerMove(0, 1);
                    break;
                case KEY_DOWN:
                    engine->playerMove(1, 0);
                    break;
                default:
                    break;
            }
        }
        if (getchar() == 32) { // space
            engine->playerShoot();
        }
    }
    return 0;
};