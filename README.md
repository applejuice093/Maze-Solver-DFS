# 🧩 Maze-Solver-DFS

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Algorithm](https://img.shields.io/badge/Algorithm-DFS-red?style=for-the-badge)](https://en.wikipedia.org/wiki/Depth-first_search)

A specialized C++ application designed to bridge the gap between image processing and graph theory. This tool takes a digital image of a maze (PNG) and utilizes **Depth First Search (DFS)** to find a viable path from a designated start point to the exit.

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
- **Tested:** Unit tests cover backtracking, cycles, unreachable goals and malformed input.
- **Backtracking Logic:** Implements robust DFS to ensure all possible paths are explored until a solution is found.
- **Executable Ready:** Includes a pre-compiled `MazeFinal.exe` for quick testing on Windows environments.
- **Custom Maze Support:** Capable of processing various maze designs as long as they follow the supported image format.

---

## 📂 Project Structure

```text
├── src/
│   ├── graph.h / graph.cpp   # Maze graph + .edges file parser
│   ├── dfs.h / dfs.cpp       # Iterative DFS solver with backtracking
│   └── main.cpp              # Command line entry point
├── tests/test_dfs.cpp        # Unit tests (make test)
├── maze/                     # Sample mazes: mazeN.png + mazeN.edges
├── docs/EDGES_FORMAT.md      # Description of the .edges input format
├── Makefile                  # Build, run and test targets
├── MazeFinal.exe             # Pre-compiled Windows build
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
Without make:
```bash
g++ -std=c++17 -O2 src/graph.cpp src/dfs.cpp src/main.cpp -o maze_solver
```

### Running the solver
```bash
./build/maze_solver maze/maze1.edges
# Path (17 cells): 1 -> 7 -> 8 -> 9 -> 15 -> ... -> 36
make run        # solve every sample maze in maze/
```
The program exits with status `0` when a path is found, `1` when the goal is
unreachable and `2` on bad input. See [docs/EDGES_FORMAT.md](docs/EDGES_FORMAT.md)
to create your own mazes.

On Windows you can also run the bundled `MazeFinal.exe` and follow its prompts.

### Running the tests
```bash
make test
```

## 👤 Author
applejuice093

GitHub: @applejuice093
