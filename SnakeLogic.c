#include "SnakeLogic.h"
#include "BoardFuncs.h"
#include <stdio.h>
#include <stdlib.h>

enum endCode currentEndCode = safe;
/**  
 * Creates a new snake head that must be saved to a variable and be used with all other
 * snake logic.
*/
Snake* createSnake(Space** board, int startRow, int startColumn) {
    board[startRow][startColumn].hasSnake = true;

    Snake* newSnake = (Snake*)malloc(sizeof(Snake));
    newSnake->Row = startRow;
    newSnake->Column = startColumn;
    newSnake->previousSpot = NULL;
    // Since the header file doesn't actually create a variable for this, it must be made here
    
    return newSnake;
}

bool checkLoss(Space** board, int size, int newRow, int newColumn) {
    if ((newRow < 0  || newRow >= size) || 
        (newColumn < 0  || newColumn >= size)) {
            currentEndCode = outOfBounds;
            return true;
        }
    else if (board[newRow][newColumn].hasSnake) {
        currentEndCode = hitSelf;
        return true;
    }
    else {
        return false;
    }
}

Snake* moveSnake(gameData gameInfo, Snake* currentHead, int newRow, int newColumn) {
    Space** board = gameInfo.board;
    int size = gameInfo.boardSize;

    // Allocates memory for the new head
    Snake* newHeadPtr = (Snake*)malloc(sizeof(Snake));
    if (newHeadPtr == NULL) {
        printf("Failled to allocate Memory");
        return NULL; //Intentional early return;
    }  

    if (checkLoss(board, size, newRow, newColumn)) {
        return NULL;
    }
    
    // Sets data for the new head
    newHeadPtr->Row = newRow;
    newHeadPtr->Column = newColumn;
    newHeadPtr->previousSpot = currentHead;

    // Tracks head change in valid positions
    removeSpace(gameInfo, newRow, newColumn);

    // Updates board status
    board[newRow][newColumn].hasSnake = true;

    // Checks for apples
    if (board[newRow][newColumn].hasApple) {
        board[newRow][newColumn].hasApple = false;
        if (addApple(gameInfo)) {
            return newHeadPtr;
        }
        
        currentEndCode = won;
        // Force game end or the code will get overidden
        return NULL;
    }
    

    // Finds end of snake
    Snake* currSpot = currentHead;
    Snake* priorSpot = NULL;
    while (currSpot->previousSpot != NULL) {
        priorSpot = currSpot;
        currSpot = currSpot->previousSpot;
    }
    

    // Updates board and destroys old end
    if(priorSpot == NULL) {
        // Handles if snake is only size of 1
        newHeadPtr->previousSpot = NULL;
    }
    else {
        priorSpot->previousSpot = NULL;
    }
    board[currSpot->Row][currSpot->Column].hasSnake = false;

    // Tracks head change in valid positions
    addSpace(gameInfo, currSpot->Row, currSpot->Column);

    free(currSpot);

    // Returns a new head to track
    return newHeadPtr;
}

/**
 * Debugging function for figuring out info on the current head.
 */
void printHeadData(Snake* currentHead) {
    printf("Current X: %d\n", currentHead->Row);
    printf("Current Y: %d\n", currentHead->Column);
    printf("Previous Part: %p\n", currentHead->previousSpot);
}