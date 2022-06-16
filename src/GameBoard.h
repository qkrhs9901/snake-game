#include <iostream>
#include <ncurses.h>
#include "Settings.h"
#include "Board.h"

// MACRO
#ifndef __GAMEBOARD__
#define __GAMEBOARD__


class GameBoard : public Board {
    WINDOW *board_win;

public:
    GameBoard(int height, int width, int y, int x) : Board(height, width, y, x) {}
    ~GameBoard(){}

};


#endif