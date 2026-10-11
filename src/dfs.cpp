// dfs.cpp - Iterative DFS with backtracking.
//
// An explicit stack is used instead of recursion so very large mazes cannot
// overflow the call stack.
#include "dfs.h"

#include <algorithm>
#include <set>
#include <utility>

std::vector<int> solveDFS(const Maze& maze) {
    if (maze.start == maze.goal) return {maze.start};
    if (!maze.hasNode(maze.start)) return {};

    std::set<int> visited{maze.start};
    // Each frame: (node, index of next neighbour to try).
    std::vector<std::pair<int, size_t>> stack{{maze.start, 0}};

    while (!stack.empty()) {
        auto& [node, next] = stack.back();
        std::vector<int> nbrs = maze.adj.at(node);
        std::sort(nbrs.begin(), nbrs.end());

        if (next >= nbrs.size()) {  // dead end: backtrack
            stack.pop_back();
            continue;
        }
        int nb = nbrs[next++];
        if (visited.count(nb)) continue;
        visited.insert(nb);
        stack.push_back({nb, 0});
        if (nb == maze.goal) break;
    }

    std::vector<int> path;
    if (!stack.empty() && stack.back().first == maze.goal) {
        for (const auto& frame : stack) path.push_back(frame.first);
    }
    return path;
}
