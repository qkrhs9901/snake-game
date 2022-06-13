#include "innerWall.h"
#include <ncurses.h>

innerWall::innerWall(){
    currSize = 0;
    innerWallArray = new int *[INNERWALL_MAX_SIZE];
    for(int i=0; i<INNERWALL_MAX_SIZE; i++) innerWallArray[i] = new int[2];
}

innerWall::~innerWall(){

    for(int r=0; r<INNERWALL_MAX_SIZE; r++) delete[] innerWallArray[r];
    delete[] innerWallArray;
}

void innerWall::addRowWall(int sz, int y, int start_x){
    for(int x = start_x; x<start_x+sz; x++){
        innerWallArray[currSize][0] = y;
        innerWallArray[currSize][1] = x;
        currSize++;
    }
}

void innerWall::addColWall(int sz, int start_y, int x){
    for(int y = start_y; y < start_y+sz; y++){
        innerWallArray[currSize][0] = y;
        innerWallArray[currSize][1] = x;
        currSize++;
    }
}

void innerWall::drawWall(){
    attron(COLOR_PAIR(BLUE));
    for(int r=0; r<currSize; r++){
        move(innerWallArray[r][0], innerWallArray[r][1]);
        addch(' ');
    }
    attroff(COLOR_PAIR(BLUE));
    refresh();
}

void innerWall::eraseWall(){
    attron(COLOR_PAIR(WHITE));
    for(int r=0; r<currSize; r++) {
        move(innerWallArray[r][0], innerWallArray[r][1]);
        addch(' ');
    }
    attroff(COLOR_PAIR(WHITE));
    refresh();
    currSize = 0;
}




