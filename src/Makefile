CC = g++
STD = -std=c++11
CCFLAG1 = -g
CCFLAG2 = -o
CURSES = -lncursesw

main : main.cpp Board.h GameBoard.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) main main.cpp $(CURSES)

clean:
	rm -f *.o


%.o : %.cpp %.h
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) -c $< $(CURSES)
%.o : %.cpp
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) -c $< $(CURSES)
% : %.cpp
	$(CC) $(STD) $(CCFLAG1) $(CCFLAG2) -o $@ $< $(CURSES)
