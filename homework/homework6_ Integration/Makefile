CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

all: main

main: main.o integrator.o
	$(CXX) $(CXXFLAGS) -o main main.o integrator.o

main.o: main.cc integrator.h
	$(CXX) $(CXXFLAGS) -c main.cc

integrator.o: integrator.cc integrator.h
	$(CXX) $(CXXFLAGS) -c integrator.cc

clean:
	rm -f *.o main