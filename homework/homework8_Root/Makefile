CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

all: main

main: main.o matrix.o qr.o root.o rk.o
	$(CXX) $(CXXFLAGS) -o main main.o matrix.o qr.o root.o rk.o

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

matrix.o: matrix.cc
	$(CXX) $(CXXFLAGS) -c matrix.cc

qr.o: qr.cc
	$(CXX) $(CXXFLAGS) -c qr.cc

root.o: root.cc
	$(CXX) $(CXXFLAGS) -c root.cc

rk.o: rk.cc
	$(CXX) $(CXXFLAGS) -c rk.cc

clean:
	rm -f *.o main hydrogen.dat out.txt conv_*.dat