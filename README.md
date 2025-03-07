# Recursion and Stack-Based Computational Programs
This repository contains five C++ programs that implement recursion and stack-based algorithms to solve problems including grid traversal, blob detection, pathfinding, and arithmetic expression evaluation. 

## Features
**Cell Counting (`cells.cpp`)**
- Counts the number of connected cells in a given grid using recursion.
- Supports a 4-way and 8-way connectivity.
- Input: A grid file, grid dimensions, start position, and connection type.

**Blob Counting (`blobs.cpp`)**
- Counts the total number of disconnected blobs in a given grid.
- Uses recursive Depth-First Search (DFS) to detect and count blobs in the grid.

**Pathfinding in Elevation Map (`path.cpp`)**
- Identifies highest and lowest elevation points and determines if a path exists between them without going downward.

**Infix to Postfix Conversion (`in2pos.cpp`)**
- Converts an infix arithmetic expression to postfix notation.
- Uses a stack-based approach for conversion.

**Postfix Expression Evaluation (`eval.cpp`)**
- Evaulates a postfix arithmetic expression using a stack.

## Usage
### ***Compile all programs***
```sh
g++ -o cells cells.cpp
g++ -o blobs blobs.cpp
g++ -o path path.cpp
g++ -o in2pos in2pos.cpp
g++ -o eval eval.cpp
```
### ***Run all Programs***
```sh
./cells grid.txt 8 8 3 4 4
./blobs grid.txt 8 8 4
./path map.txt 5 5
./in2pos "5 + 3 * ( 8 - 2 )"
./eval "5 3 8 2 - * +"
```
## Technologies Used
- C++
- Data Structures: Stack, Recursion
- Algorithms: DFS, Expression Parsing

## Author 
Alyana Barbosa
