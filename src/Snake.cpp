#include <cstdlib>
#include <unistd.h>     
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Snake.h"
#include "Settings.h"
#include "Player.h"

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
    bad = false;
    snakeLen = 5;

    play = new Player();
    play->setGrowthCount(0);
    play->setGateCount(0);
    play->setPoisonCount(0);
    play->setMaxSize(50);
    play->setCurrentLoc(1);
    play->setBoard();

    for (int i = 0; i < snakeLen; i++) {
        snake.push_back(Snakepart(40+i, 10));
    }

    goodF = 'G';
    badF = 'P';
    food.x = 0;
    food.y = 0;
    poison.x = 0;
    poison.y = 0;
    srand(time(0));
    putfood();
    putpoison();

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
            if(i == stuckWallSize) break; 
        }
        else break;
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

    // draw first gate
    attron(COLOR_PAIR(MAGENTA));
    move(gateArray[0][0], gateArray[0][1]);
    addch(' ');

    // draw second gate
    move(gateArray[1][0], gateArray[1][1]);
    addch(' ');
    attroff(COLOR_PAIR(MAGENTA));

}

void Snake::enterGate(int inGateIdx){
    int outGateIdx = -inGateIdx + 1; // inGate가 1이면 0, 0이면 1(gateArray의 idx이다)
    int *inGate = gateArray[inGateIdx];
    int *outGate = gateArray[outGateIdx];

    // outGate가 sideWall에 있다면
    if(outGate[2] == 0){ 
        if(outGate[0] == GAMEBOARD_START_Y - 1){ // upWall
            direction = 'd';
        }
        else if(outGate[1] == GAMEBOARD_END_X){ // rightWall
            direction = 'l';
        }
        else if(outGate[0] == GAMEBOARD_END_Y){ // downWall
            direction = 'u';
        }
        else{ // leftWall
            direction = 'r';
        }
    }   
    // outGate가 innerWall에 있다면
    else{ 
        int checkDirection[4] = {0,0,0,0}; 
        // <val> 0: 열려있음 | 1: 막혀있음 
        // <idx> 0: top / 1: right / 2: bottom / 3: left

        // 만약 gate가 sideWall과 붙어있으면 막혀있는 부분이 생김
        if(outGate[0] == GAMEBOARD_START_Y) checkDirection[0] = 1;
        else if(outGate[0] == GAMEBOARD_END_Y) checkDirection[2] = 1;
        if(outGate[1] == GAMEBOARD_START_X) checkDirection[3] = 1;
        else if(outGate[1] == GAMEBOARD_END_X - 1) checkDirection[1] = 1;

        // innerWallArray를 순회하며 gate를 막고 있는 방향 체크
        for(int i=0; i<innerWallSize; i++){
            int y = innerWallArray[i][0];
            int x = innerWallArray[i][1];

            if(y == outGate[0] - 1 && x == outGate[1]) checkDirection[0] = 1; // up
            else if(y == outGate[0] && x == outGate[1] + 1) checkDirection[1] = 1; // right
            else if(y == outGate[0] + 1 && x == outGate[1]) checkDirection[2] = 1; // down
            else if(y == outGate[0] && x == outGate[1] - 1) checkDirection[3] = 1; // left
        }
        
        // setDirectionInnerGate에서 막혀 있는 방향을 파악하여 진행방향 변경 혹은 유지
        switch (direction)
        {
        case 'u': // inGate에 up 방향으로 들어왔을 때
            setDirectionInnerGate(0, checkDirection); 
            break;
        case 'r': // inGate에 right 방향으로 들어왔을 때
            setDirectionInnerGate(1, checkDirection);
            break;
        case 'd': // inGate에 down 방향으로 들어왔을 때
            setDirectionInnerGate(2, checkDirection);
            break;
        case 'l': // inGate에 left 방향으로 들어왔을 때
            setDirectionInnerGate(1, checkDirection);
            break;
        
        default:
            break;
        }
    }

    // head의 위치를 outGate로 이동
    moveHeadOutGate(outGate); 

    // body가 gate 통과
    for(int i=0; i<snakeLen; i++){
        usleep(del);
        moveSnake();
    }

    // inGate 제거
    attron(COLOR_PAIR(BLUE));
    move(inGate[0], inGate[1]);
    addch(' ');

     // outGate 제거
    move(outGate[0], outGate[1]);
    addch(' ');
    attroff(COLOR_PAIR(BLUE));

    // new gate 생성
    setGate();
}

void Snake::setDirectionInnerGate(int currDirection, int* checkDirection){  
    int newDirection;

    if(checkDirection[currDirection] != 0) {// 현재 진행방향이 닫혀 있는 상태라면
        for(int i=0; i<4; i++){ // 나머지 방향에서 열려 있는 방향을 찾음
            if(i == currDirection) continue;
            if(checkDirection[i] == 0){
                newDirection = i;
                break;
            }
        }
    }
    else newDirection = currDirection;

    switch (newDirection)
    {
    case 0:
        direction = 'u';
        break;
    case 1:
        direction = 'r';
        break;
    case 2:
        direction = 'd';
        break;
    case 3:
        direction = 'l';
        break;
    }
}

