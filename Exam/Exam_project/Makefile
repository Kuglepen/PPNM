CXX = g++
CXXFLAGS = -std=c++23 -O2 -Wall -Wextra

TARGET = main
OBJS = main.o quasi_newton.o matrix.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o: main.cc quasi_newton.h matrix.h
	$(CXX) $(CXXFLAGS) -c main.cc

quasi_newton.o: quasi_newton.cc quasi_newton.h matrix.h
	$(CXX) $(CXXFLAGS) -c quasi_newton.cc

matrix.o: matrix.cc matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cc

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean