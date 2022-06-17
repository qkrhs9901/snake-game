#include <iostream>
#include <ncurses.h>

// MACRO
#ifndef __BOARD__
#define __BOARD__

class Board{
    WINDOW *board_win;
    int height, width;
    
public:
    Board(int height, int width, int y, int x) {
        int xMax=getmaxx(stdscr);
        int yMax=getmaxy(stdscr);

        board_win = newwin(height, width, y, x);
    }

    void initialize() {
        clear();
        refresh();
    }

    void addBox() {
        box(board_win, 0, 0);
    }

    void addAt(int y, int x, chtype ch) {
        mvwaddch(board_win, y, x, ch);
    }

    chtype getInput() {
        return wgetch(board_win);
    }

    void setBkgd(chtype color_pair) {
        wbkgd(board_win, color_pair);
    }

    void addBorder(chtype color_pair) {
        wattron(board_win, color_pair);
        wborder(board_win,' ',' ',' ',' ',' ',' ',' ',' ');
        wattroff(board_win, color_pair);
    } 

    void clear() {
        wclear(board_win);
        addBox();
    }

    void refresh() {
        wrefresh(board_win);
    }

};

#endif