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

Wall : Wall.o Wall.h Settings.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) Wall Wall.o $(CURSES)

main : main.o Player.o Snake.o Wall.o Player.h Board.h GameBoard.h Snake.h Wall.h Settings.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) main main.o $(CURSES)


clean :
	rm -f *.o

%.o : %.cpp %.h
	$(CC) $(STD) $(CCFLAG1) -c $< $(CURSES)
%.o : %.cpp
	$(CC) $(STD) $(CCFLAG1) -c $< $(CURSES)
% : %.cpp
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) $@ $< $(CURSES)
