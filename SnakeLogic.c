#include "SnakeLogic.h"
#include "BoardFuncs.h"
#include <stdio.h>
#include <stdlib.h>


/**  
 * Creates a new snake head that must be saved to a variable and be used with all other
 * snake logic.
*/
Snake* createSnake(Pos** board, int startRow, int startCol) {
    board[startRow][startCol].hasSnake = true;

    Snake* newSnake = (Snake*)malloc(sizeof(Snake));
    newSnake->row = startRow;
    newSnake->column = startCol;
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
    //TODO: had to flip this to get move to work, go check if anything else feeding this is flipped.
    newHeadPtr-> column = newY;
    newHeadPtr-> row = newX;
    newHeadPtr-> previousSpot = currentHead;


    // Finds end of snake
    
    Snake* currSpot = currentHead;
    Snake* priorSpot = NULL;
    while (currSpot->previousSpot != NULL) {
        printf("%p\n", currSpot->previousSpot);
        priorSpot = currSpot;
        currSpot = currSpot->previousSpot;
    }
    

    // Updates board and destroys old end
    if(priorSpot == NULL) {
        //TODO: See if this and the regular ending cna be optimized to have less repition.
        // Handles if snake is only size of 1
        newHeadPtr->previousSpot = NULL;
        board[currSpot->row][currSpot->column].hasSnake = false;
        free(currSpot);
        return newHeadPtr;
    }
    board[currSpot->row][currSpot->column].hasSnake = false;
    priorSpot->previousSpot = NULL;
    free(currSpot);

    // Returns a new head to track
    return newHeadPtr;
}

/**
 * Debugging function for figuring out info on the current head.
 */
void printHeadData(Snake* currentHead) {
    printf("Current X: %d\n", currentHead->column);
    printf("Current Y: %d\n", currentHead->row);
    printf("Previous Part: %p\n", currentHead->previousSpot);
}