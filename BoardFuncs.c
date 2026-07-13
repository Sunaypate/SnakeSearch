#include "BoardFuncs.h"
#include <stdbool.h>

void printBoard(int size, Posit board[size][size]) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Posit currPosition = board[row][col];
            if (currPosition.hasApple) {
                printf(RED "A ");
            }
            else if (currPosition.hasSnake) {
                printf(GRN "S ");
            }
            else {
                printf(WHT "E ");
            }
        }
        printf("\n");
    }
}

void initalizeBoard(int size, Posit board[size][size]) {
    Posit emptyPosit = {.hasApple = false, .hasSnake = false};

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board[row][col] = emptyPosit;
        }
    }
}