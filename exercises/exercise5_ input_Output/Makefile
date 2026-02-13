CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.0 = $(CXX) $(LDFLAGS)
LDLIBS += -lstdc++ -lm

main: main.o

Out.txt: main
	./$< > $@

.PHONY: clean
clean:
	$(RM) main main.o Out.txt *.o

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM)
	@echo $(cc)

