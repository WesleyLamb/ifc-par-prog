#ifndef BattleField_h
#define BattleField_h

#define BATTLEFIELD_HEIGHT 50
#define BATTLEFIELD_WIDTH 50

typedef struct {
    int width;
    int height;
} BattleField;

BattleField* createNewBattleField();

#endif