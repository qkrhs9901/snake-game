#include <ncurses.h>
#include <iostream>
#include <vector>
#include "Board.h"
#include "GameBoard.h"
#include "GameBoard.cpp"
#include "Snake.h"
#include "Snake.cpp"
#include "Player.h"
#include "Player.cpp"
#include "Settings.h"
#include "innerWall.h"
#include "innerWall.cpp"

int main(int argc, char *argv[]){
    initscr();
    nodelay(stdscr, true);      // getch will not wait until user press a key
    // keypad(stdscr, true);       // keypad to control
    noecho();
    curs_set(0);                // invisible cursor
    start_color();
    refresh();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);     // set color as a pair to number 5 (text and background) - WHITE
    init_pair(2, COLOR_BLACK, COLOR_BLUE);      // set color as a pair to number 5 (text and background) - BLUE
    init_pair(3, COLOR_BLACK, COLOR_CYAN);      // set color as a pair to number 5 (text and background) - CYAN
    init_pair(5, COLOR_RED, COLOR_WHITE);       // set color as a pair to number 5 (text and background) - RED
    

    // inner wall
    innerWall wall_1;
    wall_1.addColWall(10, GAMEBOARD_START_Y, (GAMEBOARD_START_X + GAMEBOARD_END_X) / 2);
    int** innerWall_1 = wall_1.getWallArray();
    int wall_1_sz = wall_1.getCurrentWallSize();

    // gameboard
    GameBoard game(GAMEBOARD_ROWS, GAMEBOARD_COLS, GAMEBOARD_POS, GAMEBOARD_POS, wall_1_sz);
    game.initialize();
    game.setBkgd(COLOR_PAIR(1));
    game.addBorder(COLOR_PAIR(1));
    game.refresh();

    game.setWallArray(innerWall_1);
    game.drawWall();

    
    // score board
    Board score(SCOREBOARD_ROWS, SCOREBOARD_COLS, SCOREBOARD_POS_Y, SCOREBOARD_POS_X);
    score.initialize();
    score.setBkgd(COLOR_PAIR(1));
    score.addBox();
    score.refresh();

    // mission board
    Board mission(SCOREBOARD_ROWS, SCOREBOARD_COLS, MISSIONBOARD_POS_Y, MISSIONBOARD_POS_X);
    mission.initialize();
    mission.setBkgd(COLOR_PAIR(1));
    mission.addBox();
    mission.refresh();

    Player p;
    p.setBoard();
    
    Snake s;
    s.start();
    
    attron(COLOR_PAIR(5));      // set color 2 to terminal
    move(14, 18);
    printw("G A M E   O V E R");
    refresh();
    attroff(COLOR_PAIR(5));     // reset color to terminal

    nodelay(stdscr, false);
    getch();
    endwin();

    return 0;
}



