#include <iostream>
#include <ncurses.h>

// MACRO
#ifndef __GAMEBOARD__
#define __GAMEBOARD__

class GameBoard : public Board {
    WINDOW *board_win;
    int height, width;
    
public:
    GameBoard(int height, int width, int y, int x) : Board(height, width, y, x) {
    }
};

#endif