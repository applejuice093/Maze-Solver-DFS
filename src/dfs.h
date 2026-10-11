// dfs.h - Depth First Search path finding over a Maze.
#ifndef MAZE_DFS_H
#define MAZE_DFS_H

#include <vector>

#include "graph.h"

// Returns the sequence of nodes from maze.start to maze.goal found by DFS,
// or an empty vector if the goal is unreachable. Neighbours are explored in
// ascending order so results are deterministic.
std::vector<int> solveDFS(const Maze& maze);

#endif
