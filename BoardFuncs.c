#include "BoardFuncs.h"
#include "SnakeLogic.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

enum Axis {
    Horizontal = 1,
    Vertical = 2
} randAxis;

void moveToRight(int size) {
    for (int i = 0; i < size * 2; i++) {
        printf(RIT);
    }
}

Snake* addNode(Snake* oldNode, int X, int Y) {
    Snake* newSpot;
    newSpot->X = X;
    newSpot->Y = Y;
    newSpot->previousSpot = oldNode;
    return newSpot;
}

//TODO: actually test to see if this works
void addApple(Pos** board, int size, Snake* head) {
    // Seeds with random time
    srand((unsigned int)GetTickCount());

    // Random Placement Values
    randAxis = (rand() % (2)) + 1;
    int randLine = (rand() % ((size - 1) + 1));

    // Treat this as a linked list of valid locations rather than a player snake
    Snake* validSpots;
    int count = 0;

    //TODO: check to see if line has no valid spaces
    switch (randAxis) {
        case Horizontal:
            for (int i = 0; i < size; i++) {
                if (board[randLine][i].hasSnake) {
                    continue;
                }
                count++;
                validSpots = addNode(validSpots, randLine, i);
            }

            int newApple = (rand() % (count + 1));
            Snake* newAppleLoc = validSpots;

            while(count > newApple) {
                newAppleLoc = newAppleLoc->previousSpot;
                count--;
            }

            board[newAppleLoc->X][newAppleLoc->Y].hasApple = true;
            return;
        break;

        //TODO: Copy horizontal case over to vertical
        case Vertical:
        break;
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

void freeBoard(int size, Pos** board) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}