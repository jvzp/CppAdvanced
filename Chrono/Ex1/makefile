CC = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = myprog

all: myprog

myprog: main.o
	$(LINK.cc) $^ -o $@

main.o: main.cpp

clean:
	$(RM) myprog *.o *~
