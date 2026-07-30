#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/BoardFuncs.h"
#include "../include/SnakeLogic.h"
#include "../include/SnakeAlg.h"
#include "../include/DataStructs.h"

char spinner(int cCycle) {
    char loadTypes[4] = {'|', '/', '-', '\\'};
    char cLoad = loadTypes[cCycle % 4];
    return cLoad;
}

unsigned int generateSeed() {
    LARGE_INTEGER qpc;
    QueryPerformanceCounter(&qpc);
    return (unsigned int)(qpc.QuadPart ^ (qpc.QuadPart >> 32));
}

int main(int argc, char *argv[]) {
    SYSTEMTIME sTime;
    SYSTEMTIME eTime;
    GetLocalTime(&sTime);

    if (argc < 3) {
        printf("Pass total tests to trial and board size.\n");
        return 0;
    }

    int totalCycles = atoi(argv[1]);
    int boardSize = atoi(argv[2]);

    FILE* snakeData = fopen("Data/SimpleSnakeData.csv", "w");
	gameData gameInfo;

    srand(generateSeed());

    for (int currentCycle = 0; currentCycle < totalCycles; currentCycle++) {
        printf("Current Cycle: %d %c", currentCycle, spinner(currentCycle));
        unsigned int seed = generateSeed();
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

        char nextMove;
        int totalMoves = 0;

        while (true) {
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
            if (currentEndCode != safe) {
                break;
            }
        }

        int totalApples = ((boardSize * boardSize) - *(gameInfo.totalValidSpaces) - 1);

        freeBoard(boardSize, board);
        freeValidSpaces(gameInfo.validSpaces);
        free(gameInfo.appleLocation);
        freeSnake(snakeHead);
        
        
        char dataBuffer[100];
        snprintf(dataBuffer, sizeof(dataBuffer), "%d,%d,%u\n", totalMoves, totalApples, seed);
        fputs(dataBuffer, snakeData);
        printf(DEL "\r");
    }
    GetLocalTime(&eTime);
    SYSTEMTIME tTime = {.wMinute = eTime.wMinute - sTime.wMinute, 
                        .wSecond = eTime.wSecond - sTime.wSecond,
                        .wMilliseconds = eTime.wMilliseconds - sTime.wMilliseconds};
    printf("Total Time: %d:%d.%d", tTime.wMinute, tTime.wSecond, tTime.wMilliseconds);
}