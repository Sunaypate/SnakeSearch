#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "BoardFuncs.h"
#include "SnakeLogic.h"
#include "SnakeAlg.h"
#include "DataStructs.h"

enum Timing {
	std = 0, 
	lose = 225
}; // These values scale with board size

enum gameMode {
	human = 1,
	bot = 2,
	end = -1
} currMode = human;

int main() {
	// Seed for apple spawns
	// 
	srand((unsigned int)GetTickCount());
	gameData gameInfo;

	printf("Select Game Mode (1:Human, 2:Bot, -1:Quit)\n");
	scanf(" %d", &currMode);
	printf(UP DEL "\r");
	printf(UP DEL "\r");
	
	while (currMode != end) {
		int boardSize = 0;

		printf("Select A Board Size (must be greater than 2)\n");
		while (boardSize < 3) {
				scanf(" %d", &boardSize);
				printf(UP DEL "\r");
		}
		printf(UP DEL "\r");

		Space** board = initalizeBoard(boardSize);
		Snake* snakeHead = createSnake(board, 2, 2);

		gameInfo.board = board;
		gameInfo.boardSize = boardSize;
		gameInfo.validSpaces = initializeValidSpaces(boardSize);
		gameInfo.totalValidSpaces = &(int){boardSize * boardSize};
		gameInfo.appleLocation = (Coor*)malloc(sizeof(gameInfo.appleLocation));

		removeSpace(gameInfo, 2, 2);
		addApple(gameInfo);
		

		printBoard(boardSize, (std/(boardSize * boardSize)), board);
		char nextMove;
		int moveCount = 0;

		while (true) {
			nextMove = ' ';
			moveCount++;
			printf("Move %d (w a s d)\n", moveCount);

			if(currMode == human) {
				while (!(nextMove == 'w' || nextMove == 'a' || nextMove == 's' || nextMove == 'd')) {
					scanf(" %c", &nextMove);
					printf(UP DEL "\r");
				}
			}
			else {
				nextMove = simpleMove(gameInfo, snakeHead);
				Sleep(1000);
			}
			
			if (nextMove == 'w') {
				snakeHead = moveSnake(gameInfo, snakeHead, snakeHead->Row - 1, snakeHead->Column);
			}
			else if (nextMove == 'a') {
				snakeHead = moveSnake(gameInfo, snakeHead, snakeHead->Row, snakeHead->Column - 1);
			}
			else if (nextMove == 's') {
				snakeHead = moveSnake(gameInfo, snakeHead, snakeHead->Row + 1, snakeHead->Column);
			}
			else if (nextMove == 'd') {
				snakeHead = moveSnake(gameInfo, snakeHead, snakeHead->Row, snakeHead->Column + 1);           
			}
			
			
			clearBoard(boardSize);
			printBoard(boardSize, (std/(boardSize * boardSize)), board);
			
			if (snakeHead == NULL) {
				endGame(boardSize, (lose/(boardSize * boardSize)));
				break;
			}
			
		}

		freeBoard(boardSize, board);
		freeValidSpaces(gameInfo.validSpaces);
		free(gameInfo.appleLocation);

		printf("Select Game Mode (1:Human, 2:Bot, -1:Quit)\n");
		scanf(" %d", &currMode);
		printf(UP DEL "\r");
	}

	return 0;
}