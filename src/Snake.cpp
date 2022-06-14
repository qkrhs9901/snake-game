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
    snakeLen = 5;
    for (int i = 0; i < snakeLen; i++) {
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

void Snake::setStuckWall(int sz, int** stuckWallArray){
    stuckWallSize = sz;
    this->stuckWallArray = stuckWallArray;
}

void Snake::setGate(){
    // sideWall 혹은 innerWall에서 첫 번째 gate가 될 wall의 idx를 랜덤 추출
    int idx_1; 

    // idx_1이 sideWall일 때 stuckWall이 아닌 wall이 나올 때까지 반복
    //(바로 근처에 innerWall이 막고 있어서 snake가 통과할 수 없는 상태가 아닐 때까지)
    while(true){
        idx_1 = rand() % (SIDEWALL_SIZE + innerWallSize); 

        if(idx_1 < SIDEWALL_SIZE){ // idx_1이 sideWall이라면 stuckWall인지 검사
            int i;
            for(i=0; i<stuckWallSize; i++){
                if(sideWallArray[idx_1][0] == stuckWallArray[i][0] && sideWallArray[idx_1][1] == stuckWallArray[i][1])
                    break;
            }
            if(i == stuckWallSize) break; // idx_1이 stuckWall이 아니면 탈출
        }
        else break; // idx_1이 sideWall이 아니면 탈출
    }

    int idx_2;
    while(true){
        idx_2 = rand() % (SIDEWALL_SIZE + innerWallSize); 
        if(abs(idx_2 - idx_1) < 10) continue; // idx_1과 10칸 이상 떨어져 있어야 통과

        if(idx_2 < SIDEWALL_SIZE){
            int i;
            for(i=0; i<stuckWallSize; i++){
                if(sideWallArray[idx_2][0] == stuckWallArray[i][0] && sideWallArray[idx_2][1] == stuckWallArray[i][1])
                    break;
            }
            if(i == stuckWallSize) break; // idx_1이 stuckWall이 아니면 탈출
        }
        else break; // idx_1이 sideWall이 아니면 탈출
    }

    // first gate
    int x_1, y_1;
    if(idx_1 >= SIDEWALL_SIZE) { // gate가 innerWall에 있을 때
        y_1 = innerWallArray[idx_1 - SIDEWALL_SIZE][0];
        x_1 = innerWallArray[idx_1 - SIDEWALL_SIZE][1];
        gateArray[0][2] = 1;
    }
    else{ // gate가 sideWall에 있을 때
        y_1 = sideWallArray[idx_1][0];
        x_1 = sideWallArray[idx_1][1];
        gateArray[0][2] = 0;
    }
    gateArray[0][0] = y_1; gateArray[0][1] = x_1;

    // draw first gate
    attron(COLOR_PAIR(MAGENTA));
    move(gateArray[0][0], gateArray[0][1]);
    addch(' ');

    // second gate
    int x_2, y_2;
    if(idx_2 >= SIDEWALL_SIZE) {
        y_2 = innerWallArray[idx_2 - SIDEWALL_SIZE][0];
        x_2 = innerWallArray[idx_2 - SIDEWALL_SIZE][1];
        gateArray[1][2] = 1;
    }
    else{
        y_2 = sideWallArray[idx_2][0];
        x_2 = sideWallArray[idx_2][1];
        gateArray[1][2] = 0;
    }
    gateArray[1][0] = y_2; gateArray[1][1] = x_2;

    // draw second gate
    move(gateArray[1][0], gateArray[1][1]);
    addch(' ');
    attroff(COLOR_PAIR(MAGENTA));

}

void Snake::enterGate(int inGateIdx){
    int outGateIdx = -inGateIdx + 1; // inGate가 1이면 0, 0이면 1(gateArray의 idx이다)
    int *inGate = gateArray[inGateIdx];
    int *outGate = gateArray[outGateIdx];

    if(outGate[2] == 0){ // outGate가 sideWall에 있다면
        if(outGate[0] == GAMEBOARD_START_Y - 1){ // topWall
            direction = 'd';
        }
        else if(outGate[1] == GAMEBOARD_END_X){ // rightWall
            direction = 'l';
        }
        else if(outGate[0] == GAMEBOARD_END_Y){ // bottomWall
            direction = 'u';
        }
        else{ // leftWall
            direction = 'r';
        }
    }   

    moveHeadOutGate(outGate); // head의 위치를 outGate로 옮김
    usleep(del);

    for(int i=0; i<snakeLen-1; i++){ // snakeLen - 1만큼 move
        moveSnake();
        usleep(del);
    }
    
    moveSnake();

    // inGate 제거
    Board gate_in(1, 1, inGate[0], inGate[1]);
    gate_in.initialize();
    gate_in.setBkgd(COLOR_PAIR(BLUE));
    gate_in.addBorder(COLOR_PAIR(BLUE));
    gate_in.refresh();

     // outGate 제거
    Board gate_out(1, 1, outGate[0], outGate[1]);
    gate_out.initialize();
    gate_out.setBkgd(COLOR_PAIR(BLUE));
    gate_out.addBorder(COLOR_PAIR(BLUE));
    gate_out.refresh();

    setGate();
}

void Snake::moveHeadOutGate(int* outGate) {

    if (!get) {
        attron(COLOR_PAIR(WHITE));
        move(snake[snake.size()-1].y, snake[snake.size()-1].x);
        addch(' ');
        attroff(COLOR_PAIR(WHITE));
        refresh();
        snake.pop_back();
    }
    
    snake.insert(snake.begin(), Snakepart(outGate[1], outGate[0]));


    // draw head
    attron(COLOR_PAIR(RED));
    move(snake[0].y, snake[0].x);
    addch(snakepart);
    attroff(COLOR_PAIR(RED));

    // draw first body (just beside head)
    attron(COLOR_PAIR(GREEN));
    move(snake[1].y, snake[1].x);
    addch(snakepart);
    refresh();
    attroff(COLOR_PAIR(GREEN));
}

bool Snake::collision() {
    if ((snake[0].x == GAMEBOARD_START_X-1 || snake[0].x == GAMEBOARD_END_X) || (snake[0].y == GAMEBOARD_START_Y -1 || snake[0].y == GAMEBOARD_END_Y)) {
        if(snake[0].x == gateArray[0][1] && snake[0].y == gateArray[0][0]){
            enterGate(0);
            return false;
        }
        else if(snake[0].x == gateArray[1][1] && snake[0].y == gateArray[1][0]){
            enterGate(1);
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
        
    }
    return false;
}

void Snake::setDirection(int key){
    // user input
    switch(key) {
        case RIGHT_KEY:
            if (direction != 'l') {
                direction = 'r';
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
            if (direction != 'r') {
                direction = 'l';
            }
            break;
        case KEY_BACKSPACE:
            direction= 'q';
            break;
    }

    moveSnake();
}

void Snake::moveSnake() {

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


    // draw head
    attron(COLOR_PAIR(RED));
    move(snake[0].y, snake[0].x);
    addch(snakepart);
    attroff(COLOR_PAIR(RED));

    // draw first body (just beside head)
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
        setDirection(tmp);
        if (direction == 'q') {
            break;
        }
        usleep(del);
    }
}