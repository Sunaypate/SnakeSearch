#include <stdio.h>
#include "BoardFuncs.h"
#include "SnakeLogic.h"


int main() {
    int boardSize = 5;

    Pos** board = initalizeBoard(boardSize);
    Snake* snakeHead = createSnake(board, 2, 2);
    printBoard(boardSize, board);
    
    char nextMove;

    for (int i = 0; i < 10; i++) {
        scanf(" %c", &nextMove);
        printf("\n");
        
        if (nextMove == 'w') {
            snakeHead = moveSnake(board, snakeHead, snakeHead->row - 1, snakeHead->column);
        }
        else if (nextMove == 'a') {
            snakeHead = moveSnake(board, snakeHead, snakeHead->row, snakeHead->column - 1);
        }
        else if (nextMove == 's') {
            snakeHead = moveSnake(board, snakeHead, snakeHead->row + 1, snakeHead->column);
        }
        else if (nextMove == 'd') {
                snakeHead = moveSnake(board, snakeHead, snakeHead->row, snakeHead->column + 1);           
        }
        printBoard(boardSize, board);
    }

    freeBoard(boardSize, board);
    return 0;
}