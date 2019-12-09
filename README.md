# A* Pathfinding Algorithm Written in C++
Using the concept of A*, to create a simulation of a supervised robot with a set task to find the shortest possible path (if feasible) by traversing a given environment.

The basis of A* search with manhattan distance heuristic => `f(n) = g(n) + h(n)` constitutes of:
- `f(n)` = Evaluation function.
- `g(n)` = Total Cost of a cumulative total from the start node to the current node
- `h(n)` = Estimated shortest cost from current node to goal.

 The project consists mainly of:
 - Doubly Linked Lists
 - Pointer manipulation
 - Sorting (Built on top of a FIFO Queue, but arranged based on paths with lower costs)


# Table of Contents
- [General](#general)
  - [Directory Structure](#directory-structure)
- [Usage](#usage)
  - [Compiling](#compiling)
  - [Important Notes Before Execution](#important-notes-before-execution)
    - [Environment Structure](#environment-structure)
    - [Program Arguments](#program-arguments)
  - [Running the Program](#running-the-program)
  - [Understanding the Output](#understanding-the-output)
    - [Environment Grid Output](#enviroment-grid-output)
    - [Iteration Output](#iteration-output)
- [Limitations](#limitations)
- [Further Improvements](#further-improvements)

# General
## Directory Structure
Initial directory structure without any make-shift changes or modifications are as specified:
```bash
A-Star-Pathfinding
├── build
│   ├── sample-grid
│   │   ├── grid-large.txt
│   │   └── grid-small.txt
│   └── robotplanner
├── include
│   ├── global.h
│   ├── initDefn.h
│   ├── pathDefn.h
│   └── struct.h
├── src
│   ├── initDefn.cpp
│   ├── main.cpp
│   └── pathDefn.cpp
├── .gitignore
├── Makefile
└── README.md
```
Please take note that:
- All compilation and execution files created by the Makefile are located in `/build`, this also includes the execution file and a sample test enviroment.
- All header files `.h` are located in `/include`
- All source files `.cpp` are located in `/src`

# Usage
The project comes bundled with a pre-existing execution file and can be run without any need for compiling. However, if you wish to make any changes to the source code itself, the `Makefile` will need to be run to create a new executable with applied changes.

## Compiling
To generate a new executable, save any made changes to the files located in `/include` or `/src` and navigate to the root directory: `A-Star-Pathfinding`.
Run the command:
```bash
 make
```

## Important Notes Before Execution
Please read carefully the following notes, as unexpected behavior may arise if the schematics of the program are not properly followed. Although there is indeed a limitation in the program that some error avoidance have not been implemented, the main focus of this project was solely on A* itself, and assuming input data adhere to such schematics.

### Enviroment Structure
The grid environment consists of two possible states:
```bash
0 - a moveable space
1 - A non-moveable space, indicating a wall
```
Where, the layout of a created `test-grid` file environment must be `tab-spaced` and in the following format:
```bash
<x dimension length>    <y dimension length>
<grid corresponding to above dimensions and states>
```
For example, using the supplied testgrid `grid-small.txt`:
```bash
5	5
0	1	0	0	1
0	0	1	0	0
1	0	1	0	1
1	0	0	0	0
0	0	0	1	0
```
### Program Arguments
When specifying starting and ending positions, please note that coordinates start in *top-left* of the testgrid and start at `(0, 0)`. That is to say, numbers must start at **0** and not **1**, simulating a real` (x, y)` coordinate space.

## Running the Program
*NOTE: If you have not already read [Important Notes Before Execution](#important-notes-before-execution), please read the notes first as they are important to ensuring the program behaves correctly.*
To run the program, by initially starting at the root directory `A-Star-Pathfinding`, navigate to: `/build`
```bash
cd ./build
```
In the case that you do not have necessary permission for `robotplanner` (and this would result in other files aswell), run the following commands prior to executing the above command:
```bash
chmod u=rwx permissions.sh
```
then
```bash
./permissions.sh
```

Since the program expects 5 specified arguments as defined below:
- Arguments Defintion:
  - `grid-file location`: Denotes the relative path to a specified grid file
  - `start-x coordinate`: Denotes the x-coordinate of the starting position
  - `start-y coordinate`: Denotes the y-coordinate of the starting position
  - `end-x coordinate`: Denotes the x-coordinate of the end position
  - `end-y coordinate`: Denotes the y-coordinate of the end position

the required format of the arguments are as follows:
```bash
./robotplanner <grid-file location> <start-x coordinate> <start-y coordinate> <end-x coordinate> <end-y coordinate>
```
For example (executing from the current `/build` directory):
```bash
./robotplanner ./sample-grid/grid-small.txt 0 0 4 1
```

## Understanding the Output
The following details by steeping through the achieved outputs and how to fully understand what is being printed out to the user.

### Enviroment Output
Initially running the program, there will be two columns of numbers:
```bash
0, 5
0, 4
1, -1
1, -1
...
0, 0
1, -1
0, 2
0, 3
```
These numbers are based on per-line inputs of the grid separated by each `tab-spaced` state.
```bash
<Space State> <heuristic Cost>
```
 Where the columns can be refereed to as:
- Space State:
  If the current space is either a moveable space:`0`, or a wall:`1`
- Heuristic Cost `h(n)`
  The shortest distance using the manhattan distance to reach the end goal from the current `(x, y)` coordinate, where:
   - a `number >= 0` is a moveable space
   - a `number == -1` is a space occupied by a wall

### Iteration Output
The following is a Snapshot of the last two iterations using the command in [Running the Program](#running-the-program):
```bash
Iteration 15
=======================
Branched Nodes from: (3, 0)
        Path Cost - g(n): 10
        Eval Cost - f(n) = g(n) + h(n): 13
        Current Coord: 2, 0
        Previous Coord: 3, 0

--- Vector Resultants & Summary ---
Iterative Node Expansion Count: 17
Iterative Node Explored Count: 15
Fringes: (4, 1), (2, 0),
Visited Nodes: (0, 0), (0, 1), (1, 1), (1, 2), (1, 3), (2, 3), (1, 4), (2, 4), (3, 3), (0, 4), (3, 2), (4, 3), (3, 1), (4, 4), (3, 0),
=======================


Iteration 16
=======================
Execution Time: 0.015625 seconds
Path Iterations: 16
Explored Nodes: 17

Generated Path Size: 9
Generated Path: D R D D R R U U R
```
To understand such output, the first part containing `Branched Nodes from` denotes the possible paths that can occur from the current `(x, y)` coordinate, with a generated total of up to 3 possible paths. Where, each of the corresponding paths are shown its related information of:
- `Path Cost`: A cumlative sum to get to the current position.
- `Evaluation Cost`: The combined cost from the `path cost` and manhattan distance cost to the end goal.
- `Current Coordinate`: The current position as a `(x, y)` coordinate.
- `Previous Coordinate`: The parent node position as a `(x, y)` coordinate.

The next segment which displays the `Vector Resultants & Summary`, details the iterative process and state at each stage of the A* algorithm. Where each iterative step details the following information:
- `Iterative Node Expansion Count`: The number of cumlative nodes that have been looked at, including those not yet explored.
- `Iterative Node Explored Count`: The number of cumulative nodes that have been explored, but not expanded.
- `Fringes`: The `(x, y)` coordinates of nodes that need to be explored
- `Visited Nodes`: The `(x, y)` coordinates of nodes that have already been explored

The last part of the output, details the final state of the program and whether a path was successfully achieved.
In the case that a path from the supplied coordinates of start and end is possible and a path exists, the information details the following aspects:
- `Execution Time`: Total time in seconds to generate a path
- `Path Iterations`: The number of  iterative processes required to obtain a solution
- `Explored Nodes`: The total number of nodes needed to be explored.
- `Generated Path Size`: The total number of steps of the generated path.
- `Generated Path`: The steps to reach the end position from the starting position.

Likewise, in the case that solution can not be achieved, the only difference are the output details:
```bash
Iteration 18
=======================
--- No Path Found ---
Reason: Invalid Ending Point
Execution Time: 0.03125 seconds
Path Iterations: 18
Explored Nodes: 17

Generated Path Size: 0
Generated Path: not found
```

# Limitations
Although if the schematics are followed step by step there may be other factors and options which results in the obtained results to be in-accurate or not the optimal path. These limitations include but are not limited to:
- Since the robot can only take 90 degree turns, this introduces the fact that the most optimal path to move from one block to another would be a 45 degree angle to the next block. That is to say, the current implementation takes two moves to the next to a possible path, which instead the optimal way would be the move straight to that path by moving diagonally. This of cause would result in calculating the euclidean distance and not the manhattan distance instead.
- If the supplied grid is arbitrary large, then the computational cost and efficiency of the program will greatly decrease. In addition, the storage complexity will vastly increase as each node must be stored in memory and kept track of.

# Further Improvements
Like stated in the above section titled [Limitations](#limitations), the created project could be improved to obtain even further more accurate results, and reduce the complexity both in regards to space and time. Such improvements could be:
- Reducing the time complexity of the program.
Since the program mainly is a nested loop nested inside a continuous while loop, the complexity in terms of a real-world application would be just plain unfeasible. That is, the amount of time taken to generate a result would be unreliable and in-efficient. With this in mind, a few ideas could be:
  - To reduce the time complexity, a different type of algorithm which does not need to keep track of all nodes and compute pre-existing distances between the current nodes and end goals
  - Possibly break a large grid into smaller grids and generate for each possible `arrival` space the most optimal path to reach any of the other paths. This would possibly allow multi-core threading to concurrently process multiple batches at once.
- As mentioned above, to improve the shortest path the program should be modified to allow diagonal movement for the robot.
- Build a docker container environment to allow execution of the program in a tested and built environment that should theocratically work on other devices.