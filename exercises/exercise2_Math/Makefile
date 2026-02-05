CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.0 = $(CXX) $(LDFLAGS)
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt

main: main.o sfuns.o
	$(CXX) $(LDFLAGS) main.o sfuns.o -o main $(LDLIBS)
# $(CXX) $(LDFLAGS) $(LDLIBS) -o main $^

main.o: sfuns.h main.cc
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

sfuns.o: sfuns.h sfuns.cc
	$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o

.PHONY: clean
clean:
	$(RM) main main.o Out.txt *.o


test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM)
	@echo $(cc)

