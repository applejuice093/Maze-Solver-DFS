# `.edges` maze format

Each maze in `maze/` is stored twice: as a picture (`mazeN.png`) and as a
plain-text graph (`mazeN.edges`) that the solver reads.

```text
# start 1
# goal 36

1 7
7 8
```

* Each cell of the maze is a node identified by a positive integer id.
* `# start N` and `# goal N` are required header lines naming the entry and
  exit cells. Any other `#` line is treated as a comment.
* Every other non-blank line is an edge `A B`: cells `A` and `B` are adjacent
  with no wall between them. Edges are undirected, so `A B` and `B A` mean
  the same thing.
* Blank lines are ignored. A line that is not a comment and does not start
  with two integers is reported as an error with its line number.

## Adding a new maze

1. Save the image as `maze/mazeN.png`.
2. Give each cell an id and list each open passage as an edge in
   `maze/mazeN.edges`, together with the `start`/`goal` header.
3. Run `./build/maze_solver maze/mazeN.edges` (or `make run`).
