#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "../include/BoardFuncs.h"
#include "../include/SnakeLogic.h"
#include "../include/SnakeAlgs.h"
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
    clock_t startTime = clock();

    if (argc < 3) {
        printf("Pass total tests to trial and board size.\n");
        return 0;
    }

    int totalCycles = atoi(argv[1]);
    int boardSize = atoi(argv[2]);

    FILE* snakeData = fopen("Data/SmartSnakeData.csv", "w");
	gameData gameInfo;

    srand(generateSeed());

    for (int currentCycle = 0; currentCycle < totalCycles; currentCycle++) {
        printf("Current Cycle: %d %c", currentCycle, spinner(currentCycle));
        unsigned int seed = generateSeed();
        srand(seed);
        
        // char dataBuffer[100];
        // snprintf(dataBuffer, sizeof(dataBuffer), "%u\n", seed);
        // fputs(dataBuffer, snakeData);
        // Use above lines for collecting endless loop seeds

        Space** board = initalizeBoard(boardSize);
        Snake* snakeHead = createSnake(board, boardSize);
        int totalValidSpaces = boardSize*boardSize;

        gameInfo.board = board;
        gameInfo.boardSize = boardSize;
        gameInfo.validSpaces = initializeValidSpaces(boardSize);
        gameInfo.totalValidSpaces = &totalValidSpaces;
        gameInfo.appleLocation = (Coor*)malloc(sizeof(Coor));

        removeSpace(gameInfo, snakeHead->Row, snakeHead->Column);
        addApple(gameInfo);

        char nextMove;
        int totalMoves = 0;

        while (true) {
            nextMove = ' ';
            nextMove = smartMove(gameInfo, snakeHead);
            
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
            if (currentEndCode != alive) {
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
    clock_t endTime = clock();

    double totalSeconds = (double)((endTime - startTime) / CLOCKS_PER_SEC);
    long long miliseconds = (long long)(totalSeconds * 1000);

    long long minutes = miliseconds / 60000;
    long long seconds = (miliseconds % 60000) / 1000;
    miliseconds %= 1000;

    printf("Total Time: %lld:%lld.%lld", minutes, seconds, miliseconds);
}