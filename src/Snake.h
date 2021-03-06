#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include "Board.h"
#include "Player.h"
using namespace std;

// 스네이크의 움직임 포함 게임의 전체적인 실행

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
    char goodF, badF;
    Snakepart food;
    Snakepart poison;
    bool get, bad;

    int** sideWallArray;
    int** innerWallArray = nullptr;
    int** stuckWallArray = nullptr;
    int innerWallSize = 0;
    int stuckWallSize = 0;
    int gateArray[2][3]; //  0: y_pos / 1: x_pos / 2: side(0) | inner(1) 

public:
    bool clear;
    Snake(int** sideWallArray);
    ~Snake();
    void setInnerWall(int sz, int** innerWallArray);
    void setStuckWall(int sz, int** stuckWallArray);

    void setGate();
    void enterGate(int inGateIdx);
    void setDirectionInnerGate(int currDirection, int* checkDirection);
    void moveHeadOutGate(int* outGate);

    bool collision();
    void setDirection(int key);
    void moveSnake();

    void putfood();
    void putpoison();

    Player* play;

    void start();
    vector<Snakepart> snake;
};

#endif