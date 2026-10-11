// graph.h - Undirected graph used to represent a maze.
//
// Each maze cell is a numbered node; an edge means the two cells are
// connected (no wall between them). Mazes are loaded from ".edges" files,
// see docs/EDGES_FORMAT.md for the format.
#ifndef MAZE_GRAPH_H
#define MAZE_GRAPH_H

#include <istream>
#include <map>
#include <string>
#include <vector>

struct Maze {
    int start = -1;                          // node to start from
    int goal = -1;                           // node to reach
    std::map<int, std::vector<int>> adj;     // adjacency list (sorted keys)

    void addEdge(int a, int b);
    bool hasNode(int n) const { return adj.count(n) > 0; }
};

// Parse a maze from a stream. Throws std::runtime_error on malformed input.
Maze parseEdges(std::istream& in);

// Convenience wrapper that opens and parses a file.
Maze loadEdgesFile(const std::string& path);

#endif
