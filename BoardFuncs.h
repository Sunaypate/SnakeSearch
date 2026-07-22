#ifndef BoardFuncs_h
#define BoardFuncs_h

#include <stdbool.h>
#include "DataStructs.h"

//Defining Color Codes for printing

#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define WHT "\x1b[0m"
#define DETH "\x1b[1;95m"

#define UP "\x1b[A"
#define DOWN "\x1b[B"
#define DEL "\x1b[2K"
#define RIT "\x1b[C"

// typedef struct Board {
//     Pos **board;
//     int width;
//     int height;
// } Board;

bool addApple(Pos** board, int size);

void printBoard(int size, int waitTime, Pos **board);

void clearBoard(int size);

void lostGame(int size, int speed);

Pos** initalizeBoard(int size);

Coor* initializeValidSpaces(int size);

void removeSpace (Pos** board, Coor* validSpaces, int* totalValidSpaces, int rRow, int rCol);

void addSpace (Pos** board, Coor* validSpaces, int* totalValidSpaces, int aRow, int aCol);

void listValidSpaces(Pos** board, Coor* validSpaces, int* totalValidSpaces);

void freeBoard(int size, Pos** board);

void freeValidSpaces(Coor* validSpaces);


#endif