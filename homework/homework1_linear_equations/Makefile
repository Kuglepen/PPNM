CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS += -lm

OBJS = main.o matrix.o vector.o qr.o

all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDLIBS)

main.o: main.cc matrix.h vector.h qr.h
matrix.o: matrix.cc matrix.h vector.h
vector.o: vector.cc vector.h
qr.o: qr.cc qr.h matrix.h vector.h

clean:
	rm -f *.o main