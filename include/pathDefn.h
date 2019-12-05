#include "struct.h"
#include <string>
#include <vector>

#ifndef _PATH_DEFN_
#define _PATH_DEFN_

int calculate_evaluation(int pathCost, int heuristicCost);
std::vector<char> find_node_paths(Fringe currentFringe, int optionCount, int *options);
void moveto_visited(Fringe* currentFringe, std::vector<Fringe*> &fringes, std::vector<Fringe*> &visitedNodes);
int check_existance(std::vector<Fringe*> list, Coordinates* position);
void addto_fringe(Fringe* newFringe, std::vector<Fringe*> &fringes, int existPos);
void construct_path(Fringe* endPosition, std::vector<Fringe*> visitedNodes, int exploredNodes, int iterations, float executionTime);

#endif // _PATH_DEFN_

