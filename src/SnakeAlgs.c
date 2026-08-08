#include "../include/SnakeAlgs.h"

#include "../include/DataStructs.h"
#include "../include/BoardFuncs.h"
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

enum Direction {
	W,
	A,
	S,
	D
};

void getTargetDirection(Coor snakeLoc, Coor appleLoc, bool targetDirection[4]) {
	int snakeRow = snakeLoc.Row;
	int snakeCol = snakeLoc.Column;

	if(snakeRow > appleLoc.Row) {
		targetDirection[W] = true;
	}
	if(snakeCol > appleLoc.Column) {
		targetDirection[A] = true;
	}
	if(snakeRow < appleLoc.Row) {
		targetDirection[S] = true;
	}
	if(snakeCol < appleLoc.Column) {
		targetDirection[D] = true;
	}
}

/**
 * @brief Tries to move directly toward the apple with no regard to itself.
 *  
 */ 
char simpleMove(gameData gameInfo, Snake* snakeHead) {
	Coor appleLoc = *(gameInfo.appleLocation);
	Coor snakeLoc = {.Row = snakeHead->Row, .Column = snakeHead->Column};

	bool targetDirection[4] = {false, false, false, false};
	getTargetDirection(snakeLoc, appleLoc, targetDirection);
	
	// Checks to see what will get it to the apple the fastest.
	if (targetDirection[S]) {
		return 's';
	}
	else if (targetDirection[W]) {
		return 'w';
	}
	else {
		if (targetDirection[D]) {
			return 'd';
		}
		else if (targetDirection[A]) {
			return 'a';
		}
	}
	return 'w';
}

/**
 * @brief Assigns bool array that corresponds to four valid directions.
 * 
 * Each boolean in the array represents if that direction has a snake. Each of these directions
 * represent moving up, down, left, and right.
 */
void getSafeMoves(Space** board, int boardSize, Coor snakeLoc, bool validMoves[4]) {
	int snakeRow = snakeLoc.Row;
	int snakeCol = snakeLoc.Column;

	if (!(snakeRow-1 < 0) && !(board[snakeRow-1][snakeCol].hasSnake)) {
		validMoves[W] = true;
	}
	if (!(snakeCol-1 < 0) && !(board[snakeRow][snakeCol-1].hasSnake)) {
		validMoves[A] = true;
	}
	if (!(snakeRow+1 == boardSize) && !(board[snakeRow+1][snakeCol].hasSnake)) {
		validMoves[S] = true;
	}
	if (!(snakeCol+1 == boardSize) && !(board[snakeRow][snakeCol+1].hasSnake)) {
		validMoves[D] = true;
	}
}

char enumToChar(enum Direction move) {
	switch (move) {
		case W:
			return 'w';
		break;
		case A:
			return 'a';
		break;
		case S:
			return 's';
		break;
		case D:
			return 'd';
		break;
		default:
			return 'w';
		break;
	}
}

// Attempts to move toward the apple with move, but will avoid running into itself.
char safeMove(gameData gameInfo, Snake* snakeHead) {
	Coor appleLoc = *(gameInfo.appleLocation);
	Coor snakeLoc = {.Row = snakeHead->Row, .Column = snakeHead->Column};

	// Figures out which moves can be made [w, a, s, d]
	bool validMoves[4] = {false, false, false, false};
	bool targetDir[4] = {false, false, false, false};
	getSafeMoves(gameInfo.board, gameInfo.boardSize, snakeLoc, validMoves);
	getTargetDirection(snakeLoc, appleLoc, targetDir);
	
	for (int i = 0; i < 4; i++) {
		if ((targetDir[i]) && (validMoves[i])) {
			return enumToChar(i);
		}
	}
	for (int i = 0; i < 4; i++) {
		if ((validMoves[i])) {
			return enumToChar(i);
		}
	}
	return 'w';
}

char** initTrackMoveTable(int boardSize) {
	char** lookUpTable = (char**)malloc(boardSize * sizeof(char*));
	if (lookUpTable == NULL) {
		printf("Failled to allocate Memory");
		return NULL; //Intentional early return;
	}  

	for (int row = 0; row < boardSize; row++) {
		lookUpTable[row] = (char*)malloc(boardSize * sizeof(char));
		if (lookUpTable[row] == NULL) {
			printf("Failled to allocate Memory");
			return NULL; //Intentional early return;
		}  
	}

	for (int topCell = 1; topCell < boardSize; topCell++) {
		lookUpTable[0][topCell] = 'a';
	}
	for (int leftCell = 0; leftCell < boardSize - 1; leftCell++) {
		lookUpTable[leftCell][0] = 's';
	}
	for (int rightCell = 1; rightCell < boardSize; rightCell++) {
		lookUpTable[rightCell][boardSize - 1] = 'w';
	}
	for (int bTurnCell = 0; bTurnCell < boardSize - 1; bTurnCell++) {
		if (bTurnCell % 2 == 0) {
			lookUpTable[boardSize - 1][bTurnCell] = 'd';
		}
		else {
			lookUpTable[boardSize - 1][bTurnCell] = 'w';
		}
	}
	for (int tTurnCell = 1; tTurnCell < boardSize - 1; tTurnCell++) {
		if (tTurnCell % 2 == 0) {
			lookUpTable[1][tTurnCell] = 's';
		}
		else {
			lookUpTable[1][tTurnCell] = 'd';
			
		}
	}

	for (int cCol = 1; cCol < boardSize - 1; cCol++) {
		char colMove = ' ';
		if (cCol % 2 == 0) {
			colMove = 's';
		}
		else {
			colMove = 'w';
		}

		for (int cRow = 2; cRow < boardSize - 1; cRow++) {
			lookUpTable[cRow][cCol] = colMove;
		}
	}

	return lookUpTable;
}

