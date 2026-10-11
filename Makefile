CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
BUILD    := build
LIB_SRC  := src/graph.cpp src/dfs.cpp

all: $(BUILD)/maze_solver

$(BUILD)/maze_solver: $(LIB_SRC) src/main.cpp src/*.h | $(BUILD)
	$(CXX) $(CXXFLAGS) $(LIB_SRC) src/main.cpp -o $@

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/test_dfs: $(LIB_SRC) tests/test_dfs.cpp src/*.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -UNDEBUG $(LIB_SRC) tests/test_dfs.cpp -o $@

test: $(BUILD)/test_dfs
	./$(BUILD)/test_dfs

clean:
	rm -rf $(BUILD)

.PHONY: all clean test
