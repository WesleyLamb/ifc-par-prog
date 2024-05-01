#include "BattleField.h"

BattleField *createNewBattleField()
{
    BattleField*  battleField = malloc(sizeof(BattleField));
    battleField->height = BATTLEFIELD_HEIGHT;
    battleField->width = BATTLEFIELD_WIDTH;

    return battleField;
}
