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

run: $(BUILD)/maze_solver
	@for f in maze/*.edges; do echo "$$f"; ./$(BUILD)/maze_solver $$f; done

test: $(BUILD)/test_dfs $(BUILD)/maze_solver
	./$(BUILD)/test_dfs
	sh tests/cli_test.sh ./$(BUILD)/maze_solver

# Build and run the unit tests with AddressSanitizer and UBSan to catch
# out-of-bounds access, use-after-free and undefined behaviour.
SANFLAGS := -std=c++17 -Wall -Wextra -g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer

sanitize: | $(BUILD)
	$(CXX) $(SANFLAGS) -UNDEBUG $(LIB_SRC) tests/test_dfs.cpp -o $(BUILD)/test_dfs_san
	./$(BUILD)/test_dfs_san

clean:
	rm -rf $(BUILD)

.PHONY: all clean test run sanitize
