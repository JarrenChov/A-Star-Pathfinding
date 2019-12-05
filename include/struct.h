#ifndef _STRUCT_H_
#define _STRUCT_H_

// declaration of x, y coordiantes
struct Coordinates
{
	int x_coord;
	int y_coord;
};

// declaration of a state per block (node) in a testgrid
struct Node 
{
	Coordinates* node_coord;
	int space_state;
	int heuristic_cost;
};

// declaration of state for a visited node
struct Fringe 
{
	int path_cost;
	int eval_cost;
	Coordinates* current_coord;
	Coordinates* previous_coord;
};

#endif // _STRUCT_H_
