CXX ?= g++
CXXFLAGS += -Wall -Wextra -std=c++17 -pedantic -O3 -fopenmp -march=native -I test_2019 -I gen


SRC = test_2019/main.cc
OBJS = ${SRC:.cc=.o}
BIN = main

all: $(BIN)

$(BIN): ${OBJS}
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BIN)

check: CXXFLAGS += -g3 -O0 -fno-inline -fsanitize=address
check: $(BIN)

.PHONY: clean check
clean:
	${RM} ${OBJS}
	${RM} $(BIN)
