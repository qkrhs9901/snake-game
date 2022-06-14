#include <cstdlib>
#include <unistd.h>     
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Snake.h"
#include "Settings.h"

Snakepart::Snakepart(int col, int row) {
    x = col;
    y = row;
}
Snakepart::Snakepart() {
    x = 0;
    y = 0;
}

Snake::Snake(int** sideWallArray) : sideWallArray(sideWallArray){
    srand(time(NULL));

    direction = 'l';
    snakepart=' ';
    del = 110000;
    get = false;
    for (int i = 0; i < 5; i++) {
        snake.push_back(Snakepart(40+i, 10));
    }

    // head
    attron(COLOR_PAIR(RED));
    move(snake[0].y, snake[0].x);
    addch(snakepart);
    attroff(COLOR_PAIR(RED));

    // body
    attron(COLOR_PAIR(GREEN));
    for (int i = 1; i <  snake.size(); i++) {
        move(snake[i].y, snake[i].x);
        addch(snakepart);
    } 
    refresh();
    attroff(COLOR_PAIR(GREEN));
}
Snake::~Snake() {}

void Snake::setInnerWall(int sz, int** innerWallArray){
    innerWallSize = sz;
    this->innerWallArray = innerWallArray;
}

void Snake::setGate(){
    // sideWall 혹은 innerWall에서 첫 번째 gate가 될 wall의 idx를 랜덤 추출
    int idx_1 = rand() % (SIDEWALL_SIZE + innerWallSize); 
    int idx_2;
    while(true){
        idx_2 = rand() % (SIDEWALL_SIZE + innerWallSize);
        if(idx_2 > idx_1 + 10 || idx_2 < idx_1 - 10) break;
    }

    // first gate
    int x_1, y_1;
    if(idx_1 >= SIDEWALL_SIZE) {
        y_1 = innerWallArray[idx_1 - SIDEWALL_SIZE][0];
        x_1 = innerWallArray[idx_1 - SIDEWALL_SIZE][1];
    }
    else{
        y_1 = sideWallArray[idx_1][0];
        x_1 = sideWallArray[idx_1][1];
    }
    gateArray[0][0] = y_1; gateArray[0][1] = x_1;

    // draw first gate
    Board gate_1(1, 1, gateArray[0][0], gateArray[0][1]);
    gate_1.initialize();
    gate_1.setBkgd(COLOR_PAIR(MAGENTA));
    gate_1.addBorder(COLOR_PAIR(MAGENTA));
    gate_1.refresh();

    // second gate
    int x_2, y_2;
    if(idx_2 >= SIDEWALL_SIZE) {
        y_2 = innerWallArray[idx_2 - SIDEWALL_SIZE][0];
        x_2 = innerWallArray[idx_2 - SIDEWALL_SIZE][1];
    }
    else{
        y_2 = sideWallArray[idx_2][0];
        x_2 = sideWallArray[idx_2][1];
    }
    gateArray[1][0] = y_2; gateArray[1][1] = x_2;

    // draw second gate
    Board gate_2(1, 1, gateArray[1][0], gateArray[1][1]);
    gate_2.initialize();
    gate_2.setBkgd(COLOR_PAIR(MAGENTA));
    gate_2.addBorder(COLOR_PAIR(MAGENTA));
    gate_2.refresh();

    // move(gateArray[1][0], gateArray[1][1]);
    // addch(' ');
    // attroff(COLOR_PAIR(MAGENTA));

}

void Snake::enterGate(int inGate){
    int outGate = -inGate + 1; // inGate가 1이면 0, 0이면 1(gateArray의 idx이다)


}
bool Snake::collision() {
    if ((snake[0].x == GAMEBOARD_START_X-1 || snake[0].x == GAMEBOARD_END_X+1) || (snake[0].y == GAMEBOARD_START_Y -1 || snake[0].y == GAMEBOARD_END_Y)) {
        if(snake[0].x == gateArray[0][1] && snake[0].y == gateArray[0][0]){
            return false;
        }
        else if(snake[0].x == gateArray[1][1] && snake[0].y == gateArray[1][0]){
            return false;
        }
        return true;
    }

    for(int i=0; i<innerWallSize; i++){
        if(snake[0].x == innerWallArray[i][1] && snake[0].y == innerWallArray[i][0]){
            if(snake[0].x == gateArray[0][1] && snake[0].y == gateArray[0][0]){
                return false;
            }
            else if(snake[0].x == gateArray[1][1] && snake[0].y == gateArray[1][0]){
                return false;
            }
            return true;
        }
    }

    for (int i = 2; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }
    return false;
}

void Snake::movesnake(int key) {

    // user input
    switch(key) {
        case RIGHT_KEY:
            if (direction != 'r') {
                direction = 'l';
            }
            break;
        case UP_KEY: 
            if (direction != 'd') {
                direction = 'u';
            }
            break;
        case DOWN_KEY:
            if (direction != 'u') {
                direction = 'd';
            }
            break;
        case LEFT_KEY:
            if (direction != 'l') {
                direction = 'r';
            }
            break;
        case KEY_BACKSPACE:
            direction= 'q';
            break;
    }

    if (!get) {
        attron(COLOR_PAIR(WHITE));
        move(snake[snake.size()-1].y, snake[snake.size()-1].x);
        addch(' ');
        attroff(COLOR_PAIR(WHITE));
        refresh();
        snake.pop_back();
    }
    
    if (direction == 'l') {
        snake.insert(snake.begin(), Snakepart(snake[0].x-1, snake[0].y));
    } else if (direction == 'r') {
        snake.insert(snake.begin(), Snakepart(snake[0].x+1, snake[0].y));
    } else if (direction == 'u') {
        snake.insert(snake.begin(), Snakepart(snake[0].x, snake[0].y-1));
    } else if (direction == 'd') {
        snake.insert(snake.begin(), Snakepart(snake[0].x, snake[0].y+1));
    }


    attron(COLOR_PAIR(RED));
    move(snake[0].y, snake[0].x);
    addch(snakepart);
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(GREEN));
    move(snake[1].y, snake[1].x);
    addch(snakepart);
    refresh();
    attroff(COLOR_PAIR(GREEN));
}

void Snake::start() {
    while (1) {
        if (collision()) {
            break;
        }
        int tmp = getch();
        movesnake(tmp);
        if (direction == 'q') {
            break;
        }
        usleep(del);
    }
}