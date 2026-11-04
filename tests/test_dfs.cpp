// test_dfs.cpp - Minimal self-contained tests for the parser and solver.
// Run with: make test
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "../src/dfs.h"
#include "../src/graph.h"

static Maze parse(const std::string& text) {
    std::istringstream in(text);
    return parseEdges(in);
}

// Every consecutive pair in a path must be an edge of the maze.
static bool isValidPath(const Maze& m, const std::vector<int>& p) {
    if (p.empty() || p.front() != m.start || p.back() != m.goal) return false;
    for (size_t i = 1; i < p.size(); ++i) {
        const auto& nb = m.adj.at(p[i - 1]);
        bool found = false;
        for (int n : nb) found |= (n == p[i]);
        if (!found) return false;
    }
    return true;
}

int main() {
    // Straight corridor.
    Maze line = parse("# start 1\n# goal 3\n1 2\n2 3\n");
    assert((solveDFS(line) == std::vector<int>{1, 2, 3}));

    // Dead end branch must be backtracked out of.
    Maze branch = parse("# start 1\n# goal 4\n1 2\n2 5\n5 6\n1 3\n3 4\n");
    assert(isValidPath(branch, solveDFS(branch)));

    // Cycle should not cause infinite looping.
    Maze cyc = parse("# start 1\n# goal 9\n1 2\n2 3\n3 1\n3 9\n");
    assert(isValidPath(cyc, solveDFS(cyc)));

    // Unreachable goal.
    Maze split = parse("# start 1\n# goal 4\n1 2\n3 4\n");
    assert(solveDFS(split).empty());

    // Start == goal.
    Maze same = parse("# start 2\n# goal 2\n1 2\n");
    assert((solveDFS(same) == std::vector<int>{2}));

    // Start == goal but the cell is not in the maze: no path.
    Maze ghost;
    ghost.start = ghost.goal = 7;
    ghost.addEdge(1, 2);
    assert(solveDFS(ghost).empty());

    // Missing header is rejected.
    bool threw = false;
    try { parse("1 2\n"); } catch (const std::runtime_error&) { threw = true; }
    assert(threw);

    // Malformed edge line is rejected.
    threw = false;
    try { parse("# start 1\n# goal 2\n1 x\n"); } catch (const std::runtime_error&) { threw = true; }
    assert(threw);

    // Extra tokens after an edge are rejected...
    for (const char* bad : {"1 2 3\n", "1 2x\n"}) {
        threw = false;
        try { parse(std::string("# start 1\n# goal 2\n") + bad); }
        catch (const std::runtime_error&) { threw = true; }
        assert(threw);
    }
    // ...but a trailing comment is fine.
    Maze commented = parse("# start 1\n# goal 2\n1 2  # corridor\n");
    assert((solveDFS(commented) == std::vector<int>{1, 2}));

    // '#' does not need to be followed by a space; '#' lines are comments.
    Maze tight = parse("#start 1\n#goal 2\n#comment\n1 2\n");
    assert(tight.start == 1 && tight.goal == 2);

    // Malformed, negative or repeated start/goal headers are rejected.
    for (const char* bad : {"# start x\n# goal 2\n1 2\n",
                            "# start -1\n# goal 2\n1 2\n",
                            "# start 1 2\n# goal 2\n1 2\n",
                            "# start 1\n# start 2\n# goal 2\n1 2\n"}) {
        threw = false;
        try { parse(bad); } catch (const std::runtime_error&) { threw = true; }
        assert(threw);
    }

    // Negative node ids are rejected (-1 is the "unset" marker).
    threw = false;
    try { parse("# start 1\n# goal 2\n1 -2\n"); }
    catch (const std::runtime_error&) { threw = true; }
    assert(threw);

    // Start or goal that is not part of any edge is reported.
    for (const char* bad : {"# start 9\n# goal 2\n1 2\n",
                            "# start 1\n# goal 9\n1 2\n"}) {
        threw = false;
        try { parse(bad); } catch (const std::runtime_error&) { threw = true; }
        assert(threw);
    }

    // Files saved on Windows (CRLF line endings) parse the same way.
    Maze crlf = parse("# start 1\r\n# goal 3\r\n1 2\r\n2 3 # end\r\n");
    assert((solveDFS(crlf) == std::vector<int>{1, 2, 3}));

    // A 200k-cell corridor would overflow the call stack of a recursive DFS;
    // the iterative solver must handle it and return every cell in order.
    Maze corridor;
    const int kLen = 200000;
    corridor.start = 0;
    corridor.goal = kLen - 1;
    for (int i = 0; i + 1 < kLen; ++i) corridor.addEdge(i, i + 1);
    std::vector<int> longPath = solveDFS(corridor);
    assert(longPath.size() == static_cast<size_t>(kLen));
    assert(isValidPath(corridor, longPath));

    // Bundled sample mazes must all be solvable.
    for (const char* f : {"maze/maze1.edges", "maze/maze2.edges", "maze/maze3.edges"}) {
        Maze m = loadEdgesFile(f);
        assert(isValidPath(m, solveDFS(m)));
    }

    std::cout << "All tests passed\n";
    return 0;
}
