#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include "Board.h"
using namespace std;

// MACRO
#ifndef __SNAKE__
#define __SNAKE__

class Snakepart {
public:
    int x, y;
    Snakepart(int col, int row);
    Snakepart();
};

class Snake {
    int del;
    int snakeLen;
    char direction, snakepart;
    bool get;
    int** sideWallArray;
    int** innerWallArray = nullptr;
    int** stuckWallArray = nullptr;
    int innerWallSize = 0;
    int stuckWallSize = 0;
    int gateArray[2][3]; //  0: y_pos / 1: x_pos / 2: side(0) | inner(1) 

public:
    Snake(int** sideWallArray);
    ~Snake();
    void setInnerWall(int sz, int** innerWallArray);
    void setStuckWall(int sz, int** stuckWallArray);
    void setGate();

    bool collision();
    void enterGate(int inGateIdx);
    void setDirection(int key);
    void moveSnake();
    void moveHeadOutGate(int* outGate);

    void start();
    vector<Snakepart> snake;
};

#endif