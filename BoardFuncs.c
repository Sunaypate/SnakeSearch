#include "BoardFuncs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

void moveToRight(int size) {
    for (int i = 0; i < size * 2; i++) {
        printf(RIT);
    }
}

void printBoard(int size, int waitTime, Pos** board) {
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
            Sleep(waitTime);
        }
        printf("\n");
    }
    printf(WHT "\n");
}

void clearBoard(int size) {
    for (int i = 0; i < size + 2; i++) {
        printf(DEL UP "");
    }
    printf(DEL "\r");
}

void lostGame(int size, int speed) {
    printf(UP "\r");
    moveToRight(size);
    printf(UP"\b");
    for (int row = size - 1; row >= 0; row--) {
        for (int col = size - 1; col >= 0; col--) {
            Sleep(speed);
            printf(BRED "\bX\b\b");
        }
        printf("\r");
        moveToRight(size);
        printf(UP "\b");
    }
    for (int i = 0; i <= size; i++) {
        printf(DOWN);
    }
    printf(WHT "YOU LOST!!!!");
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