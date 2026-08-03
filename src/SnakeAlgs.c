#include "../include/SnakeAlgs.h"

#include "../include/DataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

enum Direction {
	UP,
	LEFT,
	DOWN,
	RIGHT
};

void getSafeMoves(Space** board, int boardSize, Snake* snakeLoc, bool validMoves[4]) {
	int snakeRow = snakeLoc->Row;
	int snakeCol = snakeLoc->Column;

	if (!(snakeRow-1 < 0) && !(board[snakeRow-1][snakeCol].hasSnake)) {
		validMoves[UP] = true;
	}
	if (!(snakeCol-1 < 0) && !(board[snakeRow][snakeCol-1].hasSnake)) {
		validMoves[LEFT] = true;
	}
	if (!(snakeRow+1 == boardSize) && !(board[snakeRow+1][snakeCol].hasSnake)) {
		validMoves[DOWN] = true;
	}
	if (!(snakeCol+1 == boardSize) && !(board[snakeRow][snakeCol+1].hasSnake)) {
		validMoves[RIGHT] = true;
	}
}

void getTargetDirection(Snake* snakeLoc, Coor appleLoc, bool targetDirection[4]) {
	int snakeRow = snakeLoc->Row;
	int snakeCol = snakeLoc->Column;

	if(snakeRow > appleLoc.Row) {
		targetDirection[UP] = true;
	}
	if(snakeCol > appleLoc.Column) {
		targetDirection[LEFT] = true;
	}
	if(snakeRow < appleLoc.Row) {
		targetDirection[DOWN] = true;
	}
	if(snakeCol < appleLoc.Column) {
		targetDirection[RIGHT] = true;
	}
}

char enumToChar(enum Direction move) {
	switch (move) {
		case UP:
			return 'w';
		break;

		case LEFT:
			return 'a';
		break;

		case DOWN:
			return 's';
		break;

		case RIGHT:
			return 'd';
		break;

		default:
			return 'w';
		break;
	}
}

// Tries to move directly toward the apple with no regard to itself.
char simpleMove(gameData gameInfo, Snake* snakeHead) {
	Coor appleLoc = *(gameInfo.appleLocation);

	bool targetDirection[4] = {false, false, false, false};
	getTargetDirection(snakeHead, appleLoc, targetDirection);
	
	// Checks to see what will get it to the apple the fastest.
	if (targetDirection[DOWN]) {
		return 's';
	}
	else if (targetDirection[UP]) {
		return 'w';
	}
	else {
		if (targetDirection[RIGHT]) {
			return 'd';
		}
		else if (targetDirection[LEFT]) {
			return 'a';
		}
	}
	return 'w';
}

// Attempts to move toward the apple with move, but will avoid running into itself.
char safeMove(gameData gameInfo, Snake* snakeHead) {
	Coor appleLoc = *(gameInfo.appleLocation);

	// Figures out which moves can be made [w, a, s, d]
	bool validMoves[4] = {false, false, false, false};
	bool targetDir[4] = {false, false, false, false};
	getSafeMoves(gameInfo.board, gameInfo.boardSize, snakeHead, validMoves);
	getTargetDirection(snakeHead, appleLoc, targetDir);
	
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
	for (int row = 0; row < boardSize; row++) {
		lookUpTable[row] = (char*)malloc(boardSize * sizeof(char));
	}


	for (int topCell = 1; topCell < boardSize; topCell++) {
		lookUpTable[0][topCell] = 'a';
	}

	for (int leftCell = 0; leftCell < boardSize - 1; leftCell++) {
		lookUpTable[leftCell][0] = 's';
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

	for (int rightCell = 1; rightCell < boardSize; rightCell++) {
		lookUpTable[rightCell][boardSize - 1] = 'w';
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

// char smartMove(gameData gameInfo, Snake* snakeHead, int snakeSize) {
// 	Coor snakeLocs[snakeSize];
// 	Coor appleLoc = *(gameInfo.appleLocation);

// 	Snake* currSpot = snakeHead;
// 	int currIndx = 0;
// 	while (currSpot->previousSpot != NULL) {
// 		snakeLocs[currIndx].Row = currSpot->Row;
// 		snakeLocs[currIndx].Column = currSpot->Column;

// 		currSpot = currSpot->previousSpot;
// 		currIndx++;
// 	}
// 	snakeLocs[currIndx].Row = currSpot->Row;
// 	snakeLocs[currIndx].Column = currSpot->Column;


	
// 	return 'w';
// }