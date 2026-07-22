#ifndef BoardFuncs_h
#define BoardFuncs_h

#include <stdbool.h>
#include "DataStructs.h"

//Defining Color Codes for printing

#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define WHT "\x1b[0m"
#define DETH "\x1b[1;95m"
#define WON "\x1b[1;93m"

#define UP "\x1b[A"
#define DOWN "\x1b[B"
#define DEL "\x1b[2K"
#define RIT "\x1b[C"


Space** initalizeBoard(int size);

Coor* initializeValidSpaces(int size);

bool addApple(gameData gameInfo);

void printBoard(int size, int waitTime, Space **board);

void clearBoard(int size);

void endGame(int size, int speed);

void removeSpace (gameData gameInfo, int rRow, int rCol);

void addSpace (gameData gameInfo, int aRow, int aCol);

void listValidSpaces(gameData gameInfo);

void freeBoard(int size, Space** board);

void freeValidSpaces(Coor* validSpaces);


#endif