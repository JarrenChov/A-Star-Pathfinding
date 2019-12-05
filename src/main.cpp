#include "../include/struct.h"
#include "../include/global.h"
#include "../include/initDefn.h"
#include "../include/pathDefn.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

Node **env = 0;
int env_xSize = 0;
int env_ySize = 0;
bool details = true; 

int main(int argc, char* argv[]) {
	int optionCount = 2;
	int options[2] = {1, -1};

	Coordinates *startPosition, *endPosition;
 
 	// Initalize enviroment map, starting and ending points
 	// Check to ensure input is valid
	int init_success = initalize(argc, argv, &startPosition, &endPosition);
	if (init_success == -1) {
		return -1;
	}

	vector<Fringe*> fringes;
	vector<Fringe*> visitedNodes;
	vector<string> trackedPath; 
	int nodeExpanded = 1;

	// Inital parameters declarations
	bool traverse = true;
	bool startPoint = true;
	bool goalFound = false;
	int iterations = 1;

	// Start execution timer
	float exeTimeStart = clock();

	// Find a path from start to end goal
	while (traverse) {
		if (details == true) {
			cout << "Iteration " << iterations << endl;
			cout << "=======================" << endl;
		}

		if (startPoint == true) {
			// Check if start node is a valid position
			if ((env[startPosition->x_coord][startPosition->y_coord]).space_state == 1) {
				// Calculate execution time (seconds)
				float executionTime = (clock() - exeTimeStart) / CLOCKS_PER_SEC;
				
				cout << "--- No Path Found ---" << endl;
				cout << "Reason: Invalid Starting Point" << endl;

				cout << "Execution Time: " << executionTime << " seconds" << endl;
				cout << "Path Iterations: " << iterations << endl;
				cout << "Explored Nodes: " << nodeExpanded << endl << endl;
				cout << "Generated Path Size: 0" << endl;
				cout << "Generated Path: not found" << endl;
				
				traverse = false;
				continue;
			}

			// Create a new fring for the inital node
			Fringe* newFringe = new Fringe;
			newFringe->path_cost = 0;
			newFringe->eval_cost = calculate_evaluation(newFringe->path_cost, (env[startPosition->x_coord][startPosition->y_coord]).heuristic_cost);
			newFringe->current_coord = startPosition;
			newFringe->previous_coord = startPosition;

			fringes.push_back(newFringe);
			startPoint = false;
		}

		Fringe* currentFringe = new Fringe;
		if (!(fringes.empty())) {
			currentFringe = fringes[0];
		}

		// Check current fringe is the end goal
		if (currentFringe->current_coord->x_coord == endPosition->x_coord &&
			currentFringe->current_coord->y_coord == endPosition->y_coord) {
			// Calculate execution time (seconds)
			float executionTime = (clock() - exeTimeStart) / CLOCKS_PER_SEC;
		
			construct_path(currentFringe, visitedNodes, nodeExpanded, iterations, executionTime);

			goalFound = true;
			traverse = false;
			continue;
		// If a path can not be found to the end goal due to all possible paths being traversed
		}else if (fringes.empty() && goalFound == false) {
			// Calculate execution time (seconds)
			float executionTime = (clock() - exeTimeStart) / CLOCKS_PER_SEC;

			cout << "--- No Path Found ---" << endl;
			if ((env[endPosition->x_coord][endPosition->y_coord]).space_state == 1) {
				cout << "Reason: Invalid Ending Point" << endl;
			}

			cout << "Execution Time: " << executionTime << " seconds" << endl;
			cout << "Path Iterations: " << iterations << endl;
			cout << "Explored Nodes: " << nodeExpanded << endl << endl;
			cout << "Generated Path Size: 0" << endl;
			cout << "Generated Path: not found" << endl;

			traverse = false;
			continue;
		}

		// Update current node as already searched and generate possible paths from current node
		moveto_visited(&(*currentFringe), fringes, visitedNodes);
		vector<char> nodePaths = find_node_paths(*currentFringe, optionCount, options);

		if (details == true) {
			cout << "Branched Nodes from: (" << currentFringe->current_coord->x_coord << ", " << currentFringe->current_coord->y_coord << ")" << endl;
		}

		// Generate a state for each possible path
		for (unsigned int i = 0; i < nodePaths.size(); i++) {
			int xValue = 0;
			int yValue = 0;

			switch(nodePaths[i]) {
				case 'U': 
					yValue = -1;
					break;
				case 'D':
					yValue = 1;
					break;
				case 'L':
					xValue = -1;
					break;
				case 'R':
					xValue = 1;
					break;
			}

			int fringe_exist = check_existance(fringes, (env[currentFringe->current_coord->x_coord + xValue][currentFringe->current_coord->y_coord + yValue]).node_coord);
			int node_explored = check_existance(visitedNodes, (env[currentFringe->current_coord->x_coord + xValue][currentFringe->current_coord->y_coord + yValue]).node_coord);

			// Create fringe of possible path if it has not been looked at already
			if (node_explored == -1) {
				Fringe* newFringe = new Fringe;
				newFringe->path_cost = currentFringe->path_cost + 1;
				newFringe->eval_cost = calculate_evaluation(newFringe->path_cost, (env[currentFringe->current_coord->x_coord + xValue][currentFringe->current_coord->y_coord + yValue]).heuristic_cost);
				newFringe->current_coord = (env[currentFringe->current_coord->x_coord + xValue][currentFringe->current_coord->y_coord + yValue]).node_coord;
				newFringe->previous_coord = currentFringe->current_coord;

				addto_fringe(&(*newFringe), fringes, fringe_exist);
				if (fringe_exist == -1) {
					nodeExpanded ++;

					if (details == true) {
						cout << '\t' << "Path Cost - g(n): " << newFringe->path_cost << endl;
						cout << '\t' << "Eval Cost - f(n) = g(n) + h(n): " << newFringe->eval_cost << endl;
						cout << '\t' << "Current Coord: " << newFringe->current_coord->x_coord << ", " << newFringe->current_coord->y_coord << endl;
						cout << '\t' << "Previous Coord: " << newFringe->previous_coord->x_coord << ", " << newFringe->previous_coord->y_coord << endl;
						cout << endl;
					}
				}else {
					free(newFringe);
				}
			}
		}

		if (details == true) {
			iterations ++;

			cout << "--- Vector Resultants & Summary ---" << endl;
			cout << "Iterative Node Expansion Count: " << nodeExpanded << endl;
			cout << "Iterative Node Explored Count: " << visitedNodes.size() << endl;
			cout << "Fringes: ";
			for (unsigned int i = 0; i < fringes.size(); i++) {
				cout << "(" << fringes[i]->current_coord->x_coord << ", " << fringes[i]->current_coord->y_coord << "), ";
			}
			cout << endl;
			cout <<  "Visited Nodes: ";
			for (unsigned int i = 0; i < visitedNodes.size(); i++) {
				cout << "(" << visitedNodes[i]->current_coord->x_coord << ", " << visitedNodes[i]->current_coord->y_coord << "), ";
			}
			cout << endl;
			cout << "=======================" << endl << endl << endl;
		}
	} 
	return 0;
}
