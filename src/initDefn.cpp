#include "../include/initDefn.h"
#include "../include/struct.h"
#include "../include/global.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// Convert a string format into a integer number
int integer_conversion(string numberString) {
	int number;

	istringstream value(numberString);
	value >> number;
	if (value.fail()) {
		cout << "Error: Invalid integer '" << numberString << "'" << endl;
		return -1;
	}
	return number;
}

// Calculate the total x&y distance between the current and goal node
int manhattan_distance_heuristic(int node_xValue, int node_yValue, int end_xValue, int end_yValue) {
	return (abs(node_xValue - end_xValue) + abs(node_yValue - end_yValue));
}

// Initalize and setup map environment from testgrid
int init_env(string file, Coordinates* startPosition, Coordinates* endPosition) {
	string envLine, line;
	int envLineNum = 0;

	// Open file and parse line by line corresponding fields
	ifstream envFile (file.c_str());
	if (envFile.is_open()) {
		while (getline(envFile, envLine)) {
			vector<int> envVariables;
		    size_t preEnvItemPos = 0, envDelimiterPos;

		    // Seperate and store each value of a parsed line by corresponding "tab" 
		    while ((envDelimiterPos = envLine.find_first_of(" \t", preEnvItemPos)) != string::npos) {
		        if (envDelimiterPos > preEnvItemPos) {
		            envVariables.push_back(integer_conversion(envLine.substr(preEnvItemPos, (envDelimiterPos - preEnvItemPos))));
		        }
		        // Next tab
		        preEnvItemPos = (envDelimiterPos + 1);
		    }

		    // Check if a tab occurs at the end of the string
		    if (preEnvItemPos < envLine.length()) {
		        envVariables.push_back(integer_conversion(envLine.substr(preEnvItemPos, string::npos)));
	    	}

	    	// Create inital 2D-Array from correpsonding datagrid dimension
	    	if (envLineNum == 0) {
	    		env_xSize = envVariables[0];
	    		env_ySize = envVariables[1];

	    		env = new Node*[env_xSize];
	    		for (int i = 0; i < env_xSize; i++) {
	    			env[i] = new Node[env_ySize];
	    		}
	    	}

	    	// fill correspodning 2D-Array line by line, with states for each block in datagrid
	    	if (envLineNum > 0) {
	    		for (unsigned int i = 0; i < envVariables.size(); i++) {
	    			Coordinates* nodePlane = new Coordinates;
	    			nodePlane->x_coord = i;
	    			nodePlane->y_coord = (envLineNum - 1);

	    			(env[i][(envLineNum - 1)]).node_coord = nodePlane;
	    			(env[i][(envLineNum - 1)]).space_state = envVariables[i];

	    			// Calculate the x&y distance only if a block is traversable (Not a wall)
	    			int heuristicValue = -1;
	    			if ((env[i][(envLineNum - 1)]).space_state == 0) {
	    				heuristicValue = manhattan_distance_heuristic(i, (envLineNum - 1), endPosition->x_coord, endPosition->y_coord);
	    			}
	    			(env[i][(envLineNum - 1)]).heuristic_cost = heuristicValue;
	    		}
	    	}
	    	// Read next line (If applicable)
	    	envLineNum ++;
		}
		envFile.close();
	} else {
		cout << "Error: File not found / Unable to open file" << endl;
		return -1;
	}

	// Print list of corresponding states 
	// 	- Space state [path or wall]
	// 	- Cost to end goal
	if (details == true) {
		for (int i = 0; i < env_xSize; i++) {
			for (int j = 0; j < env_ySize; j++) {
				cout << (env[i][j]).space_state << ", "<< (env[i][j]).heuristic_cost << endl;
			}
		}	
	}
	return 0;
}

// Assign a new node with corresponding x and y position from testgrid
int init_coordinates(Coordinates** location, int x_value, int y_value) {
	Coordinates* position = new Coordinates;

	position->x_coord = x_value;
	position->y_coord = y_value;

	if (position->x_coord == -1 || position->y_coord == -1) {
		return -1;
	}

	*location = position;
	return 0;
}

// Setup corresponding map from user input [start and end goals] and the environment
int initalize(string envPath, int* startCoordiantes, int* endCoordiantes,
	Coordinates** startPosition, Coordinates** endPosition) {

	// Assign start coordinates
	int start_success = init_coordinates(&(*startPosition), startCoordiantes[0], startCoordiantes[1]);
	// Assign end coordinates
	int end_success = init_coordinates(&(*endPosition), endCoordiantes[0], endCoordiantes[1]);
	// Generate testgrid into a 2D-Array
	int env_success = init_env(envPath, *startPosition, *endPosition);

	if (start_success == -1 || end_success == -1 || env_success == -1) {
		return -1;
	}
	return 0;
}
