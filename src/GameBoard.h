#include <iostream>
#include <ncurses.h>

class GameBoard : public Board{
    WINDOW *board_win;
    int height, width;
    
public:
    GameBoard(int height, int width, int y, int x) : Board(height, width, y, x){
    }
};