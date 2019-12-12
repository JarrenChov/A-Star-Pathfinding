#include "../include/pathDefn.h"
#include "../include/struct.h"
#include "../include/global.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Calculate the total current cost using the traversal cost and shortest path to end goal
int calculate_evaluation(int pathCost, int heuristicCost) {
	return (pathCost + heuristicCost);
}

// Find all possible paths traversable by one block in environment map from current node
vector<char> find_node_paths(Fringe currentFringe, int optionCount, int *options) {
	vector<char> paths;

	for (int i = 0; i < optionCount; i++) {
		int xLocation = (currentFringe.current_coord->x_coord) + (options[i]);
		// Stay within x bounds of the map
		if (xLocation >= 0 && xLocation < env_xSize) {
			// If x-coordinates are not the same,
			// take all possible traverses which are not a wall
			// 	- Right
			// 	- Left		
			if (!(xLocation == currentFringe.previous_coord->x_coord)) {
				if ((env[xLocation][currentFringe.current_coord->y_coord]).space_state == 0) {
					if (options[i] == 1) {
						paths.push_back('R');
					}

					if (options[i] == -1) {
						paths.push_back('L');
					}
				}
			}
		}

		int yLocation = (currentFringe.current_coord->y_coord) + (options[i]);
		// Stay within y bounds of the map
		if (yLocation >= 0 && yLocation < env_ySize) {
			// If y-coordinates are not the same,
			// take all possible traverses which are not a wall
			// 	- Up
			// 	- Down	
			if (!(yLocation == currentFringe.previous_coord->y_coord)) {
				if ((env[currentFringe.current_coord->x_coord][yLocation]).space_state == 0) {
					if (options[i] == 1) {
						paths.push_back('D');
					}

					if (options[i] == -1) {
						paths.push_back('U');
					}
				}
			}
		}
	}
	// Return avaliable paths
	return paths;
}

// Move a explored node into a visited list
void moveto_visited(Fringe* currentFringe, vector<Fringe*> &fringes, vector<Fringe*> &visitedNodes) {
	visitedNodes.push_back(currentFringe);

	int fringePos = 0;
	for (unsigned int i = 0; i < fringes.size(); i++) {
		if (currentFringe->current_coord == fringes[i]->current_coord) {
			fringePos = i;
			break;
		}
	}
	fringes.erase(fringes.begin() + fringePos);
}

// Check if a node already exists in the current list
int check_existance(vector<Fringe*> list, Coordinates* position) {
	for (unsigned int i = 0; i < list.size(); i++) {
		if (list[i]->current_coord == position) {
			return i;
		}
	}
	return -1;
}

// Add a visited node to the list
void addto_fringe(Fringe* newFringe, vector<Fringe*> &fringes, int existPos) {
	// Append to an empty vector
	if (fringes.empty()) {
		fringes.push_back(newFringe);
		return;
	}

	// If a better path is found, update the entry state to the newer "best" path
	if (existPos >= 0) {
		if (newFringe->path_cost < fringes[existPos]->path_cost) {
			fringes[existPos]->path_cost = newFringe->path_cost;
			fringes[existPos]->eval_cost = newFringe->eval_cost;
			fringes[existPos]->previous_coord = newFringe->previous_coord;
		}
	// Append to list, sorted based on smallest f(n) (evaluation cost)
	}else {
		int insertSlot = 0;
		for (unsigned int i = 0; i < fringes.size(); i++) {
			insertSlot ++;
			if (newFringe->eval_cost <= fringes[i]->eval_cost) {
				break;
			}
		}
		fringes.insert(fringes.begin() + insertSlot, newFringe);
	}
}

// Generate taken path by backtracking from the end goal
void construct_path(Fringe* endPosition, vector<Fringe*> visitedNodes, int exploredNodes, int iterations, float executionTime) {
	vector<char> path;
	bool generate = true;

	Fringe* target = endPosition;
	while (generate) {
		// End the path construction if the current node points to itself (start position)
		if (target->current_coord->x_coord == target->previous_coord->x_coord &&
			target->current_coord->y_coord == target->previous_coord->y_coord) {
			generate = false;
			continue;
		}

		for (unsigned int i = 0; i < visitedNodes.size(); i++) {
			if (visitedNodes[i]->current_coord == target->previous_coord) {
				// Backtracked x-coordinates are the same,
				// the difference between corresponding y poistions are taken:
				// 	- up (-1:)
				// 	- down (1)
				if (visitedNodes[i]->current_coord->x_coord == target->current_coord->x_coord) {
					int option = target->current_coord->y_coord - visitedNodes[i]->current_coord->y_coord;
					if (option == 1) {
						path.push_back('D');
					}

					if (option == -1) {
						path.push_back('U');
					}
				}

				// Backtracked y-coordinates are the same,
				// the difference between corresponding x poistions are taken:
				// 	- left (-1:)
				// 	- right (1)
				if (visitedNodes[i]->current_coord->y_coord == target->current_coord->y_coord) {
					int option = target->current_coord->x_coord - visitedNodes[i]->current_coord->x_coord;
					if (option == 1) {
						path.push_back('R');
					}

					if (option == -1) {
						path.push_back('L');
					}
				}
				// Update to previous node (backtracking)
				target = visitedNodes[i];
				break;
			}
		}
	}

	// Print resulting information based on A* algorithm 
	cout << "= = = S O L U T I O N = = =" << endl;
	cout << "Execution Time: " << executionTime << " seconds" << endl;
	cout << "Path Iterations: " << iterations << endl;
	cout << "Explored Nodes: " << exploredNodes << endl << endl;
	cout << "Generated Path Size: " << path.size() << endl;
	cout << "Generated Path: ";
	for (int i = (path.size() - 1); i >= 0; i--) {
		cout << path[i];
		(i > 0) ? cout << " " : cout << endl;
	}
	cout << "= = = = = = = = = = = = = =" << endl;
}
