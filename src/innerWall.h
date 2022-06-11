#ifndef __INNERWALL__
#define __INNERWALL__

#include <iostream>
#include "Settings.h"
using namespace std;

#define WALL_MAX_SIZE (GAMEBOARD_COLS * GAMEBOARD_ROWS) / 2 // wall을 추가할 수 있는 최대 sz는 총 픽셀의 절반

class innerWall{
    int** wall_array;
    int idx = 0;
public:
    innerWall();
    ~innerWall();

    void addRowWall(int sz, int y, int start_x); // 가로벽 추가
    void addColWall(int sz, int start_y, int x); // 세로벽 추가
    int** getWallArray() {return wall_array;}
    int getCurrentWallSize() {return idx;} // wall_array의 max size가 아닌 현재 wall의 갯수를 return
    
};

#endif


