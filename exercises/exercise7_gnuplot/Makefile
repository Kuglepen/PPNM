CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS += -lstdc++ -lm

main: main.o functions.o

main.o: main.cc functions.h
functions.o: functions.cc functions.h

Out.txt: main
	./$< > $@

.PHONY: clean
clean:
	$(RM) main main.o erf.o Out.txt *.o

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM)
	@echo $(cc)
