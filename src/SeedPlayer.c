#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/BoardFuncs.h"
#include "../include/SnakeLogic.h"
#include "../include/SnakeAlg.h"
#include "../include/DataStructs.h"

int main() {
	// Seed for apple spawns
	gameData gameInfo;
    int boardSize = 4; // Must Preset This Line

    unsigned int seed = 32021025; // And Also This Line (Also Do Bot Type Below)
    srand(seed);

    Space** board = initalizeBoard(boardSize);
    Snake* snakeHead = createSnake(board, 2, 2);
    int totalValidSpaces = boardSize*boardSize;

    gameInfo.board = board;
    gameInfo.boardSize = boardSize;
    gameInfo.validSpaces = initializeValidSpaces(boardSize);
    gameInfo.totalValidSpaces = &totalValidSpaces;
    gameInfo.appleLocation = (Coor*)malloc(sizeof(Coor));

    removeSpace(gameInfo, 2, 2);
    addApple(gameInfo);
    

    printBoard(boardSize, 0, board);
    char nextMove;
    int moveCount = 0;

    while (true) {
        nextMove = ' ';
        moveCount++;
        printf("Move %d (w a s d)\n", moveCount);
        nextMove = safeMove(gameInfo, snakeHead); //Bot Type Here

        printf("Next Move: %c", nextMove);
        Sleep(250);

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
        printBoard(boardSize, 0, board);
        
        if (currentEndCode != safe) {
            endGame(boardSize, 50);
            printf("Total Moves: %d Total Apples: %d\n", moveCount, ((boardSize * boardSize) - *(gameInfo.totalValidSpaces) - 1));
            break;
        }
    }

    freeBoard(boardSize, board);
    freeValidSpaces(gameInfo.validSpaces);
    free(gameInfo.appleLocation);
    freeSnake(snakeHead);

	return 0;
}