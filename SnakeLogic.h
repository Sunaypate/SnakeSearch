#ifndef SnakeLogic_H
#define SnakeLogic_H

#include "BoardFuncs.h"
#include "DataStructs.h"

Snake* createSnake(Space** board, int startRow, int startCol);

Snake* moveSnake(gameData gameInfo, Snake* currentHead, int newRow, int newColumn);

void printHeadData(Snake* currentHead);

#endif