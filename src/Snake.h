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
    char direction, snakepart;
    bool get;
    int** sideWallArray;
    int** innerWallArray = nullptr;
    int innerWallSize = 0;
    int gateArray[2][2];

public:
    Snake(int** sideWallArray);
    ~Snake();
    void setInnerWall(int sz, int** innerWallArray);
    void setGate();

    bool collision();
    void enterGate(int inGate);
    void movesnake(int key);

    void start();
    vector<Snakepart> snake;
};

#endif