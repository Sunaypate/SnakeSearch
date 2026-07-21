#include "BoardFuncs.h"
#include "SnakeLogic.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

void moveToRight(int size) {
    for (int i = 0; i < size * 2; i++) {
        printf(RIT);
    }
}

//TODO: Implement tracking of all empty spaces for better efficiency
bool addApple(Pos** board, int size) {    
    // Treat this as a list of valid locations rather than a player snake
    Coor validSpots[size];
    int count = 0;
    
    // Creates array of valid positions
    while (count <= 0) {
        int randRow = (rand() % ((size - 1) + 1));
        
        // Finds all valid spots
        for (int i = 0; i < size; i++) {
            if (board[randRow][i].hasSnake) {
                continue;
            }
            validSpots[count].Row = randRow;
            validSpots[count].Column = i;
            count++;
        }
    }

    // randFormula = ((rand() % (max - min + 1)) + 1)
    int newApple = rand() % ((count - 1) + 0 + 1);
    board[validSpots[newApple].Row][validSpots[newApple].Column].hasApple = true;
    return true;
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
    int exClearLines = 2;

    for (int i = 0; i < size + exClearLines; i++) {
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
            printf(DETH "\bX\b\b");
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

Coor* initializeValidSpaces(int size) {
    Coor* validSpaces = (Coor*)malloc(size * (sizeof(Coor)));

    int count = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            validSpaces[count].Row = row;
            validSpaces[count].Column = col;
            count++;
        }
    }

    return validSpaces;
}

void freeBoard(int size, Pos** board) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

void freeValidSpaces(Coor* validSpaces) {
    free(validSpaces);
}