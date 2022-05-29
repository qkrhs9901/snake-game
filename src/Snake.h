#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
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
public:
    Snake();
    ~Snake();
    void start();
    bool collision();
    void movesnake();
    vector<Snakepart> snake;
};

#endif