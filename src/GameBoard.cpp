
#include <ncurses.h>
#include "Settings.h"
#include "GameBoard.h"
#include "Board.h"

GameBoard::GameBoard(int height, int width, int y, int x) : Board(height, width, y, x){
    
    sideWallArray = new int *[SIDEWALL_SIZE];
    for(int i=0; i<SIDEWALL_SIZE; i++)
        sideWallArray[i] = new int[2];

    int idx = 0;

    // top
    for(int c=GAMEBOARD_START_X; c< GAMEBOARD_END_X; c++){
        sideWallArray[idx][0] = GAMEBOARD_START_Y - 1;
        sideWallArray[idx][1] = c;
        idx++;
    }

    // right
    for(int r=GAMEBOARD_START_Y; r< GAMEBOARD_END_Y; r++){
        sideWallArray[idx][0] = r;
        sideWallArray[idx][1] = GAMEBOARD_END_X;
        idx++;
    }

    // bottom
    for(int c=GAMEBOARD_START_X; c< GAMEBOARD_END_X; c++){
        sideWallArray[idx][0] = GAMEBOARD_END_Y;
        sideWallArray[idx][1] = c;
        idx++;
    }

    // left
    for(int r=GAMEBOARD_START_Y; r< GAMEBOARD_END_Y; r++){
        sideWallArray[idx][0] = r;
        sideWallArray[idx][1] = GAMEBOARD_START_X - 1;
        idx++;
    }
}

GameBoard::~GameBoard(){
    for(int i=0; i<SIDEWALL_SIZE; i++)
        delete[] sideWallArray[i];
    delete[] sideWallArray;
}


void GameBoard::drawWall(){

    // top
    Board topWall(1, GAMEBOARD_COLS, GAMEBOARD_START_Y-1, GAMEBOARD_START_X);
    topWall.initialize();
    topWall.setBkgd(COLOR_PAIR(BLUE));
    topWall.addBorder(COLOR_PAIR(BLUE));
    topWall.refresh();

    // right
    Board rightWall(GAMEBOARD_ROWS, 1, GAMEBOARD_START_Y, GAMEBOARD_END_X);
    rightWall.initialize();
    rightWall.setBkgd(COLOR_PAIR(BLUE));
    rightWall.addBorder(COLOR_PAIR(BLUE));
    rightWall.refresh();

    // bottom
    Board bottomWall(1, GAMEBOARD_COLS, GAMEBOARD_END_Y, GAMEBOARD_START_X);
    bottomWall.initialize();
    bottomWall.setBkgd(COLOR_PAIR(BLUE));
    bottomWall.addBorder(COLOR_PAIR(BLUE));
    bottomWall.refresh();

    // left
    Board leftWall(GAMEBOARD_ROWS, 1, GAMEBOARD_START_Y, GAMEBOARD_START_X-1);
    leftWall.initialize();
    leftWall.setBkgd(COLOR_PAIR(BLUE));
    leftWall.addBorder(COLOR_PAIR(BLUE));
    leftWall.refresh();

    // edges
    Board topEdgeL(1, 1, GAMEBOARD_START_Y-1, GAMEBOARD_START_X-1);
    topEdgeL.initialize();
    topEdgeL.setBkgd(COLOR_PAIR(CYAN));
    topEdgeL.addBorder(COLOR_PAIR(CYAN));
    topEdgeL.refresh();

    Board topEdgeR(1, 1, GAMEBOARD_START_Y-1, GAMEBOARD_END_X);
    topEdgeR.initialize();
    topEdgeR.setBkgd(COLOR_PAIR(CYAN));
    topEdgeR.addBorder(COLOR_PAIR(CYAN));
    topEdgeR.refresh();

    Board btmEdgeL(1, 1, GAMEBOARD_END_Y, GAMEBOARD_START_X-1);
    btmEdgeL.initialize();
    btmEdgeL.setBkgd(COLOR_PAIR(CYAN));
    btmEdgeL.addBorder(COLOR_PAIR(CYAN));
    btmEdgeL.refresh();

    Board btmEdgeR(1, 1, GAMEBOARD_END_Y, GAMEBOARD_END_X);
    btmEdgeR.initialize();
    btmEdgeR.setBkgd(COLOR_PAIR(CYAN));
    btmEdgeR.addBorder(COLOR_PAIR(CYAN));
    btmEdgeR.refresh();

}
