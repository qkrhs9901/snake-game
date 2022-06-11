
#include <ncurses.h>
#include "Settings.h"
#include "GameBoard.h"
#include "Board.h"

GameBoard::GameBoard(int height, int width, int y, int x, int innerWallSize) : Board(height, width, y, x), innerWallSize(innerWallSize) {
    this->wallSize = SIDEWALL_SIZE + innerWallSize;
    wallArray = new int *[wallSize];
    
    for(int i=0; i<wallSize; i++)
        wallArray[i] = new int[2];
}

GameBoard::~GameBoard(){
    for(int i=0; i<wallSize; i++)
        delete[] wallArray[i];
    delete[] wallArray;
}

void GameBoard::setWallArray(int** innerWall){
    // 테두리벽과 board 내부 벽의 좌표를 arr에 추가

    // sideWall
    int size = 0;

    // top
    for(int c=GAMEBOARD_START_X; c< GAMEBOARD_END_X; c++){
        wallArray[size][0] = GAMEBOARD_START_Y - 1;
        wallArray[size][1] = c;
        size++;
    }

    // right
    for(int r=GAMEBOARD_START_Y; r< GAMEBOARD_END_Y; r++){
        wallArray[size][0] = r;
        wallArray[size][1] = GAMEBOARD_END_X;
        size++;
    }

    // bottom
    for(int c=GAMEBOARD_START_X; c< GAMEBOARD_END_X; c++){
        wallArray[size][0] = GAMEBOARD_END_Y;
        wallArray[size][1] = c;
        size++;
    }

    // left
    for(int r=GAMEBOARD_START_Y; r< GAMEBOARD_END_Y; r++){
        wallArray[size][0] = r;
        wallArray[size][1] = GAMEBOARD_START_X - 1;
        size++;
    }

    // inner wall
    for(int r=0; r<innerWallSize; r++){
        wallArray[size][0] = innerWall[r][0];
        wallArray[size][1] = innerWall[r][1];
        size++;
    }
}

void GameBoard::drawWall(){
    // top
    Board topWall(1, GAMEBOARD_COLS, GAMEBOARD_START_Y-1, GAMEBOARD_START_X);
    topWall.initialize();
    topWall.setBkgd(COLOR_PAIR(2));
    topWall.addBorder(COLOR_PAIR(2));
    topWall.refresh();

    // right
    Board rightWall(GAMEBOARD_ROWS, 1, GAMEBOARD_START_Y, GAMEBOARD_END_X);
    rightWall.initialize();
    rightWall.setBkgd(COLOR_PAIR(2));
    rightWall.addBorder(COLOR_PAIR(2));
    rightWall.refresh();

    // bottom
    Board bottomWall(1, GAMEBOARD_COLS, GAMEBOARD_END_Y, GAMEBOARD_START_X);
    bottomWall.initialize();
    bottomWall.setBkgd(COLOR_PAIR(2));
    bottomWall.addBorder(COLOR_PAIR(2));
    bottomWall.refresh();

    // left
    Board leftWall(GAMEBOARD_ROWS, 1, GAMEBOARD_START_Y, GAMEBOARD_START_X-1);
    leftWall.initialize();
    leftWall.setBkgd(COLOR_PAIR(2));
    leftWall.addBorder(COLOR_PAIR(2));
    leftWall.refresh();

    // edges
    Board topEdgeL(1, 1, GAMEBOARD_START_Y-1, GAMEBOARD_START_X-1);
    topEdgeL.initialize();
    topEdgeL.setBkgd(COLOR_PAIR(3));
    topEdgeL.addBorder(COLOR_PAIR(3));
    topEdgeL.refresh();

    Board topEdgeR(1, 1, GAMEBOARD_START_Y-1, GAMEBOARD_END_X);
    topEdgeR.initialize();
    topEdgeR.setBkgd(COLOR_PAIR(3));
    topEdgeR.addBorder(COLOR_PAIR(3));
    topEdgeR.refresh();

    Board btmEdgeL(1, 1, GAMEBOARD_END_Y, GAMEBOARD_START_X-1);
    btmEdgeL.initialize();
    btmEdgeL.setBkgd(COLOR_PAIR(3));
    btmEdgeL.addBorder(COLOR_PAIR(3));
    btmEdgeL.refresh();

    Board btmEdgeR(1, 1, GAMEBOARD_END_Y, GAMEBOARD_END_X);
    btmEdgeR.initialize();
    btmEdgeR.setBkgd(COLOR_PAIR(3));
    btmEdgeR.addBorder(COLOR_PAIR(3));
    btmEdgeR.refresh();

    // innerWall
    for(int r=SIDEWALL_SIZE; r<SIDEWALL_SIZE+innerWallSize; r++){
        Board wall(1, 1, wallArray[r][0], wallArray[r][1]);
        wall.initialize();
        wall.setBkgd(COLOR_PAIR(2));
        wall.addBorder(COLOR_PAIR(2));
        wall.refresh();
    }
}
