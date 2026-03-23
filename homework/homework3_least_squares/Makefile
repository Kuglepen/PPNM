CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS += -lm

OBJS = main.o matrix.o qr.o lsfit.o

all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDLIBS)

main.o: main.cc matrix.h lsfit.h
matrix.o: matrix.cc matrix.h
qr.o: qr.cc qr.h matrix.h
lsfit.o: lsfit.cc lsfit.h matrix.h qr.h

clean:
	rm -f *.o main