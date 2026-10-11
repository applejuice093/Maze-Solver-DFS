# 🧩 Maze-Solver-DFS

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Algorithm](https://img.shields.io/badge/Algorithm-DFS-red?style=for-the-badge)](https://en.wikipedia.org/wiki/Depth-first_search)

A specialized C++ application designed to bridge the gap between image processing and graph theory. This tool takes a digital image of a maze (PNG) and utilizes **Depth First Search (DFS)** to find a viable path from a designated start point to the exit.

---

## 🚀 How It Works

The solver operates in three distinct phases:

### 1. Image Parsing & File Handling
The program reads the `.png` maze file and converts pixel data into a digital matrix. It distinguishes between:
* **Walls:** Obstacles represented by specific pixel values (usually black).
* **Paths:** Walkable space (usually white).

### 2. Algorithmic Solving (DFS)
Once the grid is established, the engine applies the **Depth First Search** algorithm:
* **Exploration:** It dives as deep as possible into a branch before backtracking.
* **Stack Management:** Uses a stack-based approach (implicit recursion) to keep track of the current path.
* **Path Identification:** Marks the successful route while avoiding cycles by tracking visited nodes.

### 3. Output Generation
After finding the exit, the program identifies the valid route and can be extended to visualize the solution directly on the maze structure.

---

## ✨ Key Features

- **Pixel-to-Grid Conversion:** Efficiently handles image files to create a logical map.
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
### 🛠️ Requirements & Usage

## Prerequisites
A C++ compiler (GCC/Clang/MSVC)

Standard C++ libraries for file handling

## Running the Solver
Place your maze image in the /maze folder.

## Run the executable:

```Bash
./MazeFinal.exe
Follow the on-screen prompts to select the image file and define start/end coordinates if required.
```

## 👤 Author
applejuice093

GitHub: @applejuice093
