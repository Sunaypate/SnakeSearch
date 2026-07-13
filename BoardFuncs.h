#ifndef BoardFuncs_h
#define BoardFuncs_h

#include <stdbool.h>

//Defining Color Codes for printing

#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define WHT "\x1b[0m"

typedef struct Position {
    bool hasApple;
    bool hasSnake;
} Posit;

void printBoard(int size, Posit board[size][size]);


#endif