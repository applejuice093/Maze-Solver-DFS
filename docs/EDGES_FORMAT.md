# `.edges` maze format

Each maze in `maze/` is stored twice: as a picture (`mazeN.png`) and as a
plain-text graph (`mazeN.edges`) that the solver reads.

```text
# start 1
# goal 36

1 7
7 8
```

* Each cell of the maze is a node identified by a non-negative integer id.
* `# start N` and `# goal N` are required header lines naming the entry and
  exit cells. Each must appear exactly once, with exactly one non-negative
  id, and both cells must appear in at least one edge. The space after `#`
  is optional (`#start 1` works too).
* Any other line starting with `#` is a comment.
* Every other non-blank line is an edge `A B`: cells `A` and `B` are adjacent
  with no wall between them. Edges are undirected, so `A B` and `B A` mean
  the same thing. An edge may be followed by a `# comment`, but nothing else
  (`1 2 3` is an error, not the edge `1 2`).
* Blank lines are ignored. Windows (CRLF) line endings are fine.

Any violation stops the solver with exit status 2 and an error message that
includes the line number, for example:

```text
error: line 7: unexpected text after edge: '3'
error: goal node 63 does not appear in any edge
```

## Adding a new maze

1. Save the image as `maze/mazeN.png`.
2. Give each cell an id and list each open passage as an edge in
   `maze/mazeN.edges`, together with the `start`/`goal` header.
3. Run `./build/maze_solver maze/mazeN.edges` (or `make run`). You can also
   pipe a maze in: `cat my.edges | ./build/maze_solver -`.
