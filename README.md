# 🧩 Maze-Solver-DFS

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Algorithm](https://img.shields.io/badge/Algorithm-DFS-red?style=for-the-badge)](https://en.wikipedia.org/wiki/Depth-first_search)

A C++ application that models a maze as a graph and uses **Depth First Search (DFS)** to find a path from a designated start cell to the exit. Each sample maze ships as a PNG picture plus a text `.edges` graph that the solver reads.

---

## 🚀 How It Works

The solver operates in three distinct phases:

### 1. Maze Representation
Each maze image in `maze/` has a companion `.edges` file that describes the
maze as a graph: every cell is a node and every open passage between two
cells is an edge. The `# start` / `# goal` headers mark the entry and exit.

### 2. Algorithmic Solving (DFS)
Once the grid is established, the engine applies the **Depth First Search** algorithm:
* **Exploration:** It dives as deep as possible into a branch before backtracking.
* **Stack Management:** Uses an explicit stack (no recursion), so large mazes cannot overflow the call stack. The stack always holds the current path.
* **Path Identification:** Marks the successful route while avoiding cycles by tracking visited nodes.

### 3. Output Generation
After reaching the exit, the program prints the route as a sequence of cell ids. Neighbours are explored in ascending order, so the output is deterministic.

---

## ✨ Key Features

- **Graph-based Input:** Simple text `.edges` format that is easy to write by hand.
- **Strict input checking:** Malformed edges, bad or duplicate headers and start/goal cells that are not in the maze are reported with a line number instead of being silently ignored.
- **Tested:** Unit tests cover backtracking, cycles, unreachable goals, malformed input and a 200k-cell maze; a shell script checks the command line exit codes.
- **Backtracking Logic:** Implements robust DFS to ensure all possible paths are explored until a solution is found.
- **Custom Maze Support:** Any maze can be solved once it is written down as an `.edges` graph (see [docs/EDGES_FORMAT.md](docs/EDGES_FORMAT.md)); the solver does not read the PNG images themselves.

---

## 📂 Project Structure

```text
├── src/
│   ├── graph.h / graph.cpp   # Maze graph + .edges file parser
│   ├── dfs.h / dfs.cpp       # Iterative DFS solver with backtracking
│   └── main.cpp              # Command line entry point
├── tests/test_dfs.cpp        # Unit tests (make test)
├── tests/cli_test.sh         # Command line exit-code tests (make test)
├── maze/                     # Sample mazes: mazeN.png + mazeN.edges
├── docs/EDGES_FORMAT.md      # Description of the .edges input format
├── Makefile                  # Build, run, test and sanitize targets
├── CMakeLists.txt            # Alternative CMake build (MSVC, IDEs, ctest)
├── MazeFinal.exe             # Legacy Windows build of the original menu app
├── README.md                 # Project documentation
└── Readme.txt                # Quick-start pointer
```
## 🛠️ Requirements & Usage

### Prerequisites
* A C++17 compiler (GCC, Clang or MSVC)
* `make` (optional, for the provided Makefile)

### Build from source
```bash
make            # builds build/maze_solver
```
With CMake (also works with Visual Studio / MSVC):
```bash
cmake -S . -B build-cmake
cmake --build build-cmake
ctest --test-dir build-cmake --output-on-failure
```
Without make or CMake:
```bash
g++ -std=c++17 -O2 src/graph.cpp src/dfs.cpp src/main.cpp -o maze_solver
```

### Running the solver
```bash
./build/maze_solver maze/maze1.edges
# Path (17 cells): 1 -> 7 -> 8 -> 9 -> 15 -> ... -> 36
make run        # solve every sample maze in maze/
cat my.edges | ./build/maze_solver -   # read a maze from stdin
./build/maze_solver --help
```
The program exits with status `0` when a path is found, `1` when the goal is
unreachable and `2` on bad input. See [docs/EDGES_FORMAT.md](docs/EDGES_FORMAT.md)
to create your own mazes.

`MazeFinal.exe` is a legacy Windows build of the original interactive menu
version of this project. It is not built from the current `src/` code; build
from source (e.g. with CMake and MSVC) to get the current solver on Windows.

### Running the tests
```bash
make test       # unit tests + command line tests
make sanitize   # unit tests under AddressSanitizer and UBSan (GCC/Clang)
```

## 📄 License
Released under the MIT License, see [LICENSE](LICENSE).

## 👤 Author
applejuice093

GitHub: [@applejuice093](https://github.com/applejuice093)
