#ifndef DataStructs_h
#define DataStructs_h

typedef struct Positon {
    bool hasApple;
    bool hasSnake;
} Pos;

typedef struct Coordinate {
    int Row;
    int Column;
} Coor;

typedef struct SnakeBody {
    int Row;
    int Column;
    struct SnakeBody* previousSpot;
} Snake;

#endif