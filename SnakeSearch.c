#include <stdio.h>
#include "BoardFuncs.h"
#include "SnakeLogic.h"


int main() {
    int boardSize = 9;

    Pos** board = initalizeBoard(boardSize);
    Snake* snakeHead = createSnake(board, 4, 4);


    board[0][3].hasApple = true;

    printBoard(boardSize, board);
    freeBoard(boardSize, board);

    return 0;
}