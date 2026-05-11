CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

all: main

main: main.o matrix.o qr.o minimization.o
	$(CXX) $(CXXFLAGS) -o main main.o matrix.o qr.o minimization.o

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

matrix.o: matrix.cc
	$(CXX) $(CXXFLAGS) -c matrix.cc

qr.o: qr.cc
	$(CXX) $(CXXFLAGS) -c qr.cc

minimization.o: minimization.cc minimization.h
	$(CXX) $(CXXFLAGS) -c minimization.cc

clean:
	rm -f *.o main out.txt