#include "struct.h"
#include <string>

#ifndef _INIT_DEFN_
#define _INIT_DEFN_

int integer_conversion(std::string numberString);
int manhattan_distance_heuristic(int node_xValue, int node_yValue, int end_xValue, int end_yValue);
int init_env(std::string file, Coordinates* startPosition, Coordinates* endPosition);
int init_coordinates(Coordinates** location, int x_value, int y_value);
int initalize(std::string envPath, int* startCoordiantes, int* endCoordiantes, Coordinates** startPosition, Coordinates** endPosition);

#endif // _INIT_DEFN_
