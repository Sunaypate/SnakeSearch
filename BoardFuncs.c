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

    int count = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board[row][col] = emptyPosit;
            board[row][col].Index = count;
            count++;
        }
    }

    return board;
}

Coor* initializeValidSpaces(int size) {
    Coor* validSpaces = (Coor*)malloc(size * size * (sizeof(Coor)));
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

void removeSpace (Pos** board, Coor* validSpaces, int* totalValidSpaces, int rRow, int rCol) {
    int filledIndex = board[rRow][rCol].Index;
    int lastCoorIndex = (*totalValidSpaces) - 1;
    
    if(filledIndex == lastCoorIndex) {
        (*totalValidSpaces)--;
        return;
    }

    Coor lastCoor = validSpaces[lastCoorIndex];
    validSpaces[lastCoorIndex] = validSpaces[filledIndex];
    validSpaces[filledIndex] = lastCoor;

    board[rRow][rCol].Index = lastCoorIndex;
    board[lastCoor.Row][lastCoor.Column].Index = filledIndex;
    
    (*totalValidSpaces)--;
}

void addSpace (Pos** board, Coor* validSpaces, int* totalValidSpaces, int aRow, int aCol) {
    // 1: Get index of the space to add, and the invalid space immediately after valid spaces
    int newindex = board[aRow][aCol].Index;
    int lastInvalidIndex = (*totalValidSpaces);

    // There will never be a case where there is only one invalid spot when adding, 
    // so indexing out of the array should be impossible with the above line

    // 3: Swap the new space and nearest filled space in validSpaces
    Coor lastInvalidCoor = validSpaces[lastInvalidIndex];
    validSpaces[lastInvalidIndex] = validSpaces[newindex];
    validSpaces[newindex] = lastInvalidCoor;


    // 4: Update their representation in the board so that the board indexes match the valid spaces array
    board[aRow][aCol].Index = lastInvalidIndex;
    board[lastInvalidCoor.Row][lastInvalidCoor.Column].Index = newindex;

    // 5: Increment the valid spaces so that the freed space is included in
    (*totalValidSpaces)++;
}

void listValidSpaces(Pos** board, Coor* validSpaces, int* totalValidSpaces) {
    for (int i = 0; i < (*totalValidSpaces); i++) {
        printf("Loc: %d is Valid with coordinate Row: %d Col: %d\n", i, validSpaces[i].Row, validSpaces[i].Column);
    }
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