void freeTrackMoveTable(char** moveTable, int tableSize) {
	for (int row = 0; row < tableSize; row++) {
		free(moveTable[row]);
	}

	free(moveTable);
}

char trackMove(Snake* snakeHead, char** moveLoc) {
	return moveLoc[snakeHead->Row][snakeHead->Column];
}

//TODO implement tail tracking
int validArea(Space** board, int boardSize, Coor snakeHead, Coor tailLoc, bool* hasTail) {
	int totalSpaces = 0;
	int snakeRow = snakeHead.Row;
	int snakeCol = snakeHead.Column;
	int yMoveTypes[4] = {-1, 0, 1, 0};
	int xMoveTypes[4] = {0, -1, 0, 1};
	board[snakeRow][snakeCol].hasSnake = true;

	for (int direction = 0; direction < 4; direction++) {
		int nextRow = snakeHead.Row + yMoveTypes[direction];
		int nextCol = snakeHead.Column + xMoveTypes[direction];

		if (!(nextRow < 0) && !(nextRow == boardSize) &&
			!(nextCol < 0) && !(nextCol == boardSize) &&
			!(board[nextRow][nextCol].hasSnake)) {

			totalSpaces++;
			totalSpaces += validArea(board, boardSize, (Coor){.Row = nextRow, .Column = nextCol}, tailLoc, hasTail);
		}

		if (nextRow == tailLoc.Row && nextCol == tailLoc.Column) {
			*hasTail = true;
		}
	}


	return totalSpaces;
}


char smartMove(gameData gameInfo, Snake* snakeHead) {
	Coor appleLoc = *(gameInfo.appleLocation);
	Coor snakeLoc = {.Row = snakeHead->Row, .Column = snakeHead->Column};
	Coor tailLoc;

	Snake* currSpot = snakeHead;
	while (currSpot->previousSpot != NULL) {
		currSpot = currSpot->previousSpot;
	}
	tailLoc.Row = currSpot->Row;
	tailLoc.Column = currSpot->Column;

	bool validMoves[4] = {false, false, false, false};
	getSafeMoves(gameInfo.board, gameInfo.boardSize, snakeLoc, validMoves);
	bool targetDir[4] = {false, false, false, false};
	getTargetDirection(snakeLoc, appleLoc, targetDir);

 	int yMoveTypes[4] = {-1, 0, 1, 0};
	int xMoveTypes[4] = {0, -1, 0, 1};

	int potMoveAreas[4] = {0, 0, 0, 0};
	bool hadTail[4] = {false, false, false, false};

	for (int i = 0;  i < 4; i++) {
		if (validMoves[i] == true) {
			Space** boardCopy = copyBoard(gameInfo.board, gameInfo.boardSize);
			potMoveAreas[i] = validArea(
				boardCopy, 
				gameInfo.boardSize, 
				(Coor){.Row = snakeLoc.Row + yMoveTypes[i], .Column = snakeLoc.Column + xMoveTypes[i]}, 
				tailLoc, 
				&hadTail[i]
			);

			//Debug Line that shows moves in each direction		
			// printf("Move Count: %d %d\n", i, potMoveAreas[i]);
			// printf("Bool tail: %d\n", (int)hadTail[i]);

			freeBoard(gameInfo.boardSize, boardCopy);
		}
	}

	char finalDirection[4] = {' ', ' ', ' ', ' '};
	int directionCount = -1;
	// Try to make a move toward the apple that has an escape
	// if (!(gameInfo.board[snakeLoc.Row + yMoveTypes[i]][snakeLoc.Column + xMoveTypes[i]].hasApple)) {
	// 			return enumToChar(i);
	// 	}
	// && (potMoveAreas[i]) >= 1
	for (int i = 0; i < 4; i++) {
		if ((targetDir[i]) && (validMoves[i]) && hadTail[i]) {
			directionCount++;
			finalDirection[directionCount] = enumToChar(i);
		}
	}
	if (directionCount >= 0) {
		// randFormula = ((rand() % (max - min + 1)) + min)
		int directionIndx = (rand() % (directionCount - 0 + 1) + 0);
		return finalDirection[directionIndx];
	}

	// Try to make a general safe move with an escape
	for (int i = 0; i < 4; i++) {
		if ((validMoves[i]) && (potMoveAreas[i]) >= 1 && hadTail[i]) {
			directionCount++;
			finalDirection[directionCount] = enumToChar(i);
		}
	}
	if (directionCount >= 0) {
		// randFormula = ((rand() % (max - min + 1)) + min)
		int directionIndx = (rand() % (directionCount - 0 + 1) + 0);
		return finalDirection[directionIndx];
	}

	// Just try to move somewhere with space
	for (int i = 0; i < 4; i++) {
		if ((validMoves[i]) && (potMoveAreas[i]) >= 1) {
			directionCount++;
			finalDirection[directionCount] = enumToChar(i);
		}
	}
	if (directionCount >= 0) {
		// randFormula = ((rand() % (max - min + 1)) + min)
		int directionIndx = (rand() % (directionCount - 0 + 1) + 0);
		return finalDirection[directionIndx];
	}

	// Preserve Life
	for (int i = 0; i < 4; i++) {
		if ((validMoves[i])) {
			directionCount++;
			finalDirection[directionCount] = enumToChar(i);;
		}
	}
	if (directionCount >= 0) {
		// randFormula = ((rand() % (max - min + 1)) + min)
		int directionIndx = (rand() % (directionCount - 0 + 1) + 0);
		return finalDirection[directionIndx];
	}

	return 'w';
}