#include "BoardFuncs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void printBoard(int size, Pos** board) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Pos currPosition = board[row][col];
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
    printf("\n");
}

Pos** initalizeBoard(int size) {
    Pos emptyPosit = {.hasApple = false, .hasSnake = false};

    Pos** board = (Pos**)malloc(size * (sizeof(Pos*)));

    for (int row = 0; row < size; row++) {
        board[row] = (Pos*)malloc(size * sizeof(Pos));
    }

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board[row][col] = emptyPosit;
        }
    }

    return board;
}

void freeBoard(int size, Pos** board) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}