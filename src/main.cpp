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

int main(){
    initscr();
    nodelay(stdscr, true);      // getch will not wait until user press a key
    // keypad(stdscr, true);       // keypad to control
    noecho();
    curs_set(0);                // invisible cursor
    start_color();
    refresh();
    init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);     // set color as a pair to number 1 (background - WHITE) 
    init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);      // set color as a pair to number 2 (background - BLUE)
    init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);      // set color as a pair to number 3 (background - CYAN) 
    init_pair(RED, COLOR_BLACK, COLOR_RED);       // set color as a pair to number 4 (background - RED) 
    init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);     // set color as a pair to number 5 (background - GREEN) 
    init_pair(MAGENTA, COLOR_BLACK, COLOR_MAGENTA);       // set color as a pair to number 6 (background - MAGENTA) 
    init_pair(RED_WHITE, COLOR_RED, COLOR_WHITE);       // set color as a pair to number 7 (text - RED / background - WHITE) 


    // gameboard
    GameBoard game(GAMEBOARD_ROWS, GAMEBOARD_COLS, GAMEBOARD_POS, GAMEBOARD_POS);
    game.initialize();
    game.setBkgd(COLOR_PAIR(WHITE));
    game.addBorder(COLOR_PAIR(WHITE));
    game.refresh();
    game.drawWall();
    int** sideWallArray = game.getSideWallArray();

    // inner wall
    innerWall wall_1;
    wall_1.addColWall(10, GAMEBOARD_START_Y, (GAMEBOARD_START_X + GAMEBOARD_END_X) / 2);
    wall_1.drawWall();
    int** innerWallArray = wall_1.getInnerWallArray();
    int innerWallSize = wall_1.getCurrentSize();

    
    // score board
    Board score(SCOREBOARD_ROWS, SCOREBOARD_COLS, SCOREBOARD_POS_Y, SCOREBOARD_POS_X);
    score.initialize();
    score.setBkgd(COLOR_PAIR(WHITE));
    score.addBox();
    score.refresh();

    // mission board
    Board mission(SCOREBOARD_ROWS, SCOREBOARD_COLS, MISSIONBOARD_POS_Y, MISSIONBOARD_POS_X);
    mission.initialize();
    mission.setBkgd(COLOR_PAIR(WHITE));
    mission.addBox();
    mission.refresh();

    Player p;
    p.setBoard();
    
    Snake s(sideWallArray);
    s.setInnerWall(innerWallSize, innerWallArray);
    s.setGate();
    s.start();
    
    attron(COLOR_PAIR(RED_WHITE));      // set color 2 to terminal
    move(14, 18);
    printw("G A M E   O V E R");
    refresh();
    attroff(COLOR_PAIR(RED_WHITE));     // reset color to terminal

    nodelay(stdscr, false);
    getch();
    endwin();

    return 0;
}



