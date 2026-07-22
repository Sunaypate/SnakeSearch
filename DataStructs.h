#ifndef DataStructs_h
#define DataStructs_h
//TODO: Pick a better name for this since its similar to coordinate
typedef struct Positon {
    bool hasApple;
    bool hasSnake;
    int Index;
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

//TODO: Make a struct to represent all key compoments that are used by most functions
// I.E. board, board size, valid spaces, amount of valid spaces, ETC

#endif