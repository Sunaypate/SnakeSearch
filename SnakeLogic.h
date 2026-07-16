#ifndef SnakeLogic_H
#define SnakeLogic_H

#include "BoardFuncs.h"

typedef struct SnakeBody {
    int row;
    int column;
    struct SnakeBody* previousSpot;
} Snake;

Snake* createSnake(Pos** board, int startRow, int startCol);

Snake* moveSnake(Pos** board, Snake* currentHead, int newX, int newY);

#endif