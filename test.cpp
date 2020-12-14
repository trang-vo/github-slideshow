#include <iostream>
#include <lemon/list_graph.h>
using namespace lemon;
using namespace std;

int main()
{
    ListGraph g;
    ListGraph::Node a = g.addNode();
    ListGraph::Node b = g.addNode();
    ListGraph::Node c = g.addNode();
    ListGraph::Edge e = g.addEdge(a, b);
    ListGraph::Edge f = g.addEdge(b, a);
    g.addEdge(b, c);
    g.addEdge(c,a);
    cout << "Hello World! This is LEMON library here." << endl;
    cout << "We have a directed graph with " << countNodes(g) << " nodes "
        << "and " << countEdges(g) << " arc." << endl;

    for (ListGraph::EdgeIt i(g); i!=INVALID; ++i)
        std::cout << " (" << g.id(g.u(i)) << "," << g.id(g.v(i)) << ")";
    return 0;
}