void Snake::moveHeadOutGate(int* outGate) {
    play->gateCountIncrease();
    play->setBoard();

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

void Snake::putfood() {
    attron(COLOR_PAIR(WHITE));
    while (1) {
        int tmpx1 = rand() % GAMEBOARD_END_X + 1;          // food
        int tmpy1 = rand() % GAMEBOARD_END_Y + 1;
        for (int i = 0; i < snake.size(); i++) {
            if (snake[i].x == tmpx1 && snake[i].y == tmpy1) {
                continue;
            }
        }
        for(int i=0; i<innerWallSize; i++){
            if(snake[0].x == innerWallArray[i][1] && snake[0].y == innerWallArray[i][0]) {
                continue;
            }
        }
        if (tmpx1 >= GAMEBOARD_END_X-1 || tmpx1 <= GAMEBOARD_START_X || tmpy1 >= GAMEBOARD_END_Y-1 || tmpy1 <= GAMEBOARD_START_Y) {
            continue;
        }
        food.x = tmpx1;     // food
        food.y = tmpy1;
        break;
    }
    move(food.y, food.x);
    addch(goodF);
    attroff(COLOR_PAIR(WHITE));
    refresh();
}

void Snake::putpoison() {
    attron(COLOR_PAIR(WHITE));
    while (1) {
        int tmpx2 = rand() % GAMEBOARD_END_X + 1;          // poison
        int tmpy2 = rand() % GAMEBOARD_END_Y + 1;
        for (int i = 0; i < snake.size(); i++) {
            if (snake[i].x == tmpx2 && snake[i].y == tmpy2) {
                continue;
            }
        }
        for(int i=0; i<innerWallSize; i++){
            if(snake[0].x == innerWallArray[i][1] && snake[0].y == innerWallArray[i][0]) {
                continue;
            }
        }
        if (tmpx2 >= GAMEBOARD_END_X-1 || tmpx2 <= GAMEBOARD_START_X || tmpy2 >= GAMEBOARD_END_Y-1 || tmpy2 <= GAMEBOARD_START_Y) {
            continue;
        }
        poison.x = tmpx2;   // poison
        poison.y = tmpy2;
        break;
    }
    move(poison.y, poison.x);
    addch(badF);
    attroff(COLOR_PAIR(WHITE));
    refresh();
}

bool Snake::collision() {
    // head가 gate에 진입
    if(snake[0].x == gateArray[0][1] && snake[0].y == gateArray[0][0]){ // inGate가 0일 때
        enterGate(0);
        return false;
    }
    else if(snake[0].x == gateArray[1][1] && snake[0].y == gateArray[1][0]){ // inGate가 1일 때
        enterGate(1);
        return false;
    }

    // head가 sideWall과 충돌
    if ((snake[0].x == GAMEBOARD_START_X-1 || snake[0].x == GAMEBOARD_END_X) || (snake[0].y == GAMEBOARD_START_Y -1 || snake[0].y == GAMEBOARD_END_Y))
        return true;
    
    // head가 innerWall과 충돌
    for(int i=0; i<innerWallSize; i++){
        if(snake[0].x == innerWallArray[i][1] && snake[0].y == innerWallArray[i][0])
            return true;
    }

    // head가 body와 충돌
    for (int i = 2; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }

    if (snake[0].x == food.x && snake[0].y == food.y) {
        get = true;
        play->growthIncrease();
        play->setCurrentSize(snake.size()+1);
        play->setBoard();
        putfood();
        move(GAMEBOARD_END_Y-1, 0);
        if (play->getScore()%100 == 0) {
            del -= 10000;
        }

    } else {
        get = false;
    }

    if (snake[0].x == poison.x && snake[0].y == poison.y) {
        bad = true;
        play->poisonIncrease();
        play->setCurrentSize(snake.size()-1);
        play->setBoard();
        putpoison();
        move(GAMEBOARD_END_Y-1, 0);
        if (play->getScore()%100 == 0) {
            del -= 10000;
        }
    } else {
        bad = false;
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
    play->setCurrentSize(snake.size());
    play->setBoard();

    if (!get) {
        attron(COLOR_PAIR(WHITE));
        move(snake[snake.size()-1].y, snake[snake.size()-1].x);
        addch(' ');
        attroff(COLOR_PAIR(WHITE));
        refresh();
        snake.pop_back();
    }

    if (bad) {
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
        if (collision() || snake.size() == 3) {
            play->setCurrentSize(snake.size());
            play->setBoard();
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