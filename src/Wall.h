#ifndef __INNERWALL__
#define __INNERWALL__

#include <iostream>
#include "Settings.h"
using namespace std;

#define INNERWALL_MAX_SIZE (GAMEBOARD_COLS * GAMEBOARD_ROWS) / 2 // wall을 추가할 수 있는 최대 sz는 총 픽셀의 절반
#define STUCKWALL_MAX_SIZE (GAMEBOARD_COLS + GAMEBOARD_ROWS) / 2

class Wall{
    int **sideWallArray;
    int **innerWallArray;
    int **stuckWallArray; // sideWall 중 innerWall에 가려져 3면이 막혀 있는 wall(gate가 되지 못하는 wall)
    int innerWallSize;
    int stuckWallSize;
public:
    Wall();
    ~Wall();

    void addRowWall(int sz, int y, int start_x); // 가로벽 추가
    void addColWall(int sz, int start_y, int x); // 세로벽 추가

    void drawSideWall();
    void drawInnerWall(int a);
    void eraseInnerWall();
    
    int** getSideWallArray() {return sideWallArray;}
    int** getInnerWallArray() {return innerWallArray;}
    int** getStuckWallArray() {return stuckWallArray;}
    int getInnerWallSize() {return innerWallSize;}
    int getStuckWallSize() {return stuckWallSize;}

    
};
 
#endif



