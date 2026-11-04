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

        if (first[0] == '#') {
            // Header comments: "# start N" / "# goal N"; others are ignored.
            // The space after '#' is optional, so "#start N" works too
            // (it used to be misread as an edge line and rejected).
            std::istringstream hs(line.substr(line.find('#') + 1));
            std::string key;
            if (hs >> key && (key == "start" || key == "goal")) {
                // A malformed value used to be ignored silently, which then
                // surfaced as a misleading "missing header" error.
                int value;
                std::string extra;
                if (!(hs >> value) || value < 0 ||
                    (hs >> extra && extra[0] != '#')) {
                    throw std::runtime_error(
                        "line " + std::to_string(lineNo) + ": '# " + key +
                        "' needs exactly one non-negative node id");
                }
                int& slot = (key == "start") ? m.start : m.goal;
                if (slot >= 0) {
                    throw std::runtime_error("line " + std::to_string(lineNo) +
                                             ": duplicate '# " + key +
                                             "' header");
                }
                slot = value;
            }
            continue;
        }

        int a, b;
        std::istringstream edge(line);
        if (!(edge >> a >> b)) {
            throw std::runtime_error("line " + std::to_string(lineNo) +
                                     ": expected two node ids");
        }
        if (a < 0 || b < 0) {
            throw std::runtime_error("line " + std::to_string(lineNo) +
                                     ": node ids must be non-negative");
        }
        // Anything after the two ids must be a trailing "# comment". Before,
        // lines such as "1 2 3" or "1 2x" were silently accepted as "1 2".
        std::string rest;
        if (edge >> rest && rest[0] != '#') {
            throw std::runtime_error("line " + std::to_string(lineNo) +
                                     ": unexpected text after edge: '" +
                                     rest + "'");
        }
        m.addEdge(a, b);
    }
    if (m.start < 0 || m.goal < 0) {
        throw std::runtime_error("missing '# start' or '# goal' header");
    }
    // Catch typos such as "# goal 63" in a maze whose exit is cell 64: the
    // solver would otherwise just report "no path".
    if (!m.hasNode(m.start)) {
        throw std::runtime_error("start node " + std::to_string(m.start) +
                                 " does not appear in any edge");
    }
    if (!m.hasNode(m.goal)) {
        throw std::runtime_error("goal node " + std::to_string(m.goal) +
                                 " does not appear in any edge");
    }
    return m;
}

Maze loadEdgesFile(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("cannot open " + path);
    return parseEdges(f);
}
