#ifndef __SETTINGS__
#define __SETTINGS__

// 게임을 위한 모든 상수 저장

// keyboard inputs
#define UP_KEY 'w' | 'W'        // W
#define DOWN_KEY 's' | 'S'      // S
#define LEFT_KEY 'a' | 'A'     // A
#define RIGHT_KEY 'd' | 'D'      // D

// board size
#define GAMEBOARD_DIM 22
#define GAMEBOARD_ROWS (GAMEBOARD_DIM)
#define GAMEBOARD_COLS (GAMEBOARD_DIM * 2)
#define GAMEBOARD_POS 4
// X: column Y: row
#define GAMEBOARD_START_X (GAMEBOARD_POS)
#define GAMEBOARD_START_Y (GAMEBOARD_POS)
#define GAMEBOARD_END_X (GAMEBOARD_POS+GAMEBOARD_COLS)
#define GAMEBOARD_END_Y (GAMEBOARD_POS+GAMEBOARD_ROWS)
#define SIDEWALL_SIZE (GAMEBOARD_COLS*2 + GAMEBOARD_ROWS*2)

#define SCOREBOARD_DIM 10
#define SCOREBOARD_ROWS (SCOREBOARD_DIM)
#define SCOREBOARD_COLS (SCOREBOARD_DIM * 3)
#define SCOREBOARD_POS_Y 4
#define SCOREBOARD_POS_X 58

#define MISSIONBOARD_DIM 10
#define MISSIONBOARD_ROWS (MISSIONBOARD_DIM)
#define MISSIONBOARD_COLS (MISSIONBOARD_DIM * 3)
#define MISSIONBOARD_POS_Y 16
#define MISSIONBOARD_POS_X 58

#define WHITE 1
#define BLUE 2
#define CYAN 3
#define RED 4
#define GREEN 5
#define MAGENTA 6
#define RED_WHITE 7
#define RED_YELLOW 8
#define GREEN_YELLOW 9

#endif