#include "../include/SnakeLogic.h"

#include "../include/BoardFuncs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum endCode currentEndCode = alive;
/**  
 * Creates a new snake head that must be saved to a variable and be used with all other
 * snake logic.
*/
Snake* createSnake(Space** board, int boardSize) {
	Snake* newSnake = (Snake*)malloc(sizeof(Snake));

	newSnake->Row = (rand() % ((boardSize - 1) - 0 + 1) + 0);
	newSnake->Column = (rand() % ((boardSize - 1) - 0 + 1) + 0);
	newSnake->previousSpot = NULL;

	board[newSnake->Row][newSnake->Column].hasSnake = true;
	// Since the header file doesn't actually create a variable for this, it must be made here
	currentEndCode = alive;
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

Snake* moveSnake(gameData gameInfo, Snake* snakeHead, int newRow, int newColumn) {
	Space** board = gameInfo.board;
	int size = gameInfo.boardSize;

	// Allocates memory for the new head
	Snake* newHeadPtr = (Snake*)malloc(sizeof(Snake));
	if (newHeadPtr == NULL) {
		printf("Failled to allocate Memory");
		return NULL; //Intentional early return;
	}  

	if (checkLoss(board, size, newRow, newColumn)) {
		return snakeHead;
	}
	
	// Sets data for the new head
	newHeadPtr->Row = newRow;
	newHeadPtr->Column = newColumn;
	newHeadPtr->previousSpot = snakeHead;

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
		return newHeadPtr;
	}


	// Finds end of snake
	Snake* currSpot = snakeHead;
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

void freeSnake(Snake* currentHead) {
	Snake* nextSpot = currentHead;
	Snake* priorSpot = NULL;
	while (nextSpot->previousSpot != NULL) {
		priorSpot = nextSpot;
		nextSpot = nextSpot->previousSpot;
		free(priorSpot);
	}
	free(nextSpot);
}

/**
 * Debugging function for figuring out info on the current head.
 */
void printHeadData(Snake* currentHead) {
	printf("Current Row: %d\n", currentHead->Row);
	printf("Current Column: %d\n", currentHead->Column);
	printf("Previous Part: %p\n", currentHead->previousSpot);
}