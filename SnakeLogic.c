#include "SnakeLogic.h"
#include "BoardFuncs.h"
#include <stdio.h>
#include <stdlib.h>


// Needs to be redone with malloc to return a snake pointer
Snake createSnake(int startRow, int startCol, Pos** board) {
    board[startRow][startCol].hasSnake = true;

    Snake start = {.row = startRow, .column = startCol};
    return start;
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
    board[currSpot->row][currSpot->column].hasSnake = false;
    priorSpot->previousSpot = NULL;
    free(currSpot);

    // Returns a new head to track
    return newHeadPtr;
}
