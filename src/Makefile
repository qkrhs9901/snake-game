CC = g++
STD = -std=c++11
CCFLAG1 = -g
CCFLAG2 = -o
CURSES = -lncursesw

all : main

Player : Player.o Player.h Settings.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) Player Player.o $(CURSES)

Snake : Snake.o Snake.h Settings.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) Snake Snake.o $(CURSES)

GameBoard : GameBoard.o GameBoard.h Settings.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) GameBoard GameBoard.o $(CURSES)

InnerWall : innerWall.o innerWall.h Settings.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) innerWall innerWall.o $(CURSES)

main : main.o Player.o Snake.o GameBoard.o innerWall.o Player.h Board.h GameBoard.h Snake.h innerWall.h Settings.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) main main.o $(CURSES)


clean :
	rm -f *.o

%.o : %.cpp %.h
	$(CC) $(STD) $(CCFLAG1) -c $< $(CURSES)
%.o : %.cpp
	$(CC) $(STD) $(CCFLAG1) -c $< $(CURSES)
% : %.cpp
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) $@ $< $(CURSES)
