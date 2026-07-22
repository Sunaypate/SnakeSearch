#include <stdio.h>
#include <windows.h>
#include "BoardFuncs.h"
#include "SnakeLogic.h"
#include "DataStructs.h"

enum Timing {
    std = 0, //25
    lose = 75
};

int main() {
    // Seed for apple spawns
    //(unsigned int)GetTickCount()
    srand(1);

    int boardSize = 3;

    Pos** board = initalizeBoard(boardSize);
    Snake* snakeHead = createSnake(board, 2, 2);
    Coor* validSpots = initializeValidSpaces(boardSize);
    int totalValidSpots = (boardSize * boardSize);
    removeSpace(board, validSpots, &totalValidSpots, 2, 2);


    board[0][0].hasApple = true;

    printBoard(boardSize, std, board);
    char nextMove;

    for (int i = 0; i < 200; i++) {
        nextMove = ' ';
        printf("Move %d of 200 (w a s d)\n", i);
        while (!(nextMove == 'w' || nextMove == 'a' || nextMove == 's' || nextMove == 'd')) {
            scanf(" %c", &nextMove);
            printf(UP DEL "\r");
        }
        clearBoard(boardSize);
        
        if (nextMove == 'w') {
            snakeHead = moveSnake(board, boardSize, snakeHead, snakeHead->Row - 1, snakeHead->Column);
        }
        else if (nextMove == 'a') {
            snakeHead = moveSnake(board, boardSize, snakeHead, snakeHead->Row, snakeHead->Column - 1);
        }
        else if (nextMove == 's') {
            snakeHead = moveSnake(board, boardSize, snakeHead, snakeHead->Row + 1, snakeHead->Column);
        }
        else if (nextMove == 'd') {
                snakeHead = moveSnake(board, boardSize, snakeHead, snakeHead->Row, snakeHead->Column + 1);           
        }
        
        printf("\n");
        printBoard(boardSize, std, board);

        if (snakeHead == false) {
            lostGame(boardSize, lose);
            break;
        }
    }

    freeBoard(boardSize, board);
    freeValidSpaces(validSpots);
    return 0;
}