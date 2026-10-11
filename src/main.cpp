// main.cpp - Command line entry point.
//
// Usage: maze_solver <file.edges>
// Prints the path from start to goal, or exits with status 1 if none exists.
#include <iostream>

#include "dfs.h"
#include "graph.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <maze.edges>\n";
        return 2;
    }
    try {
        Maze maze = loadEdgesFile(argv[1]);
        std::vector<int> path = solveDFS(maze);
        if (path.empty()) {
            std::cout << "No path from " << maze.start << " to " << maze.goal << "\n";
            return 1;
        }
        std::cout << "Path (" << path.size() << " cells): ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << (i ? " -> " : "") << path[i];
        }
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 2;
    }
    return 0;
}
