# Introduction to Programming

Two independent university programming assignments in C, focused on recursive algorithms, data structures and dynamic memory management.

## Projects

### Exact Cover — Algorithm X

An exact-cover solver using recursive backtracking based on Algorithm X. It selects combinations of rows that cover every column exactly once and formats each solution according to an input filter.

- Array-based matrix representation, recursive search and restoration of search state.
- Input rows use `_` for an absent entry; the first line contains a `+`/`-` output filter.

[Source code](algorithm_x/solution/algorytm_x.c) · [Task](algorithm_x/statement/WDP-zadanie-2.md) · [Examples](algorithm_x/statement/examples/) · [Tests](algorithm_x/tests/)

### Recursive Integer Calculator — Colossal Numbers

A stack-based calculator for non-negative integers represented as recursive trees. Each node represents the sum of powers of two whose exponents are represented by its children, allowing arithmetic to be implemented directly on this recursive structure.

- Dynamically allocated trees, recursive addition and multiplication, and normalisation of the number representation.
- Commands: `+` for addition, `*` for multiplication, `^` for `2^n`, `:` to duplicate the top value and `.` to print and pop it.
- Numbers use the assignment's recursive `0`/`1` encoding: for example, `0` represents zero and `100` represents one.

[Source code](colossal_numbers/solution/colossal_numbers.c) · [Task](colossal_numbers/statement/WDP-zadanie-3.md) · [Examples](colossal_numbers/statement/examples/) · [Tests](colossal_numbers/tests/)

## Build and run

Requirements: GCC with C23 support. The commands below use GCC's `c2x` spelling of the C23 option and a POSIX shell. Run them from the repository root.

```sh
mkdir -p build

gcc -std=c2x -Wall -Wextra -O2 \
  algorithm_x/solution/algorytm_x.c -o build/algorithm_x

gcc -std=c2x -Wall -Wextra -O2 \
  colossal_numbers/solution/colossal_numbers.c -o build/colossal_numbers

./build/algorithm_x < algorithm_x/statement/examples/przyklad1.in
./build/colossal_numbers < colossal_numbers/statement/examples/przyklad1.in
```

### Check an example

Algorithm X may enumerate solutions in a different order, so compare sorted output with the supplied `.out.sorted` file:

```sh
./build/algorithm_x < algorithm_x/statement/examples/przyklad1.in \
  | LC_ALL=C sort > build/algorithm_x.out.sorted
diff -u algorithm_x/statement/examples/przyklad1.out.sorted \
  build/algorithm_x.out.sorted

./build/colossal_numbers < colossal_numbers/statement/examples/przyklad1.in \
  > build/colossal_numbers.out
diff -u colossal_numbers/statement/examples/przyklad1.out \
  build/colossal_numbers.out
```

For a short calculator example, add two and four, then print the result:

```sh
printf '11000\n1110000\n+\n.\n' | ./build/colossal_numbers
```

Expected output: `11100011000`, the recursive encoding of six.

## Assignment materials

Each project has its own `solution/`, `statement/` and `tests/` directories. The original statements are in Polish, and the supplied examples and test fixtures are kept alongside the implementations.
