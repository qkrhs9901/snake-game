#include "Wall.h"
#include "Board.h"
#include <ncurses.h>

Wall::Wall(){
    // sideWall
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

    // innerWall
    innerWallSize = 0;
    innerWallArray = new int *[INNERWALL_MAX_SIZE];
    for(int i=0; i<INNERWALL_MAX_SIZE; i++) innerWallArray[i] = new int[2];

    // stuckWall
    stuckWallSize = 0;
    stuckWallArray = new int *[STUCKWALL_MAX_SIZE];
    for(int i=0; i<STUCKWALL_MAX_SIZE; i++) stuckWallArray[i] = new int[2];

}

Wall::~Wall(){

    for(int i=0; i<SIDEWALL_SIZE; i++) delete[] sideWallArray[i];
    delete[] sideWallArray;

    for(int r=0; r<INNERWALL_MAX_SIZE; r++) delete[] innerWallArray[r];
    delete[] innerWallArray;

    for(int i=0; i<STUCKWALL_MAX_SIZE; i++) delete[] stuckWallArray[i];
    delete[] stuckWallArray;
}

void Wall::addRowWall(int y, int start_x, int end_x){

    if(start_x > end_x){ // 오른쪽에서 왼쪽으로 wall을 추가하려는 경우
        int tmp = end_x;
        end_x = start_x; 
        start_x = tmp;
    }

    if(start_x == GAMEBOARD_START_X){
        stuckWallArray[stuckWallSize][0] = y;
        stuckWallArray[stuckWallSize][1] = start_x - 1;
        stuckWallSize++;
    }
    if(end_x == GAMEBOARD_END_X){
        stuckWallArray[stuckWallSize][0] = y;
        stuckWallArray[stuckWallSize][1] = end_x;
        stuckWallSize++;
    }

    for(int x = start_x; x<end_x; x++){
        innerWallArray[innerWallSize][0] = y;
        innerWallArray[innerWallSize][1] = x;
        innerWallSize++;
    }
}

void Wall::addColWall(int start_y, int end_y, int x){

    if(start_y > end_y){ // 아래에서 위로 wall을 추가하려는 경우
        int tmp = end_y;
        end_y = start_y; 
        start_y = tmp;
    }

    if(start_y == GAMEBOARD_START_Y){
        stuckWallArray[stuckWallSize][0] = start_y - 1;
        stuckWallArray[stuckWallSize][1] = x;
        stuckWallSize++;
    }
    if(end_y == GAMEBOARD_END_Y){
        stuckWallArray[stuckWallSize][0] = end_y;
        stuckWallArray[stuckWallSize][1] = x;
        stuckWallSize++;
    }

    for(int y = start_y; y < end_y; y++){
        innerWallArray[innerWallSize][0] = y;
        innerWallArray[innerWallSize][1] = x;
        innerWallSize++;
    }
}

void Wall::drawSideWall(){

    // top
    attron(COLOR_PAIR(BLUE));
    for(int x=GAMEBOARD_START_X; x<GAMEBOARD_END_X; x++){
        move(GAMEBOARD_START_Y-1, x);
        addch(' ');
    }

    // right
    for(int y=GAMEBOARD_START_Y; y<GAMEBOARD_END_Y; y++){
        move(y, GAMEBOARD_END_X);
        addch(' ');
    }

    // bottom
    for(int x=GAMEBOARD_START_X; x<GAMEBOARD_END_X; x++){
        move(GAMEBOARD_END_Y, x);
        addch(' ');
    }

    // left
    for(int y=GAMEBOARD_START_Y; y<GAMEBOARD_END_Y; y++){
        move(y, GAMEBOARD_START_X-1);
        addch(' ');
    }

    refresh();
    attroff(COLOR_PAIR(BLUE));

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

void Wall::drawInnerWall(){
    attron(COLOR_PAIR(BLUE));
    for(int r=0; r<innerWallSize; r++){
        move(innerWallArray[r][0], innerWallArray[r][1]);
        addch(' ');
    }
    attroff(COLOR_PAIR(BLUE));
    refresh();
}

void Wall::eraseInnerWall(){
    attron(COLOR_PAIR(WHITE));
    for(int r=0; r<innerWallSize; r++) {
        move(innerWallArray[r][0], innerWallArray[r][1]);
        addch(' ');
    }
    attroff(COLOR_PAIR(WHITE));
    refresh();
    innerWallSize = 0;
    stuckWallSize = 0;
}




