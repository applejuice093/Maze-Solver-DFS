CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
BUILD    := build
LIB_SRC  := src/graph.cpp src/dfs.cpp

all: $(BUILD)/maze_solver

$(BUILD)/maze_solver: $(LIB_SRC) src/main.cpp src/*.h | $(BUILD)
	$(CXX) $(CXXFLAGS) $(LIB_SRC) src/main.cpp -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

.PHONY: all clean
