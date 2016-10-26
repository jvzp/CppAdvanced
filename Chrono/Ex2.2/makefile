CC = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = myprog

all: myprog

myprog: main.o
	$(LINK.cc) $^ -o $@

main.o: main.cpp ScopedDurationLogger.hpp

clean:
	$(RM) myprog *.o *~
