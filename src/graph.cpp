// graph.cpp - Parsing of ".edges" maze files.
#include "graph.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

void Maze::addEdge(int a, int b) {
    // Maze passages are two-way, so store the edge in both directions.
    adj[a].push_back(b);
    adj[b].push_back(a);
}

Maze parseEdges(std::istream& in) {
    Maze m;
    std::string line;
    int lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        std::istringstream ss(line);
        std::string first;
        if (!(ss >> first)) continue;  // blank line

        if (first == "#") {
            // Header comments: "# start N" / "# goal N"; others are ignored.
            std::string key;
            int value;
            if (ss >> key >> value) {
                if (key == "start") m.start = value;
                else if (key == "goal") m.goal = value;
            }
            continue;
        }

        int a, b;
        std::istringstream edge(line);
        if (!(edge >> a >> b)) {
            throw std::runtime_error("line " + std::to_string(lineNo) +
                                     ": expected two node ids");
        }
        m.addEdge(a, b);
    }
    if (m.start < 0 || m.goal < 0) {
        throw std::runtime_error("missing '# start' or '# goal' header");
    }
    return m;
}

Maze loadEdgesFile(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("cannot open " + path);
    return parseEdges(f);
}
