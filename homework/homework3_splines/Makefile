CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

all: main

main: main.o spline.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc spline.h
	$(CXX) $(CXXFLAGS) -c $<

spline.o: spline.cc spline.h
	$(CXX) $(CXXFLAGS) -c $<

plot:
	gnuplot plot.gp

clean:
	rm -f *.o main