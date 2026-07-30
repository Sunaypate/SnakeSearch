#include "../include/SnakeAlg.h"

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