#include <stdio.h>
#include <windows.h>
#include "BoardFuncs.h"
#include "SnakeLogic.h"
#include "DataStructs.h"

enum Timing {
    std = 0, 
    lose = 225
}; // These values scale with board size

int main() {
    // Seed for apple spawns
    srand((unsigned int)GetTickCount());

    int boardSize = 0;
    printf("Select a board size (must be greater than 2)\n");
    while (boardSize < 3) {
            scanf(" %d", &boardSize);
            printf(UP DEL "\r");
    }
    printf(UP DEL "\r");

    Space** board = initalizeBoard(boardSize);
    Snake* snakeHead = createSnake(board, 2, 2);
    Coor* validSpots = initializeValidSpaces(boardSize);
    int totalValidSpots = (boardSize * boardSize);
    gameData gameInfo = {.board = board, .boardSize = boardSize, .validSpaces = validSpots, .totalValidSpaces = &totalValidSpots};

    removeSpace(gameInfo, 2, 2);
    board[0][0].hasApple = true;

    printBoard(boardSize, (std/(boardSize * boardSize)), board);
    char nextMove;

    for (int i = 0; i < 500; i++) {
        nextMove = ' ';
        printf("Move %d of 500 (w a s d)\n", i);
        while (!(nextMove == 'w' || nextMove == 'a' || nextMove == 's' || nextMove == 'd')) {
            scanf(" %c", &nextMove);
            printf(UP DEL "\r");
        }
        clearBoard(boardSize);
        
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

        printBoard(boardSize, (std/(boardSize * boardSize)), board);
        
        if (snakeHead == false) {
            endGame(boardSize, (lose/(boardSize * boardSize)));
            break;
        }
    }

    freeBoard(boardSize, board);
    freeValidSpaces(validSpots);
    return 0;
}