CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

OBJ = main.o matrix.o problems.o rk.o

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)

main.o: main.cc
matrix.o: matrix.cc matrix.h
problems.o: problems.cc problems.h
rk.o: rk.cc rk.h

clean:
	rm -f *.o main