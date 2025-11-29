Maze Solver Using DFS (C Project)

This project is a C-based application that reads a maze from a PNG image file and solves it using the Depth First Search (DFS) algorithm.
The program processes the image through file handling, converts it into a grid, and finds a valid path from the start point to the exit.

📌 Features

Written entirely in C

Reads maze from PNG files

Converts image pixels into a 2D matrix

Uses DFS to find a valid path

Supports recursion and backtracking

Outputs the solved maze or prints the path

Lightweight and efficient

🧠 How It Works

The program loads a PNG image representing the maze
(walls, paths, start, and end points are differentiated by pixel colors)

The PNG is converted into a grid (2D array).

DFS is applied to traverse possible routes.

The algorithm stops once it finds a path to the exit.

The final solution is displayed or exported.

📂 Project Structure
├── src/
│   ├── main.c
│   ├── dfs.c
│   ├── dfs.h
│   ├── maze_reader.c
│   ├── maze_reader.h
│
├── mazes/
│   ├── maze1.png
│   ├── maze2.png
│
├── output/
│   ├── solved_maze.png (if implemented)
│
└── README.md

⚙️ Technologies & Libraries

C programming language

DFS (Depth First Search)

PNG handling library

lodepng or stb_image (whichever you used)

🚀 How to Compile

Using gcc:

gcc src/*.c -o MazeSolver


If your PNG library requires linking, add its flags.

▶️ How to Run
./MazeSolver mazes/maze1.png


🤝 Contributing

Pull requests and improvements are welcome.

📄 License

This project is available under the MIT License.