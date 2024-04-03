#include "GameBoard.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

GameBoard* createGameBoard(int height, int width) {
    GameBoard* gameBoard = malloc(sizeof(GameBoard));
    gameBoard->height = height;
    gameBoard->width = width;

    return gameBoard;
}

void render(GameBoard* gameBoard, Snek* snek, Food* food) {
    printf("\033[2J\033[1;1H\n"); // Limpar terminal
    char* screen = malloc(sizeof(char)*4096);
    zeroFill(screen);

    drawScreenTop(screen, gameBoard);
    drawGameBoard(screen, gameBoard, snek, food);
    drawGameBoardBottom(screen, gameBoard);
    // drawGameInfo(screen, gameBoard, snek, food);
    // drawScreenBottom(screen, gameBoard);

    printf("%s\n", screen);
    free(screen);
}

void zeroFill(char* ch) {
    for (int i = 0; i < strlen(ch); i++)
        ch[i] = 0;
}

void drawScreenTop(char* screen, GameBoard* gameBoard) {
    // ╔═════════════════╗
    appendStr(screen, DOUBLE_UPPER_LEFT_CORNER);
    for (int i = 0; i < gameBoard->width; i++) {
        appendStr(screen, DOUBLE_HORIZONTAL);
    }

    appendStr(screen, DOUBLE_UPPER_RIGHT_CORNER);
    appendStr(screen, "\n");
}

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



    // char*** mat = (char***) malloc(sizeof(char***) * gameBoard->height);
    // int i, j;
    // for (i = 0; i < gameBoard->height; i++) {
    //     mat[i] = (char**) malloc(sizeof(char**) * gameBoard->width);
    //     for (j = 0; j < gameBoard->width; j++) {
    //         mat[i][j] = (char*) malloc(sizeof(char*) * 5);
    //         strcpy(mat[i][j], " ");
    //     }
    // }
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
        // free(mat[i]);
    }
}

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

void drawGameInfo(char *, GameBoard *, Snek *, Food *)
{
}

void drawScreenBottom(char *, GameBoard *)
{
}


void appendStr(char* dest, char* src)
{
    dest = strcat(dest, src);
}
