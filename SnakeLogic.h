#ifndef SnakeLogic_H
#define SnakeLogic_H

#include "BoardFuncs.h"
#include "DataStructs.h"

Snake* createSnake(Pos** board, int startRow, int startCol);

Snake* moveSnake(Pos **board, int boardSize, Snake *currentHead, int newRow, int newColumn);

void printHeadData(Snake* currentHead);

#endif