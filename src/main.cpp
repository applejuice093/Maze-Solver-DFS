// main.cpp - Command line entry point.
//
// Usage: maze_solver <file.edges>   (use "-" to read the maze from stdin)
// Exit codes: 0 = path found, 1 = goal unreachable, 2 = usage or input error.
// Prints the path from start to goal, or exits with status 1 if none exists.
#include <iostream>
#include <string>

#include "dfs.h"
#include "graph.h"

static void usage(std::ostream& out, const char* prog) {
    out << "usage: " << prog << " <maze.edges | ->\n"
        << "Find a path from '# start' to '# goal' with depth first search.\n"
        << "Pass '-' to read the maze from standard input.\n"
        << "Exit status: 0 path found, 1 no path, 2 usage or input error.\n";
}

int main(int argc, char** argv) {
    if (argc != 2) {
        usage(std::cerr, argv[0]);
        return 2;
    }
    const std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
        usage(std::cout, argv[0]);
        return 0;
    }
    try {
        Maze maze = (arg == "-") ? parseEdges(std::cin) : loadEdgesFile(arg);
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
