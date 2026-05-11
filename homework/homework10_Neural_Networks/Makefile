CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

all: main

main: main.o ann.o matrix.o qr.o
	$(CXX) $(CXXFLAGS) -o main \
	main.o ann.o matrix.o qr.o

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

ann.o: ann.cc
	$(CXX) $(CXXFLAGS) -c ann.cc

matrix.o: matrix.cc
	$(CXX) $(CXXFLAGS) -c matrix.cc

qr.o: qr.cc
	$(CXX) $(CXXFLAGS) -c qr.cc

clean:
	rm -f *.o main