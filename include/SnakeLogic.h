#ifndef SnakeLogic_H
#define SnakeLogic_H

#include "BoardFuncs.h"
#include "DataStructs.h"

Snake* createSnake(Space** board, int boardSize);

Snake* moveSnake(gameData gameInfo, Snake* snakeHead, int newRow, int newColumn);

void printHeadData(Snake* currentHead);

void freeSnake(Snake* currentHead);

#endif