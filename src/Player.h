#ifndef __PLAYER__
#define __PLAYER__
#include <ncurses.h>
#include <iostream>

class Player {
    int current_size;
    int max_size;
    int growth_count;
    int poison_count;
    int gate_count;
    int current_loc;
public:
    Player();
    int getCurrentSize();
    void setCurrentSize(const int current_size);
    int getMaxSize();
    void setMaxSize(const int current_size);
    int getGrowthCount();
    void setGrowthCount(const int growth_count);
    int getPoisonCount();
    void setPoisonCount(const int poison_count);
    void growthIncrease();
    void poisonIncrease();
    int getGateCount();
    void setGateCount(const int gate_count);
    void gateCountIncrease();
    int getScore();
    int getCurrentLoc();
    void setCurrentLoc(const int current_loc);
    void locIncrease();
    void setBoard();
    char checkSize();
    char checkGrowth();
    char checkPoison();
    char checkGate();
    void reset();
};
 
#endif
