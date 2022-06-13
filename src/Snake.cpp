#include <cstdlib>
#include <unistd.h>     
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

Snake::Snake() {
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
}
Snake::~Snake() {
    attroff(COLOR_PAIR(GREEN));         // reset color to terminal
}
bool Snake::collision() {
    if ((snake[0].x == GAMEBOARD_START_X-1 || snake[0].x == GAMEBOARD_END_X+1) || (snake[0].y == GAMEBOARD_START_Y -1 || snake[0].y == GAMEBOARD_END_Y)) {
        return true;
    }
    for (int i = 2; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }
    return false;
}
void Snake::movesnake() {
    int tmp = getch();

    // user input
    switch(tmp) {
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
        attroff(COLOR_PAIR(GREEN));
        attron(COLOR_PAIR(WHITE));
        move(snake[snake.size()-1].y, snake[snake.size()-1].x);
        addch(' ');
        attroff(COLOR_PAIR(WHITE));
        refresh();
        snake.pop_back();
    }

    if(get) {attroff(COLOR_PAIR(GREEN));}
    
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
}
void Snake::start() {
    while (1) {
        if (collision()) {
            attroff(COLOR_PAIR(GREEN));     // reset color to terminal
            break;
        }
        movesnake();
        if (direction == 'q') {
            attroff(COLOR_PAIR(GREEN));     // reset color to terminal
            break;
        }
        usleep(del);
    }
}