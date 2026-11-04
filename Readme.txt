Maze Solver Using DFS (C++)
===========================

Quick start:

  make                                  # build build/maze_solver
  ./build/maze_solver maze/maze1.edges  # solve a sample maze
  make test                             # run unit + command line tests
  ./build/maze_solver --help            # usage and exit codes

Or with CMake (Windows/MSVC, IDEs):

  cmake -S . -B build-cmake && cmake --build build-cmake
  ctest --test-dir build-cmake

Input mazes are plain-text graphs, see docs/EDGES_FORMAT.md.
Full documentation is in README.md.

License: MIT (see LICENSE).
