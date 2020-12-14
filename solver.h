#ifndef SOLVER_H
#define SOLVER_H

#include <lemon/list_graph.h>

using namespace lemon;

class Test {
	int c;
public:
	lemon::ListGraph graph;
	lemon::ListGraph::NodeMap<int> nodeMap;
	Test(): nodeMap(graph) {};
};

#endif // !SOLVER_H
