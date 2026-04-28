CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

OBJS = main.o matrix.o rk.o problems.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cc matrix.h rk.h problems.h
	$(CXX) $(CXXFLAGS) -c main.cc

matrix.o: matrix.cc matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cc

rk.o: rk.cc rk.h matrix.h
	$(CXX) $(CXXFLAGS) -c rk.cc

problems.o: problems.cc problems.h matrix.h
	$(CXX) $(CXXFLAGS) -c problems.cc

clean:
	rm -f *.o main