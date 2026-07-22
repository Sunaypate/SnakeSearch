#ifndef DataStructs_h
#define DataStructs_h

typedef struct Space {
    bool hasApple;
    bool hasSnake;
    int Index;
} Space;

typedef struct Coordinate {
    int Row;
    int Column;
    
} Coor;

typedef struct SnakeBody {
    int Row;
    int Column;
    struct SnakeBody* previousSpot;
} Snake;

typedef struct gameData {
    Space** board;
    int boardSize;
    Coor* validSpaces;
    int* totalValidSpaces;
} gameData;

enum endCode {
    safe,
    won,
    outOfBounds,
    hitSelf
};

// Since end code is used by multiple files, it must be declared as existing, but only be edited in one file
extern enum endCode currentEndCode;

#endif