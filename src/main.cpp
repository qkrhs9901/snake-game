#include <ncurses.h>
#include "Board.h"
#include "GameBoard.h"

#define GAMEBOARD_DIM 22
#define GAMEBOARD_ROWS GAMEBOARD_DIM
#define GAMEBOARD_COLS GAMEBOARD_DIM * 2
#define GAMEBOARD_POS 4

#define SCOREBOARD_DIM 10
#define SCOREBOARD_ROWS SCOREBOARD_DIM
#define SCOREBOARD_COLS SCOREBOARD_DIM * 3

#define MISSIONBOARD_DIM 10
#define MISSIONBOARD_ROWS MISSIONBOARD_DIM
#define MISSIONBOARD_COLS MISSIONBOARD_DIM * 3

int main(int argc, char *argv[]){

    initscr();
    start_color();
    refresh();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);

    // gameboard
    GameBoard game(GAMEBOARD_ROWS, GAMEBOARD_COLS, GAMEBOARD_POS, GAMEBOARD_POS);
    game.initialize();
    game.setBkgd(COLOR_PAIR(1));
    game.addBorder(COLOR_PAIR(2));
    game.refresh();

    // gameboard's edges
    Board topEdgeL(1, 1, GAMEBOARD_POS, GAMEBOARD_POS);
    topEdgeL.initialize();
    topEdgeL.setBkgd(COLOR_PAIR(3));
    topEdgeL.addBorder(COLOR_PAIR(3));
    topEdgeL.refresh();

    Board topEdgeR(1, 1, GAMEBOARD_POS, GAMEBOARD_POS+GAMEBOARD_COLS-1);
    topEdgeR.initialize();
    topEdgeR.setBkgd(COLOR_PAIR(3));
    topEdgeR.addBorder(COLOR_PAIR(3));
    topEdgeR.refresh();

    Board btmEdgeL(1, 1, GAMEBOARD_POS+GAMEBOARD_ROWS-1, GAMEBOARD_POS);
    btmEdgeL.initialize();
    btmEdgeL.setBkgd(COLOR_PAIR(3));
    btmEdgeL.addBorder(COLOR_PAIR(3));
    btmEdgeL.refresh();

    Board btmEdgeR(1, 1, GAMEBOARD_POS+GAMEBOARD_ROWS-1, GAMEBOARD_POS+GAMEBOARD_COLS-1);
    btmEdgeR.initialize();
    btmEdgeR.setBkgd(COLOR_PAIR(3));
    btmEdgeR.addBorder(COLOR_PAIR(3));
    btmEdgeR.refresh();

    // score board
    Board score(SCOREBOARD_ROWS, SCOREBOARD_COLS, 4, 58);
    score.initialize();
    score.setBkgd(COLOR_PAIR(1));
    score.addBox();
    score.refresh();

    // mission board
    Board mission(SCOREBOARD_ROWS, SCOREBOARD_COLS, 16, 58);
    mission.initialize();
    mission.setBkgd(COLOR_PAIR(1));
    mission.addBox();
    mission.refresh();

    getch();

    endwin();

    return 0;
}



