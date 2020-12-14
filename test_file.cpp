#include <lemon/list_graph.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace lemon;

int main() {
    ListGraph graph;
    vector<ListGraph::Node> vertices;
    ListGraph::Node vertex;
    ListGraph::Edge edge;
    vector<vector<int>> edges;

    ListGraph::NodeMap<int> nodeMap(graph);
    ListGraph::EdgeMap<int> edgeMap(graph);
    for (int i = 0; i < 10; ++i)
    {
        vertex = graph.addNode();
        nodeMap[vertex] = i;
    };

    vector<int> edges_i;
    for (ListGraph::NodeIt it(graph); it != INVALID; ++it)
    {
        ListGraph::NodeIt jt = it;
        ++jt;
        while (jt != INVALID)
        {
            edge = graph.addEdge(it, jt);
            edgeMap[edge] = graph.id(it) + graph.id(jt);
            ++jt;
        };
    };

    //cout << edgeMap[graph.edgeFromId(edges[5][4])] << endl;
    cout << countEdges(graph) << endl;
    cout << edgeMap[findEdge(graph, graph.nodeFromId(4), graph.nodeFromId(9))] << endl;
    return 0;
}