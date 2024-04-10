#include "GameBoard.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

void render(GameBoard*, Snek*, Food*);
void update(GameBoard*, Snek*, Food*);


/** Cria uma instância do "tabuleiro" */
GameBoard* createGameBoard(int height, int width) {
    GameBoard* gameBoard = malloc(sizeof(GameBoard));
    gameBoard->height = height;
    gameBoard->width = width;

    return gameBoard;
}

/** Apaga o console e desenha o tabuleiro */
void render(GameBoard* gameBoard, Snek* snek, Food* food) {
    printf("\033[2J\033[1;1H\n"); // Limpar terminal
    char* screen = malloc(sizeof(char)*4096);
    zeroFill(screen);

    drawScreenTop(screen, gameBoard);
    drawGameBoard(screen, gameBoard, snek, food);
    drawGameBoardBottom(screen, gameBoard);
    drawGameInfo(screen, gameBoard, snek, food);

    printf("%s\n", screen);
    free(screen);
}

/** Remove lixo de memória do string */
void zeroFill(char* ch) {
    for (int i = 0; i < strlen(ch); i++)
        ch[i] = 0;
}
/** Desenha o topo da tela */
void drawScreenTop(char* screen, GameBoard* gameBoard) {
    // ╔═════════════════╗
    appendStr(screen, DOUBLE_UPPER_LEFT_CORNER);
    for (int i = 0; i < gameBoard->width; i++) {
        appendStr(screen, DOUBLE_HORIZONTAL);
    }

    appendStr(screen, DOUBLE_UPPER_RIGHT_CORNER);
    appendStr(screen, "\n");
}

/** Desenha o tabuleiro e seus componentes (cobrinha e comida) */
void drawGameBoard(char* screen, GameBoard* gameBoard, Snek* snek, Food* food)
{
    // ║                ║
    // ║   ▒▒▓ ð        ║
    // ║   ▒            ║
    // ║   ▒            ║

    Snek* sn = snek;
    char* mat[gameBoard->height][gameBoard->width];
    int i, j;
    for (i = 0; i < gameBoard->height; i++) {
        // mat[i] = (char**) malloc(sizeof(char**) * gameBoard->width);
        for (j = 0; j < gameBoard->width; j++) {
            mat[i][j] = (char*) malloc(sizeof(char*) * 5);
            strcpy(mat[i][j], " ");
        }
    }

    // draw food
    strcpy(mat[food->y][food->x], FOOD_SPRITE);

    // draw snek head
    strcpy(mat[sn->y][sn->x], SNEK_HEAD_SPRITE);

    // draw snek body
    while (NULL != (sn = sn->next)) {
        strcpy(mat[sn->y][sn->x], SNEK_BODY_SPRITE);
    }
    for (i = 0; i < gameBoard->height; i++) {
        appendStr(screen, DOUBLE_VERTICAL);
        for (j = 0; j < gameBoard->width; j++) {
            appendStr(screen, mat[i][j]);
        }
        appendStr(screen, DOUBLE_VERTICAL);
        appendStr(screen, "\n");
    }

    for (i = gameBoard->height - 1 ; i >=0; i--) {
        for (j = gameBoard->width - 1; j >= 0 ; j--) {
            free(mat[i][j]);
        }
    }
}


/** Desenha o rodapé do tabuleiro */
void drawGameBoardBottom(char* screen, GameBoard* gameBoard)
{
    // ╚═════════════════╝
    appendStr(screen, DOUBLE_LOWER_LEFT_CORNER);
    for (int i = 0; i < gameBoard->width; i++) {
        appendStr(screen, DOUBLE_HORIZONTAL);
    }

    appendStr(screen, DOUBLE_LOWER_RIGHT_CORNER);
    appendStr(screen, "\n");
}

/** A ideia era escrever algumas informações como pontos,
 * tempo decorrido, mas fiquei sem saco pra implementar (alivia pra nóis psor, fiquei a noite inteira acordado)
*/
void drawGameInfo(char *, GameBoard *, Snek *, Food *)
{
    // TODO: implementar
}

/** Concatena uma string e escreve na primeira variável */
void appendStr(char* dest, char* src)
{
    dest = strcat(dest, src);
}

/** Detecta se a cobrinha está tal coordenada */
bool isOccupied(Snek* snek, int x, int y)
{
    Snek* sn = snek;
    while (NULL != sn) {
        if ((sn->x == x) && (sn->y == y))
            return true;
        sn = sn->next;
    }

    return false;
}

/** Reposiciona aleatoriamente a comida após a cobra comer */
void moveFood(GameBoard* gameBoard, Snek* snek, Food* food) {
    int newX, newY;
    bool placed = false;
    while (!placed) {
        newX = rand() % gameBoard->width;
        newY = rand() % gameBoard->height;
        if (!isOccupied(snek, newX, newY)) {
            food->x = newX;
            food->y = newY;

            placed = true;
        }
    }
}

/** Detecta a colisão da cobrinha com as bordas com com ela mesma */
bool canMoveToDirection(GameBoard* gameBoard, Snek* snek) {
    return  (snek->x + snek->x_step >= 0) &&
            (snek->x + snek->x_step < gameBoard->width) &&
            (snek->y + snek->y_step >= 0) &&
            (snek->y + snek->y_step < gameBoard->height) &&
            !isOccupied(snek, snek->x + snek->x_step, snek->y + snek->y_step);
}

/** Come a comida */
void eatFood(GameBoard* gameBoard, Snek* snek, Food* food) {
    if ((snek->x == food->x) && (snek->y == food->y)) {
        createSnekSeg(snek);
        moveFood(gameBoard, snek, food);
    }
}

/** Move a cobrinha */
void moveSnek(GameBoard* gameBoard,Snek* snek, Food* food) {
    Snek* sn = snek;
    while (NULL != sn->next) {
        sn = sn->next;
    }
    while (NULL != sn) {
        if (canMoveToDirection(gameBoard, sn)) {
            applyMove(sn);
            if (NULL != sn->prev) {
                sn->x_step = sn->prev->x_step;
                sn->y_step = sn->prev->y_step;
            }
            sn = sn->prev;
        } else {
            gameOver = true;
            return;
        }
    }
    eatFood(gameBoard, snek, food);
    canChangeDirection = true;
}