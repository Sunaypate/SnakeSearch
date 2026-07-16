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

    return newSnake;
}

Snake* moveSnake(Pos** board, Snake* currentHead, int newX, int newY) {

    // Updates board
    board[newY][newX].hasSnake = true;

    // Allocates memory for the new head
    Snake* newHeadPtr = (Snake*)malloc(sizeof(Snake));
    if (newHeadPtr == NULL) {
        printf("Failled to allocate Memory");
        return NULL; //Intentional early return;
    }
    
    // Sets data for the new head
    newHeadPtr-> column = newX;
    newHeadPtr-> row = newY;
    newHeadPtr-> previousSpot = currentHead;


    // Finds end of snake
    Snake* currSpot = currentHead;
    Snake* priorSpot;
    while (currSpot->previousSpot != NULL) {
        priorSpot = currSpot;
        currSpot = currSpot->previousSpot;
    }
    
    // Updates board and destroys old end

    if(priorSpot == NULL) {
        // Handles if snake is only size of 1
        return newHeadPtr;
    }
    board[currSpot->row][currSpot->column].hasSnake = false;
    priorSpot->previousSpot = NULL;
    free(currSpot);

    // Returns a new head to track
    return newHeadPtr;
}
