CC = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = myprog

all: myprog

myprog: ScopedDurationLogger.o main.o
	$(LINK.cc) $^ -o $@

main.o: main.cpp ScopedDurationLogger.hpp

ScopedDurationLogger.o: ScopedDurationLogger.cpp ScopedDurationLogger.hpp

clean:
	$(RM) myprog *.o *~
