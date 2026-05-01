CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

all: main

main: main.o lcg.o matrix.o
	$(CXX) $(CXXFLAGS) -o main main.o lcg.o matrix.o

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

lcg.o: lcg.cc
	$(CXX) $(CXXFLAGS) -c lcg.cc

matrix.o: matrix.cc
	$(CXX) $(CXXFLAGS) -c matrix.cc

clean:
	rm -f *.o main mcplot.pdf