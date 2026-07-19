#include "SnakeLogic.h"
#include "BoardFuncs.h"
#include <stdio.h>
#include <stdlib.h>


/**  
 * Creates a new snake head that must be saved to a variable and be used with all other
 * snake logic.
*/
Snake* createSnake(Pos** board, int startX, int startY) {
    board[startX][startY].hasSnake = true;

    Snake* newSnake = (Snake*)malloc(sizeof(Snake));
    newSnake->X = startX;
    newSnake->Y = startY;
    newSnake->previousSpot = NULL;
    
    return newSnake;
}

Snake* moveSnake(Pos** board, Snake* currentHead, int newX, int newY) {
    // Updates board
    board[newX][newY].hasSnake = true;

    // Allocates memory for the new head
    Snake* newHeadPtr = (Snake*)malloc(sizeof(Snake));
    if (newHeadPtr == NULL) {
        printf("Failled to allocate Memory");
        return NULL; //Intentional early return;
    }  
    
    // Sets data for the new head
    newHeadPtr->X = newX;
    newHeadPtr->Y = newY;
    newHeadPtr->previousSpot = currentHead;

    if (board[newX][newY].hasApple) {
        board[newX][newY].hasApple = false;
        return newHeadPtr;
        //TODO: make a call to boardfuncs to produce a new apple.
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
    board[currSpot->X][currSpot->Y].hasSnake = false;
    free(currSpot);

    // Returns a new head to track
    return newHeadPtr;
}

/**
 * Debugging function for figuring out info on the current head.
 */
void printHeadData(Snake* currentHead) {
    printf("Current X: %d\n", currentHead->X);
    printf("Current Y: %d\n", currentHead->Y);
    printf("Previous Part: %p\n", currentHead->previousSpot);
}