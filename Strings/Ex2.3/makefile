CXX = g++-5
CXXFLAGS = -Wall -Wextra -std=c++1y

TARGET = myprog

all: myprog

myprog: main.o
	$(LINK.cc) $^ -o $@

main.o: main.cpp

clean:
	$(RM) myprog *.o *~
