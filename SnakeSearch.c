#include <stdio.h>
#include "BoardFuncs.h"


int main() {
    int boardSize = 10;

    Pos** board = initalizeBoard(boardSize);


    board[0][3].hasApple = true;
    board[2][3].hasSnake = true;
    board[2][4].hasSnake = true;

    printBoard(boardSize, board);
    freeBoard(boardSize, board);

    return 0;
}