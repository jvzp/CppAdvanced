CC = g++
CXXFLAGS = -Wall -Wextra -std=c++1y -pthread

TARGET = myprog

all: myprog

myprog: main.o
	$(LINK.cc) $^ -o $@

main.o: main.cpp

clean:
	$(RM) myprog *.o *~
