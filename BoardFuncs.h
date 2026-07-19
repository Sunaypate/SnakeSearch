#ifndef BoardFuncs_h
#define BoardFuncs_h

#include <stdbool.h>

//Defining Color Codes for printing

#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define WHT "\x1b[0m"
#define BRED "\x1b[1;95m"

#define UP "\x1b[A"
#define DOWN "\x1b[B"
#define DEL "\x1b[2K"
#define RIT "\x1b[C"

typedef struct Positon {
    bool hasApple;
    bool hasSnake;
} Pos;

void printBoard(int size, int waitTime, Pos** board);

void clearBoard(int size);

void lostGame(int size, int speed);

Pos** initalizeBoard(int size);

void freeBoard(int size, Pos** board);

#endif