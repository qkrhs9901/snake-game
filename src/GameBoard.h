#include <iostream>
#include <ncurses.h>
#include "Settings.h"
#include "Board.h"

// MACRO
#ifndef __GAMEBOARD__
#define __GAMEBOARD__

#define WALL_COLOR 1000

class GameBoard : public Board {
    WINDOW *board_win;
    int **wallArray;
    int wallSize;
    int innerWallSize;
    
public:
    GameBoard(int height, int width, int y, int x, int innerWallSize=0);
    ~GameBoard();

    void setWallArray(int** innerWall);
    void drawWall();
    int** getWallArray() {return wallArray;}

};


#endif