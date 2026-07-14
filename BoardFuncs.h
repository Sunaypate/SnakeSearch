#ifndef BoardFuncs_h
#define BoardFuncs_h

#include <stdbool.h>

//Defining Color Codes for printing

#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define WHT "\x1b[0m"

typedef struct Positon {
    bool hasApple;
    bool hasSnake;
} Pos;

void printBoard(int size, Pos** board);

Pos** initalizeBoard(int size);

void freeBoard(int size, Pos** board);

#endif