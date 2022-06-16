#include "Player.h"
#include "Settings.h"

Player::Player() {
    current_size = 5;
    max_size = 5;
    growth_count = 0;
    poison_count = 0;
    gate_count = 0;
    check_s = false;
    check_gr = false; 
    check_p = false; 
    check_ga = false;
}

int Player::getCurrentSize() {
    return current_size;
}
void Player::setCurrentSize(const int current_size) {
    this->current_size = current_size;
}

int Player::getMaxSize() {
    return max_size;
}
void Player::setMaxSize(const int current_size) {
    if (current_size > max_size) { max_size = current_size; }
}

int Player::getGrowthCount() {
    return growth_count;
}
void Player::setGrowthCount(const int growth_count) {
    this->growth_count = growth_count;
}

int Player::getPoisonCount() {
    return poison_count;
}
void Player::setPoisonCount(const int poison_count) {
    this->poison_count = poison_count;
}

void Player::growthIncrease() {
    this->growth_count = growth_count;
    growth_count++;
}

void Player::poisonIncrease() {
    this->poison_count = poison_count;
    poison_count++;
}

int Player::getGateCount() {
    return gate_count;
}
void Player::setGateCount(const int gate_count) {
    this->gate_count = gate_count;
}

void Player::gateCountIncrease() {
    this->gate_count = gate_count;
    gate_count++;
}

int Player::getScore() {
    int total_score = (growth_count * 8) - (poison_count * 4) + (gate_count * 15) + (current_loc * 10);
    return total_score;
}

int Player::getCurrentLoc() {
    return current_loc;
}
void Player::setCurrentLoc(const int current_loc) {
    this->current_loc = current_loc;
}

char Player::checkSize() {
    if (Player::getCurrentSize() >= 10) { return 'V'; }
    else { return ' ';}
}
char Player::checkGrowth() {
    if (Player::getGrowthCount() >= 5) { return 'V'; }
    else { return ' ';}
}
char Player::checkPoison() {
    if (Player::getPoisonCount() >= 2) { return 'V'; }
    else { return ' ';}
}
char Player::checkGate() {
    if (Player::getGateCount() >= 1) { return 'V'; }
    else { return ' ';}
}

void Player::setBoard() {

    attron(COLOR_PAIR(WHITE));
    move(SCOREBOARD_POS_Y+1, SCOREBOARD_POS_X+1);
    printw("--------CURRENT SCORE-------");
    move(SCOREBOARD_POS_Y+3, SCOREBOARD_POS_X+2);
    printw("Score : %5d", Player::getScore());
    move(SCOREBOARD_POS_Y+4, SCOREBOARD_POS_X+2);
    printw("B     : %5d / %3d", current_size, max_size);
    move(SCOREBOARD_POS_Y+5, SCOREBOARD_POS_X+2);
    printw("+     : %5d", growth_count);
    move(SCOREBOARD_POS_Y+6, SCOREBOARD_POS_X+2);
    printw("-     : %5d", poison_count);
    move(SCOREBOARD_POS_Y+7, SCOREBOARD_POS_X+2);
    printw("G     : %5d", gate_count);

    move(MISSIONBOARD_POS_Y+1, MISSIONBOARD_POS_X+1);
    printw("-----------MISSION----------");
    move(MISSIONBOARD_POS_Y+3, MISSIONBOARD_POS_X+2);
    printw("B     : %5d   ( %c )", 10, Player::checkSize());
    move(MISSIONBOARD_POS_Y+4, MISSIONBOARD_POS_X+2);
    printw("+     : %5d   ( %c )", 5, Player::checkGrowth());
    move(MISSIONBOARD_POS_Y+5, MISSIONBOARD_POS_X+2);
    printw("-     : %5d   ( %c )", 2, Player::checkPoison());
    move(MISSIONBOARD_POS_Y+6, MISSIONBOARD_POS_X+2);
    printw("G     : %5d   ( %c )", 1, Player::checkGate());
    move(MISSIONBOARD_POS_Y+8, MISSIONBOARD_POS_X+2);
    printw("Stage : %5d", current_loc);

    refresh();
    attroff(COLOR_PAIR(WHITE));
}
