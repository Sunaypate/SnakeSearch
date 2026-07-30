#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "BoardFuncs.h"
#include "SnakeLogic.h"
#include "SnakeAlg.h"
#include "DataStructs.h"

char spinner(int cCycle) {
    char loadTypes[4] = {'|', '/', '-', '\\'};
    char cLoad = loadTypes[cCycle % 4];
    return cLoad;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Pass total tests to trial and board size.\n");
        return 0;
    }

    int totalCycles = atoi(argv[1]);
    int boardSize = atoi(argv[2]);
    int currentCycle = 1;

    FILE* snakeData = fopen("SnakeData.csv", "w");

    srand((unsigned int)GetTickCount());
	gameData gameInfo;


    for (int currentCycle = 0; currentCycle < totalCycles; currentCycle++) {
        printf("Current Cycle: %d %c", currentCycle, spinner(currentCycle));
        //Sleep(5000/(100*totalCycles));

        Space** board = initalizeBoard(boardSize);
        Snake* snakeHead = createSnake(board, 2, 2);

        gameInfo.board = board;
        gameInfo.boardSize = boardSize;
        gameInfo.validSpaces = initializeValidSpaces(boardSize);
        gameInfo.totalValidSpaces = &(int){boardSize * boardSize};
        gameInfo.appleLocation = (Coor*)malloc(sizeof(gameInfo.appleLocation));

        removeSpace(gameInfo, 2, 2);
        addApple(gameInfo);

        char nextMove;
        int totalMoves = 0;

        Snake* currSpot;
        while (true) {
            Snake* headCopy = snakeHead;
            nextMove = ' ';
            nextMove = simpleMove(gameInfo, snakeHead);
            
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
            totalMoves++;
            
            if (snakeHead == NULL) {
                currSpot = headCopy;
                break;
            }
        }

        int totalApples = 0;
        Snake* priorSpot = NULL;
        
        while (currSpot->previousSpot != NULL) {
            totalApples++;
            priorSpot = currSpot;
            currSpot = currSpot->previousSpot;
        }

        freeBoard(boardSize, board);
        freeValidSpaces(gameInfo.validSpaces);
        free(gameInfo.appleLocation);


        char dataBuffer[100];
        snprintf(dataBuffer, sizeof(dataBuffer), "%d,%d,%d\n", totalMoves, totalApples, boardSize);
        fputs(dataBuffer, snakeData);
        printf(DEL "\r");
    }
}