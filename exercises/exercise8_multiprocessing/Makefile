CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O -pthread

main: main.o harm.o
	$(CXX) $(CXXFLAGS) main.o harm.o -o main

main.o: main.cc harm.h
	$(CXX) $(CXXFLAGS) -c main.cc

harm.o: harm.cc harm.h
	$(CXX) $(CXXFLAGS) -c harm.cc

Out.txt: main
	./main > Out.txt

.PHONY: clean
clean:
	rm -f main *.o Out.txt

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM)
	@echo $(cc)

