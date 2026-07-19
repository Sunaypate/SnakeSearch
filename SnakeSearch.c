#include <stdio.h>
#include "BoardFuncs.h"
#include "SnakeLogic.h"

enum Pause {
    std = 10,
    lose = 50
};

int main() {
    int boardSize = 5;

    Pos** board = initalizeBoard(boardSize);
    Snake* snakeHead = createSnake(board, 2, 2);
    board[2][3].hasApple = true;
    // board[1][1].hasApple = true;
    // board[4][4].hasApple = true;
    printBoard(boardSize, std, board);
    char nextMove;


    for (int i = 0; i < 15; i++) {
        scanf(" %c", &nextMove);
        clearBoard(boardSize);

        if (nextMove == 'w') {
            snakeHead = moveSnake(board, snakeHead, snakeHead->X - 1, snakeHead->Y);
        }
        else if (nextMove == 'a') {
            snakeHead = moveSnake(board, snakeHead, snakeHead->X, snakeHead->Y - 1);
        }
        else if (nextMove == 's') {
            snakeHead = moveSnake(board, snakeHead, snakeHead->X + 1, snakeHead->Y);
        }
        else if (nextMove == 'd') {
                snakeHead = moveSnake(board, snakeHead, snakeHead->X, snakeHead->Y + 1);           
        }
        printBoard(boardSize, std, board);
    }
    lostGame(boardSize, lose);
    freeBoard(boardSize, board);
    return 0;
}