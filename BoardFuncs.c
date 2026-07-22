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
bool addApple(gameData gameInfo) {
    Space** board = gameInfo.board;
    Coor* validSpaces = gameInfo.validSpaces;
    int totalOpenSpaces = *(gameInfo.totalValidSpaces);
    
    // Triggers win since theres no room to add an apple
    if (totalOpenSpaces == 0) {
        return false;
    }

    // randFormula = ((rand() % (max - min + 1)) + min)
    int appleCoorIndx = (rand() % ((totalOpenSpaces - 1) - 0 + 1) + 0);
    board[validSpaces[appleCoorIndx].Row][validSpaces[appleCoorIndx].Column].hasApple = true;
    
    return true;
}

void printBoard(int size, int waitTime, Space** board) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Space currPosition = board[row][col];
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

void endGame(int size, int speed) {
    printf(UP "\r");
    moveToRight(size);
    printf(UP"\b");
    
    if (currentEndCode == won) {
        for (int row = size - 1; row >= 0; row--) {
            for (int col = size - 1; col >= 0; col--) {
                Sleep(speed);
                printf(WON "\bO\b\b");
            }
            printf("\r");
            moveToRight(size);
            printf(UP "\b");
        }
        for (int i = 0; i <= size; i++) {
            printf(DOWN);
        }
        printf(WHT "YOU WIN!!!!");
    }
    else if (currentEndCode != safe) {
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
        printf(WHT "You Died To: ");
        if (currentEndCode == outOfBounds) {
            printf("Going Out Of Bounds (seriously?)");
        }
        else if (currentEndCode == hitSelf) {
            printf("Running Into Yourself");
        }
    }
}

Space** initalizeBoard(int size) {
    Space emptyPosit = {.hasApple = false, .hasSnake = false};

    Space** board = (Space**)malloc(size * (sizeof(Space*)));

    for (int row = 0; row < size; row++) {
        board[row] = (Space*)malloc(size * sizeof(Space));
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

void removeSpace (gameData gameInfo, int rRow, int rCol) {
    // Assign out variables for game data
    Space** board = gameInfo.board;
    Coor* validSpaces = gameInfo.validSpaces;
    int* totalValidSpaces = gameInfo.totalValidSpaces;

    // Get the indicies for the coord that was just filled, and the last open coord in valid spaces
    int filledIndex = board[rRow][rCol].Index;
    int lastCoorIndex = (*totalValidSpaces) - 1;
    
    // Checks if the space that was just filled was already last in the array; if so then return and decrement without swapping
    if (filledIndex == lastCoorIndex) {
        (*totalValidSpaces)--;
        return;
    }

    // Swaps the last valid coord with the newly filled coord
    Coor lastCoor = validSpaces[lastCoorIndex];
    validSpaces[lastCoorIndex] = validSpaces[filledIndex];
    validSpaces[filledIndex] = lastCoor;

    // Updates representation in the board so the spaces represent the correct array items
    board[rRow][rCol].Index = lastCoorIndex;
    board[lastCoor.Row][lastCoor.Column].Index = filledIndex;
    
    // Decrement valid spaces since a new one was made invalid
    (*totalValidSpaces)--;
}

void addSpace (gameData gameInfo, int aRow, int aCol) {
    // Assign out variables for game data
    Space** board = gameInfo.board;
    Coor* validSpaces = gameInfo.validSpaces;
    int* totalValidSpaces = gameInfo.totalValidSpaces;

    //  Gets index of the space to add, and the invalid space immediately after valid spaces
    int newindex = board[aRow][aCol].Index;
    int lastInvalidIndex = (*totalValidSpaces);

    // There will never be a case where there is only one invalid spot when adding, 
    // so indexing out of the array should be impossible with the above line

    // Swap the new space and nearest filled space in validSpaces
    Coor lastInvalidCoor = validSpaces[lastInvalidIndex];
    validSpaces[lastInvalidIndex] = validSpaces[newindex];
    validSpaces[newindex] = lastInvalidCoor;

    // Update representation in the board so that the board indexes match the valid spaces array
    board[aRow][aCol].Index = lastInvalidIndex;
    board[lastInvalidCoor.Row][lastInvalidCoor.Column].Index = newindex;

    // Increment the valid spaces so that the freed space is included in
    (*totalValidSpaces)++;
}

void listValidSpaces(gameData gameInfo) {
    for (int i = 0; i < *(gameInfo.totalValidSpaces); i++) {
        printf("Loc: %d is Valid with coordinate Row: %d Col: %d\n", i, gameInfo.validSpaces[i].Row, gameInfo.validSpaces[i].Column);
        
    }
}

void freeBoard(int size, Space** board) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

void freeValidSpaces(Coor* validSpaces) {
    free(validSpaces);
}