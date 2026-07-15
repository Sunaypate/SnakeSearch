#ifndef SnakeLogic_H
#define SnakeLogic_H

#include "BoardFuncs.h"

typedef struct SnakeBody {
    int row;
    int column;
    Snake* previousSpot;
} Snake;

#endif