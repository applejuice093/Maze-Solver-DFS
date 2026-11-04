#!/bin/sh
# cli_test.sh - End-to-end checks of the maze_solver exit codes and output.
# Usage: tests/cli_test.sh [path/to/maze_solver]   (run by `make test`)
BIN=${1:-./build/maze_solver}
fail=0

# expect <wanted exit code> <description> <command...>
expect() {
    want=$1; desc=$2; shift 2
    "$@" >/dev/null 2>&1
    got=$?
    if [ "$got" -ne "$want" ]; then
        echo "FAIL: $desc (exit $got, expected $want)"
        fail=1
    fi
}

expect 0 "sample maze 1 is solvable" "$BIN" maze/maze1.edges
expect 0 "--help succeeds" "$BIN" --help
expect 2 "no arguments is a usage error" "$BIN"
expect 2 "missing file is an input error" "$BIN" maze/does-not-exist.edges

reachable='# start 1
# goal 3
1 2
2 3'
unreachable='# start 1
# goal 4
1 2
3 4'
expect 0 "maze from stdin" sh -c "printf '%s\n' '$reachable' | '$BIN' -"
expect 1 "unreachable goal" sh -c "printf '%s\n' '$unreachable' | '$BIN' -"
expect 2 "malformed edge" sh -c "printf '# start 1\n# goal 2\n1 x\n' | '$BIN' -"

out=$(printf '%s\n' "$reachable" | "$BIN" -)
if [ "$out" != "Path (3 cells): 1 -> 2 -> 3" ]; then
    echo "FAIL: unexpected output: $out"
    fail=1
fi

[ "$fail" -eq 0 ] && echo "CLI tests passed"
exit "$fail"
