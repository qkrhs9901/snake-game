#include "innerWall.h"

innerWall::innerWall(){
    wall_array = new int *[WALL_MAX_SIZE];
    for(int i=0; i<WALL_MAX_SIZE; i++) wall_array[i] = new int[2];
}

innerWall::~innerWall(){
    for(int i=0; i<WALL_MAX_SIZE; i++) delete[] wall_array[i];
    delete[] wall_array;
}

void innerWall::addRowWall(int sz, int y, int start_x){
    for(int x = start_x; x<start_x+sz; x++){
        wall_array[idx][0] = y;
        wall_array[idx][1] = x;
        idx++;
    }
}

void innerWall::addColWall(int sz, int start_y, int x){
    for(int y = start_y; y < start_y+sz; y++){
        wall_array[idx][0] = y;
        wall_array[idx][1] = x;
        idx++;
    }
}





