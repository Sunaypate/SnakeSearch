#ifndef SnakeLogic_H
#define SnakeLogic_H

#include "BoardFuncs.h"

typedef struct SnakeBody {
    int X;
    int Y;
    struct SnakeBody* previousSpot;
} Snake;

Snake* createSnake(Pos** board, int startRow, int startCol);

Snake* moveSnake(Pos **board, Snake *currentHead, int newX, int newY);

void printHeadData(Snake* currentHead);

#endif