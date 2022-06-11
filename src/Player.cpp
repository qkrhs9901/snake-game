#include "Player.h"
#include "Settings.h"

Player::Player() {
    current_size = 5;
    max_size = 5;
    growth_count = 0;
    poison_count = 0;
    gate_count = 0;
}

int Player::getCurrentSize() {
    return current_size;
}
void Player::setCurrentSize(const int current_size) {
    this->current_size = current_size;
    Player::setMaxSize(current_size);
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
    int total_score = (max_size * 5) + (growth_count * 5) - (poison_count * 8) + (gate_count * 10) + current_loc;
    return total_score;
}

int Player::getCurrentLoc() {
    return current_loc;
}
void Player::setCurrentLoc(const int current_loc) {
    this->current_loc = current_loc;
}

void Player::setBoard() {

    attron(COLOR_PAIR(1));
    move(SCOREBOARD_POS_Y+1, SCOREBOARD_POS_X+1);
    printw("--------CURRENT SCORE--------");
    move(SCOREBOARD_POS_Y+3, SCOREBOARD_POS_X+2);
    printw("Score : %d", Player::getScore());
    move(SCOREBOARD_POS_Y+4, SCOREBOARD_POS_X+2);
    printw("B     : %d / %d", current_size, max_size);
    move(SCOREBOARD_POS_Y+5, SCOREBOARD_POS_X+2);
    printw("+     : %d", growth_count);
    move(SCOREBOARD_POS_Y+6, SCOREBOARD_POS_X+2);
    printw("-     : %d", poison_count);
    move(SCOREBOARD_POS_Y+7, SCOREBOARD_POS_X+2);
    printw("G     : %d", gate_count);
    refresh();
    attroff(COLOR_PAIR(1));
}