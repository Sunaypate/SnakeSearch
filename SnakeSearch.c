#include <stdio.h>
#include <stdbool.h>

//Defining Color Codes for printing

#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define WHT "\x1b[0m"
// printf(RED "This text is red!" WHT"\n");

typedef struct Position {
    bool hasApple;
    bool hasSnake;
} Posit;

void printBoard(int size, Posit board[size][size]) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Posit currPosition = board[row][col];
            if (currPosition.hasApple) {
                printf(RED "A ");
            }
            else if (currPosition.hasSnake) {
                printf(GRN "S ");
            }
            else {
                printf(WHT "E ");
            }
        }
        printf("\n");
    }
}

void initalizeBoard(int size, Posit board[size][size]) {
    Posit emptyPosit = {.hasApple = false, .hasSnake = false};

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board[row][col] = emptyPosit;
        }
    }
}

int main() {
    int boardSize = 5;
    Posit board[boardSize][boardSize];
    initalizeBoard(boardSize, board);

    board[0][3].hasApple = true;
    board[2][3].hasSnake = true;
    board[2][4].hasSnake = true;


    printBoard(boardSize, board);

    return 0;
}