#ifndef SnakeAlg_h
#define SnakeAlg_h

#include "DataStructs.h"

char simpleMove(gameData gameInfo, Snake* snakeHead);

char safeMove(gameData gameInfo, Snake* snakeHead);

char** initTrackMoveTable(int boardSize);

void freeTrackMoveTable(char** moveTable, int tableSize);

char trackMove(Snake* snakeHead, char** moveLoc);

#endif