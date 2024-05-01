#ifndef GameBoard_h
#define GameBoard_h

#include "Snek.h"
#include "Food.h"
#include "GameBoard.h"
#include <stdbool.h>

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 30
#define DOUBLE_LEFT_INTERSECTION "\u2563" // ╣
#define DOUBLE_VERTICAL "\u2551" // ║
#define DOUBLE_UPPER_RIGHT_CORNER "\u2557" // ╗
#define DOUBLE_LOWER_RIGHT_CORNER "\u255D" // ╝
#define DOUBLE_LOWER_LEFT_CORNER "\u255A" // ╚
#define DOUBLE_UPPER_LEFT_CORNER "\u2554" // ╔
#define DOUBLE_RIGHT_INTERSECTION "\u2560" // ╠
#define DOUBLE_HORIZONTAL "\u2550" // ═
#define DOUBLE_CROSS_INTERSECTION "\u256C" // ╬
#define FOOD_SPRITE  "\u00F0" // ð
#define SNEK_HEAD_SPRITE "\u2593" // ▓
#define SNEK_BODY_SPRITE "\u2588" // █

typedef struct GameBoard {
    int height;
    int width;
} GameBoard;

GameBoard* createGameBoard(int, int);
void render(GameBoard*, Snek*, Food*) ;
void zeroFill(char*);
void drawScreenTop(char*, GameBoard*);
void drawGameBoard(char*, GameBoard*, Snek*, Food*);
void drawGameBoardBottom(char*, GameBoard*);
void drawGameInfo(char*, GameBoard*, Snek*, Food*);
void appendStr(char*, char*);
bool isOccupied(Snek*, int, int);
void moveFood(GameBoard*, Snek*, Food*);
bool canMoveToDirection(GameBoard*, Snek*);
void eatFood(GameBoard*, Snek*, Food*);
void moveSnek(GameBoard*, Snek*, Food*);

#endif